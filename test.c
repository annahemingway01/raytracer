#include<SDL2/SDL.h>
#include<stdio.h>
#include "shapes.h"
#include "view.h"
#include "color.h"



int main(int argc, char *argv[])
{

    Light light;
    Vector light_location = {0,1000,0};
    Color light_color = {127, 127, 127, 255};
    light.location = light_location;
    light.color = light_color;
    light.intensity = 1;
    //make 2 circles in the scene
    Color red = {255, 0, 0, 255};
    //Color blue = {0, 0, 255, 255};
    Vector circ_1_loc = {1000,0, 0};
    //Vector circ_2_loc = {200, 100, 0};
    Data data;
    data.sphere.radius = 300;
    Solid circle_1 = {SPHERE, red, 0.5, circ_1_loc, data};
    //Solid circle_2 = {SPHERE, blue, default_diffusion, circ_2_loc, data};
    //Solid solids[2] = {circle_1, circle_2};

    
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("test window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH,HEIGHT,0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    Ray camera_ray = {camera, screen_center};
    for (float i = screen_center.z - (WIDTH / 2); i < screen_center.z + (WIDTH / 2); i++) {
        for (float j = screen_center.y - (HEIGHT / 2); j < screen_center.y + (HEIGHT / 2); j++) {
            //This will not work for long as soon as I implement moving the camera! the camera
            //must be perpendicular to the viewport. Hence this is rather bad.
            camera_ray.direction.x = screen_center.x;
            camera_ray.direction.y = j;
            camera_ray.direction.z = i;
            //this is gonna need to be part of a loop to keep track of closest object
            Vector location = {0,0,0};
            if (ray_hit(&camera_ray, &circle_1, &location)) {
                Color color = multiply_by_scalar(circle_1.color, diffuse_brightness(circle_1, location, light));
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, circle_1.color.alpha);
                SDL_RenderDrawPoint(renderer, i + (WIDTH / 2), j + (HEIGHT / 2));
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
