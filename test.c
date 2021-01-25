#include<SDL2/SDL.h>
#include<stdio.h>
#include <float.h>
#include "shapes.h"
#include "view.h"
#include "color.h"
#define NUM_SHAPES (3)



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
    Color blue = {0, 0, 255, 255};
    Color lavender = {218, 179, 255, 255};
    Vector circ_1_loc = {800,0, -100};
    Vector circ_2_loc = {700, 0, 700};
    Data data;
    data.sphere.radius = 300;
    //make a plane in the scene
    Vector norm = {0, 1, 0};
    Vector point = {0, -500, 0};
    Data plane_data;
    plane_data.plane.normal = norm;
    plane_data.plane.point = point;
    Solid plane = {PLANE, lavender, 0.9, 0.2, point, plane_data};
    Solid circle_1 = {SPHERE, red, 0.5, 0.5, circ_1_loc, data};
    Solid circle_2 = {SPHERE, blue, 0.8, 0.5, circ_2_loc, data};
    Solid solids[NUM_SHAPES] = {plane, circle_1, circle_2};

Vector screen_center = {50, 0, 0};
Vector screen_top_left = {50, HEIGHT / 2, (-1) * WIDTH / 2};
Vector screen_bottom_right = {50, (-1) * HEIGHT / 2, WIDTH / 2};
float camera_distance_from_screen = 50;

Vector screen_normal = {50, 0, 0};//should always be scaled by camera distance
//screen in the y-z plane
Vector down = {0,-1,0};
//in the "height" direction
Vector right = {0, 0, 1};
//in the width direction


Vector camera = {0,0,0};//screen_center - screen_normal

    
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("test window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH,HEIGHT,0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    /*
     *viewport is in the y-z plane at an x distance of 50 from the camera.
     */
    Ray camera_ray = {camera, screen_center};
    Vector curr_pos = screen_top_left;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            float closest_hit = FLT_MAX;
            camera_ray.direction = curr_pos;
            for (int k = 0; k < NUM_SHAPES; k++) {
                Vector location = {0,0,0};
                float dist = ray_hit(&camera_ray, &solids[k], &location);
                if (dist > 0 && dist < closest_hit) {
                    //this is the closest object in the screen, so color it whatever color it should be.
                    closest_hit = dist;
                    //account for diffuse brightness
                    Color color = multiply_color_by_scalar(solids[k].color,
                            diffuse_brightness(solids[k], location, light));
                    //specular brightness
                    color = multiply_color_by_scalar(solids[k].color, 
                            specular_brightness(solids[k], location, light));
                    //shadow
                    if (is_shadow(light, solids, NUM_SHAPES, location)) {
                        color.r = 0; color.g = 0; color.b = 0;
                    }
                    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, solids[k].color.alpha);
                    SDL_RenderDrawPoint(renderer, j, i);
                }
            }
            curr_pos = add(curr_pos, right);
        }
        curr_pos = subtract(curr_pos, multiply_vector_by_scalar(right, WIDTH));//reset it back to the left
        curr_pos = add(curr_pos, down);
    }
    SDL_Event e;
    SDL_RenderPresent(renderer);
    while(SDL_PollEvent(&e) == 0 || e.type != SDL_QUIT) {
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();


    return 0;
}
