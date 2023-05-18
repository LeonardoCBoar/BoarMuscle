
// builtin
#include <assert.h>
#include <vector>

// extern
#include "SDL_video.h"

// local
#include "vector.hpp"
#include "geometry.hpp"


// forward declaration
struct SDL_Window;
struct SDL_Renderer;


class GraphicalManager
{
private:
    SDL_Window* window;
    SDL_GLContext context;
public:
    BMuscle::Vector2i32 window_size;

public:
    GraphicalManager(const std::string& window_name, const BMuscle::Vector2i32 window_size);
    ~GraphicalManager();

    void setup_sdl(const std::string& window_name);
    void setup_opengl();

    void render(std::vector<BMuscle::Circle>& circles);

    void draw_circle(const BMuscle::Vector2d center, const double radius);
};