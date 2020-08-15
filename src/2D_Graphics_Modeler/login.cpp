#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Login)
{
	ui->setupUi(this);
}

Login::~Login()
{
	delete ui;
}

void Login::on_pushButton_ok_clicked()
{

	QString username = ui->lineEdit_username->text();
	QString password = ui->lineEdit_password->text();

	if (username == "admin" && password == "password")
		accept();
	else
		QMessageBox::warning(this, "Login",
		"The username or password you entered is incorrect.");
}
