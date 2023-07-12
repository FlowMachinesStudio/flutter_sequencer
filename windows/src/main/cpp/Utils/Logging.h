#ifndef WIN_LOGGING_H
#define WIN_LOGGING_H

#define APP_NAME "FLUTTER_SEQUENCER"
#define APP_NAME "FLUTTER_SEQUENCER"
#define LOG_INFO "info"
#define LOG_ERROR "error"

void __log_print(const char* file,
    const int line, const char* level, const char* appName, const char* messageFormat, ...);

#define LOGI(...) ((void)__log_print(__FILE__, __LINE__, LOG_INFO, APP_NAME, __VA_ARGS__))
#define LOGE(...) ((void)__log_print(__FILE__, __LINE__, LOG_ERROR, APP_NAME, __VA_ARGS__))

#endif //WIN_LOGGING_H

