#ifndef BSD_H
#define BSD_H
#include "LoadShaders.h"
#include <QtWidgets/QWidget>
#include "ui_bsd.h"
#include <qgl.h>

class Bsd : public QGLWidget
{
	Q_OBJECT

public:
	Bsd(QGLWidget *parent = 0);
	~Bsd();
	void initializeGL();
	void paintGL();
	void resizeGL(int w,int h);
private:
	Ui::BsdClass ui;
};

#endif // BSD_H
