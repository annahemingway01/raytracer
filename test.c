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
    /*
    for (float i = screen_center.z - (WIDTH / 2); i < screen_center.z + (WIDTH / 2); i++) {
        for (float j = screen_center.y - (HEIGHT / 2); j < screen_center.y + (HEIGHT / 2); j++) {
    for (float i = screen_top_left.z; i < screen_top_left.z + WIDTH; i++) {
        for (float j = screen_top_left.y; j > screen_top_left.y - HEIGHT; j--) {
            //This will not work for long as soon as I implement moving the camera! the camera
            //must be perpendicular to the viewport. Hence this is rather bad.
            camera_ray.direction.x = screen_top_left.x;
            camera_ray.direction.y = j;
            camera_ray.direction.z = i;
            */
            //this is gonna need to be part of a loop to keep track of closest object
    Vector curr_pos = screen_top_left;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            camera_ray.direction = curr_pos;
            Vector location = {0,0,0};
            if (ray_hit(&camera_ray, &circle_1, &location)) {
                Color color = multiply_color_by_scalar(circle_1.color, diffuse_brightness(circle_1, location, light));
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, circle_1.color.alpha);
                SDL_RenderDrawPoint(renderer, j, i);
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
