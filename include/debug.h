//
//  mGBA logging functionality
// https://github.com/adverseengineer/libtonc/blob/master/include/tonc_mgba.h
//! \file tonc_mgba.h
//! \author Nick Sells
//! \date 20210401
//

#ifndef TONC_MGBA
#define TONC_MGBA
#ifdef DEBUG


#include <stdarg.h>
#include <stdio.h>
#include "tonc_types.h"

// --------------------------------------------------------------------
// STRUCTS
// --------------------------------------------------------------------

typedef enum LogLevel {
	LOG_FATAL                   = 0x100,
	LOG_ERR                     = 0x101,
	LOG_WARN                    = 0x102,
	LOG_INFO                    = 0x103
} LogLevel;

// --------------------------------------------------------------------
// MACROS
// --------------------------------------------------------------------

#define REG_LOG_ENABLE          *(vu16*) 0x4FFF780
#define REG_LOG_LEVEL           *(vu16*) 0x4FFF700

// --------------------------------------------------------------------
// INLINES
// --------------------------------------------------------------------

//! Outputs \a fmt formatted with varargs to mGBA's logger with \a level priority
static inline void mgba_printf(const char* fmt, /*LogLevel lvl,*/ ...) {
	REG_LOG_ENABLE = 0xC0DE;
	REG_LOG_LEVEL = LOG_INFO;

	va_list args;
	va_start(args, fmt);

	char* const log = (char*) 0x4FFF600;
	vsnprintf(log, 0x100, fmt, args);

	va_end(args);
}

#else
static inline void mgba_printf(const char* fmt, /*LogLevel lvl,*/ ...) {
	return;
}
#endif
#endif
