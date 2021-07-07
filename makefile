CXX = g++
CFLAGS = -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP 
LFLAGS = -lpthread
SOURCES = ./src/CppCICD.cpp
OBJS = $(SOURCES:.cpp=.o)
EXE = demoApp

all: $(SOURCES) $(EXE)

$(EXE): $(OBJS)
	$(CXX)  $(OBJS) -o $@ $(LFLAGS)

.cpp.o:
	$(CXX) $(CFLAGS) $< -o $@

clean: 
	rm ./src/*.o $(EXE)

clean-all: 
	rm ./src/*.o ./src/*.d $(EXE)
