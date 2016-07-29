#ifndef MYCLASS_H
#define MYCLASS_H

#include <QtWidgets/QWidget>
#include "ui_myclass.h"
#include "LoadShaders.h"
#include <QtOpenGL/qgl.h>

class MyClass : public QGLWidget
{
	Q_OBJECT

public:
	MyClass(QGLWidget *parent = 0);
	~MyClass();
	void initializeGL();
	void paintGL();
	void resizeGL(int w,int h);
private:
	Ui::MyClassClass ui;
};

#endif // MYCLASS_H
