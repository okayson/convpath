PROGRAM = convpath

OBJS = convpath.o

INCLUDES = -I.

INSTALL_DIR = /usr/local/bin

#CXX=c++
CXXFLAGS += -Wall -O2
# --- for Debug
#CXXFLAGS_DEBUG = -g
#CXXFLAGS += $(CXXFLAGS_DEBUG)
# --- for Measure
#CXXFLAGS += -std=c++11 -D_MEASURE

.PHONEY: all clean rebuild depend install

all: depend $(PROGRAM)

clean: 
	$(RM) $(PROGRAM) $(OBJS) depend.inc

rebuild: clean all

install: all
	-@ cp -f ./$(PROGRAM) $(INSTALL_DIR)/$(PROGRAM)
	-@echo $(PROGRAM) was installed to $(INSTALL_DIR)

$(PROGRAM): $(OBJS)
	$(CXX) -o $(PROGRAM) $^

.SUFFIXES: .cpp .o

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

depend: $(OBJS:.o=.cpp)
	-@ $(RM) depend.inc
	-@ for i in $^; do cpp -MM $$i | sed "s/\[_a-zA-Z0-9][_a-zA-Z0-9]*\.c//g" >> depend.inc; done
-include depend.inc

