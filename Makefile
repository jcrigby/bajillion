CC = gcc
CFLAGS = -Wall -Wextra

TARGET = md5sum_bajillion

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)
