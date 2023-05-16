
// builtin
#include <SDL_error.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <cstddef>
#include <ostream>
#include <vector>
#include <assert.h>
   
// extern
#include <SDL.h>

// local
#include "collisions.hpp"
#include "geometry.hpp"
#include "vector.hpp"
#include "sdl_manager.hpp"


const double MOVE_SPEED = 4;

void add_circle(std::vector<BMuscle::Circle>& circle_vector, const BMuscle::Vector2d center, const double radius)
{
    circle_vector.emplace_back(center, radius);
}

void move_circle(std::vector<BMuscle::Circle>& circles, size_t index, BMuscle::Vector2d movement)
{
    circles[index].center.x += movement.x;
    circles[index].center.y += movement.y;

    for(size_t i = 0; i < circles.size(); i++)
    {
        if(i == index) continue;

        auto collision = BMuscle::Collisions::collides(circles[index],circles[i]);
        if(collision)
        {   
            const BMuscle::Vector2d response = collision.value().direction * collision.value().depth;
            move_circle(circles, i, response);
        }
    }
}


int main()
{
    std::vector<BMuscle::Circle> circles{};
    add_circle(circles, {100,100}, 30);
    add_circle(circles, {500,500}, 50);
    add_circle(circles, {303,700}, 10);
    add_circle(circles, {403,550}, 10);
    add_circle(circles, {200,600}, 70);
    BMuscle::Circle& player = circles[2];



    SDLManager sdl_manager("Circle Collisions", {1280,720});
    SDL_Renderer* renderer = sdl_manager.renderer;
    
    SDL_Event event;
    bool shall_quit = false;
    while(!shall_quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                shall_quit = true;
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        shall_quit = true;
                        break;

                    case SDLK_w:
                        move_circle(circles, 2, {0,-MOVE_SPEED});
                        break;
                    case SDLK_s:
                        move_circle(circles, 2, {0,MOVE_SPEED});
                        break;
                    case SDLK_a:
                        move_circle(circles, 2, {-MOVE_SPEED, 0});
                        break;
                    case SDLK_d:
                        move_circle(circles, 2, {MOVE_SPEED,0});
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
        SDL_RenderClear(renderer);
        for(const auto circle : circles)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            sdl_manager.draw_circle(renderer, circle.center, circle.radius);
        }
        SDL_RenderPresent(renderer);

    }



}



