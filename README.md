"# Barnomala - Bangla Programming Language Compiler

A compiler for a programming language using Bangla (Bengali) syntax. This project implements lexical analysis and syntax parsing for a comprehensive set of programming constructs.

## Project Structure

```
Barnomala/
├── blexer.l          # Flex lexical analyzer
├── bparser.y         # Bison syntax parser
├── binput.bn.txt     # Sample Bangla program
├── Makefile          # Build configuration
└── README.md         # This file
```

## Features

### Indentation-Based Blocks
Barnomala uses **Python-style indentation** to define code blocks. Use consistent indentation (spaces or tabs) to nest statements:

```bangla
যদি বয়স ১৮ থেকে বড়ঃ
    দেখাও "প্রাপ্তবয়স্ক"।
    দেখাও "ভোট দিতে পারবেন"।
নাহলে
    দেখাও "কিশোর"।
```

**Important**: 
- Use **4 spaces** or **1 tab** per indentation level
- Be consistent throughout your program
- Indentation determines where blocks begin and end

### Data Types
- `সংখ্যা` - Integer (Number)
- `দশমিক` - Float (Decimal)
- `বুলিয়ান` - Boolean
- `অক্ষর` - Character
- `বাক্য` - String

### Control Structures
- `যদি` / `নাহলে` - If/Else
- `যতক্ষণ` - While loop
- `ঘুরতে_থাক` - For loop
- `প্রক্রিয়া` - Function definition

### Input/Output
- `নাও(variable)।` - Input from user
- `দেখাও expression।` - Print output

### Operators
- Arithmetic: `যোগ` (+), `বিয়োগ` (-), `গুণ` (*), `ভাগ` (/), `ভাগশেষ` (%)
- Comparison: `সমান` (==), `অসমান` (!=), `বড়` (>), `ছোট` (<)
- Logical: `এবং` (&&), `অথবা` (||), `নয়` (!)

### Math Functions
- `শক্তি(base, exp)` - Power
- `বর্গমূল(n)` - Square root
- `ফ্লোর(n)` - Floor
- `সিল(n)` - Ceiling
- `পরম(n)` - Absolute value

## Building the Compiler

### Prerequisites
- Flex (lexical analyzer generator)
- Bison (parser generator)
- GCC (C compiler)

### On Windows with MSYS64:
```bash
cd /home/Shormi/Barnomala
make clean
make
```

### On Linux/Unix:
```bash
make clean
make
```

## Running the Compiler

### Parse a Bangla program:
```bash
./barnomala binput.bn.txt
```

### Or use make:
```bash
make run
```

## Example Program

```bangla
শুরু_প্রোগ্রাম

মন্তব্য ইনপুট নেওয়ার উদাহরণ মন্তব্য_শেষ
সংখ্যা বয়স।
দেখাও "আপনার বয়স লিখুনঃ "।
নাও(বয়স)।
দেখাও বয়স।

যদি বয়স ১৮ থেকে বড়ঃ
    দেখাও "প্রাপ্তবয়স্ক"।
নাহলে
    দেখাও "কিশোর"।

শেষ_প্রোগ্রাম
```

## Input Syntax Examples

### Taking Integer Input:
```bangla
সংখ্যা সংখ্যা_ভ্যার।
দেখাও "একটি সংখ্যা লিখুনঃ "।
নাও(সংখ্যা_ভ্যার)।
```

### Taking String Input:
```bangla
বাক্য নাম।
দেখাও "আপনার নামঃ "।
নাও(নাম)।
```

### Taking Float Input:
```bangla
দশমিক উচ্চতা।
নাও(উচ্চতা)।
```

## Compiler Phases

### ✅ Phase 1: Lexical Analysis (COMPLETED)
- Tokenizes Bangla source code
- Handles Bengali numerals (০-৯)
- Recognizes keywords, operators, and literals

### ✅ Phase 2: Syntax Analysis (COMPLETED)
- Validates program structure
- Checks grammar rules
- Builds parse tree

### 🚧 Phase 3: Semantic Analysis (IN PROGRESS)
- Type checking
- Symbol table management
- Scope resolution

### 📋 Phase 4: Code Generation (PLANNED)
- Generate intermediate code
- Target code generation
- Optimization

## Development

### Clean build:
```bash
make clean
```

### Rebuild:
```bash
make rebuild
```

### Test with output:
```bash
make test
cat result.txt
```

## Language Syntax Reference

### Program Structure:
```bangla
শুরু_প্রোগ্রাম
    [statements]
শেষ_প্রোগ্রাম
```

### Variable Declaration:
```bangla
type identifier।
type identifier = value।
```

### Comments:
```bangla
মন্তব্য your comment here মন্তব্য_শেষ
```

## Contributing

This is an educational project for building a compiler for Bengali language programming.

## License

Educational/Open Source Project

---

**Note**: This compiler is under active development. The lexical and syntax analysis phases are complete. Semantic analysis and code generation are in progress.
```" 
