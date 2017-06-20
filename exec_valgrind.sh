#/bin/bash

valgrind --suppressions=debug.suppressions --leak-check=full --show-leak-kinds=all ./debug
