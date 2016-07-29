#version 430 core
uniform Uniforms{
	vec3 translation;
	float scale;
	vec4 rotation;
	bool enable;
};
in vec2 vPos;
in vec3 vColor;
out vec4 fColor;
void main()
{
	vec3 pos = vec3(vPos,0.0);
	float ang = rotation[0];
	vec3 axis = normalize(rotation.xyw);
	mat3 I = mat3(1.0);
	mat3 S = mat3(		0,		-axis.z,		 axis.y,
							axis.z,		0,			-axis.x,
						   -axis.y,	  axis.x,			0		);
	mat3 uuT = outerproduct(axis,axis);
	mat3 rot = uuT + cos(ang)*(I-uuT) + sin(ang)*S;
	pos *= scale;
	pos *= rot;
	pos += translation;
	fColor = vec4(scale,scale,scale,1);
	gl_Position = vec4(pos,1);
}