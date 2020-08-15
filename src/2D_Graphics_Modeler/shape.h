#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QPaintDevice>
#include <assert.h>

/*!
 * @class Shape
 * @brief This class represents a Shape object. It manages 5 attribute.
 */
class Shape {
public:

	using id_t = unsigned int;
	static id_t shapeid;

	/*!
	 * \enum ShapeType
	 * \brief Represents different supported shapes
	 */
	enum ShapeType {
		NoShape,	//!< value 0
		Line,		//!< value 1
		Polyline,	//!< value 2
		Polygon,	//!< value 3
		Rectangle,	//!< value 4
		Square,		//!< value 5
		Ellipse,	//!< value 6
		Circle,		//!< value 7
		Text		//!< value 8
	};

	/*!
	 * \brief Initialize class attributes
     * \param Id of shape
	 * \param color of the pen
	 * \param width of the pen point
	 * \param style of the pen ball point
	 * \param cap style of the pen
	 * \param join style of the pen
	 * \param color of the brush
	 * \param style of the brush
	 */
	explicit Shape(const QPoint& pos = {}, id_t id = 0, const QPen& pen = {},
		const QBrush& brush = {});

	/*!
	 * \brief deallocates any allocated memory
	 */
	virtual ~Shape() = default;

	/*!
	 * \brief prevent the usage of a copy contructor
	 * \param type instance of a Shape class
	 */
	Shape(Shape& type) = delete;
	Shape& operator=(const Shape&) = delete;

	bool operator==(const Shape &other) const {return id == other.id;}
	bool operator<(const Shape &other) const {return id < other.id;}

	/*!
	 * \brief sets an id for a shape
	 * \param ID new id
	 */
	void setID(const id_t ID) {id = ID;}

	void setPen(const QPen &pen) {this->pen = pen;}
	void setBrush(const QBrush &brush) {this->brush = brush;}

	void setPos(int x, int y)
	{
		position.setX(x);
		position.setY(y);
	}

	void setPos(const QPoint& pos) {position = pos;}

	/*!
	 * \brief gets the id for the shape
	 * \return shape id
	 */
	id_t getID() const {return id;}

	/*!
	 * \brief gets the pen object
	 * \return pen reference (non-mutable)
	 */
	const QPen& getPen() const {return pen;}

	/*!
	 * \brief gets the brush object
	 * \return brush reference (non-mutable)
	 */
	const QBrush& getBrush() const {return brush;}

	const QPoint& getPos() const {return position;}

	/*!
	 * \brief moves the shape or parts of shapes
	 * \param xcoord of that vertex
	 * \param ycoord of that vertex
	 */
	void move(int dx, int dy);

	virtual QRect getRect() const = 0;
	/*!
	 * \brief gets the shape type
	 * \return Shape Type
	 */
	virtual ShapeType getShape() const = 0;

	/*!
	 * \brief Draws the shape
	 * \param (QPaintDevice*) device to interface with painter object
	 */
	virtual void draw(QPaintDevice*) = 0;

	/*!
	 * \brief area of a shape
	 * \return (double) area of a specific shape
	 */
	virtual double area() const = 0;

	/*!
	 * \brief perimeter of a shape
	 * \return (double) perimeter of a specific shape
	 */
	virtual double perimeter() const = 0;
	static bool hasfill(ShapeType);
protected:
	void swap(Shape&) noexcept;
	/*!
	 * \brief gets the painter object
	 * \return reference to a painter instance
	 */
	QPainter& getPainter() {return painter;}
private:
	QPainter painter;
	QPoint position;
	id_t id{0};
	QPen pen;
	QBrush brush;
};

extern const QMap<Shape::ShapeType, QString> SHAPE_NAMES;
extern const QMap<QString, QColor> COLOR_NAMES;
extern const QMap<Qt::PenStyle, QString> STYLE_NAMES;
extern const QMap<Qt::PenCapStyle, QString> CAP_NAMES;
extern const QMap<Qt::PenJoinStyle, QString> JOIN_NAMES;
extern const QMap<Qt::BrushStyle, QString> BSTYLE_NAMES;

#endif // SHAPE_H
