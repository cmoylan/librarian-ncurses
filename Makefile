CFLAGS = -lncurses

# Libraries
# TODO: curl-config --libs and curl-config --cflags
LDFLAGS = -L/usr/lib/i386-linux-gnu
LDLIBS = -lcurl

# stuff i'll probably need later
# INCLUDE = ...
# SOURCES = ...
# OUT = ...


all: main

clean:
	rm -rf ./main


# Always use the 'clean' target defined in this file.
.PHONY: clean
