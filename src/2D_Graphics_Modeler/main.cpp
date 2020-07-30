#include "mainwindow.h"
#include <QApplication>
#include "login.h"
#include "vector.h"
#include "textparse.h"

//#define TEST

#ifndef TEST
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	  MainWindow w;
	  w.show();
  
    return a.exec();
}
#else
#include <iostream>
using namespace std;

int main() {

	return 0;
}
#endif
