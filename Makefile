SRC            = $(wildcard src/*.c)
LDFLAGS        =
DEBUG_FLAGS    = -DDEBUG_BUILD
DEBUG_DIR      = ./build/debug
DEBUG_OBJS     = $(addprefix $(DEBUG_DIR)/, $(notdir $(SRC:.c=.o)))
DEBUG_TARGET   = $(DEBUG_DIR)/main
RELEASE_FLAGS  =
RELEASE_DIR    = ./build/release
RELEASE_OBJS   = $(addprefix $(RELEASE_DIR)/, $(notdir $(SRC:.c=.o)))
RELEASE_TARGET = $(RELEASE_DIR)/main
all:
	make $(DEBUG_TARGET)

release:
	make $(RELEASE_TARGET)

$(DEBUG_DIR):
	mkdir -p $@

$(DEBUG_TARGET): $(DEBUG_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(DEBUG_DIR)/%.o: src/%.c $(DEBUG_DIR)
	$(COMPILE.c) $(DEBUG_FLAGS) -o $@ $<

$(RELEASE_DIR):
	mkdir -p $@

$(RELEASE_TARGET): $(RELEASE_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(RELEASE_DIR)/%.o: src/%.c $(RELEASE_DIR)
	$(COMPILE.c) $(RELEASE_FLAGS) -o $@ $<
clean:
	$(RM) -r build

.PHONY: all clean
