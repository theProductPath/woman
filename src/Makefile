# WOMAN - WoMAN Pages
# Originally by Steven R. Jones, 1989
# Modernized for ncurses/POSIX systems, 2026

CC = cc
CFLAGS = -Wall -O2
LDFLAGS = -lncurses

# On Linux you may also need: -ltinfo
# On macOS, ncurses is included with the system

HEADER = woman.h

SRC = main.c highlt.c get_comm.c get_topics.c pick_topic.c \
      pr_array.c get_string.c pr_heading.c end_prog.c story.c

OBJ = $(SRC:.c=.o)

TARGET = woman

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/woman
	@echo "Installed woman to /usr/local/bin/woman"

.PHONY: all clean install
