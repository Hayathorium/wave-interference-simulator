#include <SDL.h>
#include <vector>
using namespace std;
struct vec2
{
    long double x,y;
};

class Screen
{
    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    vector<vec2> points;

    public:

    Screen()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(900, 500, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, 1, 1);
    }

    void pixel(long double x, long double y)
    {
        points.push_back({x,y});
    }

    void show()
    {
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        for(auto& point : points)
        {
            SDL_RenderDrawPointF(renderer, point.x, point.y);
        }

        SDL_RenderPresent(renderer);
    }

    void clear_screen()
    {
        points.clear();
    }

    void input()
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                SDL_Quit();
                exit(0);
            }
        }
    }
};
