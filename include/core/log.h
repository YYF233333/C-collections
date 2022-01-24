#ifndef LOG_H_
#define LOG_H_

#include "logger.h"

#define LOG_ENABLED(level) logger->enabled(__FILE__, level)
#define LOG(level, payload, ...) \
    (void)(LOG_ENABLED(level) ?\
    logger->log(__FILE__, level, payload, ##__VA_ARGS__) :\
    (void *)0)
#define FATAL(format, ...) LOG(FATAL, format, ##__VA_ARGS__)
#define ERROR(format, ...) LOG(ERROR, format, ##__VA_ARGS__)
#define WARN(format, ...) LOG(WARN, format, ##__VA_ARGS__)
#define INFO(format, ...) LOG(INFO, format, ##__VA_ARGS__)
#define DEBUG(format, ...) LOG(DEBUG, format, ##__VA_ARGS__)


#endif /* Not LOG_H_ */