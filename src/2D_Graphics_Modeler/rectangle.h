#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <math.h>
#include <QPoint>
#include "shape.h"

/*!
  \class Rectangle: inherits Shape
 * \brief This class represents a Rectangle object. It manages 4 attribute.
 */
class Rectangle: public Shape{
public:
//    Rectangle() {};
    /*!
     * \brief initializes data pertaining to Rectangle and shape
     * \param color of the pen
     * \param width of the pen point
     * \param style of the pen ball point
     * \param cap style of the pen
     * \param join style of the pen
     * \param color of the brush
     * \param style of the brush
     * \param x axis of upper left corner
     * \param y axis of upper left corner
     * \param width of the Rectangle
     * \param length of the Rectangle
    */
    explicit Rectangle(int id, int color, int penWidth, int style, int cap, int join,
		int brushColor, int brushStyle, int aX, int aY, double aWidth,
        double aLength, QString shapeType);

    /*!
     * \brief deallocates any allocated memory
     */
    ~Rectangle() override {};

    /*!
     * \brief moves the Rectangle or parts of Rectangle
     * \param xcoord of upper left corner
     * \param ycoord of upper left corner
     */
    void Move(const int xcoord,
        const int ycoord) override;

    /*!
     * \brief Draws the Rectangle
     * \param (QPaintDevice*) device to interface with painter object
     */
    void Draw(QPaintDevice *) override;

    /*!
     * \brief calcualates the area of a Rectangle
     * \return (double) area of Rectangle
     */
    double area() const override;

    /*!
     * \brief calculates the perimeter of a Rectangle
     * \return (double) perimeter of Rectangle
     */
    double perimeter() const override;


private:
    int x;
    int y;
    double width;
    double length;

};

#endif // RECTANGLE_H
