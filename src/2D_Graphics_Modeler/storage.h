#ifndef STORAGE_H
#define STORAGE_H

#include "shapesModel.h"

struct Storage {
	Storage();
	~Storage();

	cs1c::vector<Shape*> shapes;
	ShapesModel model;
};

#endif // STORAGE_H
