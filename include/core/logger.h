#ifndef LOGGER_H_
#define LOGGER_H_
#include <stdio.h>
#include <stdbool.h>

typedef enum Level{OFF = 0, FATAL, ERROR, WARN, INFO, DEBUG} Level;

typedef struct Logger {
    bool (*enabled)(const char *target, Level level);
    void (*log)(const char *target, Level level, char *payload, ...);
    void (*flush)();
} Logger;

extern Logger *logger;

typedef enum LoggerState{Uninitialized, Initialized} LoggerState;

extern LoggerState logger_state;

extern void Logger_init(FILE *stream);

#endif /* Not LOGGER_H_ */