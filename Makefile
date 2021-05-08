SHELL = /bin/sh

REQ_CFLAGS = --std=c99 -fPIC -s
WARN_CFLAGS = -Wall -Wextra
CFLAGS ?= -Ofast -flto -pipe
ACTUAL_CFLAGS = $(REQ_CFLAGS) $(WARN_CFLAGS) $(CFLAGS)

DESTDIR ?= /
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin

CC ?= gcc
STRIP ?= strip
CP ?= cp
RM ?= rm


default: bottom-encode bottom-decode

bottom-encode:
	$(CC) $(ACTUAL_CFLAGS) bottom-encode.c -o bottom-encode

bottom-decode:
	$(CC) $(ACTUAL_CFLAGS) bottom-decode.c -o bottom-decode


install: default
	$(CP) bottom-encode bottom-decode $(DESTDIR)$(BINDIR)

uninstall:
	$(RM) $(DESTDIR)$(BINDIR)/bottom-encode $(DESTDIR)$(BINDIR)/bottom-decode

clean:
	$(RM) bottom-encode bottom-decode
