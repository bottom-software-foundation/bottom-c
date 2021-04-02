SHELL = /bin/sh

CFLAGS = -Wall -Wextra --std=c99 -Ofast -fPIC

CC ?= gcc
STRIP ?= strip
CP ?= cp
RM ?= rm


default: bottom-encode bottom-decode

bottom-encode:
	$(CC) $(CFLAGS) bottom-encode.c -o bottom-encode
	$(STRIP) ./bottom-encode

bottom-decode:
	$(CC) $(CFLAGS) bottom-decode.c -o bottom-decode
	$(STRIP) ./bottom-decode


install: default
	$(CP) bottom-encode bottom-decode /usr/bin

uninstall:
	$(RM) /usr/bin/bottom-encode /usr/bin/bottom-decode

clean:
	$(RM) bottom-encode bottom-decode
