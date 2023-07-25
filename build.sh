set -xe

# MacOS uses dylib, windows has dll and linux has SO
clang -o ./logger.dylib -fPIC -shared ./logger.c
clang -o ./main ./main.c

./main
