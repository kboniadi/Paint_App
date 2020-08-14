#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <math.h>
#include <QPoint>
#include <QGraphicsItem>
#include "rectangle.h"

/*!
 * @class Ellipse
 * @brief Represents an Ellipse object. Manages 3 attributes.
 */
class Ellipse : public Rectangle
{
public:
//	Ellipse(QGraphicsItem *parent = nullptr);
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
	explicit Ellipse(id_t id = 0, const QPen &pen = {},
		const QBrush &brush = {}, const QPoint &point = {}, int x = 0,
		int y = 0);

    explicit Ellipse(const QRect &rect, id_t id = 0, const QPen &pen = {},
        const QBrush &brush = {}): Rectangle{rect, id, pen, brush} {}
    /*!
     * \brief deallocates any allocated memory
     */
	~Ellipse() override;
    Ellipse(Ellipse&&) noexcept;
    Ellipse& operator=(Ellipse&&) noexcept;

	ShapeType getShape() const override {return Shape::Ellipse;}
    /*!
     * \brief Draws the Polygon
     * \param (QPaintDevice*) device to interface with painter object
     */
	void draw(QPaintDevice *device) override;

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
//	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
//	QRectF boundingRect() const override;
protected:
//	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
//	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:
//    QPoint center;
//	int radius_x;
//	int radius_y;
};

#endif // ELLIPSE_H
