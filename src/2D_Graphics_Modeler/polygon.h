#ifndef POLYGON_H
#define POLYGON_H

#include <math.h>
#include <QPoint>
#include "shape.h"

constexpr int MAX_VERT = 8;	//!<max number of supported vertices

/*!
  \class Polygon: inherits Shape
 * \brief This class represents a Polygon object. It manages 2 attribute.
 */
class Polygon: public Shape {
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
    explicit Polygon(int, int, int, int, int, int, int , int, int, QPoint*, QString);

	/*!
	 * \brief deallocates any allocated memory
	 */
	~Polygon() override {}

	/*!
     * \brief moves the entire Polygon to coordinate
     * moves first point in vert_list to coordinate
	 * \param xcoord of that vertex
	 * \param ycoord of that vertex
	 */
    void Move(const int xcoord, const int ycoord) override;

	/*!
	 * \brief Draws the Polygon
	 * \param (QPaintDevice*) device to interface with painter object
	 */
	void Draw(QPaintDevice *) override;

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
	{return sqrt(pow(two.x() - one.x(), 2) + pow(two.y() - one.y(), 2) * 1.0);}

	QPoint vert_list[MAX_VERT];
	int vert_count;
};

#endif // POLYGON_H
