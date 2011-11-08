#!/bin/sh
valgrind --leak-check=yes --log-file=valgrind.out.txt ./${TEST_EXE_NAME} -i -s --detect_fp_exceptions=y  --show_progress -lDEBUG -o
