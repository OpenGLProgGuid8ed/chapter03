#ifndef XTB_H
#define XTB_H

#include <QtWidgets/QWidget>
#include "ui_xtb.h"
#include "Loadshaders.h"
#include "vmath.h"
#include "vbm.h"
#include <qgl.h>

class xtb : public QGLWidget
{
	Q_OBJECT

public:
	xtb(QGLWidget *parent = 0);
	~xtb();
	void initializeGL();
	void paintGL();
	void resizeGL(int w,int h);
	void timerEvent(QTimerEvent *);

private:
	Ui::xtbClass ui;
	// Member variables
    float aspect;
    GLuint update_prog;
    GLuint vao[2];
    GLuint vbo[2];
    GLuint xfb;

    GLuint render_prog;
    GLuint geometry_vbo;
    GLuint render_vao;
    GLint render_model_matrix_loc;
    GLint render_projection_matrix_loc;

    GLuint geometry_tex;

    GLuint geometry_xfb;
    GLuint particle_xfb;

    GLint model_matrix_loc;
    GLint projection_matrix_loc;
    GLint triangle_count_loc;
    GLint time_step_loc;

    VBObject object;
};

#endif // XTB_H
