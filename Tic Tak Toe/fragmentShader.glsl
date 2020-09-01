#version 440 core

in vec3 color;
in vec2 textureCoord;

out vec4 pixelColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	pixelColor = mix( texture(texture0, textureCoord), texture(texture1, textureCoord), texture(texture1, textureCoord).a * 0.8) + vec4(color, 1.f);
}