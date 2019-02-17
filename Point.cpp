/*  Point.cpp  */

#include <math.h>
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
unsigned int Point::getAbsis() const {
    return this->x;
}

unsigned int Point::getOrdinat() const {
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
    int a = round(((int) this->getAbsis() - (int) P.getAbsis()) * cos(degree/180 * M_PI));
    int b = round(((int) this -> getOrdinat() - (int) P.getOrdinat()) * sin(degree/180 * M_PI));
    int c = round(((int) this->getAbsis() - (int) P.getAbsis()) * sin(degree/180 * M_PI));
    int d = round(((int) this->getOrdinat() - (int) P.getOrdinat()) * cos(degree/180 * M_PI));

    int x = floor(a - b + (int)P.getAbsis());
    int y = floor(c + d + (int)P.getOrdinat());

    this -> setAbsis(x);
    this -> setOrdinat(y);
}

/** Operator Overloading **/
bool Point::operator== (const Point &P) const {
    return ((this->x == P.getAbsis()) and (this->y == P.getOrdinat()));
}

bool Point::operator!= (const Point &P) const {
    return ((this->x != P.getAbsis()) or (this->y != P.getOrdinat()));
}