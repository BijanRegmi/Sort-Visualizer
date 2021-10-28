# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall

# Executable
EXEC = sorts

# Source directory
SRC = src

# Include directory
INC = include

# Binaries directory
BIN = bin

# Lib directory
LIBS = none

# Linking flags
LDFLAGS = -pthread  -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system

###################################################################################################

# Source files
SOURCE_FILES = $(wildcard $(SRC)/*.cpp)

# Object files
OBJ_FILES = $(patsubst %,$(BIN)/%, $(notdir $(SOURCE_FILES:.cpp=.o)))

# Create executable from obj files
$(BIN)/$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile source files to create obj files
$(BIN)/%.o: $(SRC)/%.cpp
	$(CC) -c $^ $(CFLAGS) -o $@ -I $(INC) -L $(LIBS)

.PHONY: run clean

# Build & Run executable
run: $(BIN)/$(EXEC)
	./$(BIN)/$(EXEC)

# Clean
clean:
	rm -f $(BIN)/*

# Assign executable to be the default target
all: $(BIN)/$(EXEC)
