#include "textparse.h"

// helper functions for encapsulation of switch cases

int getBrushStyle(std::string key) {
    if (key == "NoBrush") return 0;
    else if (key == "SolidPattern") return 1;
    else if (key == "HorPattern") return 2;
    else if (key == "VerPattern") return 3;
    return -1;
}

int getJoinStyle(std::string key) {
    if ( key == "MiterJoin") return 0;
    else if ( key == "BevelJoin" ) return 1;
    else if ( key == "RoundJoin" ) return 2;
    else if ( key == "SvgMiterJoin" ) return 3;
    return -1;
}

int getCapStyle(std::string key) {
    if ( key == "FlatCap") return 0;
    else if ( key == "SquareCap" ) return 1;
    else if ( key == "RoundCap" ) return 2;
    return -1;
}

int getPenStyle(std::string key) {
    if ( key == "NoPen") return 0;
    else if ( key == "SolidLine") return 1;
    else if ( key == "DashLine") return 2;
    else if ( key == "DotLine") return 3;
    else if ( key == "DashDotLine") return 4;
    else if ( key == "DashDotDotLine") return 5;
    else if ( key == "CustomDashLine") return 6;
    else return -1;
}

int getColor(std::string key) {
    if (key == "white") return 0;
    else if (key == "black") return 1;
    else if (key == "red") return 2;
    else if (key == "green") return 3;
    else if (key == "blue") return 4;
    else if (key == "cyan") return 5;
    else if (key == "magenta") return 6;
    else if (key == "yellow") return 7;
    else if (key == "gray") return 8;
    return -1;
}

int getTextAlig(std::string key) {
    if ( key == "AlignLeft") return 0;
    if ( key == "AlignRight") return 1;
    if ( key == "AlignTop") return 2;
    if ( key == "AlignBottom") return 3;
    if ( key == "AlignCenter") return 4;
    return -1;
}

int getTextStyle(std::string key) {
    if ( key == "StyleNormal") return 0;
    if ( key == "StyleItalic") return 1;
    if ( key == "StyleOblique") return 2;
    return -1;
}

int getFontWeight(std::string key) {
    if ( key == "Thin") return 0;
    if ( key == "Light") return 1;
    if ( key == "Normal") return 2;
    if ( key == "Bold") return 3;
    return -1;
}

Shape * parseLine(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
    std::string shapeType="Line", pencolor, penstyle, pencap, penjoin, brushcolor, brushstyle;
    int penwidth;
    in >> pencolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penwidth;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penstyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> pencap;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penjoin;

	return new Line(shapeid, getColor(pencolor), penwidth,
		getPenStyle(penstyle), getCapStyle(pencap), getJoinStyle(penjoin), 0,
		0, QPoint(dims[0], dims[1]), QPoint(dims[3], dims[4]), "Line");
}

Shape * parsePolyline(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
    std::string shapeType="Polyline", pencolor, penstyle, pencap, penjoin, brushcolor, brushstyle;
    int penwidth;
    in >> pencolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penwidth;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penstyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> pencap;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penjoin;

    QPoint* points = new QPoint[dims.getLength()/2];
    auto it = dims.begin();
    for (std::size_t i = 0; i < dims.getLength()/2; ++i) {
        points[i].setX(*it);
        ++it;
        points[i].setY(*it);
        ++it;
    }
	 return new Polyline(shapeid, getColor(pencolor), penwidth,
		getPenStyle(penstyle), getCapStyle(pencap), getJoinStyle(penjoin),0 ,0,
		dims.getLength()/2, points, "Polyline");
}

Shape * parsePolygon(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
    std::string shapeType="Polygon", pencolor, penstyle, pencap, penjoin, brushcolor, brushstyle;
    // std::vector<int> dims;
    int penwidth;
    in >> pencolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penwidth;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penstyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> pencap;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penjoin;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushcolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushstyle;

    QPoint* points = new QPoint[dims.getLength()/2];
    auto it = dims.begin();
    for (std::size_t i = 0; i < dims.getLength()/2; ++i) {
        points[i].setX(*it);
        ++it;
        points[i].setY(*it);
        ++it;
    }
	Polygon * pPolygon = new Polygon(shapeid, getColor(pencolor), penwidth,
		getPenStyle(penstyle), getCapStyle(pencap), getJoinStyle(penjoin),
		getColor(brushcolor), getBrushStyle(brushstyle), dims.getLength()/2,
		points, "Polygon");
    return pPolygon;
}

Shape * parseRectangle(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
	std::string shapeType="Rectangle", pencolor, penstyle, pencap, penjoin,
		brushcolor, brushstyle;
    // std::vector<int> dims;
    int penwidth;
    in >> pencolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penwidth;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penstyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> pencap;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penjoin;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushcolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushstyle;

	return new Rectangle(shapeid, getColor(pencolor), penwidth,
		getPenStyle(penstyle), getCapStyle(pencap), getJoinStyle(penjoin),
		getColor(brushcolor), getBrushStyle(brushstyle), dims[0], dims[1],
		double(dims[2]), double(dims[3]), "Rectangle");

}

Shape * parseSquare(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
	std::string shapeType="Square", pencolor, penstyle, pencap, penjoin,
		brushcolor, brushstyle;
    // std::vector<int> dims;
    int penwidth;
    in >> pencolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penwidth;
	in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penstyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> pencap;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penjoin;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushcolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushstyle;

	return new Rectangle(shapeid, getColor(pencolor), penwidth,
		getPenStyle(penstyle), getCapStyle(pencap), getJoinStyle(penjoin),
		getColor(brushcolor), getBrushStyle(brushstyle), dims[0], dims[1],
		double(dims[2]), double(dims[2]), "Square");
}

Shape * parseEllip(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
    std::string shapeType="Ellipse", pencolor, penstyle, pencap, penjoin, brushcolor, brushstyle;
    int penwidth;
    in >> pencolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penwidth;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penstyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> pencap;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penjoin;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushcolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushstyle;

	return new Ellipse(shapeid, getColor(pencolor), penwidth,
		getPenStyle(penstyle), getPenStyle(penstyle), getJoinStyle(penjoin),
		getColor(brushcolor), getBrushStyle(brushstyle), QPoint(dims[0],
		dims[1]), dims[2], dims[3], "Ellipse");
}

Shape * parseCircle(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
	std::string shapeType="Circle", pencolor, penstyle, pencap, penjoin,
		brushcolor, brushstyle;
    int penwidth;
    in >> pencolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penwidth;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penstyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> pencap;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penjoin;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushcolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushstyle;

	return new Ellipse(shapeid, getColor(pencolor), penwidth,
		getPenStyle(penstyle), getPenStyle(penstyle), getJoinStyle(penjoin),
		getColor(brushcolor), getBrushStyle(brushstyle), QPoint(dims[0],
		dims[1]), dims[2], dims[2], "Circle");
}

Shape * parseText(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
	std::string shapeType="Text", text, textColor, textAlig, textFont,
		textFontStyle, textFontWeight;
    int textpointsize;
	std::getline(in, text, '\n');
    in.ignore(100, ' ');
    in >> textColor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> textAlig;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> textpointsize;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
	std::getline(in, textFont, '\n');
    in.ignore(100, ' ');
    in >> textFontStyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> textFontWeight;

    QString qText = QString::fromStdString(text), qFont = QString::fromStdString(textFont);
	return new Text(shapeid, qText, getColor(textColor), getTextAlig(textAlig),
		textpointsize, qFont, getTextStyle(textFontStyle),
		getFontWeight(textFontWeight), dims[0], dims[1], dims[2], dims[3],
		"Text");
}

int getShapeType(std::string key) {
    if (key == "Line") return 1;
    if (key == "Polyline") return 2;
    if (key == "Polygon") return 3;
    if (key == "Rectangle") return 4;
    if (key == "Square") return 5;
    if (key == "Ellipse") return 6;
    if (key == "Circle") return 7;
    if (key == "Text") return 8;
    return -1;
}

cs1c::vector<Shape *> textParse() {
    std::ifstream in;
    in.open("shapes.txt");
    std::string shapeType;
    cs1c::vector<int> dims;
    cs1c::vector<Shape*> shapes;
    int shapeIdtemp, dimsTemp;
    while (1) {
        dims.clear();
        in.ignore(100, '\n');
        in.ignore(100, ' ');
        in >> shapeIdtemp;
        if (in.fail()) {
            in.clear();
            return shapes;
        }
        in.ignore(100, '\n');
        in.ignore(100, ' ');
        in >> shapeType;
        in.ignore(100, '\n');
        in.ignore(100, ' ');
        while (in >> dimsTemp) {
            dims.push_back(dimsTemp);
            in.ignore(100, ' ');
        }
        in.clear();
        // in.ignore(100);
        switch(getShapeType(shapeType)) {
            case 1:
                shapes.push_back(parseLine(in, shapeIdtemp, dims));
                break;
            case 2:
                shapes.push_back(parsePolyline(in, shapeIdtemp, dims));
                break;
            case 3:
                shapes.push_back(parsePolygon(in, shapeIdtemp, dims));
                break;
            case 4:
                shapes.push_back(parseRectangle(in, shapeIdtemp, dims));
                break;
            case 5:
                shapes.push_back(parseSquare(in, shapeIdtemp, dims));
                break;
            case 6:
                shapes.push_back(parseEllip(in, shapeIdtemp, dims));
                break;
            case 7:
                shapes.push_back(parseCircle(in, shapeIdtemp, dims));
                break;
            case 8:
                shapes.push_back(parseText(in, shapeIdtemp, dims));
                break;
        }
    }
}
