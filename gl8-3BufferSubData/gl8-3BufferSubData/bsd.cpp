#include "bsd.h"
#include <iostream>
using namespace std;
enum VAO_IDs { Triangles, NumVAOs };
GLuint VAOs[NumVAOs];
static const GLfloat position[] =
{
	-0.5,-0.5,0.0,1.0,
	0.5,-0.5,0.0,1.0,
	0.5,0.5,0.0,1.0,
	-0.5,0.5,0.0,1.0,
};

static const GLfloat colors[] = 
{
	1.0,0.0,0.0,1.0,
	0.0,1.0,0.0,1.0,
	0.0,0.0,1.0,1.0,
	1.0,1.0,1.0,1.0,
};

Bsd::Bsd(QGLWidget *parent)
	: QGLWidget(parent)
{
	ui.setupUi(this);
}

Bsd::~Bsd()
{

}

void Bsd::initializeGL()
{
	if(glewInit())
	{
		cout << "Unable to init GLEW.... exiting" <<endl;
		exit(EXIT_FAILURE);
	}
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER,"triangle.vert" },
		{ GL_FRAGMENT_SHADER,"triangle.frag" },
		{ GL_NONE,NULL }
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
	GLuint buffer[2];
	glGenBuffers(2,buffer);
	glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(position),position,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,buffer[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_STATIC_DRAW);
	glGenVertexArrays(1,VAOs);  
	glBindVertexArray(VAOs[0]); 
    glEnableVertexAttribArray(0);//顶点坐标  
    glEnableVertexAttribArray(1);//顶点颜色  
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);  
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);  
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void Bsd::paintGL()
{
	
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.3f, 0.3f, 0.0f);
	glBindVertexArray(VAOs[0]);
	glDrawArrays(GL_TRIANGLE_FAN,0, 4);
}
void Bsd::resizeGL(int w,int h)
{
	if(0 == h)
		h =1 ;
	glViewport(0,0,w,h);
}
