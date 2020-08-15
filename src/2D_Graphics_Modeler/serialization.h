#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "storage.h"
#include "line.h"
#include "ellipse.h"
#include "polygon.h"
#include "text.h"

#include <iostream>

std::ostream& operator<<(std::ostream& out, const cs1c::vector<Shape*> &shapes);
#endif // SERIALIZATION_H
