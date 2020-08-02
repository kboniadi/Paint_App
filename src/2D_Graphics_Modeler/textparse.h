#ifndef TEXTPARSE_H
#define TEXTPARSE_H
#include <iostream>
#include <fstream>
#include <string>
#include <QPainter>
#include "vector.h"
#include "shape.h"
#include "text.h"
#include "rectangle.h"
#include "polyline.h"
#include "polygon.h"
#include "line.h"
#include "ellipse.h"

//!@brief text parser modifies vector<Shape *> to add typecast polymorphic objects to shape class.
cs1c::vector< Shape * > textParse();

// helper functions for encapsulation of switch cases

/*!
* \brief finds appropraite array index for the key returns -1 key is invalid
* \param key is the string to be searched
*/
Qt::BrushStyle getBrushStyle(std::string key);
/*!
* \brief finds appropraite array index for the key returns -1 key is invalid
* \param key is the string to be searched
*/
Qt::PenJoinStyle getJoinStyle(std::string key);
/*!
* \brief finds appropraite array index for the key returns -1 key is invalid
* \param key is the string to be searched
*/
Qt::PenCapStyle getCapStyle(std::string key);
/*!
* \brief finds appropraite array index for the key returns -1 key is invalid
* \param key is the string to be searched
*/
Qt::PenStyle getPenStyle(std::string key);
/*!
* \brief finds appropraite array index for the key returns -1 key is invalid
* \param key is the string to be searched
*/
Qt::GlobalColor getColor(std::string key);
/*!
* \brief finds appropraite array index for the key returns -1 key is invalid
* \param key is the string to be searched
*/
QFont::Weight getFontWeight(std::string key);
/*!
* \brief finds appropraite array index for the key returns -1 key is invalid
* \param key is the string to be searched
*/
Shape::ShapeType getShapeType(std::string key);
/*!
* \brief fcreates a line object from the values parsed
* \param in is ifstream object
* \param shapeid is the parsed shape id
* \param dims is the vector of dimensions used to create the object
*/
Shape * parseLine(std::ifstream& in, int shapeid, cs1c::vector<int> &dims);
/*!
* \brief fcreates a line object from the values parsed
* \param in is ifstream object
* \param shapeid is the parsed shape id
* \param dims is the vector of dimensions used to create the object
*/
Shape * parsePolyline(std::ifstream& in, int shapeid, cs1c::vector<int> &dims);
/*!
* \brief fcreates a Polyline object from the values parsed
* \param in is ifstream object
* \param shapeid is the parsed shape id
* \param dims is the vector of dimensions used to create the object
*/
Shape * parsePolygon(std::ifstream& in, int shapeid, cs1c::vector<int> &dims);
/*!
* \brief fcreates a polygon object from the values parsed
* \param in is ifstream object
* \param shapeid is the parsed shape id
* \param dims is the vector of dimensions used to create the object
*/
Shape * parseRectangle(std::ifstream& in, int shapeid, cs1c::vector<int> &dims);
/*!
* \brief fcreates a Rectangle object from the values parsed
* \param in is ifstream object
* \param shapeid is the parsed shape id
* \param dims is the vector of dimensions used to create the object
*/
Shape * parseSquare(std::ifstream& in, int shapeid, cs1c::vector<int> &dims);
/*!
* \brief fcreates a Square object from the values parsed
* \param in is ifstream object
* \param shapeid is the parsed shape id
* \param dims is the vector of dimensions used to create the object
*/
Shape * parseEllip(std::ifstream& in, int shapeid, cs1c::vector<int> &dims);
/*!
* \brief fcreates a ellipse object from the values parsed
* \param in is ifstream object
* \param shapeid is the parsed shape id
* \param dims is the vector of dimensions used to create the object
*/
Shape * parseCircle(std::ifstream& in, int shapeid, cs1c::vector<int> &dims);
/*!
* \brief fcreates a text object from the values parsed
* \param in is ifstream object
* \param shapeid is the parsed shape id
* \param dims is the vector of dimensions used to create the object
*/
Shape * parseText(std::ifstream& in, int shapeid, cs1c::vector<int> &dims);

#endif // TEXTPARSE_H
