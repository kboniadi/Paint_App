#include "move.h"
#include "ui_move.h"
#include <QMessageBox>

Move::Move(int numShapes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Move)
{
    ui->setupUi(this);
    shapeCount = numShapes;
	ui->spinBox_x_coordinate->setMaximum(2000);
	ui->spinBox_y_coordinate->setMaximum(1000);
}

Move::~Move()
{
    delete ui;
}

void Move::on_pushButton_cancel_clicked()
{
    close();
}


void Move::on_pushButton_ok_clicked()
{

    QString shapeID = ui->lineEdit_shapeID->text();
    int x_coord = ui->spinBox_x_coordinate->value();
    int y_coord = ui->spinBox_y_coordinate->value();

    if (shapeID.toInt() > 0)
    {
        accept();
        emit Move_Signal(shapeID.toInt(), x_coord, y_coord);
    }else
        QMessageBox::warning(this, "Move",
        "The shape ID you entered does not exist.");
}
