#include "uniform.h"
#include <iostream>
using namespace std;
#include<cstring>
size_t TypeSize(GLenum type)
{
	size_t size;
   #define CASE(Enum ,Count,Type) \
   case Enum : size = Count * sizeof(Type);break

	switch (type)
	{
		CASE(GL_FLOAT,						1,	GLfloat);
		CASE(GL_FLOAT_VEC2,				2,	GLfloat);
		CASE(GL_FLOAT_VEC3,				3,	GLfloat);
		CASE(GL_FLOAT_VEC4,				4,	GLfloat);
		CASE(GL_INT,							1,	GLint);
		CASE(GL_INT_VEC2,					2,	GLint);
		CASE(GL_INT_VEC3,					3,	GLint);
		CASE(GL_INT_VEC4,					4,	GLint);
		CASE(GL_UNSIGNED_INT,			1,	GLuint);
		CASE(GL_UNSIGNED_INT_VEC2,	2,	GLuint);
		CASE(GL_UNSIGNED_INT_VEC3,	3,	GLuint);
		CASE(GL_UNSIGNED_INT_VEC4,	4,	GLuint);
		CASE(GL_BOOL,							1,	GLboolean);
		CASE(GL_BOOL_VEC2,				2,	GLboolean);
		CASE(GL_BOOL_VEC3,				3,	GLboolean);
		CASE(GL_BOOL_VEC4,				4,	GLboolean);
		CASE(GL_FLOAT_MAT2x3,			6,	GLfloat);
		CASE(GL_FLOAT_MAT2x4,			8,	GLfloat);
		CASE(GL_FLOAT_MAT3x2,			6,	GLfloat);
		CASE(GL_FLOAT_MAT3,				9,	GLfloat);
		CASE(GL_FLOAT_MAT3x4,			12	,GLfloat);
		CASE(GL_FLOAT_MAT4x2,			8,	GLfloat);
		CASE(GL_FLOAT_MAT4x3,			12,	GLfloat);
		CASE(GL_FLOAT_MAT4,				16,	GLfloat);
		#undef CASE
	default:
		cout << "Unknown type "<<endl;
		exit(EXIT_FAILURE);
		break;
	}
	return size;
}

uniform::uniform(QGLWidget *parent)
	: QGLWidget(parent)
{
	ui.setupUi(this);
}

uniform::~uniform()
{

}

void uniform::initializeGL()
{
	if(glewInit())
	{
		cout<<"Unale to Init GLEW" <<endl;
		exit(EXIT_FAILURE);
	}
	glClearColor(1,0,0,1);
	ShaderInfo shaders[] ={
		{GL_VERTEX_SHADER,"vShader.vert"},
		{GL_FRAGMENT_SHADER,"fShader.frag"},
		{GL_NONE,NULL}
	};
	GLint progma = LoadShaders(shaders);
	glUseProgram(progma);
	//变量
	GLuint uboIndex;
	GLint uboSize;
	GLuint ubo;
	GLvoid *buffer;
	
	//查找并判断块大小
	uboIndex  = glGetUniformBlockIndex(progma,"Uniforms");
	glGetActiveUniformBlockiv(progma,uboIndex,
		GL_UNIFORM_BLOCK_DATA_SIZE,&uboSize);
	buffer = malloc(uboSize);
	if (buffer == NULL)
	{
		cout <<"Unable to allocate buffer"<<endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		enum 
		{
			Translation,Scale,Rotation,Enabled,NumUniforms
		};
		GLfloat scale = 0.5;
		GLfloat translation[] = {0.1,0.1,0.0};
		GLfloat rotation[] = {90,0.0,0.0,1.0};
		GLboolean enabled = GL_TRUE;
		const char* names[NumUniforms] = {
			"translation","scale","rotation","enabled"
		};
		GLuint indices[NumUniforms];
		GLint size[NumUniforms];
		GLint offset[NumUniforms];
		GLint type[NumUniforms];
		//向数据缓存中写数据
		glGetUniformIndices(progma,NumUniforms,names,indices);
		glGetActiveUniformsiv(progma,NumUniforms,indices,GL_UNIFORM_OFFSET,offset);
		glGetActiveUniformsiv(progma,NumUniforms,indices,GL_UNIFORM_SIZE,size);
		glGetActiveUniformsiv(progma,NumUniforms,indices,GL_UNIFORM_TYPE,type);
		//将uniform数据拷贝入缓存
		memcpy(&buffer +offset[Scale],&scale,size[Scale] * TypeSize(type[Scale]));
		memcpy(&buffer +offset[Translation],&translation,size[Translation]*TypeSize(type[Translation]));
		memcpy(&buffer +offset[Rotation],&rotation,size[Rotation]*TypeSize(type[Rotation]));
		memcpy(&buffer +offset[Enabled],&enabled,size[Enabled]*TypeSize(type[Enabled]));

		glGenBuffers(1,&ubo);
		glBindBuffer(GL_UNIFORM_BUFFER,ubo);
		glBufferData(GL_UNIFORM_BUFFER,uboSize,buffer,GL_STATIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER,uboIndex,ubo);
	}
}

void uniform::paintGL()
{
	
	glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 0.3f, 0.3f, 0.0f);
	//glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES,0, 4);
	glFlush();
}

void uniform::resizeGL(int w,int h)
{
	if(0 == h)
		h =1 ;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
