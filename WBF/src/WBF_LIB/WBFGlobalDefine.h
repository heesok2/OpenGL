#pragma once

#define _SAFE_DELETE(x) {if(x){delete (x);(x)=NULL;}}