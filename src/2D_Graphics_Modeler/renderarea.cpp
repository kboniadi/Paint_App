#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    //sets the background to white
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    //parse shapes.txt
    //assign it to a variable
    //assignShapeID
    //update();
	shapes_list = textParse();
    update();
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

QSize RenderArea::minimumSizeHint() const
{
	return QSize(1200, 700);
}

//can comment out "event" to compile
void RenderArea::paintEvent(QPaintEvent */*event*/)
{
    //initialize variables for specific shapes
    //e.g. QPoints for a polygon

	for (auto it = shapes_list.begin(); it != shapes_list.end(); ++it) {
		(*it)->draw(this);
    }
	update();
	//save
    //restore


}

RenderArea::~RenderArea()
{
    //save shapes
    //delete shapes in vector

	for (auto it = shapes_list.begin(); it != shapes_list.end(); ++it) {
        delete (*it);
    }
}

void RenderArea::addShape(Shape *shape)
{
	shapes_list.push_back(shape);
    update();
}

void RenderArea::deleteShape(int ID)
{
	if (static_cast<size_t>(ID) > shapes_list.size()) {
		QMessageBox::warning(this, "Errors",
		"That ID is out of range!");
		return;
	}
	shapes_list.erase(shapes_list.begin() + (ID - 1));
	update();
}

void RenderArea::moveShape(int ID, int x_coord, int y_coord)
{
	for (auto it = shapes_list.begin(); it != shapes_list.end(); it++)
    {
		if ((*it)->getID() == (id_t) ID)
        {
			(*it)->move(x_coord, y_coord);
            break;
        }
    }
    update();
}

