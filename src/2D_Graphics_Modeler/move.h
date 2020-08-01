#ifndef MOVE_H
#define MOVE_H

#include <QDialog>

namespace Ui {
class Move;
}

/*!
* \class Move
* \brief This class represents the Move dialog. It passes a signal to mainwindow's Move_Signal_Handler().
*/
class Move : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief move the shape
     * \param number of shapes
     * \param parent of the dialog
     */
    explicit Move(int numShapes, QWidget *parent = nullptr);

    /*!
     * \brief deallocates any allocated memory
     */
    ~Move();

signals:
    /*!
     * \brief sends a signal to the Move_Signal_Handler in mainWindow
     * \param ID of the shape to move
     * \param new x-coord of the starting point of the shape
     * \param new y-coord of the starting point of the shape
     */
    void Move_Signal(int ID, int x_coord, int y_coord);

private slots:
    /*!
     * \brief function that runs when the cancel button is clicked
     */
    void on_pushButton_cancel_clicked();

    /*!
     * \brief function that runs when the ok button is clicked
     */
    void on_pushButton_ok_clicked();

private:
    Ui::Move *ui;
    int shapeCount;
};

#endif // MOVE_H
