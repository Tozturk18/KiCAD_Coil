CC = gcc
CFLAGS = -w -Wall -Wextra -std=c99
LDFLAGS = -lm

TARGET = coil
SRCS = coil.c
LIBS = libs/TextToMath/textMath.c
OBJS = $(SRCS:.c)

ifeq ($(shell uname),tozturk)
	LDFLAGS += -Wl,-no_compact_unwind
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) $(LIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
