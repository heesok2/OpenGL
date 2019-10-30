#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 aFragPos;
out vec3 aFragNormal;

uniform mat4 matModel;
uniform mat4 matModelViewProjection;

void main()
{
	aFragPos = vec3(matModel * vec4(aPos, 1.f));
	aFragNormal = aNormal;

	gl_Position = matModelViewProjection * vec4(aPos, 1.f);
}