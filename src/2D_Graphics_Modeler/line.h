#ifndef LINE_H
#define LINE_H

#include <math.h>
#include <QPoint>
#include "shape.h"

/*!
 * @class Line
 * @brief Represents a Line object. Manages 2 attributes.
 */
class Line: public Shape
{
public:
    /*!
     * \brief Line destructor deallocates memory
     */
	~Line() override = default;

    /*!
     * \brief initializes data pertaining to line
     * \param color of the pen
     * \param width of the pen point
     * \param style of the pen ball point
     * \param cap style of the pen
     * \param join style of the pen
     * \param color of the brush
     * \param style of the brush
     * \param starting point
     * \param ending poing
    */

	explicit Line(const id_t id = 0, const QPen& pen = {},
        const QBrush& brush = {}, const QPoint& pos_A = {},
        const QPoint& pos_B = {})
		: Shape{id, pen, brush, QPoint{}}, startPoint{pos_A}, endPoint{pos_B} {}

    Line(Line&&) noexcept;
    Line& operator=(Line&&) noexcept;

    void setStart(const QPoint &otherstart) {startPoint = otherstart;}
    void setEnd(const QPoint &otherend) {endPoint = otherend;}

	QRect getRect() const override;
	ShapeType getShape() const override {return Shape::Line;}
    QPoint getStart() const {return startPoint;}
    QPoint getEnd() const {return endPoint;}
    /*!
     * \brief calculates the area of line
     * \return 0
     */
    double area() const override;

    /*!
     * \brief calculates the perimeter of Line (is an approximation)
     * \return 0
     */
    double perimeter() const override;

    /*!
     * \brief Draws the line
     * \param (QPaintDevice*) device to interface with painter object
     */
	void draw(QPaintDevice *) override;


private:
    QPoint startPoint;
    QPoint endPoint;
};

#endif // LINE_H
