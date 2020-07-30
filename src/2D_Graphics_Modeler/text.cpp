#include "text.h"


Text::Text(int id, QString text, int alignment_flag, int color, int pointSize,
	QString fontFamily, int fontStyle, int fontWeight, int xcoord, int ycoord,
	int width, int length, QString shapeType)
	: Shape{id, color, shapeType}, corner_vertex{xcoord, ycoord}
{
    //text color is the same as the pen color
	assert(color < 17 && color > -1);
	font.setPointSize(pointSize);
    font.setFamily(fontFamily);
    font.setStyle(font_style_list[fontStyle]);
    font.setWeight(weight_list[fontWeight]);
    this->text = text;
    this->alignment_flag = alignment_flag;
	this->width = width;
	this->length = length;
}

void Text::setFont(int pointSize, QString fontFamily, QFont::Style fontStyle,
    QFont::Weight weight)
{
    font.setPointSize(pointSize);
    font.setFamily(fontFamily);
    font.setStyle(fontStyle);
    font.setWeight(weight);
}

void Text::Move(const int xcoord, const int ycoord)
{
    corner_vertex = QPoint(xcoord, ycoord);
}

void Text::Draw(QPaintDevice *device)
{
	getPainter().begin(device);
	getPainter().setPen(getPen());
	getPainter().setFont(getFont());
    //save the settings
    getPainter().save();
    //bounding box has to be big enough to display text
	getPainter().drawText(corner_vertex.x(), corner_vertex.y(), width, length,
	alignment_list[alignment_flag], text);
    //restore the settings from "save"
    getPainter().restore();
	getPainter().end();
}
