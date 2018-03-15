CC=g++
CCFLAGS = -Wall -g -O3
INC_PATH = -I.

LIBRARY_PATH = ""
LIBRARY_FLAG = ""

# OBJS = msymtable.o test_msymtable.o

test: test_msymtable

clean: 
	rm -rf msymtable.o test_msymtable.o

.cc.o :
	@echo "Building $@"
	$(CC) $(CCFLAGS) -o $@ -c $< $(INCLUDE_PATH)
	
test_msymtable: test_msymtable.o msymtable.o
	@echo "Building $@"
	$(CC) $(CCFLAGS) -o $@ $< msymtable.o $(INCLUDE_PATH)
	