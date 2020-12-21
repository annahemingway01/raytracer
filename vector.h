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

Vector normalize(Vector in);

float magnitude(Vector vec);

float dot(Vector vec1, Vector vec2);

float cos_angle_between(Vector vec1, Vector vec2);

Vector subtract(Vector vec1, Vector vec2);

Vector multiply_vector_by_scalar(Vector vec, float scalar);

Vector add(Vector vec1, Vector vec2);

int vector_equal(Vector vec1, Vector vec2);
