#version 330 core

in vec2 aTexCoordinate;

out vec4 FragColor;

uniform Sampler2D screen;

void main()
{
	FragColor = vec4(texture(screen, aTexCoordinate).rgb, 1.f);
}