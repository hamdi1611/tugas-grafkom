#include <iostream>
#include <cmath>
#include "Render.h"

int main(){
    Canvas screen;
    Render R;

    R.loadAsset("heli.txt");
    
    R.heli();
 
    return 0;
}