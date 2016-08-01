#include "xtb.h"
#include <iostream>
using namespace vmath;
const int point_count = 5000;
static unsigned int seed = 0x13371337;

static float random_float()
{
    float res;
    unsigned int tmp;
    seed *= 16807;
    tmp = seed ^ (seed >> 4) ^ (seed << 15);
    *((unsigned int *) &res) = (tmp >> 9) | 0x3F800000;
    return (res - 1.0f);
}
static vec3 random_vector(float minmag = 0.0f, float maxmag = 1.0f)
{
    vec3 randomvec(random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f);
    randomvec = normalize(randomvec);
    randomvec *= (random_float() * (maxmag - minmag) + minmag);
    return randomvec;
}

static inline int min(int a, int b)
{
    return a < b ? a : b;
}

xtb::xtb(QGLWidget *parent)
	: QGLWidget(parent)
{
	ui.setupUi(this);
}

xtb::~xtb()
{

}
void xtb::initializeGL()
{
	setGeometry(200,100,640,480);
	if(glewInit())
	{
		std::cout<<"Unable to init glew"<<std::endl;
		exit(EXIT_FAILURE);
	}
	ShaderInfo obj_shaders[] ={
		{GL_VERTEX_SHADER,			"update.vert"},
		{GL_FRAGMENT_SHADER,		"wf.frag"},
		{GL_NONE,							NULL}
	};
	update_prog = glCreateProgram();
	update_prog = LoadShaders(obj_shaders);
	static const char * varyings[] =
    {
        "position_out", "velocity_out"
    };
	glTransformFeedbackVaryings(update_prog, 2, varyings, GL_INTERLEAVED_ATTRIBS);
	glLinkProgram( update_prog );
	glUseProgram(update_prog);
	model_matrix_loc = glGetUniformLocation(update_prog, "model_matrix");
    projection_matrix_loc = glGetUniformLocation(update_prog, "projection_matrix");
    triangle_count_loc = glGetUniformLocation(update_prog, "triangle_count");
    time_step_loc = glGetUniformLocation(update_prog, "time_step");

	render_prog  = glCreateProgram();
	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER,			"obj.vert"},
		{GL_FRAGMENT_SHADER,		"obj.frag"},
		{GL_NONE,							NULL}
	};
	render_prog = LoadShaders(shaders);
	static const char * varyings2[] =
    {
        "world_space_position"
    };
	glTransformFeedbackVaryings(render_prog, 1, varyings2, GL_INTERLEAVED_ATTRIBS);

	glLinkProgram( render_prog );
	glUseProgram(render_prog);
    render_model_matrix_loc = glGetUniformLocation(render_prog, "model_matrix");
    render_projection_matrix_loc = glGetUniformLocation(render_prog, "projection_matrix");
    glGenVertexArrays(2, vao);
    glGenBuffers(2, vbo);
	 for (int i = 0; i < 2; i++)
    {
        glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, vbo[i]);
        glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, point_count * (sizeof(vec4) + sizeof(vec3)), NULL, GL_DYNAMIC_COPY);
        GLenum errCode = glGetError();
		std::cout<<errCode<<std::endl;
		if (0 == i)
        {
            struct buffer_t {
                vec4 position;
                vec3 velocity;
            } * buffer = (buffer_t *)glMapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, GL_WRITE_ONLY);

            for (int j = 0; j < point_count; j++)
            {
                buffer[j].velocity = random_vector();
                buffer[j].position = vec4(buffer[j].velocity + vec3(-0.5f, 40.0f, 0.0f), 1.0f);
                buffer[j].velocity = vec3(buffer[j].velocity[0], buffer[j].velocity[1] * 0.3f, buffer[j].velocity[2] * 0.3f);
            }

            glUnmapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER);
        }

        glBindVertexArray(vao[i]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vec4) + sizeof(vec3), NULL);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vec4) + sizeof(vec3), (GLvoid *)sizeof(vec4));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
	glGenBuffers(1, &geometry_vbo);
	 //geometry_tex没有使用到 
    glGenTextures(1, &geometry_tex);
    glBindBuffer(GL_TEXTURE_BUFFER, geometry_vbo);
    glBufferData(GL_TEXTURE_BUFFER, 1024 * 1024 * sizeof(vec4), NULL, GL_DYNAMIC_COPY);
    glBindTexture(GL_TEXTURE_BUFFER, geometry_tex);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, geometry_vbo);

    /*glGenVertexArrays(1, &render_vao);
    glBindVertexArray(render_vao);
    glBindBuffer(GL_ARRAY_BUFFER, geometry_vbo);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);*/

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    object.LoadFromVBM("C:/Vermilion-Book/trunk/Code/media/armadillo_low.vbm", 0, 1, 2);
}

void xtb::paintGL()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

	static int frame_count = 0;
    float t = float(GetTickCount() & 0x3FFFF) / float(0x3FFFF);
    static float q = 0.0f;
    static const vec3 X(1.0f, 0.0f, 0.0f);
    static const vec3 Y(0.0f, 1.0f, 0.0f);
    static const vec3 Z(0.0f, 0.0f, 1.0f);

    mat4 projection_matrix(frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 5000.0f) * translation(0.0f, 0.0f, -100.0f));
    mat4 model_matrix(scale(0.3f) *
                             rotate(t * 360.0f, 0.0f, 1.0f, 0.0f) *
                             rotate(t * 360.0f * 3.0f, 0.0f, 0.0f, 1.0f));
    
    glUseProgram(render_prog);
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix);
    glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, projection_matrix);

    glBindVertexArray(render_vao);

    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, geometry_vbo);
    glBeginTransformFeedback(GL_TRIANGLES);
    object.Render();
    glEndTransformFeedback();

    glUseProgram(update_prog);
    model_matrix = mat4::identity();
    glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, model_matrix);
    glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, projection_matrix);
    glUniform1i(triangle_count_loc, object.GetVertexCount() / 3);
    if (t > q)
    {
		 glUniform1f(time_step_loc, 0.2f);  
        //glUniform1f( time_step_loc, (t-q)*2000.0f );  
        static TCHAR debugStr[4096] = L"";  
        swprintf_s(debugStr, L" FrameCount = %.3f\n", t);  
        OutputDebugString(debugStr); 
    }
    q = t;
    if ((frame_count & 1) != 0)
    {
        glBindVertexArray(vao[1]);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo[0]);
    }
    else
    {
        glBindVertexArray(vao[0]);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo[1]);
    }

    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, point_count/*min(point_count, (frame_count >> 3))*/);
    glEndTransformFeedback();

    glBindVertexArray(0);
    frame_count++;
}

void xtb::resizeGL(int w,int h)
{
	if(0 == h)
		h = 1;
	aspect =float(h)/float(w);
	glViewport(0,0,w,h);
	glLoadIdentity();
}

void xtb::timerEvent(QTimerEvent*)
{
	updateGL();
}