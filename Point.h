/*  Point.h  */

#ifndef _POINT_H_
#define _POINT_H_

class Point {
    private:
        int x;  // Absis
        int y;  // Ordinat

    public:
        /* Operator Empat Sekawan */
        Point();
        Point(unsigned int x, unsigned int y);
        Point(const Point &P);

        /*& getter and Setter */
        int getAbsis() const;
        int getOrdinat() const;
        
        void setAbsis(unsigned int x);
        void setOrdinat(unsigned int y);
        
        /* Function and Procedure */
        void addAbsis(unsigned int x);
        void addOrdinat(unsigned int y);
        void rotatePoint(Point P, float degree);
        
        /* Operator Overloading */
        bool operator== (const Point &P) const;
        bool operator!= (const Point &P) const;
};

#endif
