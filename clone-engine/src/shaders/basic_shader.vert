#version 330 core

layout(location=0) in vec4 vertex_position;
layout(location=1) in vec3 vertex_color;

out vec3 color;
out vec4 pos;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

void main()
{
	color = vertex_color;
	gl_Position = pr_matrix * vw_matrix * ml_matrix * vertex_position;
	pos = ml_matrix * vertex_position;
}