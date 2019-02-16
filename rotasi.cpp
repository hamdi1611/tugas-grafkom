#include <iostream>
#include <cmath>

int main(){
    float degree = 10;
    float s = sin(degree / 180 * M_PI);
    float c = cos(degree / 180 * M_PI);
    int x = 0, y = 0, x0 = 960, y0 = 540;
    // translate point back to origin:
    x -= x0;
    y -= y0;

    // rotate point
    int xnew = (int)round(x * c - y * s);
    int ynew = (int)round(x * s + y * c);

    // translate point back:
    x = xnew + x0;
    y = ynew + y0;
    std::cout << x << ", " << y << std::endl;
    return 0;
}