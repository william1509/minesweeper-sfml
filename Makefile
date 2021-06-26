LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = -g -Wall
CXX := g++
LINKER = g++
TARGET = game

SRCDIR = src
OBJDIR = obj
BINDIR = bin

# all .cpp files
SOURCES  := $(wildcard $(SRCDIR)/*.cpp)

# all .h files
INCLUDES := $(wildcard $(SRCDIR)/*.h)

# obj/*.o
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LIBS) $(CFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	
%.o: %.hpp
	$(CXX) $(CFLAGS) -c $< -o $@

game: $(OBJECTS)
	@echo "** Building the game"
	$(CXX) $(CFLAGS) -o game $(OBJECTS) $(LIBS)
	
.PHONY : $(OBJECTS)

clean:
	@echo "** Removing object files and executable..."
	rm -f bin/game obj/*.o

install:
	@echo '** Installing...'
	cp game /usr/bin/

uninstall:
	@echo '** Uninstalling...'
	$(RM) /usr/bin/game
 