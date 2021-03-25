all: ww
ww: ww.c
	gcc -Wall -Werror -Wvla -fsanitize=address,undefined -std=c99 ww.c -o ww

clean: 
	rm -f ww