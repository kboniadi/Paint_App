#ifndef SHAPEPROPDELEGATE_H
#define SHAPEPROPDELEGATE_H

#include <QStyledItemDelegate>

class ShapePropDelegate : public QStyledItemDelegate {
	Q_OBJECT
public:
	ShapePropDelegate(QObject *parent = nullptr);

	QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const override;

	void setEditorData(QWidget *editor, const QModelIndex &index)
		const override;

	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const override;

	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index)
		const override;
private:
	Q_SIGNAL void valueChanged(QWidget*) const;
};

#endif // SHAPEPROPDELEGATE_H
