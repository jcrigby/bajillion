CC = gcc
CFLAGS = -Wall -Wextra

TARGETS = md5sum_bench md5sum_bench_system

all: $(TARGETS)

md5sum_bench: md5sum_bench.c
	$(CC) $(CFLAGS) -o $@ $<

md5sum_bench_system: md5sum_bench_system.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)
