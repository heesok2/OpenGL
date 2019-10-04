#pragma once

static BOOL g_warning = FALSE;

#ifndef GLOBAL_DEF
#define GLOBAL_DEF

#define DTYPE UINT // Data Type
#define DKEY UINT // Data Key

#define _SAFE_DELETE(x) {if(x){delete (x);(x)=NULL;}}
#define _SAFE_DELETE_ARRAY(x) { if(x){delete[] (x); (x)=NULL;}}

#endif // !GLOBAL_DEF
