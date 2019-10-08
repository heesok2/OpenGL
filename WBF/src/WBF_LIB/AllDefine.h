#pragma once

static BOOL g_warning = FALSE;

#ifndef GLOBAL_DEF
#define GLOBAL_DEF

#define DTYPE UINT // Data Type
#define DKEY UINT // Data Key
#define DITER DWORD_PTR // Data Iterator

#define ITR_IS_VALID(x) ((x) > 0)
#define KEY_IS_VALID(x) ((x) > 0)

#define _SAFE_DELETE(x) {if(x){delete (x);(x)=NULL;}}
#define _SAFE_DELETE_ARRAY(x) { if(x){delete[] (x); (x)=NULL;}}

#endif // !GLOBAL_DEF
