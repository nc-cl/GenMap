CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Wold-style-cast -Wuseless-cast -Werror -Wpedantic
GLFLAGS = -lSDL2 -lGLEW -lGL

DEPENDENCIES = main.o height_map.o shader_handler.o height_map_mesh.o
EXECUTABLE = main

DEPENDENCIES_NO_GUI = main.o height_map.o noise_generator.o
EXECUTABLE_NO_GUI  = main_nogui

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(DEPENDENCIES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(DEPENDENCIES) $(GLFLAGS)

.PHONY: no_gui
no_gui: $(EXECUTABLE_NO_GUI)

$(EXECUTABLE_NO_GUI): $(DEPENDENCIES_NO_GUI)
	$(CC) $(CFLAGS) -o $(EXECUTABLE_NO_GUI) $(DEPENDENCIES_NO_GUI)

%.o: %.cc
	$(CC) $(CFLAGS) -c $^

.PHONY: clean 
clean:
	rm -fv $(EXECUTABLE) $(EXECUTABLE_NO_GUI)  *\.exe *\.o
