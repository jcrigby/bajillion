CC = gcc
CFLAGS = -Wall -Wextra

TARGETS = posix_spawn_bench system_bench just_fork_bench

all: $(TARGETS)

# General compilation rule
%: %.c timer.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

ITERATIONS ?= 100

benchtest:
	@for target in $(TARGETS); do \
		echo $$target; \
		./$$target --iterations $(ITERATIONS); \
		echo ""; \
	done


shorttest: ; @$(MAKE) benchtest ITERATIONS=10

longtest: ; @$(MAKE) benchtest ITERATIONS=100000
