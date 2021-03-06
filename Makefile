CFLAGS = -lncurses -lmenu -I/usr/include/libxml2

# Libraries
# TODO: curl-config --libs and curl-config --cflags
#LDFLAGS = -L/usr/lib/i386-linux-gnu
LDLIBS = -lcurl -lxml2

# stuff i'll probably need later
# INCLUDE = ...
# SOURCES = ...
# OUT = ...
FILES = main


all: clean $(FILES)

clean:
	rm -rf ./main

check:
	valgrind ./$(FILES)

pre:
	gcc -E $(FILES) > main.out


# Always use the 'clean' target defined in this file.
.PHONY: clean
