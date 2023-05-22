#include "graphical_manager.hpp"
#include "vector.hpp"

// external
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_opengl.h>
#include <SDL_render.h>
#include <GL/glu.h>
#include <SDL_video.h>

// builtin
#include <cstdint>

void check_error()
{
    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
        std::cout << "OpenGL error: " << gluErrorString(error) << std::endl;
        std::exit(1);
    }
}

GraphicalManager::GraphicalManager(const std::string& window_name, const BMuscle::Vector2i32 window_size)
   :window_size{window_size}
{
    this->setup_sdl(window_name);
    this->setup_opengl();
}

void GraphicalManager::setup_sdl(const std::string& window_name)
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "SDL Init error: " << SDL_GetError() << std::endl;
        std::exit(1);
    }
    else
    {
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

        //Create window
        this->window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                      this->window_size.x, this->window_size.y, 
                                      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
        if( this->window == NULL )
        {
            std::cout << "SDL window creation error: " << SDL_GetError() << std::endl;
            std::exit(1);
        }
        else
        {
            //Create context
            this->context = SDL_GL_CreateContext( this->window );
            if( this->context == NULL )
            {
                std::cout << "OpenGL context creation error: " << SDL_GetError() << std::endl;
                std::exit(1);
            }
            else
            {
                if( SDL_GL_SetSwapInterval( 1 ) < 0 )
                {
                    std::cout << "Warning: VSync not working: " << SDL_GetError() << std::endl;
                }
            }
        }
    }
}

void GraphicalManager::setup_opengl()
{
    GLenum error = GL_NO_ERROR;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    check_error();

    glOrtho(0.f, this->window_size.x, 0.f, this->window_size.y, 1.0, -1.0);
    check_error();

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    check_error();

    glClearColor( 0.f, 0.f, 0.f, 1.f );
    check_error();

    glViewport(0, 0, this->window_size.x, this->window_size.y);
    check_error();

}

void GraphicalManager::render(std::vector<BMuscle::Circle>& circles)
{
    glClear( GL_COLOR_BUFFER_BIT );
    
    for(const auto& circle : circles)
    {
        this->draw_circle(circle.center, circle.radius);
    }

    SDL_GL_SwapWindow( this->window);
}

void GraphicalManager::draw_circle(const BMuscle::Vector2d center, const double radius)
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

        glColor3f( 1.f, 0.f, 0.f );
        glBegin( GL_POINTS);
            glVertex2f(x,y);
        glEnd();
    }
   }
}

GraphicalManager::~GraphicalManager()
{
	SDL_DestroyWindow( this->window);
	SDL_Quit();
}
