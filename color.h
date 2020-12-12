#pragma once

typedef struct color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char alpha;
} Color;

Color make_darker(Color color, float percent);
Color make_lighter(Color color, float percent);
Color multiply_by_scalar(Color color, float mult);
