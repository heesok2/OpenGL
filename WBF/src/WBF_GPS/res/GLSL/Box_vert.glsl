#version 330 core

layout (location = 0) in vec3 attrPos;
layout (location = 1) in vec3 attrNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;

void main()
{
	FragPos = vec3(model * vec4(attrPos, 1.f));
	Normal = vec3(model * vec4(attrNormal, 1.f));

	gl_Position = projection * view * model * vec4(attrPos, 1.f);
}