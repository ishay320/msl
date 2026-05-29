CFLAGS       = -Wall -Wextra -g -Werror=extra -fsanitize=address,undefined
TESTS        = graph header_array dynamic_array dynamic_stack link_list queue_a
INCLUDE_DIRS = . arrays queue stack link_list
INCLUDES     = $(addprefix -I, $(INCLUDE_DIRS))

BUILD_DIR = build
TESTS_BIN = $(addprefix $(BUILD_DIR)/, $(TESTS))
DEPS      = $(addsuffix .d, $(TESTS_BIN))

test: $(TESTS_BIN)
	$(foreach t,$(TESTS_BIN),./$(t); echo;)

all: $(TESTS_BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%: tests/%_test.c | $(BUILD_DIR)
	cc $(CFLAGS) $(INCLUDES) -MMD -MP $< -o $@ -ggdb3

-include $(DEPS)

coverage: CFLAGS = -Wall -Wextra -g --coverage
coverage: rm
	mkdir -p $(BUILD_DIR)
	$(foreach t,$(TESTS), \
		cc $(CFLAGS) $(INCLUDES) -c tests/$(t)_test.c -o $(BUILD_DIR)/$(t)_test.o && \
		cc --coverage $(BUILD_DIR)/$(t)_test.o -o $(BUILD_DIR)/$(t);)
	$(foreach t,$(TESTS_BIN),./$(t);)
	gcov --object-directory $(BUILD_DIR) tests/*_test.c

rm:
	rm -rf $(BUILD_DIR)

.PHONY: all test rm coverage
