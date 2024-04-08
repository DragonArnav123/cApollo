#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <conio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#if APOLLO_PLATFORM_WINDOWS == 1
	#include <Windows.h>
#else
	#error APOLLO IS ONLY ON WINDOWS
#endif
