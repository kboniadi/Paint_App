#ifndef RENDERAREA_H
#define RENDERAREA_H

//#include <QPainter>
//#include <QPainterPath>
//#include <QMessageBox>
//#include <QBrush>
//#include <QPen>
//#include <QPixmap>
#include <QWidget>
#include "storage.h"
#include "textparse.h"
#include <QGraphicsView>

/*!
 * @class RenderArea
 * @brief RenderArea class represents the canvas. Inherits QWidget
 * and manages 1 attribute: shapes_list (vector of shape pointers)
 */
class RenderArea : public QWidget
{
	Q_OBJECT
public:
    /*!
     * @brief Constructor with default parameter set to nullptr
     * @param parent (QWidget*)
     */
	RenderArea(QWidget *parent = nullptr);

    //!@ smallest size the render area window can be
//    QSize minimumSizeHint() const override;

    //!@ size of render area when it opens
//    QSize sizeHint() const override;

    /*!
     * @brief Destructor deallocates memory
     */

	void setStorage(cs1c::vector<Shape*>*);
    /*!
     * \brief Add a shape to shapes_list vector and invoke update()
     * \param shape (Shape*) pointer that is added to the vector
     */
    void addShape(Shape *shape);

	/*!
	 * @brief getter for shapes_list vector
	 * @return (vector<Shape*>) vector of Shape pointers
	 */
	cs1c::vector<Shape*> getShapes() {return *shapes;}

	/*!
	 * @brief getter for the size of the vector shape_list
	 * @return (size_t) unsigned int value in compliance with vector class
	 */
	size_t getVectSize() {return shapes->size();}
public slots:

	 void setSelected(int);
protected:
    /*!
     * @brief paintEvent is called when repaint() or update() are invoked.
     * Calls Draw function for all shapes in shapes_list and updates canvas.
     * @param event (QPaintEvent*) unused parameter. Necessary for override.
     */
    void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
//	void mouseReleaseEvent(QMouseEvent *event) override;
private:
	cs1c::vector<Shape*>* shapes;
	const QImage target;
	int selected;
};

#endif // RENDERAREA_H
