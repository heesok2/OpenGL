#pragma once

#ifndef GRAPIC_DEF
#define GRAPIC_DEF

#define MODEL_UNKNOWN 0x0000
#define MODEL_UPDATE 0x0001
#define MODEL_DELETE 0x0002

namespace gps
{
	enum E_GRAPHICS_TYPE
	{
		E_GPS_UNKNOWN = -1,
		E_GPS_SAMPLE = 0,

		E_GPS_NUM
	};
}

#endif // !GRAPIC_DEF
