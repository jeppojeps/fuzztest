AFL_CLANG=
SOURCES=test_fuzzing.c
EXECUTABLE=test_fuzzing
INPUTS=inputs

ifndef AFL_CLANG
$(error Variable AFL_CLANG is not set, point to your afl-clang binary)
endif

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(AFL_CLANG) $^ -o $@

.PHONY: fuzz

fuzz: $(EXECUTABLE) $(INPUTS)
	$(AFL_FUZZ) -i $(INPUTS) -o findings_dir -- $(EXECUTABLE)
