#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QPainter>
#include <QPainterPath>
#include <QMessageBox>
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include "shape.h"
#include "vector.h"
#include "textparse.h"
#include "text.h"

/*!
 * @class RenderArea
 * @brief RenderArea class represents the canvas. Inherits QWidget
 * and manages 1 attribute: shapes_list (vector of shape pointers)
 */
class RenderArea : public QWidget
{
public:
    /*!
     * @brief Constructor with default parameter set to nullptr
     * @param parent (QWidget*)
     */
	RenderArea(QWidget *parent = nullptr);

    //!@ smallest size the render area window can be
    QSize minimumSizeHint() const override;

    //!@ size of render area when it opens
    QSize sizeHint() const override;

    /*!
     * @brief Destructor deallocates memory
     */
    ~RenderArea();

    /*!
     * \brief Add a shape to shapes_list vector and invoke update()
     * \param shape (Shape*) pointer that is added to the vector
     */
    void addShape(Shape *shape);

    /*!
     * \brief Remove a shape from shapes_list vector and invoke update()
     * \param ID of the shape
     */
	void deleteShape(int ID);

    /*!
     * \brief move a shape
     * \param ID of the shape
     * \param x_coord of the point to move to
     * \param y_coord of the point to move to
     */
    void moveShape(int ID, int x_coord, int y_coord);

	/*!
	 * @brief getter for shapes_list vector
	 * @return (vector<Shape*>) vector of Shape pointers
	 */
	cs1c::vector<Shape*> getShapes() {return shapes_list;}

	/*!
	 * @brief getter for the size of the vector shape_list
	 * @return (size_t) unsigned int value in compliance with vector class
	 */
	size_t getVectLength() {return shapes_list.size();}

protected:
    /*!
     * @brief paintEvent is called when repaint() or update() are invoked.
     * Calls Draw function for all shapes in shapes_list and updates canvas.
     * @param event (QPaintEvent*) unused parameter. Necessary for override.
     */
    void paintEvent(QPaintEvent *event) override;
private:
    //member variables
	cs1c::vector<Shape*> shapes_list;
};

#endif // RENDERAREA_H
