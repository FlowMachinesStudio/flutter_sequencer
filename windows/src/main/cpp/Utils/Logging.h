#ifndef WIN_LOGGING_H
#define WIN_LOGGING_H

#define APP_NAME "FLUTTER_SEQUENCER"
#define APP_NAME "FLUTTER_SEQUENCER"
#define LOG_INFO "info"
#define LOG_ERROR "error"

void __log_print(const char* level, const char* appName, const char* messageFormat, ...) {
    // FIXME:...
    /*
    std::cout << "[" << level << "] " << appName << ": ";
    va_list args;
    va_start(args, messageFormat);
    vprintf(messageFormat, args);
    va_end(args);

    std::cout << std::endl;
    */
}

#define LOGI(...) ((void)__log_print(LOG_INFO, APP_NAME, __VA_ARGS__))
#define LOGE(...) ((void)__log_print(LOG_ERROR, APP_NAME, __VA_ARGS__))

#endif //WIN_LOGGING_H

