#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

// File pointer for the log file
FILE *log_file = NULL;

// Function to get current time in milliseconds
long long current_time_millis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}

void millis_to_datetime(long long millis, char* buffer, size_t buffer_size) {
 time_t seconds = (time_t)(millis / 1000);
 int milliseconds = millis % 1000;

 struct tm *tm_info = localtime(&seconds);
 strftime(buffer, buffer_size, "%Y-%m-%d %H:%M:%S", tm_info);

 // Append milliseconds to the formatted string
 snprintf(buffer + strlen(buffer), buffer_size - strlen(buffer), ".%03d", milliseconds);
}

// Function to get process name
void get_process_name(char *process_name, size_t size) {
    snprintf(process_name, size, "/proc/%d/cmdline", getpid());
    FILE *fp = fopen(process_name, "r");
    if (fp) {
        fgets(process_name, size, fp);
        fclose(fp);
    } else {
        snprintf(process_name, size, "unknown");
    }

    // Remove any path components from the process name
    char *slash = strrchr(process_name, '/');
    if (slash) {
        memmove(process_name, slash + 1, strlen(slash));
    }
}

// Function to initialize logging
void debug_init() {
    char log_file_name[300];
    snprintf(log_file_name, sizeof(log_file_name), "/var/log/invmgr_hwinfo.log");

    log_file = fopen(log_file_name, "a");
    if (!log_file) {
        perror("Failed to open log file");
        exit(EXIT_FAILURE);
    }
}

// Function to log messages to file
void log_message(const char *function, int line, const char *message, ...) {
    if (!log_file) {
        fprintf(stderr, "Log file is not initialized. Call debug_init() first.\n");
        return;
    }

    // Get current time in milliseconds
    long long timestamp = current_time_millis();

    // Get process name and PID
    char process_name[256];
    get_process_name(process_name, sizeof(process_name));
    pid_t pid = getpid();

    // Write log message
    va_list args;
    va_start(args, message);
    fprintf(log_file, "[%lld ms] [%s:%d] [%s:%d] ", timestamp, process_name, pid, function, line);
    vfprintf(log_file, message, args);
    fprintf(log_file, "\n");
    va_end(args);

    fflush(log_file);
}

// Macro for logging messages
#define LOG_MESSAGE(message, ...) log_message(__FUNCTION__, __LINE__, message, ##__VA_ARGS__)

// Example usage
int main() {
    debug_init();

    LOG_MESSAGE("This is a log message");
    LOG_MESSAGE("Another log message with a value: %d", 42);

    if (log_file) {
        fclose(log_file);
    }

    return 0;
}
