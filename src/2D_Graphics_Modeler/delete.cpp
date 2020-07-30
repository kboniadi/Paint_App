#include "delete.h"
#include "ui_delete.h"
#include <QMessageBox>

Delete::Delete(int numShapes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Delete)
{
    ui->setupUi(this);
    shapeCount = numShapes;
}

Delete::~Delete()
{
    delete ui;
}

void Delete::on_pushButton_Ok_clicked()
{
    QString shapeID = ui->lineEdit_shapeID->text();

    //only use this if when shapeID correlates closely to shape_list index
	if (shapeID.toInt() > 0 /*&& shapeID.toInt() <= shapeCount*/)
    {
        ID_to_Delete = shapeID.toInt();
        accept();
        emit ID_Delete_Signal(ID_to_Delete);
	}else {
		QMessageBox::warning(this, "Errors",
		"That ID is out of range!");
	}

}

void Delete::on_pushButton_Cancel_clicked()
{
    close();
}
