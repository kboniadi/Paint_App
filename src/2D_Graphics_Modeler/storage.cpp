#include "storage.h"

Storage::Storage(): model{&shapes} {}

Storage::~Storage()
{
	for (Shape *s: shapes)
		delete s;
}
