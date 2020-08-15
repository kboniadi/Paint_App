#ifndef SHAPESMODEL_H
#define SHAPESMODEL_H

#include <QAbstractListModel>
#include "shape.h"
#include "vector.h"

class ShapesModel: public QAbstractListModel {
	Q_OBJECT;
public:
	ShapesModel(cs1c::vector<Shape*>*);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
public slots:
	void itemsChanged();
private:
	const cs1c::vector<Shape*> *shapes_;
};

#endif // SHAPESMODEL_H
