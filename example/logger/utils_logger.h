/*
 * NETIF_logger.h
 *
 *  Created on: Dec 1, 2022
 *      Author: xuanthodo
 */

#ifndef UTILS_LOGGER_H_
#define UTILS_LOGGER_H_

#define UTILS_LOG(data, dataSize) printf(data)
#define UTILS_MAX_LOG_BUFFER 1024
#define UTILS_TIME_MS() 0

typedef enum
{
	UTILS_LOG_OFF,
	UTILS_LOG_FATAL,
	UTILS_LOG_ERROR,
	UTILS_LOG_WARN,
	UTILS_LOG_INFO,
	UTILS_LOG_DEBUG,
	UTILS_LOG_TRACE,
	UTILS_LOG_ALL
} utils_log_level_t;

#define utils_log_trace(...) utils_log_log(UTILS_LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define utils_log_debug(...) utils_log_log(UTILS_LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define utils_log_info(...) utils_log_log(UTILS_LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define utils_log_warn(...) utils_log_log(UTILS_LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define utils_log_error(...) utils_log_log(UTILS_LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define utils_log_fatal(...) utils_log_log(UTILS_LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

void utils_log_init(utils_log_level_t level);
void utils_log_log(utils_log_level_t level, const char* file, int line, const char* fmt, ...);
void utils_log_raw(const char* fmt, ...);

#endif /* UTILS_LOGGER_H_ */
