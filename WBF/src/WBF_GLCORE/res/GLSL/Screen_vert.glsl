#version 330 core

layout (location = 0) in vec3 attrPos;
layout (location = 1) in vec2 attrTexCord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 aTexCoordinate;

void main()
{
	gl_Position = projection * view * model * vec4(attrPos, 1.f);
	aTexCoordinate = aTexCoordinate;
}