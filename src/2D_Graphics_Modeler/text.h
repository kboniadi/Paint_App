#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <QPoint>
#include <QString>
#include "shape.h"

using namespace std;

extern const QMap<Qt::AlignmentFlag, QString> ALIGNMENT_TYPES;
extern const QMap<QFont::Style, QString> FONT_STYLES;
extern const QMap<QFont::Weight, QString> FONT_WEIGHTS;

/*!
 * @class Text
 * @brief This class represents a Text object. Manages 6 attributes.
 */
class Text: public Shape
{
public:
    /*!
     * \brief initializes data pertaining to Text and shape
     * \param text string
     * \param text color
     * \param text alignment
     * \param text point size
     * \param text font family
     * \param text font style
     * \param text font weight
     */
	explicit Text(const QPen &pen = {}, const QBrush &brush = {},
		const QPoint &point = {}, id_t id = 0, const QFont &font = {},
		const QString &str = "", Qt::AlignmentFlag flag = Qt::AlignCenter,
		int width = -1, int height = -1)
		: Shape{point, id, pen, brush}, font{font}, text{str}, alignment{flag},
		  width{width}, height{height} {}

    /*!
     * \brief deallocates any allocated memory
     */
	~Text() override = default;
	Text(Text&&) noexcept;
	Text& operator=(Text&&) noexcept;

	void setText(QString text) {this->text = std::move(text);}
	void setWidth(int aWidth) {width = aWidth;}
	void setHeight(int aHeight) {height = aHeight;}
	void setAlignment(Qt::AlignmentFlag align) {alignment = align;}
	void setRect(const QRect&);

	/*!
	 * \brief sets all the components of a font object
	 * \param point size int representing the size of the font
	 * \param family Qstring representing the font family of the font
	 * \param font style enum representing the style of the font (e.g. italic)
	 * \param weight enum representing the weight of the font
	 */
	void setFont(QFont font) {this->font = std::move(font);}

	ShapeType getShape() const override {return Shape::Text;}
	const QString& getText() const {return text;}
	int getWidth() const {return width;}
	int getHeight() const {return height;}
	Qt::AlignmentFlag getAlignment() const {return alignment;}
	QRect getRect() const override;
    /*!
     * \brief gets the font for the object
     * \return font reference (non-mutable)
     */
    const QFont& getFont() const {return font;}

	/*!
	 * \brief Draws the Text
	 * \param (QPaintDevice*) device to interface with painter object
	 */
	void draw(QPaintDevice *) override;

	/*!
	 * \brief perimeter (not used for text box
	 * \return -1
	 */
	double perimeter() const override {return -1;}

	/*!
	 * \brief area (not used for text box
	 * \return -1
	 */
	double area() const override {return -1;}

private:
    QFont font;
    QString text;
	Qt::AlignmentFlag alignment = Qt::AlignCenter;
	int width{-1};
	int height{-1};
};

#endif // TEXT_H
