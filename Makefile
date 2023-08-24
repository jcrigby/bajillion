CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -posix_spawn

TARGET = md5sum_bajillion

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)
