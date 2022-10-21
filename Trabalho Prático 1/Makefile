CC ?= gcc
ZIP ?= 7za
CFLAGS += -Wall -Wextra -Wpedantic
LDFLAGS += -lm
VDFLAGS += --leak-check=full --show-leak-kinds=all -s

SRCDIRS = $(sort $(dir $(wildcard src/*/)))
INC_PARAMS = $(addprefix -I ,$(SRCDIRS))

EXECUTABLE ?= build/programaTrab

ZIPFILE    ?= ../zipfile.zip
CFILES      = $(wildcard src/*.c) $(wildcard src/**/*.c)

.PHONY: all clean zip run test debug

all: $(EXECUTABLE)

clean:
	@rm -f $(ZIPFILE)
	@rm -rf build/
	@rm -rf out/*.csv

zip: clean
	$(ZIP) a $(ZIPFILE) ./*

run: $(EXECUTABLE)
	@./$(EXECUTABLE) $(ARGS)

debug: CFLAGS+= -g
debug: clean
debug: $(EXECUTABLE)

$(EXECUTABLE): $(CFILES)
	@mkdir -p build
	$(CC) $(CFLAGS) $(INC_PARAMS) -o $@ $^ $(LDFLAGS)

valgrind: $(EXECUTABLE)
	valgrind $(VDFLAGS) ./$(EXECUTABLE)
