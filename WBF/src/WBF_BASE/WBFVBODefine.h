#pragma once

#ifndef DEFINE_VBO
#define DEFINE_VBO

enum E_VBO_TYPE
{
	E_VBO_UNKNOWN = -1,

	E_VBO_NUM
};

typedef struct tagEntityVBO
{
	UINT VBO;
	UINT EBO;
	UINT VAO;
	UINT DataNum;

	tagEntityVBO(UINT _VBO = 0, UINT _EBO = 0, UINT _VAO = 0, UINT _DataNum = 0)
	{
		VBO = _VBO;
		EBO = _EBO;
		VAO = _VAO;
		DataNum = _DataNum;
	}

} TEntityVBO;


#endif // !DEFINE_VBO
