#pragma once

#ifndef DEFINE_DB
#define DEFINE_DB

typedef struct tagEntObjectParam
{
	UINT idx;
	UINT flag;

	tagEntObjectParam() : idx(0), flag(0)
	{}

} TEntObjectParam, *LPEntObjectParam;

#define D_DEFAULT_HASH_NUM 10000
#define D_HASH_INDEX(key, hash_size) ((key) % (hash_size))

#define ITR_TO_DATA(T, x) ((const T*)((CEntityDictionary<T>::TEntity*)(x))->Data)

#endif // !DEFINE_DB

