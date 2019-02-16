/*  Point.cpp  */

#include <cmath>
#include "Point.h"

/** Operator Empat Sekawan **/
Point::Point() {
/* Default Constructor */
    this->x = 0;
    this->y = 0;
}

Point::Point(unsigned int x, unsigned int y) {
/* Parameterized Constructor */
    this->x = x;
    this->y = y;
}
    
Point::Point(const Point &P) {
/* Copy Constructor */
    this->x = P.getAbsis();
    this->y = P.getOrdinat();
}


/**& getter and Setter **/
int Point::getAbsis() const {
    return this->x;
}

int Point::getOrdinat() const {
    return this->y;
}

void Point::setAbsis(unsigned int x) {
    this->x = x;
}

void Point::setOrdinat(unsigned int y) {
    this->y = y;
}

/** Function and Procedure **/
void Point::addAbsis(unsigned int x) {
    this->x += x;
}

void Point::addOrdinat(unsigned int y) {
    this->y += y;
}

void Point::rotatePoint(Point P, float degree){
    float s = sin(degree / 180 * M_PI);
    float c = cos(degree / 180 * M_PI);

    // translate point back to origin:
    this->x -= P.x;
    this->y -= P.y;

    // rotate point
    int xnew = (int)round(this->x * c - this->y * s);
    int ynew = (int)round(this->x * s + this->y * c);

    // translate point back:
    this->x = xnew + P.x;
    this->y = ynew + P.y;
}

/** Operator Overloading **/
bool Point::operator== (const Point &P) const {
    return ((this->x == P.getAbsis()) and (this->y == P.getOrdinat()));
}

bool Point::operator!= (const Point &P) const {
    return ((this->x != P.getAbsis()) or (this->y != P.getOrdinat()));
}