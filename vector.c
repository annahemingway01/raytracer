#include<math.h>
#include "vector.h"

Vector normalize(Vector in) {
    float length = magnitude(in);
    Vector ret = {in.x / length, in.y / length, in.z / length};
    return ret;
}

float magnitude(Vector vec) {
    return sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

float dot(Vector vec1, Vector vec2) {
    return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
}

float cos_angle_between(Vector vec1, Vector vec2) {
    return dot(vec1, vec2) / (magnitude(vec1) * magnitude(vec2));
}

Vector subtract(Vector vec1, Vector vec2) {
    Vector ret;
    ret.x = vec1.x - vec2.x;
    ret.y = vec1.y - vec2.y;
    ret.z = vec1.z - vec2.z;
    return ret;
}

