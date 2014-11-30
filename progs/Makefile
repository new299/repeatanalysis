RM = /bin/rm -f

C++ = emcc
CCFLAGS = -I. -O3

LDFLAGS =

.PHONY: all

all: repchar repeatscore_printonly repeatscore_make_matrix rotate_matrix trim_matrix add_unique_breaks symbolpos getsequence

repeatscore_printonly: repeatscore_printonly.cpp Array.h BitPlusArray.h KarkSuffixArray.h SimpleArray.h SuffixArray.h combined.h
	@echo --- $@ ---
	$(C++) $(CCFLAGS) repeatscore_printonly.cpp -o bin/repeatscore_printonly $(LDFLAGS)

repeatscore_make_matrix: repeatscore_make_matrix.cpp Array.h BitPlusArray.h KarkSuffixArray.h SimpleArray.h SuffixArray.h combined.h
	@echo --- $@ ---
	$(C++) $(CCFLAGS) repeatscore_make_matrix.cpp -o bin/repeatscore_make_matrix $(LDFLAGS)

rotate_matrix: rotate_matrix.cpp 
	@echo --- $@ ---
	$(C++) $(CCFLAGS) rotate_matrix.cpp -o bin/rotate_matrix $(LDFLAGS)

trim_matrix: trim_matrix.cpp 
	@echo --- $@ ---
	$(C++) $(CCFLAGS) trim_matrix.cpp -o bin/trim_matrix $(LDFLAGS)

add_unique_breaks: add_unique_breaks.cpp 
	@echo --- $@ ---
	$(C++) $(CCFLAGS) add_unique_breaks.cpp -o bin/add_unique_breaks $(LDFLAGS)

repchar: repchar.cpp
	@echo --- $@ ---
	$(C++) $(CCFLAGS) repchar.cpp -o bin/repchar $(LDFLAGS)

symbolpos: symbolpos.cpp
	@echo --- $@ ---
	$(C++) $(CCFLAGS) symbolpos.cpp -o bin/symbolpos $(LDFLAGS)

repeatscore_printonly_debug: repeatscore_printonly.cpp Array.h BitPlusArray.h KarkSuffixArray.h SimpleArray.h SuffixArray.h combined.h
	@echo --- $@ ---
	$(C++) $(CCFLAGS) repeatscore_printonly.cpp -g -o bin/repeatscore_printonly-g $(LDFLAGS)

repeatscore_make_matrix_debug: repeatscore_make_matrix.cpp Array.h BitPlusArray.h KarkSuffixArray.h SimpleArray.h SuffixArray.h combined.h
	@echo --- $@ ---
	$(C++) $(CCFLAGS) repeatscore_make_matrix.cpp -g -o bin/repeatscore_make_matrix-g $(LDFLAGS)

calc_posplot: calc_posplot.cpp
	@echo --- $@ ---
	$(C++) $(CCFLAGS) calc_posplot.cpp -o bin/calc_posplot

add_unique_breaks: add_unique_breaks.cpp
	@echo --- $@ ---
	$(C++) $(CCFLAGS) add_unique_breaks.cpp -o bin/add_unique_breaks

getsequence: get_sequence.cpp
	@echo --- $@ ---
	$(C++) $(CCFLAGS) get_sequence.cpp -o bin/getsequence

repeatscore_ems: repeatscore_ems.cpp
	emcc ./repeatscore_ems.cpp -o repeatscore_ems.js -s EXPORTED_FUNCTIONS="['_repeat_score']" -s SAFE_HEAP=1 -g -s ASSERTIONS=1 

clean:
	@echo --- $@ ---
	-$(RM) *.o core
