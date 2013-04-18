CC = gcc
CFLAGS = -Wall

debug =
ifeq ($(debug), 1)
	CFLAGS += -Wextra -DDEBUG=1 -g -O0
else
	CFLAGS += -DDEBUG=0 -O2
endif

TARGET = b8g8r8toa1r5g5b5
SRC := $(wildcard ./*.c)
OBJ := $(patsubst %.c,%.o,$(SRC))

all: $(TARGET)

b8g8r8toa1r5g5b5: $(OBJ)

sinclude $(SRC:.c=.d)

%d: %c
	@set -e; rm -f $@; \
		$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
		sed 's,\(.*\)\.o[:]*,\1.o $@:,' < $@.$$$$ > $@; \
		rm -f $@.$$$$

clean:
	-rm $(OBJ) $(TARGET) *.d

.PHONY: all clean
