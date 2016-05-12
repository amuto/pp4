default: win

win: win.c
	gcc -Wall -o win `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

clean:
	rm -f *~ *.o win

