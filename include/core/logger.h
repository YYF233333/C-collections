#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdbool.h>

typedef enum Level{FATAL = 1, ERROR, WARN, INFO, DEBUG} Level;
typedef enum LevelFilter{OFF = 0, _FATAL, _ERROR, _WARN, _INFO, _DEBUG} LevelFilter;

typedef struct Logger {
    bool (*enabled)(const char *target, Level level);
    void (*log)(const char *target, Level level, char *payload, ...);
    void (*flush)();
} *Logger;

extern Logger logger;

typedef enum LoggerState{Uninitialized, Initialized} LoggerState;

extern LoggerState logger_state;

#endif /* Not LOGGER_H_ */