#pragma once

#if APOLLO_PLATFORM_WINDOWS != 1
	#error APOLLO ONLY FOR WINDOWS
#endif

#if APOLLO_CORE == 1
	#define APOLLO_API __declspec(dllexport)
#else
	#define APOLLO_API __declspec(dllimport)
#endif

#define APOLLO_FALSE 0x000 
#define APOLLO_TRUE  0X001

// typdefs
typedef char APi08;
typedef short int APi16;
typedef int APi32;
typedef long int APi64;
typedef long long int APi128;

typedef unsigned char APu08;
typedef unsigned short int APu16;
typedef unsigned int APu32;
typedef unsigned long int APu64;
typedef unsigned long long int APu128;

typedef float APf32;
typedef double APf64;

typedef char APbyte_t;
typedef char *APstr_t;
typedef char *APfilepath_t;
