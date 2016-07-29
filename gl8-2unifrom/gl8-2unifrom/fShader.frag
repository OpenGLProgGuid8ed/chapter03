#version 430 core
uniform Uniforms{
	vec3 translation;
	float scale;
	vec4 rotation;
	bool enable;
};
in vec4 fcolor;
out vec4 color;
void main()
{
	color = fcolor;
}