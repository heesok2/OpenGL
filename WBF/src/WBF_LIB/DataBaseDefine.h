#pragma once

#ifndef DEFINE_DB
#define DEFINE_DB

typedef struct tagEntityParam
{
	UINT idx;
	UINT flag;

	tagEntityParam() : idx(0), flag(0)
	{}

} TEntityParam, *LPEntityParam;

enum E_DB_NOTIFY
{
	E_DB_UNKNOWN = 0,
	E_DB_CHANGED,
	E_DB_NUM
};

#define FLAG_DB_UNKNOWN 0x0000
#define FLAG_DB_INSERT	0x0001
#define FLAG_DB_REMOVE	0x0002
#define FLAG_DB_CHANGE	0x0004

#define ITR_TO_DATA(T, x) ((const T*)((CEntityDictionary<T>::TEntity*)(x))->Data)
#define ITR_TO_KEY(x) (((CEntityData*)(((BYTE*)(x)) + sizeof(TEntityParam)))->GetKey())

#endif // !DEFINE_DB

