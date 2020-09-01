#version 440 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 TextCoord;

out vec3 color;
out vec2 textureCoord;

void main()
{
	color = col;
	textureCoord = vec2(TextCoord.x, TextCoord.y);
	gl_Position = vec4(pos, 1.f);
}