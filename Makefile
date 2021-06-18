
OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
PTHREAD = -pthread
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib
CPPFLAGS=-g -std=c++0x -I/usr/local/include -I./irrKlang/include -I./
IRRKLANGPARAMS=./libIrrKlang.so ./ikpMP3.so

BIN=bin/application
SRCS_FILES=House.cpp Shader.cpp texture.cpp Mbox.cpp Humanoid.cpp Main.cpp
INCLUDES_FILES=House.h Shader.h texture.hpp Mbox.h Humanoid.h


INCLUDES = $(addprefix include/,$(INCLUDES_FILES))
SRCS	 = $(addprefix src/,$(SRCS_FILES))

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS) $(IRRKLANGPARAMS) $(PTHREAD)

#$(BIN):
#	g++ $(CPPFLAGS) Main.cpp -o main.out $(LDFLAGS) $(LIBS)
clean:
	rm -f *~ *.o $(BIN)
