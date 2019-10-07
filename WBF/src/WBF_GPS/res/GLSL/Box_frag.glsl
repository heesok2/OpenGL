#version 330 core

out vec4 FragColor;

uniform vec4 ourModelColor;
uniform vec4 ourLightColor;

void main()
{
	FragColor = ourModelColor * ourLightColor;
}