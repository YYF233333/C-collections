/*
 * caller interface of log library
 *
 * Before use, call Logger_init to setup global logger and other
 * necessary structs. Notice that Logger_init should be called and
 * only called **ONCE**, reinitialization will cause panic.
 *
 * Since the logger is just a bare struct currently, thread safety is
 * **NOT** guranteed.
 *
 * Stuffs in logger.h are not designed to be accessed directly by user,
 * instead, use the macros list below, which all support format string.
 * Log level will be checked before actual call, so the overhead when
 * certain level is disabled should be minor.
 */
#ifndef LOG_H_
#define LOG_H_

#include "logger.h"

#define LOG_ENABLED(level) logger->enabled(__FILE__, level)
#define LOG(level, payload, ...)                                               \
    (void)(LOG_ENABLED(level)                                                  \
               ? logger->log(__FILE__, level, payload, ##__VA_ARGS__)          \
               : (void)0)
#define FATAL(format, ...) LOG(FATAL, format, ##__VA_ARGS__)
#define ERROR(format, ...) LOG(ERROR, format, ##__VA_ARGS__)
#define WARN(format, ...) LOG(WARN, format, ##__VA_ARGS__)
#define INFO(format, ...) LOG(INFO, format, ##__VA_ARGS__)
#define DEBUG(format, ...) LOG(DEBUG, format, ##__VA_ARGS__)

/*
 * init the global logger
 * Args:
 *      stream: specify stream to write your log in
 */
extern void Logger_init(FILE *stream);

#endif /* Not LOG_H_ */