/*  
 * implementor interface of log library
 *  
 * a logger is any object which impl the logger API
 * 
 * Atomic access is not guranteed
 * 
 * Global data implementor should define:
 *  logger: pointer to global logger
 *  logger_state: indicate whether logger is initialized
 * 
 * What should be done in Logger_init:
 *  1.  construct logger object and related it to the global logger
 *      pointer, any needed data shall be initialized too
 *  2.  check environment variable 'LOG_LEVEL', use it as max log level
 *      (which means level no. bigger than it should not be logged)
 *  3.  set output stream as arg 'stream', use stdout as output stream
 *      if arg is NULL
 *  4.  check logger_state before init, panic if logger has been init,
 *      after initialization set it to 'Initialized'
 * 
 * Logger_init is supposed to be called at very start of the program,
 * race condition is unlikely to happen, but any thread safety gurantee
 * is welcomed.
 * 
*/
#ifndef LOGGER_H_
#define LOGGER_H_
#include <stdio.h>
#include <stdbool.h>

typedef enum Level{OFF = 0, FATAL, ERROR, WARN, INFO, DEBUG} Level;

typedef struct Logger {
    //  check if given category of log is enabled
    bool (*enabled)(const char *target, Level level);
    // main log functionality, write format args to output stream
    void (*log)(const char *target, Level level, char *payload, ...);
    // flush the stream if needed
    void (*flush)();
} Logger;

// global logger pointer
extern Logger *logger;

typedef enum LoggerState{Uninitialized, Initialized} LoggerState;

// global logger state
extern LoggerState logger_state;

/*
 * init the global logger
 * Args:
 *      stream: specify output stream
*/
extern void Logger_init(FILE *stream);

#endif /* Not LOGGER_H_ */