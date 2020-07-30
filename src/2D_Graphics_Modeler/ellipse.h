#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <math.h>
#include <QPoint>
#include "shape.h"

/*!
 * @class Ellipse
 * @brief Represents an Ellipse object. Manages 3 attributes.
 */
class Ellipse : public Shape
{
public:

    /*!
     * \brief initializes data pertaining to Ellipse and shape
     * \param color of the pen
     * \param width of the pen point
     * \param style of the pen ball point
     * \param cap style of the pen
     * \param join style of the pen
     * \param color of the brush
     * \param style of the brush
     * \param center point
     * \param radius in the x direction
     * \param radius in the y direction
     */
    explicit Ellipse(int id, int color, int pen_width, int style, int cap, int join,
        int brush_color, int brush_style, QPoint center, int a, int b, QString shapeType);

    /*!
     * \brief deallocates any allocated memory
     */
    ~Ellipse() override {};

    /*!
     * \brief moves the Ellipse
     * \param point_index is unused
     * \param x coordinate of center
     * \param y coordinate of center
     */
    void Move(const int xcoord, const int ycoord) override;

    /*!
     * \brief Draws the Polygon
     * \param (QPaintDevice*) device to interface with painter object
     */
    void Draw(QPaintDevice *device) override;

    /*!
     * \brief calcualates the area of a polygon with n vertices
     * \return (double) area of polygon
     */
    double area() const override;

    /*!
     * \brief calculates the perimeter of Ellipse (is an approximation)
     * \return (double) perimeter of polygon
     */
    double perimeter() const override;

private:

    /*!
     * \brief center point (x1, y1)
     */
    QPoint center;

    /*!
     * \brief radius in the x direction
     */
    int a;

    /*!
     * \brief radius in the y direction
     */
    int b;


};

#endif // ELLIPSE_H
