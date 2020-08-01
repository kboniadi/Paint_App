#ifndef POLYLINE_H
#define POLYLINE_H

#include <math.h>
#include "shape.h"
#include "vector.h"

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
	explicit Polyline(const id_t id = 0, const QPen& pen = {},
		const QBrush& brush = {}, cs1c::vector<QPoint> points = {});
    /*!
     * \brief deallocates any allocated memory
     */
	~Polyline() override = default;
    Polyline(Polyline&&) noexcept;
    Polyline& operator=(Polyline&&) noexcept;

	ShapeType getShape() const override {return Shape::Polyline;}
	QRect getRect() const override;
    std::size_t getSize() const {return points.size();}

    /*!
     * \brief Draws the Polyline
     * \param (QPaintDevice*) device to interface with painter object
     */
	void draw(QPaintDevice *) override;

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
protected:
	void setCenter();
	cs1c::vector<QPoint> points;
};

#endif // POLYLINE_H
