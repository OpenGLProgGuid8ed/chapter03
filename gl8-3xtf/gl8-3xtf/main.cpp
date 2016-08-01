#include "xtb.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	xtb w;
	w.show();
	return a.exec();
}
