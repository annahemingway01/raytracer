#pragma once
#include "vector.h"

#define WIDTH (1000)
#define HEIGHT (750)

/*
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
*/

void move_camera(float yaw, float pitch, float x, float y, float z);
//yaw, pitch will affect "normal"
//x y z will affect the x y z position of the camera (and thus of the screen center)
