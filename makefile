CC=gcc
all:
	$(CC)   -I/home/panchenliang/tux/include -o hello   -L/home/panchenliang/tux/lib simpcl.c  -ltux -lbuft  -lfml -lfml32 -lengine  -ldl -lpthread /usr/lib/libcrypt.a \
		`pkg-config --cflags --libs gtk+-2.0`

