#pragma once

#ifndef DEFINE_SHADER
#define DEFINE_SHADER

enum E_SHADER_TYPE
{
	E_SHADER_UNKNOWN = -1,
	E_SHADER_SCREEN = 0,
	E_SHADER_SAMPLE,
	E_SHADER_LIGHT,
	E_SHADER_BOX,
	E_SHADER_CONTAINER_BOX,

	E_SHADER_NUM
};

#endif // !DEFINE_SHADER

