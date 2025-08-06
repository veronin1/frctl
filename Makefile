# Compiler and flags
CC = clang
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wformat=2 -Wcast-align -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wfloat-equal -Wpointer-arith -Wsign-conversion -Wunreachable-code -O3 -march=native -flto -fno-plt -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -pipe

# Libraries
LIBS = -lraylib -lm -ldl -lpthread -lGL

# Source and output
SRC = src/main.c
OUT = main

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)
