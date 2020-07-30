#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class About;
}

/*!
 * @class About
 * @brief The About class inherits QDialog. It manages 1 attribute: ui
 */
class About : public QDialog
{
    Q_OBJECT

public:
    /*!
     * @brief About constructor with one parameter
     * @param parent (QWidget*) default value set to nullptr
     */
    explicit About(QWidget *parent = nullptr);

    /*!
     * @brief About destructor deallocated memory
     */
    ~About();

private:
    Ui::About *ui;
};

#endif // ABOUT_H
