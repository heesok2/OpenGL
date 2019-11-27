#version 330 core

out vec4 FragColor;

in vec2 aFragTexcel;

uniform sampler2D texture_diffuse;

void main()
{
	FragColor = texture(texture_diffuse, aFragTexcel);
}