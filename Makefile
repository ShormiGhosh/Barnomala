# Makefile for Bangla Compiler (Lexer + Parser)

# Compiler and tools
LEX = flex
YACC = bison
CC = /mingw64/bin/gcc
CFLAGS = -Wall -Wno-unused-function

# Target executable
TARGET = barnomala
INPUT = binput.bn.txt
OUTPUT = result.txt

# Source files
LEX_SOURCE = blexer.l
YACC_SOURCE = bparser.y
LEX_OUTPUT = lex.yy.c
YACC_OUTPUT = bparser.tab.c
YACC_HEADER = bparser.tab.h
SYMTABLE_SRC = symtable.c
SYMTABLE_HDR = symtable.h
AST_SRC = ast.c
AST_HDR = ast.h
TAC_SRC = tac.c
TAC_HDR = tac.h
IRGEN_SRC = irgen.c
IRGEN_HDR = irgen.h

# Default target
all: $(TARGET)

# Generate parser C code and header from Bison specification
$(YACC_OUTPUT) $(YACC_HEADER): $(YACC_SOURCE)
	$(YACC) -d $(YACC_SOURCE)

# Generate lexer C code from Flex specification (depends on parser header)
$(LEX_OUTPUT): $(LEX_SOURCE) $(YACC_HEADER)
	$(LEX) $(LEX_SOURCE)

# Compile the lexer, parser, symbol table and AST together
$(TARGET): $(LEX_OUTPUT) $(YACC_OUTPUT) $(SYMTABLE_SRC) $(SYMTABLE_HDR) $(AST_SRC) $(AST_HDR) $(TAC_SRC) $(TAC_HDR) $(IRGEN_SRC) $(IRGEN_HDR)
	$(CC) $(CFLAGS) $(LEX_OUTPUT) $(YACC_OUTPUT) $(SYMTABLE_SRC) $(AST_SRC) $(TAC_SRC) $(IRGEN_SRC) -o $(TARGET) -lm
	@echo "✓ Compilation successful! Executable: $(TARGET)"

# Run the compiler on input file
run: $(TARGET)
	./$(TARGET) $(INPUT)

# Test - run and save output
test: $(TARGET)
	./$(TARGET) $(INPUT) > $(OUTPUT) 2>&1
	@echo "✓ Test complete. Output saved to $(OUTPUT)"

# Test simple program
test-simple: $(TARGET)
	./$(TARGET) test_simple.bn.txt > test_output.txt 2>&1
	@echo "✓ Test complete. Output saved to test_output.txt"
	@cat test_output.txt

# Clean generated files
clean:
	rm -f $(LEX_OUTPUT) $(YACC_OUTPUT) $(YACC_HEADER) $(TARGET) $(TARGET).exe $(OUTPUT) test_output.txt
	@echo "✓ Cleaned all generated files"

# Rebuild everything
rebuild: clean all

.PHONY: all run test clean rebuild
