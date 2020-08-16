#include <QApplication>
#include "mainwindow.h"

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
#include "vector.h"

using namespace std;

int main() {
	cs1c::vector<int> v(10);
	for (int i = 0; i < (int) v.size(); i++)
		v[i] = i;

	for (auto a: v)
		cout << a << ' ';
	cout << "\n\n";
	for (auto rev = v.rbegin(); rev != v.rend(); rev++) {
		cout << *rev << " ";
	}
	cout << '\n';
	return 0;
}
#endif
