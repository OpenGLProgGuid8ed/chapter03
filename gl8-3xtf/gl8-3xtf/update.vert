#version 410 core

uniform mat4 model_matrix;
uniform mat4 projection_matrix;
uniform int triangle_count;//绘制三角形数量
//输入
layout (location = 0) in vec4 position;
layout (location = 1) in vec3 velocity;
//输出
out vec4 position_out;
out vec3 velocity_out;
// 使用采样器查找tbo三角形
uniform samplerBuffer geometry_tbo;
uniform float time_step = 0.02;
//线段与三角形平面相交测试
bool intersect(vec3 origin, vec3 direction, vec3 v0, vec3 v1, vec3 v2, out vec3 point)
{
    vec3 u, v, n, w0, w;
    float r, a, b;

    u = (v1 - v0);
	v = (v2 - v0);
    n = cross(u, v);
	if (length(n) < 0.1)
        return false;

    w0 = origin - v0;
    a = -dot(n, w0);
	b = dot(n, direction);
	if (abs(b) < 0.1)
        return false;

	r = a / b;
    if (r < 0.0 || r > 1.0)
        return false;

    point = origin + r * direction;

    float uu, uv, vv, wu, wv, D;
    uu = dot(u, u);
	uv = dot(u, v);
	vv = dot(v, v);
    w = point - v0;
	wu = dot(w, u);
	wv = dot(w, v);
    D = uv * uv - uu * vv;

    float s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)
        return false;
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)
        return false;

    return true;
}
//碰撞后反射向量计算
vec3 reflect_vector(vec3 v, vec3 n)
{
    return v - 2.0 * dot(v, n) * n;
}
void main()
{
   vec3 accelleration = vec3(0.0, -0.3, 0.0);
   vec3 new_velocity = velocity + accelleration * time_step;
   //计算粒子新的速度和位置
   vec4 new_position = position + vec4(new_velocity * time_step, 0.0);
   vec3 v0, v1, v2,point;
   int i;
   for (i = 0; i < triangle_count; i++)
   {
		//利用纹理查找tbo获取模型的三角形平面。做相交测试，如果相交在交点处计算反弹之后的新速度向量和位置
		v0 = texelFetch(geometry_tbo, i * 3).xyz;
		v1 = texelFetch(geometry_tbo, i * 3 + 1).xyz;
		v2 = texelFetch(geometry_tbo, i * 3 + 2).xyz;
		if (intersect(position.xyz, position.xyz - new_position.xyz, v0, v1, v2, point))
		{
            vec3 n = normalize(cross(v1 - v0, v2 - v0));
            new_position = vec4(point + reflect_vector(new_position.xyz - point, n), 1.0);
            new_velocity = 0.8 * reflect_vector(new_velocity, n);
        }
   }

   //超出一定范围，回归
   if (new_position.y < -80.0)
	{
		new_position = vec4(-new_position.x * 0.3, position.y + 200.0, 0.0, 1.0);
		new_velocity *= vec3(0.2, 0.1, -0.3);
	}
	//几乎无衰减的速度
	velocity_out = new_velocity * 0.9999;
	position_out = new_position;
	gl_Position = projection_matrix * (model_matrix * position);
}
