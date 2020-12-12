#pragma once
#include<stdbool.h>
#include "color.h"
#include "lighting.h"
#include "vector.h"
typedef enum type {
    SPHERE,
 //   CUBE,
    PLANE
} Type;



typedef struct sphere {
    float radius;
} Sphere;

/*
typedef struct cube {
    unsigned short length;
} Cube;
*/

typedef struct diffusion {
    float r;
    float g;
    float b;
} Diffusion;

typedef struct plane {
    //vec representing normal
    Vector normal;
    //vec representing point
    Vector point;
} Plane;


typedef union data {
    Sphere sphere;
    //Cube cube;
    Plane plane;
} Data;


typedef struct solid {
    Type type;
    Color color;
    float diffusion_coefficient;
    Vector location;
    Data data;
    //add reflectivity and such later on
} Solid;



bool ray_hit(Ray *ray, Solid *solid, Vector *location);

Vector get_normal_at(Solid solid, Vector point);

float diffuse_brightness(Solid solid, Vector point, Light light);
