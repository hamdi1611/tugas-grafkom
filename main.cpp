#include <iostream>
#include "Render.h"

int main(){
    Canvas screen;
    Render R;
    
    R.loadAsset("peluru.txt");
    
    R.map();

    return 0;
}