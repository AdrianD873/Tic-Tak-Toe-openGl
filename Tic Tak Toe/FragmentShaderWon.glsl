#version 440 core

in vec3 color;
in vec2 textureCoord;

out vec4 pixelColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	if(texture(texture2, textureCoord).r == 0.f)
	{
		pixelColor = texture(texture2, textureCoord) + vec4(color, 0.5f);
	}
	else
		pixelColor = texture(texture2, textureCoord);
}