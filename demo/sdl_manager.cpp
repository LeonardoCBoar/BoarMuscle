#include "sdl_manager.hpp"
#include "vector.hpp"

// external
#include <SDL.h>
#include <SDL_render.h>

// builtin
#include <cstdint>

SDLManager::SDLManager(const std::string window_name, const BMuscle::Vector2i32 window_size)
   :window_size{window_size}
{
    auto const sdl_init_status = SDL_Init(SDL_INIT_VIDEO);
    std::cout << SDL_GetError() << std::endl;
    assert(sdl_init_status == 0);
    std::cout << SDL_GetError() << std::endl;

    uint32_t const WINDOW_FLAGS = SDL_WINDOW_SHOWN;
    this->window = SDL_CreateWindow("BoarMuscle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    this->window_size.x, this->window_size.y, WINDOW_FLAGS);
    assert(this->window != NULL);

    uint32_t const RENDERER_FLAGS = 0;
    this->renderer = SDL_CreateRenderer(window, -1, RENDERER_FLAGS);
    assert(this->renderer != NULL);
}

SDLManager::~SDLManager()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLManager::draw_circle(SDL_Renderer* renderer,const BMuscle::Vector2d center, const double radius)
{
   int count = 0;
   const BMuscle::Vector2i32 lower_bound
   {
      std::max(0,static_cast<int32_t>(center.x - radius)), 
      std::max(0,static_cast<int32_t>(center.y - radius))
   };
   const BMuscle::Vector2i32 upper_bound
   {
      std::min(this->window_size.x, static_cast<int32_t>(center.x + radius)), 
      std::min(this->window_size.y, static_cast<int32_t>(center.y + radius))
   };
   
   for(int32_t x = lower_bound.x; x < upper_bound.x; x++)
   {
      for(int32_t y = lower_bound.y; y < upper_bound.y; y++)
      {
         const BMuscle::Vector2i32 point{x,y};
         if(!point.inside_rect({0,0}, this->window_size)) continue;
         if(point.distance_to(center) >= radius) continue;

         SDL_RenderDrawPoint(renderer, x, y);
      }
   }
}
