CC = gcc
CFLAGS = -Wall -Wextra

TARGETS = md5sum_bench md5sum_bench_system just_fork_bench

all: $(TARGETS)

md5sum_bench: md5sum_bench.c
	$(CC) $(CFLAGS) -o $@ $<

md5sum_bench_system: md5sum_bench_system.c
	$(CC) $(CFLAGS) -o $@ $<

just_fork_bench: just_fork_bench.c
	$(CC) $(CFLAGS) -o $@ $<


clean:
	rm -f $(TARGETS)

test: $(TARGETS)
	@echo "Running benchmark using posix_spawn..."
	@time ./md5sum_bench --iterations 1000

	@echo "\nRunning benchmark using system..."
	@time ./md5sum_bench_system --iterations 10
