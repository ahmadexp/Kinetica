#pragma once

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// Provide MSVC secure CRT name compatibility on non-Windows
#ifndef _WIN32

static inline int sprintf_s(char* buf, size_t bufsize, const char* format, ...){
	va_list args; va_start(args, format); int r = vsnprintf(buf, bufsize, format, args); va_end(args); return r; }

// Allow older code that calls sprintf_s(buf, format, ...)
static inline int sprintf_s(char* buf, const char* format, ...){
	va_list args; va_start(args, format); int r = vsnprintf(buf, (size_t)4096, format, args); va_end(args); return r; }

static inline int strcpy_s(char* dest, size_t destsz, const char* src){ if(destsz==0) return -1; strncpy(dest, src, destsz-1); dest[destsz-1]=0; return 0; }
static inline int strcpy_s(char* dest, const char* src){ strcpy(dest, src); return 0; }

static inline int strcat_s(char* dest, size_t destsz, const char* src){ size_t l=strlen(dest); if(l>=destsz) return -1; size_t copy = destsz - l - 1; strncat(dest, src, copy); dest[destsz-1]=0; return 0; }
static inline int strcat_s(char* dest, const char* src){ strcat(dest, src); return 0; }

#ifndef MAX_PATH
#define MAX_PATH 4096
#endif

// Minimal wchar/WCHAR/OemToCharW stubs where needed
#include <wchar.h>
static inline void OemToCharW(const char* in, wchar_t* out){ size_t i=0; for(; in[i] && i<256; ++i) out[i]= (unsigned char)in[i]; out[i]=0; }

#endif
