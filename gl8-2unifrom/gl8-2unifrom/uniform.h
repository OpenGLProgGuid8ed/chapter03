#ifndef UNIFORM_H
#define UNIFORM_H

#include "LoadShaders.h"
#include <QtWidgets/QWidget>
#include "ui_uniform.h"
#include <QtOpenGL\qgl.h>

class uniform : public QGLWidget
{
	Q_OBJECT

public:
	uniform(QGLWidget *parent = 0);
	~uniform();
	void initializeGL();
	void paintGL();
	void resizeGL(int w,int h);
private:
	Ui::uniformClass ui;
};

#endif // UNIFORM_H
