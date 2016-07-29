#include "myclass.h"
#include <iostream>
using namespace std;
enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDS { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const char* title = "OpenGL";
const GLuint NumVertices = 6;
MyClass::MyClass(QGLWidget *parent)
	: QGLWidget(parent)
{
	ui.setupUi(this);
}

MyClass::~MyClass()
{

}

void MyClass::initializeGL()
{
	if(glewInit())
	{
		cout << "Unable to init GLEW.... exiting" <<endl;
		exit(EXIT_FAILURE);
	}
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	GLfloat vertices[NumVertices][2] = {
		{-0.9,-0.9},
		{0.8,-0.9},
		{-0.9,0.8},
		{0.9,-0.8},
		{0.9,0.9},
		{-0.8,0.9},
	};

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER,"triangle.vert" },
		{ GL_FRAGMENT_SHADER,"triangle.frag" },
		{ GL_NONE,NULL }
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
}
void MyClass::paintGL()
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 0.3f, 0.3f, 0.0f);
	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES,0, NumVertices);
	glFlush();
}
void MyClass::resizeGL(int w,int h)
{
	if(0 == h)
		h =1 ;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
