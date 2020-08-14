#include "proptree.h"

#include "mainwindow.h"
#include "itembutton.h"
#include "ellipse.h"
#include "line.h"
#include "polygon.h"
#include "polyline.h"
#include "rectangle.h"
#include "text.h"

using namespace std::placeholders;

/******************************************************************************
 *
 * Shape specialization
 *
 *****************************************************************************/

PropertyItem<Shape>::PropertyItem(QTreeWidgetItem* parent, Shape& s)
	: QTreeWidgetItem(parent, PropNone),
	  name{QString("ID: %1; Type: %2").arg(s.getID()).arg(SHAPE_NAMES[s.getShape()])}
{
	new PropertyItem<QPoint>(
				this,
				"Position",
				std::bind(&Shape::getPos, &s),
				[&s](QPoint p) { s.setPos(p); }
	);
	if (s.getShape() != Shape::Text) {
		new PropertyItem<QPen>(
			this,
			"Line",
			std::bind(&Shape::getPen, &s),
			std::bind(&Shape::setPen, &s, _1)
		);
	}
	if (Shape::hasfill(s.getShape())) {
		new PropertyItem<QBrush>(
			this,
			"Fill",
			std::bind(&Shape::getBrush, &s),
			std::bind(&Shape::setBrush, &s, _1)
		);
	}

#define TRY_CAST(type, var) auto* var = dynamic_cast<type*>(&s)

	if (TRY_CAST(Ellipse, ellipse)) {
		new PropertyItem<QRect>(this,
								"Ellipse",
								std::bind(&Ellipse::getRect, ellipse),
								std::bind(&Ellipse::setRect, ellipse, _1)
		);
	}
	else if (TRY_CAST(Line, line)) {
		new PropertyItem<Line>(this, *line);
	}
	else if (TRY_CAST(Polygon, poly)) {
		new PropertyItem<Polygon>(this, *poly);
	}
	else if (TRY_CAST(Polyline, poly)) {
		new PropertyItem<Polyline>(this, *poly);
	}
	else if (TRY_CAST(Rectangle, rect)) {
		new PropertyItem<QRect>(this,
								"Rectangle",
								std::bind(&Rectangle::getRect, rect),
								std::bind(&Rectangle::setRect, rect, _1)
		);
	}
	else if (TRY_CAST(Text, text)) {
		new PropertyItem<Text>(this, *text);
	}
#undef TRY_CAST

	treeWidget()->setCurrentItem(this);
}

/******************************************************************************
 *
 * Line specialization
 *
 *****************************************************************************/

PropertyItem<Line>::PropertyItem(QTreeWidgetItem* parent, Line& line)
	: QTreeWidgetItem(parent, PropNone), name{"Line"}
{
	new PropertyItem<QPoint>(
				this,
				"Start",
				std::bind(&Line::getStart, &line),
				std::bind(&Line::setStart, &line, _1)
	);
	new PropertyItem<QPoint>(
				this,
				"End",
				std::bind(&Line::getEnd, &line),
				std::bind(&Line::setEnd, &line, _1)
	);
}

/******************************************************************************
 *
 * Polygon specialization
 *
 *****************************************************************************/

PropertyItem<Polygon>::PropertyItem(QTreeWidgetItem* parent, Polygon& poly)
	: QTreeWidgetItem(parent, PropNone), name{"Polygon"}
{

	new PropertyItem<QList<QPoint>>(
				this,
				"Vertices",
				std::bind(&Polygon::getSize, &poly),
				std::bind(&Polygon::getPoint, &poly, _1),
				std::bind(&Polygon::setPoint, &poly, _1, _2),
				std::bind(&Polygon::insert, &poly, _1, _2),
				std::bind(&Polygon::erase, &poly, _1)
	);
}

/******************************************************************************
 *
 * PolyLine specialization
 *
 *****************************************************************************/

PropertyItem<Polyline>::PropertyItem(QTreeWidgetItem* parent, Polyline& poly)
	: QTreeWidgetItem(parent, PropNone), name{"PolyLine"}
{

	new PropertyItem<QList<QPoint>>(
				this,
				"Vertices",
				std::bind(&Polyline::getSize, &poly),
				std::bind(&Polyline::getPoint, &poly, _1),
				std::bind(&Polyline::setPoint, &poly, _1, _2),
				std::bind(&Polyline::insert, &poly, _1, _2),
				std::bind(&Polyline::erase, &poly, _1)
	);
}

/******************************************************************************
 *
 * Text specialization
 *
 *****************************************************************************/

PropertyItem<Text>::PropertyItem(QTreeWidgetItem* parent, Text& text)
	: QTreeWidgetItem(parent, PropNone), name{"Text"}
{
	new PropertyItem<QString>(
				this,
				"Text",
				std::bind(&Text::getText, &text),
				std::bind(&Text::setText, &text, _1),
				PropString
	);
	new PropertyItem<QString>(
				this,
				"Color",
				([&text]() { return COLOR_NAMES.key(text.getPen().color()); }),
				([&text](QString s) { QPen p = text.getPen(); p.setColor(COLOR_NAMES[s]); text.setPen(p); }),
				PropColor
	);
	new PropertyItem<QFont>(
				this,
				"Font",
				std::bind(&Text::getFont, &text),
				std::bind(&Text::setFont, &text, _1)
	);
	new PropertyItem<QRect>(
				this,
				"Box",
				std::bind(&Text::getRect, &text),
				std::bind(&Text::setRect, &text, _1)
	);
	new PropertyItem<QString>(
				this,
				"Alignment",
				([&text]() { return ALIGNMENT_TYPES[text.getAlignment()]; }),
				([&text](QString s) { text.setAlignment(ALIGNMENT_TYPES.key(s)); }),
				PropAlignment
	);
}

/******************************************************************************
 *
 * QPoint specialization
 *
 *****************************************************************************/

void Disconnect(MainWindow* window, QTreeWidget* tree)
{
	QObject::disconnect(window, &MainWindow::onCanvasClick, nullptr, nullptr);
	QObject::disconnect(tree, &QTreeWidget::currentItemChanged, nullptr, nullptr);
	window->SetDrawCursor(Qt::ArrowCursor);
	window->SetStatusBar("");
}

MainWindow* GetWindow(QTreeWidgetItem* item)
{
	auto* window = item->treeWidget()->window();
	auto* main = dynamic_cast<MainWindow*>(window);
	if (!main) {
		main = dynamic_cast<MainWindow*>(window->parent());
	}
	assert(main);
	return main;
}

PropertyItem<QPoint>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter_in)
	: QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}, setter{std::move(setter_in)}
{
	new PropertyItem<int>(
				this,
				"X",
				[this]() -> int { return getter().x(); },
				[this](int x) { setter(QPoint{x, getter().y()}); }
	);
	new PropertyItem<int>(
				this,
				"Y",
				[this]() -> int { return getter().y(); },
				[this](int y) { setter(QPoint{getter().x(), y}); }
	);

	auto* window = GetWindow(this);

	auto* buttonWidget = new ItemButton({{QIcon{":/icons/target.png"}, "Set position with mouse"}});
	QObject::connect(buttonWidget, &ItemButton::clicked, [this, window]() {
		treeWidget()->setCurrentItem(this);
		// Set pointer
		window->SetDrawCursor(Qt::CrossCursor);
		window->SetStatusBar("Click to set position");
		// Set setter
		QObject::connect(window, &MainWindow::onCanvasClick, [this, window](int x, int y) {
			setter(QPoint{x, y});
			emitDataChanged();
			// Unset setter
			Disconnect(window, treeWidget());
		});
		QObject::connect(treeWidget(), &QTreeWidget::currentItemChanged, std::bind(&Disconnect, window, treeWidget()));
	});
	treeWidget()->setItemWidget(this, 1, buttonWidget);
}

QVariant PropertyItem<QPoint>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		else {
			QPoint p = getter();
			return QString{"(%1, %2)"}.arg(p.x()).arg(p.y());
		}
	}

	return QVariant{};
}

/******************************************************************************
 *
 * QPoint list specialization
 *
 *****************************************************************************/

PropertyItem<QList<QPoint>>::PropertyItem(QTreeWidgetItem* parent, QString name, get_size_t get_size_in, get_item_t get_item_in, set_item_t set_item_in, insert_t insert_in, erase_t erase_in)
	: QTreeWidgetItem(parent, PropNone),
	  name{std::move(name)},
	  get_size{std::move(get_size_in)},
	  get_item{std::move(get_item_in)},
	  set_item{std::move(set_item_in)},
	  insert{std::move(insert_in)},
	  erase{std::move(erase_in)}
{
	size_t i = 0, count = get_size();
	for (; i < count; ++i) {
		new PropertyItem<QPoint>(
					this,
					QString{"[%1]"}.arg(i),
					std::bind(get_item, i),
					std::bind(set_item, i, std::placeholders::_1)
		);
	}

	auto* buttons = new ItemButton{{
			{QIcon{":/icons/add.png"}, "Begin appending points"},
			{QIcon{":/icons/remove.png"}, "Remove last point"}
	}};

	buttons->button(1)->setEnabled(count != 0);
	QObject::connect(buttons, &ItemButton::clicked, [this](int i) {
		switch (i) {
		case 0: add(); break;
		case 1: remove(); break;
		}
	});
	treeWidget()->setItemWidget(this, 1, buttons);
}

void PropertyItem<QList<QPoint>>::add()
{
	auto* window = GetWindow(this);
	treeWidget()->setCurrentItem(this);

	// Set pointer
	window->SetDrawCursor(Qt::CrossCursor);
	window->SetStatusBar("Click to add points");

	// Set setter
	QObject::connect(window, &MainWindow::onCanvasClick, [this](int x, int y) {
		size_t i = get_size();
		insert(i, QPoint{x, y});
		auto* prop = new PropertyItem<QPoint>(
					this,
					QString{"[%1]"}.arg(i),
					std::bind(get_item, i),
					std::bind(set_item, i, _1)
		);
		treeWidget()->expandItem(prop);
		emitDataChanged();
		dynamic_cast<ItemButton*>(treeWidget()->itemWidget(this, 1))->button(1)->setEnabled(true);
	});
	QObject::connect(treeWidget(), &QTreeWidget::currentItemChanged, std::bind(&Disconnect, window, treeWidget()));
}

void PropertyItem<QList<QPoint>>::remove()
{
	auto* window = GetWindow(this);

	Disconnect(window, treeWidget());

	size_t i = get_size() - 1;
	erase(i);
	removeChild(child(static_cast<int>(i)));
	dynamic_cast<ItemButton*>(treeWidget()->itemWidget(this, 1))->button(1)->setEnabled(i != 0);
	emitDataChanged();
}

QVariant PropertyItem<QList<QPoint>>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		else {
			return QString{"Size: %1"}.arg(get_size());
		}
	}

	return QVariant{};
}

/******************************************************************************
 *
 * QRect specialization
 *
 *****************************************************************************/

PropertyItem<QRect>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter_in)
	: QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}, setter{std::move(setter_in)}
{
	new PropertyItem<int>(
				this,
				"X",
				[this]() -> int { return getter().left(); },
				[this](int x) { auto v = getter(); v.moveLeft(x); setter(v); }
	);
	new PropertyItem<int>(
				this,
				"Y",
				[this]() -> int { return getter().top(); },
				[this](int x) { auto v = getter(); v.moveTop(x); setter(v); }
	);
	new PropertyItem<int>(
				this,
				"Width",
				[this]() -> int { return getter().width(); },
				[this](int x) { auto v = getter(); v.setWidth(x); setter(v); }
	);
	new PropertyItem<int>(
				this,
				"Height",
				[this]() -> int { return getter().height(); },
				[this](int x) { auto v = getter(); v.setHeight(x); setter(v); }
	);

	auto* window = GetWindow(this);

	auto* buttons = new ItemButton{{
			{QIcon{":/icons/corner.png"}, "Move the upper-left corner with the mouse (size stays the same)"},
			{QIcon{":/icons/size.png"}, "Set the bottom-right corner with the mouse (changes size)"}
	}};
	QObject::connect(buttons, &ItemButton::clicked, [this, window](int i) {
		window->SetDrawCursor(Qt::CrossCursor);
		switch (i) {
		case 0:
			treeWidget()->setCurrentItem(this->child(0));
			// Set pointer
			window->SetStatusBar("Click to move the top-left corner");
			// Set setter
			QObject::connect(window, &MainWindow::onCanvasClick, [this, window](int x, int y) {
				QRect r = getter();
				r.moveTopLeft(QPoint{x, y});
				setter(r);
				emitDataChanged();
				// Unset setter
				Disconnect(window, treeWidget());
			});
			break;
		case 1:
			treeWidget()->setCurrentItem(this->child(2));
			// Set pointer
			window->SetStatusBar("Click to set the bottom-right corner");
			// Set setter
			QObject::connect(window, &MainWindow::onCanvasClick, [this, window](int x, int y) {
				QRect r = getter();
				r.setBottomRight(QPoint{x, y});
				setter(r.normalized());
				emitDataChanged();
				// Unset setter
				Disconnect(window, treeWidget());
			});
		}
		QObject::connect(treeWidget(), &QTreeWidget::currentItemChanged, std::bind(&Disconnect, window, treeWidget()));
	});
	treeWidget()->setItemWidget(this, 1, buttons);
}

QVariant PropertyItem<QRect>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		else {
			QRect r = getter();
			return QString{"[(%1, %2), %3x%4]"}.arg(r.x()).arg(r.y()).arg(r.width()).arg(r.height());
		}
	}

	return QVariant{};
}

/******************************************************************************
 *
 * QPen specialization
 *
 *****************************************************************************/

PropertyItem<QPen>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter_in)
	: QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}, setter{std::move(setter_in)}
{
	new PropertyItem<int>(
				this,
				"Width",
				[this]() { return getter().width(); },
				[this](int w) { auto v = getter(); v.setWidth(w); setter(v); }
	);
	new PropertyItem<QString>(
				this,
				"Color",
				[this]() { return COLOR_NAMES.key(getter().color()); },
				[this](QString s) { auto v = getter(); v.setColor(COLOR_NAMES[s]); setter(v); },
				PropColor
	);
	new PropertyItem<QString>(
				this,
				"Style",
				[this]() { return STYLE_NAMES[getter().style()]; },
				[this](QString s) { auto v = getter(); v.setStyle(STYLE_NAMES.key(s)); setter(v); },
				PropPenStyle
	);
	new PropertyItem<QString>(
				this,
				"Cap Style",
				[this]() { return CAP_NAMES[getter().capStyle()]; },
				[this](QString s) { auto v = getter(); v.setCapStyle(CAP_NAMES.key(s)); setter(v); },
				PropPenCapStyle
	);
	new PropertyItem<QString>(
				this,
				"Join Style",
				[this]() { return JOIN_NAMES[getter().joinStyle()]; },
				[this](QString s) { auto v = getter(); v.setJoinStyle(JOIN_NAMES.key(s)); setter(v); },
				PropPenJoinStyle
	);
}

QVariant PropertyItem<QPen>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		break;
	}

	return QVariant{};
}

/******************************************************************************
 *
 * QBrush specialization
 *
 *****************************************************************************/

PropertyItem<QBrush>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter_in)
	: QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}, setter{std::move(setter_in)}
{
	new PropertyItem<QString>(
				this,
				"Color",
				[this]() { return COLOR_NAMES.key(getter().color()); },
				[this](QString s) { auto v = getter(); v.setColor(COLOR_NAMES[s]); setter(v); },
				PropColor
	);
	new PropertyItem<QString>(
				this,
				"Style",
				[this]() { return BSTYLE_NAMES[getter().style()]; },
				[this](QString s) { auto v = getter(); v.setStyle(BSTYLE_NAMES.key(s)); setter(v); },
				PropBrushStyle
	);
}

QVariant PropertyItem<QBrush>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		break;
	}

	return QVariant{};
}

/******************************************************************************
 *
 * QFont specialization
 *
 *****************************************************************************/

PropertyItem<QFont>::PropertyItem(QTreeWidgetItem* parent, QString name, getter_t getter_in, setter_t setter_in)
	: QTreeWidgetItem(parent, PropNone), name{std::move(name)}, getter{std::move(getter_in)}, setter{std::move(setter_in)}
{
	new PropertyItem<QString>(
				this,
				"Family",
				([this]() { return getter().family(); }),
				([this](QString s) { QFont f = getter(); f.setFamily(s); setter(f); }),
				PropFont
	);
	new PropertyItem<int>(
				this,
				"Size",
				([this]() { return getter().pointSize(); }),
				([this](int s) { QFont f = getter(); f.setPointSize(s); setter(f); }),
				PropFontSize
	);
	new PropertyItem<QString>(
				this,
				"Style",
				([this]() { return FONT_STYLES[getter().style()]; }),
				([this](QString s) { QFont f = getter(); f.setStyle(FONT_STYLES.key(s)); setter(f); }),
				PropFontStyle
	);
	new PropertyItem<QString>(
				this,
				"Weight",
				([this]() { return FONT_WEIGHTS[static_cast<QFont::Weight>(getter().weight())]; }),
				([this](QString s) { QFont f = getter(); f.setWeight(FONT_WEIGHTS.key(s)); setter(f); }),
				PropFontWeight
	);
}

QVariant PropertyItem<QFont>::data(int column, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (column == 0) {
			return name;
		}
		break;
	}

	return QVariant{};
}

