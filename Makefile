CC=g++
CFLAGS=-c -Wall 
LDFLAGS= 
SOURCES=main.cpp Car.cpp Background.cpp tiny_obj_loader.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=a.out
INCLUDE=
LIBS =  -L /usr/X11R6/lib/ -lglut -lGL -lGLU -lX11 -lm 
all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $(INCLUDE) $@
clean:
	$(RM) *.o $(EXECUTABLE) *.o

