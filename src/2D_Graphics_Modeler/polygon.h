#ifndef POLYGON_H
#define POLYGON_H

#include <math.h>
#include <QPoint>
#include "polyline.h"
#include <algorithm>
#include <utility>
/*!
  \class Polygon: inherits Shape
 * \brief This class represents a Polygon object. It manages 2 attribute.
 */
class Polygon: public Polyline {
public:
	/*!
	 * \brief initializes data pertaining to Polygon and shape
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
	Polygon(std::vector<QPoint> points = {}, const id_t id = 0,
		const QPen& pen = {}, const QBrush& brush = {});

	/*!
	 * \brief deallocates any allocated memory
	 */
	~Polygon() override;
    Polygon(Polygon&&) noexcept;
    Polygon& operator=(Polygon&&) noexcept;

	ShapeType getShape() const override {return Shape::Polygon;}
//	QRect getRect() const override;
	/*!
	 * \brief Draws the Polygon
	 * \param (QPaintDevice*) device to interface with painter object
	 */
	void draw(QPaintDevice *) override;

	/*!
	 * \brief calcualates the area of a polygon with n vertices
	 * \return (double) area of polygon
	 */
	double area() const override;

	/*!
	 * \brief calculates the perimeter of a polygon with n vertices
	 * \return (double) perimeter of polygon
	 */
	double perimeter() const override;
private:
	/*!
	 * \brief Distance Formula for two QPoint objects
	 * \param one first QPoint object representing x1 and y1
	 * \param two second QPoint object representing x2 and y2
	 * \return (double) the distance between these two points
	 */
	inline double Dist_Formu(const QPoint one, const QPoint two) const
	{return std::sqrt(std::pow(two.x() - one.x(), 2) +
		std::pow(two.y() - one.y(), 2) * 1.0);}
};

#endif // POLYGON_H
