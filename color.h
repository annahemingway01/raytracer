#pragma once

typedef struct color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char alpha;
} Color;

Color make_darker(Color color, float percent);
Color make_lighter(Color color, float percent);
Color multiply_color_by_scalar(Color color, float mult);
