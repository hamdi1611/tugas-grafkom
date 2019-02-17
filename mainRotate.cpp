#include <iostream>
#include "Render.h"

int main(){
    Render R;
    
    R.loadAsset("peluru.txt");
    R.doRotate();

    return 0;
}