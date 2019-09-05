#pragma once

#ifndef DEF_GLOBAL
#define DEF_GLOBAL

#define _SAFE_DELETE(x) {if(x){delete (x);(x)=NULL;}}

#endif // !DEF_GLOBAL
