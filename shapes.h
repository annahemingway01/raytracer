#pragma once
#include<stdbool.h>
#include "vector.h"
typedef enum type {
    SPHERE,
 //   CUBE,
    PLANE
} Type;

typedef struct color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char alpha;
} Color;


typedef struct sphere {
    float radius;
} Sphere;

/*
typedef struct cube {
    unsigned short length;
} Cube;
*/

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
    Vector location;
    Data data;
    //add reflectivity and such later on
} Solid;


bool ray_hit(Ray *ray, Solid *solid, Vector *location);
