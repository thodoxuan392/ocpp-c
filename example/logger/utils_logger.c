/*
 * esp32_net_logger.c
 *
 *  Created on: Dec 1, 2022
 *      Author: xuanthodo
 */
#include "utils_logger.h"

#include <stdio.h>
#include "stdint.h"
#include "stdarg.h"

static uint8_t log_buffer[UTILS_MAX_LOG_BUFFER];
static uint8_t message_buffer[UTILS_MAX_LOG_BUFFER];

static const char* color_str[UTILS_LOG_ALL] = {
	[UTILS_LOG_OFF] = "\x1b[0m",
	[UTILS_LOG_ERROR] = "\x1b[31m", // RED
	[UTILS_LOG_INFO] = "\x1b[32m", // Green
	[UTILS_LOG_WARN] = "\x1b[33m", // Yellow
	[UTILS_LOG_TRACE] = "\x1b[34m", // Blue
	[UTILS_LOG_FATAL] = "\x1b[35m", // Magenta
	[UTILS_LOG_DEBUG] = "\x1b[36m", // Cyan
};

static const char* level_str[] = {"OFF", "FATAL", "ERROR", "WARN", "INFO", "DEBUG", "TRACE", "ALL"};

static utils_log_level_t level = UTILS_LOG_ALL;

static char* level_to_color(utils_log_level_t level)
{
	return color_str[level];
}

static char* level_to_str(utils_log_level_t level)
{
	return level_str[level];
}

void utils_log_init(utils_log_level_t _level)
{
	level = _level;
};

void utils_log_log(utils_log_level_t _level, const char* file, int line, const char* fmt, ...)
{
	va_list args;
	if(_level > level)
	{
		return;
	}
	va_start(args, fmt);
	va_end(args);
	vsnprintf(message_buffer, UTILS_MAX_LOG_BUFFER, fmt, args);
	int size = snprintf(log_buffer, UTILS_MAX_LOG_BUFFER, "%s%d [%s] %s:%d: %s%s",
						level_to_color(_level), UTILS_TIME_MS(), level_to_str(_level), file, line,
						message_buffer, level_to_color(UTILS_LOG_OFF));
	UTILS_LOG(log_buffer, size);
}

void utils_log_raw(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	va_end(args);
	size_t len = vsnprintf(message_buffer, UTILS_MAX_LOG_BUFFER, fmt, args);
	UTILS_LOG(message_buffer, len);
}
