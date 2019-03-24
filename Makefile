CFLAGS = -Wall -Wextra -Werror

.PHONY: all
all: tobin

.PHONY: clean
clean:
	rm -f tobin
