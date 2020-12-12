#pragma once

#include "vector.h"
#include "color.h"


typedef struct light {
    Vector location;
    Color color;
    float intensity;
} Light;
