CC = gcc
CFLAGS = -Wall -Wextra

TARGETS = posix_spawn_bench system_bench just_fork_bench

all: $(TARGETS)

# General compilation rule
%: %.c timer.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

shorttest: $(TARGETS)
	@for target in $(TARGETS); do \
		echo $$target; \
		./$$target --iterations 1000; \
		echo ""; \
	done

longtest: $(TARGETS)
	@for target in $(TARGETS); do \
		echo $$target; \
		./$$target --iterations 100000; \
		echo ""; \
	done
