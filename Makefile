CC      ?= gcc
INSTALL ?= install

PREFIX  ?= /usr/local
BINDIR  ?= $(PREFIX)/bin
CFLAGS  ?= -Ofast -flto -pipe

REQ_CFLAGS    = --std=c99 -fPIC -s
WARN_CFLAGS   = -Wall -Wextra
ACTUAL_CFLAGS = $(REQ_CFLAGS) $(WARN_CFLAGS) $(CFLAGS)

SRC := bottom-encode bottom-decode

all: $(SRC:%.c=%)

%: %.c
	$(CC) $(ACTUAL_CFLAGS) $@.c -o $@

install: all
	mkdir -p $(DESTDIR)$(BINDIR)
	$(INSTALL) -Dm755 $(SRC) $(DESTDIR)$(BINDIR)

uninstall:
	rm -rf $(addprefix $(DESTDIR)$(BINDIR)/, $(SRC))

clean:
	rm -r $(SRC)

.PHONY: all clean install
