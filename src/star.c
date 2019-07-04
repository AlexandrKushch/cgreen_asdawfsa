/**
 * @file star.c
 * <b> Implemantation of function for Task02/day05 </b>
 * 
 * @author Kushch A.E.
*/
#include "star.h"

void generate_sky_random(struct star stars[], size_t N, size_t max_x, size_t max_y){
    srand(time(NULL));
    int center = rand() % N;

    for(int i = 0; i < N; i++){
        stars[i].is_center = false;
        stars[i].location.x = rand() % max_x;
        stars[i].location.y = rand() % max_y;
        
        if(i == center){
            stars[i].is_center = true;
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = i + 1; j < N; j++){
            if(stars[i].location.x == stars[j].location.x && stars[i].location.y == stars[j].location.y){
                stars[i].location.x = rand() % max_x;
                stars[i].location.y = rand() % max_y;
                i = 0;
                j = 0;
            }
        }
    }
}

struct point_cartesian get_sky_center(struct star stars[], size_t size){
    struct point_cartesian center = {-1, -1};   // -1 - not in range [0..max_x), so we can use this value for compare
    for(size_t i = 0; i < size; i++){
        if(stars[i].is_center){
            center =  stars[i].location;        // The last star with 'center = true' will be returned
        }
    }
    if(center.x == -1 && center.y == -1){   // If no center is found in the array
        center.x = 0;
        center.y = 0;
    }

    return center;
}
