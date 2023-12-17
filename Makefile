CC = clang++
CFLAGS = -std=c++20 -Wall -Wextra
LDFLAGS = -lsfml-system -lsfml-window -lsfml-graphics -ltmxlite -fsanitize=address

SOURCES = main.cpp Level.cpp Hud.cpp Label.cpp Game.cpp GameManager.cpp Animations.cpp sys/AISystem.cpp sys/RenderSystem.cpp sys/PhysicsSystem.cpp sys/CollisionSystem.cpp sys/InputSystem.cpp sys/AnimationSystem.cpp
OBJECTS = $(SOURCES:.cpp=.o)

OBJECTS := $(patsubst %, obj/%, $(OBJECTS))
EXECUTABLE = game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

obj/%.o: %.cpp 
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -rf obj
	rm -f $(EXECUTABLE)
