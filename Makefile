CC = gcc
CFLAGS = -Wall -Wextra -g
INCLUDES = -I./include
SRCDIR = src
OBJDIR = obj
DATADIR = data

# List of source files
SRCS = $(wildcard $(SRCDIR)/*.c)

# Generate object file names from source files
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# CSV files
CSVFILES = $(wildcard *.csv)

# Phony target to compile all
all: main

main: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Rule to compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

.PHONY: clean copy-csv run

clean:
	rm -rf $(OBJDIR) main

# Rule to copy CSV files to the build directory
copy-csv:
	mkdir -p $(DATADIR)
	cp $(CSVFILES) $(DATADIR)

run: main copy-csv
	./main

