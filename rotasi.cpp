#include <iostream>
#include <math.h>
#include "Render.h"

#define _USE_MATH_DEFINES

int main(){
    Canvas screen;
    Render R;

    R.loadAsset("heli.txt");
    
    R.heli();
    
    return 0;
}