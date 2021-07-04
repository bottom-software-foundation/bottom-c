CC  ?= gcc
CP  ?= cp
RM  ?= rm

PREFIX  ?= /usr/local
BINDIR  ?= $(PREFIX)/bin
CFLAGS  ?= -Ofast -flto -pipe

REQ_CFLAGS    = --std=c99 -fPIC -s
WARN_CFLAGS   = -Wall -Wextra
ACTUAL_CFLAGS = $(REQ_CFLAGS) $(WARN_CFLAGS) $(CFLAGS)

SRC := bottom-encode bottom-decode

all: $(SRC)

bottom-encode:
	$(CC) $(ACTUAL_CFLAGS) bottom-encode.c -o bottom-encode

bottom-decode:
	$(CC) $(ACTUAL_CFLAGS) bottom-decode.c -o bottom-decode

install: all
	mkdir -p $(DESTDIR)$(BINDIR)
	$(CP) $(SRC) $(DESTDIR)$(BINDIR)

uninstall:
	$(RM) $(addprefix $(DESTDIR)$(BINDIR)/, $(SRC))

clean:
	$(RM) $(SRC)

.PHONY: all clean install
