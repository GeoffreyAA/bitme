#ifndef __TYPES_H__
#define __TYPES_H__

typedef signed char		int8;
typedef unsigned char	uint8;

typedef signed short	int16;
typedef unsigned short	uint16;

typedef signed int		int32;
typedef unsigned int	uint32;

#if defined(_MSC_VER)
	typedef signed __int64		int64;
	typedef unsigned __int64	uint64;
#else
	#error Cannot define 64-bit integer type.
#endif

#endif