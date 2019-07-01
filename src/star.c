#include "star.h"

void generate_sky_random(struct star stars[], size_t N, size_t max_x, size_t max_y){
    srand(time(NULL));
    size_t rand_num = 2;       // need for center of coordinate

    for(size_t i = 0; i < N; i++){
        stars[i].is_center = false;
        if(stars[i].location.x < max_x && stars[i].location.y < max_y){
            stars[i].location.x = rand() % max_x;
            stars[i].location.y = rand() % max_y;

            if(i == rand_num){
                stars[i].is_center = true;
            }
        }
    }
    for(size_t i = 0; i < N; i++){
        for(size_t j = i + 1; j < N; j++){
            if(stars[i].location.x == stars[j].location.x && stars[i].location.y == stars[j].location.y){
                stars[j].location.x = rand() % max_x;
                stars[j].location.y = rand() % max_y;
                i = 0;
                j = 0;
            }
        }
    }
}
