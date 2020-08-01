#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <QPoint>
#include <QString>
#include "shape.h"

using namespace std;



static const Qt::AlignmentFlag alignment_list[] = { Qt::AlignLeft,
                                                    Qt::AlignRight,
                                                    Qt::AlignTop,
                                                    Qt::AlignBottom,
                                                    Qt::AlignCenter};


static const QFont::Style font_style_list[] = { QFont::StyleNormal,
                                            QFont::StyleItalic,
                                            QFont::StyleOblique};


static const QFont::Weight weight_list[] = { QFont::Thin,
                                             QFont::Light,
                                             QFont::Normal,
                                             QFont::Bold};
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
	explicit Text(int, QString, int, int, int, QString, int, int, int, int,
		int, int, QString);

    /*!
     * \brief deallocates any allocated memory
     */
	~Text() override = default;
	ShapeType getShape() const override {return Shape::Text;}
	QRect getRect() const override;

    /*!
     * \brief Draws the Text
     * \param (QPaintDevice*) device to interface with painter object
     */
	void draw(QPaintDevice *) override;

    /*!
     * \brief sets all the components of a font object
     * \param point size int representing the size of the font
     * \param family Qstring representing the font family of the font
     * \param font style enum representing the style of the font (e.g. italic)
     * \param weight enum representing the weight of the font
     */
	void setFont(int pointSize = 10, QString fontFamily =
			QString("Comic Sans MS"), QFont::Style fontStyle =
			QFont::StyleNormal, QFont::Weight weight = QFont::Thin);

    /*!
     * \brief gets the font for the object
     * \return font reference (non-mutable)
     */
    const QFont& getFont() const {return font;}

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
    QPoint corner_vertex;
    QFont font;
    QString text;
    int alignment_flag;
	int width;
	int length;
};

#endif // TEXT_H
