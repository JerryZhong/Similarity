XXFLAGS= -O2 
CXXFLAGS= -g 
SRC_DIRS=.
INCLUDE_DIRS=-I ./include
LIBS=-lpthread
all: similarity

SRC=$(foreach srcdir, $(SRC_DIRS),$(wildcard $(srcdir)/*.cpp))
OBJS:=$(patsubst %.cpp, %.o, $(SRC))


vpath %.h $(INCLUDE_DIRS)
vpath %.cpp $(SRC_DIRS)


similarity: $(OBJS)
	$(CXX) $(CXXFLAGS) ${LIBS}    $^ -o  $@  

$(OBJS):%.o:%.cpp  
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<  -o $@ 

.PHONY : clean
clean:
	-@rm -rf $(OBJS)  similarity
