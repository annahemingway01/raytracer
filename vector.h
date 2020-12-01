#pragma once
typedef struct vector {
    float x;
    float y;
    float z;
} Vector;

typedef struct ray {
    Vector origin;
    Vector direction;
} Ray;//for camera ray, origin is 0, direction is pixel it goes thru



//void rays_collide(Ray *ray1, Ray *ray2, Vector *location);
