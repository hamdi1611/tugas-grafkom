#include <iostream>
#include <math.h>
#include "Render.h"

#define _USE_MATH_DEFINES

int main(){
    Canvas screen;
    Render R;
    float PI = 3.14159265359;

    // Point rotasiPoint(Point PC, Point P1, int derajat){
    //     P1.x = (P1.x - PC.x) * cos(derajat * M_PI / 180) - (P1.y - PC.y) * sin(derajat * M_PI/ 180) + PC.x;
    //     P1.y = (P1.x - PC.x) * sin(derajat * M_PI / 180) + (P1.y - PC.y)* cos(derajat * M_PI/ 180) + PC.y;
        
    //     return(P1);
    // }

    Color C = Color(0, 2555, 255, 255);

    Point P1 = Point(300,300);
    Point P2 = Point(400,400);
    Point P3 = Point(500,500);
    float derajat = 180.0;

    Line L = Line(P1, P2);
    std::cout << P1.getAbsis() << ' ' << P1.getOrdinat() << "||";
//     std::cout << P2.getAbsis() << ' ' << P2.getOrdinat() << "||";

//  float a = (P1.getAbsis() - P2.getAbsis()) * cos(derajat/180 * M_PI);
//     float b = (P1.getOrdinat() - P2.getOrdinat()) * sin(derajat/180 * M_PI);
//     float c = (P1.getAbsis() - P2.getAbsis()) * sin(derajat/180 * M_PI);
//     float d = (P1.getOrdinat() - P2.getOrdinat()) * cos(derajat/180 * M_PI);

//     std::cout << "@@" << cos(derajat/180 * M_PI) << "@@";
//     std::cout << "qq" << P1.getAbsis() << "qq";
//     std::cout << "qq" << P2.getAbsis() << "qq";
//     std::cout << "@@" << (int) P1.getAbsis() - (int) P2.getAbsis() << "@@";

//     std::cout << "         " << a << "||" << b << "||";
//     std::cout << "         " << c << "||" << d << "||";

//     int x = floor(a - b + P2.getAbsis());
//     int y = floor(c + d + P2.getOrdinat());
    // P1.setAbsis(x);
    // P1.setOrdinat(y);

    // P1.rotatePoint(P2,derajat);
    Line l1 = Line(P1, P2);
    R.drawLine(l1, C);
    // std::cout << P1.getAbsis() << ' ' << P1.getOrdinat() << "||";
    l1.rotateLine(P3, derajat);

    Color D = Color(0, 255, 0, 255);
    R.drawLine(l1, D);
    std::cout << l1.getP1().getAbsis() << ' ' << l1.getP1().getOrdinat() << "||";
    std::cout << l1.getP2().getAbsis() << ' ' << l1.getP2().getOrdinat() << "||";
    while(R.getTerminal().getIsInput() != (int)State::STOP);

    return 0;
}