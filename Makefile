CC = gcc
CFLAGS = -Wall -Wextra

TARGETS = posix_spawn_bench md5sum_bench_system just_fork_bench

all: $(TARGETS)

# General compilation rule
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

test: $(TARGETS)
	@for target in $(TARGETS); do \
		echo "Running benchmark using $$target..."; \
		time ./$$target --iterations 1000; \
		echo ""; \
	done
