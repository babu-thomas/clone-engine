#version 330 core

in vec3 color;
in vec4 pos;
out vec4 frag_color;

uniform vec2 light_pos;

void main()
{
	float intensity = 1.0 / length(pos.xy - light_pos);
	frag_color = vec4(color, 1.0) * intensity;
}