APP      := validador-credenciales
VERSION  ?= 0.1.0
CC       ?= gcc
CFLAGS   := -std=c11 -Wall -Wextra -Werror -O2 -Isrc -DAPP_VERSION=\"$(VERSION)\"
LDLIBS   := -lm

BUILD    := build
BIN      := $(BUILD)/bin
REPORTS  := $(BUILD)/reports
DIST     := $(BUILD)/dist

SRC      := src/credencial.c src/main.c
TEST_SRC := src/credencial.c tests/test_credencial.c

.PHONY: all test analyze package clean help
.DEFAULT_GOAL := help

## all: compila el ejecutable
all: $(BIN)/$(APP)

$(BIN)/$(APP): $(SRC) src/credencial.h
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDLIBS)
	@echo "OK: binario en $@ (version $(VERSION))"

## test: compila y ejecuta las pruebas unitarias
test: $(BIN)/test_credencial
	@mkdir -p $(REPORTS)
	./$(BIN)/test_credencial

$(BIN)/test_credencial: $(TEST_SRC) src/credencial.h tests/minitest.h
	@mkdir -p $(BIN) $(REPORTS)
	$(CC) $(CFLAGS) -Itests $(TEST_SRC) -o $@ $(LDLIBS)

## analyze: analisis estatico con cppcheck
analyze:
	@mkdir -p $(REPORTS)
	cppcheck --enable=warning,style --error-exitcode=0 \
	         --quiet --inline-suppr -Isrc src/ 2>&1 | tee $(REPORTS)/cppcheck.txt
	@echo "OK: analisis estatico completado"

## package: empaqueta el binario en un .tar.gz versionado
package: all
	@rm -rf $(DIST)/$(APP)-$(VERSION)
	@mkdir -p $(DIST)/$(APP)-$(VERSION)
	@cp $(BIN)/$(APP) $(DIST)/$(APP)-$(VERSION)/
	@if [ -f README.md ]; then cp README.md $(DIST)/$(APP)-$(VERSION)/; fi
	tar -czf $(DIST)/$(APP)-$(VERSION).tar.gz -C $(DIST) $(APP)-$(VERSION)
	@rm -rf $(DIST)/$(APP)-$(VERSION)
	@echo "OK: artefacto en $(DIST)/$(APP)-$(VERSION).tar.gz"

## clean: borra todo lo generado
clean:
	rm -rf $(BUILD)
	@echo "OK: arbol de compilacion limpio"

## help: muestra los objetivos disponibles
help:
	@echo "Objetivos (VERSION actual: $(VERSION)):"
	@grep -E "^## " $(MAKEFILE_LIST) | sed -e "s/## /  make /"
