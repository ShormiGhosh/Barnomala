# Makefile for Bangla Lexer

# Compiler and tools
LEX = flex
CC = gcc
CFLAGS = -Wall

# Target executable
TARGET = blexer.exe
INPUT = binput.bn.txt
OUTPUT = result.txt

# Source files
LEX_SOURCE = blexer.l
LEX_OUTPUT = lex.yy.c

# Default target
all: run

# Generate lexer C code from flex specification
$(LEX_OUTPUT): $(LEX_SOURCE)
	$(LEX) $(LEX_SOURCE)

# Compile the lexer
$(TARGET): $(LEX_OUTPUT)
	$(CC) $(CFLAGS) $(LEX_OUTPUT) -o $(TARGET)

# Run the lexer on input file
run: $(TARGET)
	./$(TARGET) $(INPUT) > $(OUTPUT)
	@echo "Lexical analysis complete. Output saved to $(OUTPUT)"

# Clean generated files
clean:
	rm -f $(LEX_OUTPUT) $(TARGET) $(OUTPUT)

# Rebuild everything
rebuild: clean all

.PHONY: all run clean rebuild
