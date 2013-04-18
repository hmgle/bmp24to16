TARGET = b8g8r8toa1r5g5b5
SRC := $(wildcard ./*.c)
OBJ := $(patsubst %.c,%.o,$(SRC))

all: $(TARGET)

b8g8r8toa1r5g5b5: $(OBJ)

clean:
	-rm $(OBJ) $(TARGET)

.PHONY: all clean
