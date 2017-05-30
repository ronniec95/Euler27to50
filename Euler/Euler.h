#pragma once
#include <Windows.h>
#ifdef _DEBUG
inline bool _trace(const char *format, ...) {
	char buf[1024];
	wvsprintfA(buf, format, ((char*)&format) + sizeof(void*));
	OutputDebugStringA(buf);
	return true;
}
#define TRACE(cond,x, ...) if(cond) _trace(x,  __VA_ARGS__)
#else
#define TRACE(cond,x,...) __noop
#endif

#include "prime.h"
#include "Euler21.h"
#include "Euler22.h"
#include "Euler23.h"
#include "Euler24.h"
#include "Euler25.h"
#include "Euler26.h"
#include "Euler27.h"
#include "Euler28.h"
#include "Euler29.h"