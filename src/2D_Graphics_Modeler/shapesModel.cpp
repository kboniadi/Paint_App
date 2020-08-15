#include "shapesModel.h"

ShapesModel::ShapesModel(cs1c::vector<Shape*> *shapes)
	: shapes_{shapes} {}

int ShapesModel::rowCount(const QModelIndex &) const
{
	return static_cast<int>(shapes_->size());
}

QVariant ShapesModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || index.row() < 0)
		return QVariant{};

	if (index.row() >= static_cast<int>(shapes_->size()))
		return "None";

	const Shape* p_shape = (*shapes_)[index.row()];

	switch (role) {
	case Qt::DisplayRole:
		return QString("ID: %1; Type: %2").arg(p_shape->getID()).arg(
		SHAPE_NAMES[p_shape->getShape()]);
	default:
		return QVariant{};
	}
}

void ShapesModel::itemsChanged()
{
	this->endResetModel();
}
