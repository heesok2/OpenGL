#version 330 core

layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;

//out vec4 aOutColor;

void main()
{
	gl_Position = vec4(aPos, 1.f);
	//aOutColor = vec4(1.f, 0.f, 0.f, 1.f);
}