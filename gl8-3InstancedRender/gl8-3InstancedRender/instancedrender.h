#ifndef INSTANCEDRENDER_H
#define INSTANCEDRENDER_H

#include <QtWidgets/QWidget>
#include "ui_instancedrender.h"
#include "LoadShaders.h"
#include "vbm.h"
#include "vmath.h"
#include <qgl.h>
class InstancedRender : public QGLWidget
{
	Q_OBJECT

public:
	InstancedRender(QGLWidget *parent = 0);
	~InstancedRender();
	void initializeGL();
	void paintGL();
	void resizeGL(int w,int h);
private:
	Ui::InstancedRenderClass ui;
	// Member variables
    float aspect;
    GLuint color_buffer;
    GLuint model_matrix_buffer;
    GLuint color_tbo;
    GLuint model_matrix_tbo;
    GLuint render_prog;
    GLint view_matrix_loc;
    GLint projection_matrix_loc;
    VBObject object;
};

#endif // INSTANCEDRENDER_H
