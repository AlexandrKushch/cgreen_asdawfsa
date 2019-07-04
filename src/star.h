#pragma once

#include "rotate.h"
#include <time.h>

/**
 * <b> Contains struct cartesian polar coordinate: </b>
 * <ul>
 * <li> x - abscissa axis </li>
 * <li> y - ordinate axis </li>
 * </ul>
 * <br> <b> And variable which tell what that center of coordinate </b> </br>
*/
struct star{
    /// Cartesian polar coordinate which contains X and Y coordiante
    struct point_cartesian location;
    /// Variable which tell what that center of coordinate
    bool is_center;
};

/**
 * <b> Function generate sky with stars using random </b>
 * <br> Using random, create center of coordinate </br>
 * <br> Create loop: which fill coordinate X and Y using random </br>
 * <br> Create new loop in loop: which check that the coordinates are not repeated </br>
 * @param array stars - struct star
 * @param N - count of stars
 * @param max_x - range for coordinate X
 * @param max-y - range for coordinate Y
*/
void generate_sky_random(struct star stars[], size_t N, size_t max_x, size_t max_y);

/**
 * <b> Function get center of sky </b>
 * <br> Make new struct which we will return with X = -1 and Y = -1, this value not in range [0..max_x), so we can use this value for compare </br>
 * <br> Make loop: which go walks through the array and find the center </br>
 * <br> If center not finded, then return X = 0 and Y = 0 </br>
 * @param array stars - struct star
 * @param size - size of array stars
 * @return center
*/
struct point_cartesian get_sky_center(struct star stars[], size_t size);
