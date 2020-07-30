#ifndef POLYLINE_H
#define POLYLINE_H

#include <math.h>
#include "shape.h"

const int MAX_POLYLINE_VERT = 8;

/*!
  \class Polyline: inherits Shape
 * \brief This class represents a Polyline object. It manages 2 attributes.
 */
class Polyline : public Shape
{
public:
    /*!
     * \brief initializes data pertaining to Polyline and Shape
     * \param color of the pen
     * \param width of the pen point
     * \param style of the pen ball point
     * \param cap style of the pen
     * \param join style of the pen
     * \param color of the brush
     * \param style of the brush
     * \param verts number of vertices
     * \param points pointer to QPoint data
     */
    explicit Polyline(int, int, int, int, int, int, int , int, int, QPoint*, QString shapeType);

    /*!
     * \brief deallocates any allocated memory
     */
    ~Polyline() override {}

    /*!
     * \brief moves the entire Polygon to coordinate
     * moves first point in vert_list to coordinate
     * \param xcoord of that vertex
     * \param ycoord of that vertex
     */
    void Move (const int xcoord, const int ycoord) override;

    /*!
     * \brief Draws the Polyline
     * \param (QPaintDevice*) device to interface with painter object
     */
    void Draw (QPaintDevice *) override;

    /*!
     * \brief returns the area of a Polyline
     * \return (double) area of Polyline always returns -1
     */
    inline double area() const override {return -1;}

    /*!
     * \brief returns the perimeter of a Polyline
     * \return (double) perimeter of Polyline always returns -1
     */
    inline double perimeter() const override {return -1;}
private:

//    inline double DistanceFormu(const QPoint one, const QPoint two) const
//    {return sqrt(pow(two.x() - one.x(), 2) + pow(two.y() - one.y(), 2) * 1.0);}

    QPoint vert_list[MAX_POLYLINE_VERT];
    int vert_count;
};

#endif // POLYLINE_H
