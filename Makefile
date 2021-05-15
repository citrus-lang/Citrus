SRC            = $(wildcard src/*.c)
LDFLAGS        =
DEBUG_FLAGS    = -DDEBUG_BUILD
DEBUG_DIR      = ./build/debug
DEBUG_OBJS     = $(addprefix $(DEBUG_DIR)/, $(subst src/,,$(SRC:.c=.o)))
DEBUG_TARGET   = $(DEBUG_DIR)/main
RELEASE_FLAGS  =
RELEASE_DIR    = ./build/release
RELEASE_OBJS   = $(addprefix $(RELEASE_DIR)/, $(subst  src/,,$(SRC:.c=.o)))
RELEASE_TARGET = $(RELEASE_DIR)/main
UNITTEST_DIR   = ./build/test
UNITTEST_OBJS  = $(filter-out $(DEBUG_DIR)/main.o,$(DEBUG_OBJS))
UNITTEST_FLAGS = -DUNIT_TEST

all:
	make $(DEBUG_TARGET)

release:
	make $(RELEASE_TARGET)

$(DEBUG_TARGET): $(DEBUG_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(DEBUG_DIR)/%.o: src/%.c
	[ -d $(dir $@) ] || mkdir -p $(dir $@)
	$(COMPILE.c) $(DEBUG_FLAGS) -o $@ $<

$(RELEASE_TARGET): $(RELEASE_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(RELEASE_DIR)/%.o: src/%.c
	[ -d $(dir $@) ] || mkdir -p $(dir $@)
	$(COMPILE.c) $(RELEASE_FLAGS) -o $@ $<

define UNITTEST
	[ -d $(dir $(UNITTEST_DIR)/$(1)) ] || mkdir -p $(dir $(UNITTEST_DIR)/$(1))
	$(CC) $(UNITTEST_FLAGS) -o $(UNITTEST_DIR)/$(1) src/$(1).c $(filter-out $(DEBUG_DIR)/$(1).o,$(UNITTEST_OBJS))
	./$(UNITTEST_DIR)/$(1)

endef

unittest:
	$(foreach p,$(filter-out main,$(subst src/,,$(SRC:.c=))),$(call UNITTEST,$(p)))

clean:
	$(RM) -r build

.PHONY: all clean release
