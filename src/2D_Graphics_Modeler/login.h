#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

/*!
 * @class Login
 * \brief The Login class derived from QDialog. Manages 1 attribute:
 * ui.
 */
class Login : public QDialog
{
	Q_OBJECT

public:
	/*!
	 * @brief Login constructor with default value set to nullptr
	 * @param parent (QWidget*)
	 */
	explicit Login(QWidget *parent = nullptr);

	/*!
	 * @brief Login destructor. Free's alocated memory.
	 */
	~Login();

private slots:
	/*!
	 * \brief on_pushButton_ok_clicked is a slot that is linked to the
	 * login "ok" push button signal.
	 */
	void on_pushButton_ok_clicked();

private:
	Ui::Login *ui;
};

#endif // LOGIN_H
