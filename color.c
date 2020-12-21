#include "color.h"
#define CLAMP(low, high, x) ( ((x) < (low)) ? (low) : (((x) > (high)) ? (high) : (x)))

Color make_darker(Color color, float percent) {
    Color diff = {percent * (255 - color.r), percent * (255 - color.g), percent *(255 - color.b), 255 - color.alpha};
    Color ret = {color.r - diff.r, color.g - diff.g, color.b - diff.b, color.alpha};
    return ret;
}

Color make_lighter(Color color, float percent) {
    Color diff = {percent * (255 - color.r), percent * (255 - color.g), percent *(255 - color.b), 255 - color.alpha};
    Color ret = {color.r + diff.r, color.g + diff.g, color.b + diff.b, color.alpha};
    return ret;
}

Color multiply_color_by_scalar(Color color, float mult) {
    Color ret;
    ret.r = CLAMP(0,255,color.r * mult);
    ret.g = CLAMP(0,255,color.g * mult);
    ret.b = CLAMP(0,255,color.b * mult);
    ret.alpha = 255;
    return ret;
}
