CFLAGS = -lncurses

# Libraries
# TODO: curl-config --libs and curl-config --cflags
LDFLAGS = -L/usr/lib/i386-linux-gnu
LDLIBS = -lcurl

# stuff i'll probably need later
# INCLUDE = ...
# SOURCES = ...
# OUT = ...
FILES = main


all: $(FILES)

clean:
	rm -rf ./main

check:
	valgrind ./$(FILES)


# Always use the 'clean' target defined in this file.
.PHONY: clean
