#version 330 core

out vec4 FragColor;

in vec4 aColor;
in vec2 aTexcel;

uniform sampler2D ourTexture;

void main()
{
	FragColor = Texture(ourTexture, aTexcel) * aColor;
}