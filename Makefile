PREFIX  ?= /usr/local
BINDIR  ?= $(PREFIX)/bin
INSTALL ?= install
CFLAGS  ?= -Ofast -flto -pipe

REQ_CFLAGS    = -std=c99 -fPIC
WARN_CFLAGS   = -Wall -Wextra
ACTUAL_CFLAGS = $(REQ_CFLAGS) $(WARN_CFLAGS) $(CFLAGS)

SRC := bottom-encode bottom-decode

all: $(SRC:%.c=%)

%: %.c
	$(CC) $(ACTUAL_CFLAGS) $^ -o $@

install: all
	$(INSTALL) -Dm755 -t $(DESTDIR)$(BINDIR) $(SRC)

uninstall:
	rm -rf $(addprefix $(DESTDIR)$(BINDIR)/, $(SRC))

clean:
	rm -r $(SRC)

.PHONY: all clean install
