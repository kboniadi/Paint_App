#include "text.h"
#include <QMap>

const QMap<Qt::AlignmentFlag, QString> ALIGNMENT_TYPES {
	{Qt::AlignLeft, "AlignLeft"},
	{Qt::AlignRight, "AlignRight"},
	{Qt::AlignTop, "AlignTop"},
	{Qt::AlignBottom, "AlignBottom"},
	{Qt::AlignCenter, "AlignCenter"}
};

const QMap<QFont::Style, QString> FONT_STYLES {
	{QFont::StyleNormal,"StyleNormal"},
	{QFont::StyleItalic, "StyleItalic"},
	{QFont::StyleOblique, "StyleOblique"}
};

const QMap<QFont::Weight, QString> FONT_WEIGHTS {
	{QFont::Thin, "Thin"},
	{QFont::Light, "Light"},
	{QFont::Normal, "Normal"},
	{QFont::Bold, "Bold"}
};

Text::Text(Text &&other) noexcept: Shape{(id_t) -1}
{
	swap(other);
	std::swap(font, other.font);
	std::swap(text, other.text);
	std::swap(alignment, other.alignment);
	std::swap(width, other.width);
	std::swap(height, other.height);
}

Text &Text::operator=(Text &&other) noexcept
{
	Text temp{std::move(other)};
	swap(temp);
	std::swap(font, other.font);
	std::swap(text, other.text);
	std::swap(alignment, other.alignment);
	std::swap(width, other.width);
	std::swap(height, other.height);
	return *this;
}

void Text::setRect(const QRect &rect)
{
	setPosition(rect.center());
	width = rect.width();
	height = rect.height();
}

QRect Text::getRect() const
{
	QFontMetrics fontdeets{font};
	QSize size{(width < 0) ? (int)(fontdeets.horizontalAdvance(text) * 1.1): width,
	(height < 0) ? (int)(fontdeets.height() * 1.1): height};

	QRect rect{QPoint{}, size};
	rect.moveCenter(getPosition());
	return rect;
}

void Text::draw(QPaintDevice *device)
{
	getPainter().begin(device);
	getPainter().setPen(getPen());
	getPainter().setFont(getFont());

	QRect rect = getRect();
	rect.moveCenter(QPoint{});

	getPainter().drawText(rect, alignment, text);
	getPainter().end();
}
