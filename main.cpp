#include "screen.h"
#include <SDL.h>
#include <cmath>
#include <iostream>
#include <fstream>
#define PI 3.14159265358979323846264338327950288
using namespace std;

struct vec3
{
    long double x,y,z;
};
void rotate(vec3& point, long double x = 1, long double y = 1, long double z = 1)
{
    long double rad;

    rad = x;
    point.y = cos(rad)*point.y - sin(rad)*point.z;
    point.z = sin(rad)*point.y + cos(rad)*point.z;

    rad = y;
    point.x = cos(rad)*point.x + sin(rad)*point.z;
    point.z = -sin(rad)*point.x + cos(rad)*point.z;

    rad = z;
    point.x = cos(rad)*point.x - sin(rad)*point.y;
    point.y = sin(rad)*point.x + cos(rad)*point.y;
}
int main(int arg, char** args)
{
    Screen screen;
    ofstream outfile;
    vector<vec3> points;
    bool shift = 0;
    long double dx=0, dy=0;
    SDL_Event event;
    // coordinates of waves with default values
    int t = 700, u = 50, v = 300, w = 500;
    int amp1 = 7, amp2 = 7;
    double r = 0;

    cout << "ArrowKeys: Move A Wave" << endl;
    cout << "R: Switch The Wave To Control" << endl;
    cout << "MouseLeftHold: Observation Mode" << endl;
    cout << "MouseScroll: Change Amplitude" << endl;

    // centroid of the graph(approximate)
    vec3 c{450,250,0};

    while(true){
    // generate graph
    points = {};
    for(int i = 100; i < 800; i+=4)
    {
        for (int j = -100; j < 600; j+=4)
        {
            points.push_back({i,j,amp1*cos(sqrt((i-t)*(i-t)+(j-u)*(j-u))/10 + r) + amp2*cos(sqrt((i-v)*(i-v)+(j-w)*(j-w))/10 + r)});
        }
    }
    r += 0.3;
    for(auto& p : points)
    {
        p.x -= c.x;
        p.y -= c.y;
        p.z -= c.z;
        rotate(p, PI/4, -PI/4, 0.5);
        p.x += c.x;
        p.y += c.y;
        p.z += c.z;
    }
    // key inputs
        while (SDL_PollEvent(&event))
        {
            screen.input();
            // observation mode
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                dx = event.motion.xrel;
                dy = event.motion.yrel;
                for(auto& p : points)
                {
                    p.x -= c.x;
                    p.y -= c.y;
                    p.z -= c.z;
                    rotate(p, dy/100, dx/100, 0);
                    p.x += c.x;
                    p.y += c.y;
                    p.z += c.z;
                }
                for(auto& p : points)
                {
                    screen.pixel(p.x, p.y);
                }
                screen.show();
                screen.clear_screen();
                screen.input();
                SDL_Delay(30);
            }
            // switch wave
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
                shift = shift?0:1;
            // change coordinate
            if (event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_UP)
                {u -= shift?0:10;
                w -= shift?10:0;}
                if (event.key.keysym.sym == SDLK_DOWN)
                {u += shift?0:10;
                w += shift?10:0;}
                if (event.key.keysym.sym == SDLK_RIGHT)
                {t += shift?0:10;
                v += shift?10:0;}
                if (event.key.keysym.sym == SDLK_LEFT)
                {t -= shift?0:10;
                v -= shift?10:0;}
            }
            // change amplitude
            if(event.type == SDL_MOUSEWHEEL)
            {
                // scroll up
                if(event.wheel.y > 0)
                {amp1 += shift?0:1;
                amp2 += shift?1:0;}
                // scroll down
                else if(event.wheel.y < 0)
                {amp1 -= shift?0:1;
                amp2 -= shift?1:0;}
            }
            // output the graph to csv file
            if(event.button.button == SDL_BUTTON_MIDDLE)
            {
                outfile.open("wave.csv");
                outfile << "x,y,z" << endl;
                for(int i = 100; i < 800; i+=4)
                {
                    for (int j = -100; j < 600; j+=4)
                    {
                        outfile << i-100 << "," << j+100 << "," << amp1*cos(sqrt((i-t)*(i-t)+(j-u)*(j-u))/10 + r) + amp2*cos(sqrt((i-v)*(i-v)+(j-w)*(j-w))/10 + r) << endl;
                    }
                }
                outfile.close();
            }
        }
    // show graph
    for(auto& p : points)
    {
        screen.pixel(p.x, p.y);
    }
    screen.show();
    screen.clear_screen();
    // detect window event
    screen.input();
    SDL_Delay(30);
    }
    return 0;
}
