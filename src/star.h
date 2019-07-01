#pragma once

#include "rotate.h"
#include <time.h>

struct star{
    struct point_cartesian location;
    bool is_center;
};

void generate_sky_random(struct star stars[], size_t N, size_t max_x, size_t max_y);
