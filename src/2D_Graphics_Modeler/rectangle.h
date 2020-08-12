#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <math.h>
#include <QPoint>
#include "shape.h"
#include <QGraphicsItem>
/*!
  \class Rectangle: inherits Shape
 * \brief This class represents a Rectangle object. It manages 4 attribute.
 */
class Rectangle: public Shape/*, QGraphicsItem*/{
public:
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
    explicit Rectangle(const QPen &pen = {}, const QBrush &brush = {},
		const QPoint &point = {}, id_t id = 0, int aWidth = 0, int aHeight = 0)
		: Shape{point, id, pen, brush}, width{aWidth}, height{aHeight} {}

	explicit Rectangle(const QRect &rect, id_t id = 0, const QPen &pen = {},
		const QBrush &brush = {})
		: Shape{rect.center(), id, pen, brush}, width{rect.width()},
		height{rect.height()} {}
    /*!
     * \brief deallocates any allocated memory
     */
	~Rectangle() override = default;
	Rectangle(Rectangle&&) noexcept;
	Rectangle& operator=(Rectangle) noexcept;
	Rectangle& operator=(Rectangle&&) noexcept;


	void setWidth(int width) {this->width = width;}
	void setLength(int length) {this->height = length;}
	void setRect(const QRect&);

	int getwidth() const {return width;}
	int getLength() const {return height;}
	QRect getRect() const override;
	ShapeType getShape() const override {return Shape::Rectangle;}

    /*!
     * \brief Draws the Rectangle
     * \param (QPaintDevice*) device to interface with painter object
     */
	void draw(QPaintDevice*) override;

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
protected:
	explicit Rectangle(id_t id): Shape{QPoint{}, id}, width{0}, height{0} {}
	int width{0};
	int height{0};
};

#endif // RECTANGLE_H
