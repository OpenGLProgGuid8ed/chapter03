#include "instancedrender.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	InstancedRender w;
	w.show();
	return a.exec();
}
