#version 330 core
// layout, uniform(global), in, out

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec4 ourColor;
out vec2 TexCoord;

void main()
{
	// local, out, member

	ourColor = vec4(aColor, 1.f);
	TexCoord = aTexCoord;

    gl_Position = proj * view * model * transform * vec4(aPos, 1.f);
}