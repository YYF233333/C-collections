#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core/logger.h"
#include "core/panic.h"

const static char *SET_LOGGER_ERROR = "attempted to set a logger after the "
                                      "logging system was already initialized";
const static char *LEVEL_PARSE_ERROR =
    "attempted to convert a string that doesn't match an existing log level";

const static char *log_level_names[6] = { "OFF",  "FATAL", "ERROR",
                                          "WARN", "INFO",  "DEBUG" };

Logger _logger = { .enabled = NULL, .log = NULL, .flush = NULL };

Logger *logger = &_logger;
LoggerState logger_state = Uninitialized;
static Level max_level = OFF;
static FILE *output_stream = NULL;

bool Logger_enabled(const char *target, Level level) {
    return level <= max_level;
}

void Logger_log(const char *target, Level level, char *payload, ...) {
    if (level < 0 || level > 5) panic(LEVEL_PARSE_ERROR);
    va_list args;
    va_start(args, payload);
    fprintf(output_stream, log_level_names[level]);
    vfprintf(output_stream, payload, args);
    fprintf(output_stream, "\n");
}

void Logger_flush() {}

void Logger_init(FILE *stream) {
    // panicked at reinitialization
    if (logger_state == Initialized) panic(SET_LOGGER_ERROR);

    // set max log level
    char *log_level = getenv("LOG_LEVEL");
    if (log_level == NULL) {
        max_level = OFF;
    } else {
        for (int i = 0; i < 6; i++) {
            if (strcmp(log_level_names[i], log_level) == 0) {
                max_level = (Level)i;
                break;
            }
        }
    }
    // register logger function
    _logger.enabled = Logger_enabled;
    _logger.log = Logger_log;
    _logger.flush = Logger_flush;
    // set output stream
    output_stream = (stream == NULL) ? stdout : stream;

    logger_state = Initialized;
}