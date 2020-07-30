#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QPaintDevice>
#include <assert.h>


static const Qt::GlobalColor color_list[] = {Qt::white,
											 Qt::black,
                                             Qt::red,
                                             Qt::green,
                                             Qt::blue,
                                             Qt::cyan,
											 Qt::magenta,
                                             Qt::yellow,
                                             Qt::gray,};



static const Qt::PenStyle style_list[] = {Qt::NoPen,
										  Qt::SolidLine,
										  Qt::DashLine,
										  Qt::DotLine,
										  Qt::DashDotLine,
										  Qt::DashDotDotLine,
										  Qt::CustomDashLine};



static const Qt::PenCapStyle cap_list[] = {Qt::FlatCap,
										   Qt::SquareCap,
										   Qt::RoundCap};

static const Qt::PenJoinStyle join_list[] = {Qt::MiterJoin,
											 Qt::BevelJoin,
											 Qt::RoundJoin,
											 Qt::SvgMiterJoin};




static const Qt::BrushStyle bstyle_list[] = {Qt::NoBrush,
                                             Qt::SolidPattern,
											 Qt::HorPattern,
                                             Qt::VerPattern};
/*!
 * @class Shape
 * @brief This class represents a Shape object. It manages 5 attribute.
 */
class Shape {
public:

	/*!
	 * \enum ShapeType
	 * \brief Represents different supported shapes
	 */
	enum ShapeType {
		NoShape,	//!< value 1
		Line,		//!< value 2
		Polyline,	//!< value 3
		Polygon,	//!< value 4
		Rectangle,	//!< value 5
		Square,		//!< value 6
		Ellipse,	//!< value 7
		Circle,		//!< value 8
		Text		//!< value 9
	};

	/*!
	 * \todo implementation unknown
	 * \param device pointer to QPaintDevice
	 */
    //TODO implementation
//	Shape(QPaintDevice *device = nullptr);
    /*!
     * \brief intialize Shape with pen color
     * \param color of the pen
     */
    Shape(int id, int color, QString shapeType);

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
    Shape(int, int, int, int, int, int, int , int, QString);

	/*!
	 * \brief deallocates any allocated memory
	 */
	virtual ~Shape() {}

	/*!
	 * \brief prevent the usage of a copy contructor
	 * \param type instance of a Shape class
	 */
	Shape(Shape& type) = delete;

	/*!
	 * \brief sets the type of Shape
	 * \param ashape enum representing a type of shape
	 */
	void setShape(ShapeType ashape) {shape = ashape;}

	/*!
	 * \brief sets all the components of a pen object
	 * \param color enum representing the color of the pen
	 * \param width size of pen mark
	 * \param style enum representing the style of the pen
	 * \param cap enum representing the cap style
	 * \param join enum representing the join style
	 */
	void setPen(Qt::GlobalColor color = Qt::black, qreal width = 1,
		Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap,
		Qt::PenJoinStyle join = Qt::BevelJoin);

	/*!
	 * \brief sets all the components of a brush object
	 * \param color enum representing the color of the brush
	 * \param style enum representing the style of the brush
	 */
	void setBrush(Qt::GlobalColor color = Qt::black,
		Qt::BrushStyle style = Qt::NoBrush);

	/*!
	 * \brief sets an id for a shape
	 * \param ID new id
	 */
	void setID(int ID) {id = ID;}

	/*!
	 * \brief sets the pen, brush, and painter object with default values
	 */
	void setDefautStyle();

//	void DrawRect(int width, int height);

	/*!
	 * \brief gets the shape type
	 * \return Shape Type
	 */
    QString getShape() const {return shape;}

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

	/*!
	 * \brief gets the id for the shape
	 * \return shape id
	 */
	int getID() const {return id;}

	/*!
	 * \brief moves the shape or parts of shapes
	 * \param xcoord of that vertex
	 * \param ycoord of that vertex
	 */
    virtual void Move(const int xcoord, const int ycoord) = 0;

	/*!
	 * \brief Draws the shape
	 * \param (QPaintDevice*) device to interface with painter object
	 */
	virtual void Draw(QPaintDevice*) = 0;

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
protected:
	/*!
	 * \brief gets the painter object
	 * \return reference to a painter instance
	 */
	QPainter& getPainter() {return painter;}
private:
	QPainter painter;
	int id;
    QString shape;
	QPen pen;
	QBrush brush;

};

#endif // SHAPE_H
