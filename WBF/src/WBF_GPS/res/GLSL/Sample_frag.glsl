#version 330 core

out vec4 FragColor;

in vec4 aColor;
in vec2 aTexcel;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	FragColor = mix(texture(ourTexture1, aTexcel), texture(ourTexture2, aTexcel), 0.2) * aColor;
}