#include "framework.h"
#include "stdio.h"
#include "stdlib.h"
#include <vector>
#include <math.h>

int main (void){
    vec2 o;
    vec2 res;
    printf("type the original vec2 in x,y format\n");

    scanf("%f, %f", &o.x, &o.y);

    printf("type the result vec2 in x,y format\n");

    scanf("%f, %f", &res.x, &res.y);

    res = res.invert();

    


}