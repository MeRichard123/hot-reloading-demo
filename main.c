#include <stdio.h>
#include <dlfcn.h> 
#include "logger.h"

logger_log_t logger_log = NULL;

int application() {
  const char *logger_lib_filename = "logger.dylib";
  void *logger_lib = dlopen(logger_lib_filename, RTLD_NOW);

  if (logger_lib == NULL) {
    fprintf(stderr, "Could not load %s: %s", logger_lib_filename, dlerror());
    return 1;
  }

  logger_log = dlsym(logger_lib, "logger_log");
  if (logger_log == NULL) {
    fprintf(stderr, "ERROR: Could not find logger_log symbol in %s: %s", logger_lib_filename, dlerror());
    return 1;
  }

  logger_log();

  dlclose(logger_lib);
}

int main(void) {
  printf("Hello Seaman \n");
  while(true) {
    application();
  }
  return 0;
}
