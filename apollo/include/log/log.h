#pragma once

#include "core/core.h"
#include "log/log.h"

/*
 * @enum: apLogSeverity
 * @brief: log severity enum
 * @desc:
 *	indicates the severity (and the corresponding color) of a log message
*/
typedef enum apLogSeverity {
	AP_LOG				,
	AP_TRACE			,
	AP_INFO				,
	AP_WARN				,
	AP_FATAL
} apLogSeverity;

/*
 * @func: AP_log
 * @param:
 *	- file [const char *]: file name where this function was invoked
 *	- func [const char *]: func name where this function was invoked
 *	- line [int]: line number in the file where this function was invoked
 *	- severity [apLogSeverity]: enum to indicate severity of log
 *	- format [const char *]: format needed for printf
 *	- ... [__VA_ARGS__]: message to be logged
 * @ret: void
 * @brief: logs the message
 * @desc:
 *	logs the given message (...) to the console in color coded fashion
*/
void APOLLO_API AP_log(
		const char *file,
		const char *func,
		int line,
		apLogSeverity severity,
		const char *format,
		...);

#define AP_LOG_LOG(format, ...)				AP_log(__FILE__, "", __LINE__, AP_LOG, format, __VA_ARGS__)
#define AP_LOG_TRACE(format, ...)			AP_log(__FILE__, "", __LINE__, AP_TRACE, format, __VA_ARGS__)
#define AP_LOG_INFO(format, ...)			AP_log(__FILE__, "", __LINE__, AP_INFO, format, __VA_ARGS__)
#define AP_LOG_WARN(format, ...)			AP_log(__FILE__, "", __LINE__, AP_WARN, format, __VA_ARGS__)
#define AP_LOG_FATAL(format, ...)			AP_log(__FILE__, "", __LINE__, AP_FATAL, format, __VA_ARGS__)
