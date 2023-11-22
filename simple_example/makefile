SOURCES=test_fuzzing.c
EXECUTABLE=test_fuzzing
INPUTS=inputs

ifndef AFL_CLANG
$(error Variable AFL_CLANG is not set, point to your afl-clang binary)
endif

ifndef AFL_FUZZ
    $(error variable AFL_FUZZ is not set, point to afl-fuzz binary)
endif

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(AFL_CLANG) $^ -o $@

.PHONY: clean
    
clean: $(EXECUTABLE)
	rm -f $(EXECUTABLE)

.PHONY: fuzz

fuzz: $(EXECUTABLE) $(INPUTS)
	$(AFL_FUZZ) -i $(INPUTS) -o findings_dir -- $(PWD)/$(EXECUTABLE)
