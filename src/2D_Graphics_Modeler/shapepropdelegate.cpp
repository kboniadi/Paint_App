#include "shapepropdelegate.h"
#include "proptree.h"
#include "fontsizecombobox.h"
#include <QComboBox>
#include <QFontComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QTreeWidget>
#include "shape.h"
#include "text.h"

ShapePropDelegate::ShapePropDelegate(QObject *parent)
	: QStyledItemDelegate{parent}
{
	connect(this, &ShapePropDelegate::valueChanged, this, &ShapePropDelegate::commitData);
}

QWidget* createComboBox(QWidget* parent, const QStringList &source) {
	QComboBox* editor = new QComboBox{parent};
	editor->insertItems(0, source);
	editor->setEditable(false);
	return editor;
}

QWidget *ShapePropDelegate::createEditor(QWidget *parent,
	const QStyleOptionViewItem &, const QModelIndex &index) const
{
	if (index.column() == 0)
		return nullptr;

	auto *tree = dynamic_cast<QTreeWidget*>(parent->parent());
	auto *item = tree->currentItem();

	int type = item->type();

	switch (type) {
	case PropInt: {
		auto *editor = new QSpinBox(parent);
		editor->setFrame(false);
		editor->setRange(0, 2000);
		return editor;
	}
	case PropString: {
		auto* editor = new QLineEdit(parent);
		return editor;
	}
	case PropAlignment:
		return createComboBox(parent, ALIGNMENT_TYPES.values());
	case PropBrushStyle:
		return createComboBox(parent, BSTYLE_NAMES.values());
	case PropColor:
		return createComboBox(parent, COLOR_NAMES.keys());
	case PropFont:
		return new QFontComboBox{parent};
	case PropFontSize:
		return new FontSizeComboBox{parent};
	case PropFontStyle:
		return createComboBox(parent, FONT_STYLES.values());
	case PropFontWeight:
		return createComboBox(parent, FONT_WEIGHTS.values());
	case PropPenStyle:
		return createComboBox(parent, STYLE_NAMES.values());
	case PropPenCapStyle:
		return createComboBox(parent, CAP_NAMES.values());
	case PropPenJoinStyle:
		return createComboBox(parent, JOIN_NAMES.values());
	}

	return nullptr;
}

#define TRY_CAST(type, var) auto *var = dynamic_cast<type*>(editor)

void ShapePropDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (TRY_CAST(QFontComboBox, fontBox)) {
		QString value = index.model()->data(index, Qt::EditRole).toString();

		fontBox->setCurrentFont(QFont{value});
		connect(fontBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, std::bind(&ShapePropDelegate::valueChanged, this, editor));
	}
	else if (TRY_CAST(QComboBox, comboBox)) {
		QString value = index.model()->data(index, Qt::EditRole).toString();

		comboBox->setCurrentText(value);
		connect(comboBox, &QComboBox::currentTextChanged, this, std::bind(&ShapePropDelegate::valueChanged, this, editor));
	}
	else if (TRY_CAST(QSpinBox, spinBox)) {
		int value = index.model()->data(index, Qt::EditRole).toInt();

		spinBox->setValue(value);
		connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, std::bind(&ShapePropDelegate::valueChanged, this, editor));
	}
	else if (TRY_CAST(QLineEdit, line)) {
		QString value = index.model()->data(index, Qt::EditRole).toString();

		line->setText(value);
		connect(line, &QLineEdit::textChanged, this, std::bind(&ShapePropDelegate::valueChanged, this, editor));
	}
}

void ShapePropDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	if (TRY_CAST(FontSizeComboBox, sizeBox)) {
		int value = sizeBox->value();

		model->setData(index, value, Qt::EditRole);
	}
	if (TRY_CAST(QComboBox, comboBox)) {
		QString value = comboBox->currentText();

		model->setData(index, value, Qt::EditRole);
	}
	else if (TRY_CAST(QSpinBox, spinBox)) {
		spinBox->interpretText();
		int value = spinBox->value();

		model->setData(index, value, Qt::EditRole);
	}
	else if (TRY_CAST(QLineEdit, line)) {
		QString value = line->text();

		model->setData(index, value, Qt::EditRole);
	}

}

#undef TRY_CAST
void ShapePropDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}

