CC=g++
CFLAGS= -g -std=c++11
LDFLAGS =
SOURCES=main.cpp gearball.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=RUNME

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm *.o RUNME

test:
	g++ -g -std=c++11 test.cpp gearball.cpp -o TEST
