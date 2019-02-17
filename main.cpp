#include <iostream>
#include "Render.h"

int main(){
    Render R;
    
    R.loadAsset("map.txt");
    
    R.map();

    return 0;
}