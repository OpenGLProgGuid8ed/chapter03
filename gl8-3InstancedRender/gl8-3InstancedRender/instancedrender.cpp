#include "instancedrender.h"
#include <iostream>
using namespace std;
using namespace vmath;
#define INSTANCE_COUNT 100
InstancedRender::InstancedRender(QGLWidget *parent)
	: QGLWidget(parent)
{
	ui.setupUi(this);
}

InstancedRender::~InstancedRender()
{

}

void InstancedRender::initializeGL()
{
	setGeometry(200,100,640,480);
	if(glewInit())
	{
		cout << "Unable to init GLEW.... exiting" <<endl;
		exit(EXIT_FAILURE);
	}
	ShaderInfo shader_Info[] = {
		{GL_VERTEX_SHADER,		"VertexShader.vert"},
		{GL_FRAGMENT_SHADER,	"FragmentShader.frag"},
		{GL_NONE,NULL}
	};
	render_prog = LoadShaders(shader_Info);
	glUseProgram(render_prog);
	 // Get the location of the projetion_matrix uniform
    view_matrix_loc = glGetUniformLocation(render_prog, "view_matrix");
    projection_matrix_loc = glGetUniformLocation(render_prog, "projection_matrix");

    // Set up the TBO samplers
    GLuint color_tbo_loc = glGetUniformLocation(render_prog, "color_tbo");
    GLuint model_matrix_tbo_loc = glGetUniformLocation(render_prog, "model_matrix_tbo");

    // Set them to the right texture unit indices
    glUniform1i(color_tbo_loc, 0);
    glUniform1i(model_matrix_tbo_loc, 1);

    // Load the object
    object.LoadFromVBM("C:/Vermilion-Book/trunk/Code/media/armadillo.vbm", 0, 1, 2);
    glGenTextures(1, &color_tbo);
    glBindTexture(GL_TEXTURE_BUFFER, color_tbo);

    // Generate the colors of the objects
    vmath::vec4 colors[INSTANCE_COUNT];
	int n;
    for (n = 0; n < INSTANCE_COUNT; n++)
    {
        float a = float(n) / 4.0f;
        float b = float(n) / 5.0f;
        float c = float(n) / 6.0f;

        colors[n][0] = 0.5f + 0.25f * (sinf(a + 1.0f) + 1.0f);
        colors[n][1] = 0.5f + 0.25f * (sinf(b + 2.0f) + 1.0f);
        colors[n][2] = 0.5f + 0.25f * (sinf(c + 3.0f) + 1.0f);
        colors[n][3] = 1.0f;
    }

    // Create the buffer, initialize it and attach it to the buffer texture
    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_TEXTURE_BUFFER, color_buffer);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, color_buffer);

    // instance.
    glGenTextures(1, &model_matrix_tbo);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_BUFFER, model_matrix_tbo);
    glGenBuffers(1, &model_matrix_buffer);
    glBindBuffer(GL_TEXTURE_BUFFER, model_matrix_buffer);
    glBufferData(GL_TEXTURE_BUFFER, INSTANCE_COUNT * sizeof(vmath::mat4), NULL, GL_DYNAMIC_DRAW);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, model_matrix_buffer);
    glActiveTexture(GL_TEXTURE0);
}

void InstancedRender::paintGL()
{
	float t = float(GetTickCount() & 0x3FFF) / float(0x3FFF);
    int n;

    // Set model matrices for each instance
    mat4 matrices[INSTANCE_COUNT];

    for (n = 0; n < INSTANCE_COUNT; n++)
    {
        float a = 50.0f * float(n) / 4.0f;
        float b = 50.0f * float(n) / 5.0f;
        float c = 50.0f * float(n) / 6.0f;

        matrices[n] = rotate(a + t * 360.0f, 1.0f, 0.0f, 0.0f) *
                      rotate(b + t * 360.0f, 0.0f, 1.0f, 0.0f) *
                      rotate(c + t * 360.0f, 0.0f, 0.0f, 1.0f) *
                      translation(10.0f + a, 40.0f + b, 50.0f + c);
    }

    // Bind the weight VBO and change its data
    glBindBuffer(GL_TEXTURE_BUFFER, model_matrix_buffer);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(matrices), matrices, GL_DYNAMIC_DRAW);

    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Activate instancing program
    glUseProgram(render_prog);

    // Set up the view and projection matrices
    mat4 view_matrix(translation(0.0f, 0.0f, -1500.0f) * rotate(t * 360.0f * 2.0f, 0.0f, 1.0f, 0.0f));
    mat4 projection_matrix(frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 5000.0f));

    glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, view_matrix);
    glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, projection_matrix);

    // Render INSTANCE_COUNT objects
    object.Render(0, INSTANCE_COUNT);

}

void InstancedRender::resizeGL(int w,int h)
{
	if(0 == h)
		h = 1;
	glViewport(0,0,w,h);
	aspect = (float)w/(float)h;
	glLoadIdentity();
}
