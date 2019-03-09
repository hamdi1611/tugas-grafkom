/*  Shape.h  */

#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Line.h"

class Shape {
    private:
        bool closed;             // Boolean to known the shape is closed or not
        unsigned int amount;     // Amount of Line to be allocated
        unsigned int neff;       // An effective amount that used
        Line *L;                 // Dynamic Array of Line
    
    public:
        /* Operator Empat Sekawan */
        Shape();
        Shape(unsigned int amount);
        Shape(Shape &shape);
        ~Shape();
        
        /*& getter and Setter */
        unsigned int getAmount() const;
        unsigned int getNeff() const;
        void resetNeff();
        void setAmount(int amount);
        Line getLineAt(unsigned int idx);
        void setLineAt(unsigned int idx, Line line);
        Line getExtremeLine();
        /* Function and Procedure */
        void addLine(Line line);
        bool isClosed() const;
        void rotateShape(Point P, float degree);
};

#endif
