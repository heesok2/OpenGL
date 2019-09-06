#pragma once

static BOOL g_warning = FALSE;

#ifndef GLOBAL_DEF
#define GLOBAL_DEF

#define _SAFE_DELETE(x) {if(x){delete (x);(x)=NULL;}}

#endif // !GLOBAL_DEF
