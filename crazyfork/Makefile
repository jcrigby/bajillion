# Compiler settings
CC = gcc
CFLAGS = -Wall

# Targets
all: custom_start_main.so example_program

# Build the shared library
custom_start_main.so: custom_start_main.c
	$(CC) $(CFLAGS) -fPIC -shared -o custom_start_main.so custom_start_main.c -ldl

# Build the example program
example_program: example_program.c
	$(CC) $(CFLAGS) -o example_program example_program.c

# Run the test
test: custom_start_main.so example_program
	LD_PRELOAD=./custom_start_main.so ./example_program

# Clean up
clean:
	rm -f custom_start_main.so example_program

