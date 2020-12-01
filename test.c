#include<SDL2/SDL.h>
#include<stdio.h>
#include "shapes.h"
#include "viewport.h"



int main(int argc, char *argv[])
{

    //make 2 circles in the scene
    Color red = {255, 0, 0, 255};
    Vector circ_1_loc = {150,0,0};
    Data data;
    data.sphere.radius = 75;
    Solid circle_1 = {SPHERE, red, circ_1_loc, data};

    
    //SDL_Rect *rect;
    /*
    rect->x = 0;
    rect->y = 0;
    rect->w = 50;
    rect->h = 50;
    */
    /*
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("P sick", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500,250,0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    SDL_RenderFillRect(renderer, &rect);
    */
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("test window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH,HEIGHT,0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    Ray camera_ray = {camera, center};
    for (float i = center.z - (WIDTH / 2); i < center.z + (WIDTH / 2); i++) {
        for (float j = center.y - (HEIGHT / 2); j < center.y + (WIDTH / 2); j++) {
            //This will not work for long as soon as I implement moving the camera! the camera
            //must be perpendicular to the viewport. Hence this is rather bad.
            camera_ray.direction.x = center.x;
            camera_ray.direction.y = j;
            camera_ray.direction.z = i;
            Vector location = {0,0,0};
            if (ray_hit(&camera_ray, &circle_1, &location)) {
                printf("ray hit!\n");
                SDL_SetRenderDrawColor(renderer, circle_1.color.r, circle_1.color.g, circle_1.color.b, circle_1.color.alpha);
                SDL_RenderDrawPoint(renderer, i + (WIDTH / 2), j + (WIDTH / 2));
            }
        }
    }

    while(1) {
        SDL_RenderPresent(renderer);
        SDL_Delay(5000);
            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(renderer);
            SDL_Quit();
    }



    return 0;
}
