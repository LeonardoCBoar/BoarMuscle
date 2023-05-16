
// builtin
#include <assert.h>

// local
#include "vector.hpp"

// forward declaration
struct SDL_Window;
struct SDL_Renderer;


class SDLManager
{
private:
    SDL_Window* window;

public:
    SDL_Renderer* renderer;
    BMuscle::Vector2i32 window_size;

public:
    SDLManager(const std::string window_name, const BMuscle::Vector2i32 window_size);
    ~SDLManager();

    void draw_circle(SDL_Renderer* renderer,const BMuscle::Vector2d center, const double radius);
};