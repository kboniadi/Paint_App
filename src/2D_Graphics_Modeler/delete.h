#ifndef DELETE_H
#define DELETE_H

#include <QDialog>

namespace Ui {
class Delete;
}

/*!
 * @class Delete
 * @brief The Delete class inherits QDialog. It manages 3 attributes:
 * shapeCount, ID_to_Delete, and ui
 */
class Delete : public QDialog
{
    Q_OBJECT

public:
    /*!
     * @brief Delete constructor with two parameters
     * @param number of shape objects stored in the shapes_list vector
     * @param parent Qwidget*
     */
    explicit Delete(int numShapes, QWidget *parent = nullptr);

    /*!
     * @brief Destructor deallocates memory
     */
    ~Delete();

    /*!
     * @brief Holds shape ID that will be deleted. Populated by user input
     */
    int ID_to_Delete;

signals:
    /*!
     * @brief signal function sends shape ID a recepient slot function in
     * MainWindow class (MainWindow::ID_Delete_Signal_Handler(int))
     * @param ID stores the shape ID to be deleted
     */
    void ID_Delete_Signal(int ID);

private slots:
    /*!
     * @brief slot function corresponding to the "Ok" button in the delete
     * dialog window.
     */
    void on_pushButton_Ok_clicked();

    /*!
     * @brief slot function corresponding to the "Cancel" button in the delete
     * dialog window.
     */
    void on_pushButton_Cancel_clicked();

private:
    Ui::Delete *ui;
    int shapeCount;
};

#endif // DELETE_H
