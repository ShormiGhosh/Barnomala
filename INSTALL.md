# Installation Guide for Barnomala Compiler

## Prerequisites

You need to install Flex and Bison in your MSYS64 environment.

## Installation Steps

### Option 1: Using MSYS64 Package Manager (Recommended)

Open MSYS64 terminal and run:

```bash
# Update package database
pacman -Syu

# Install development tools
pacman -S base-devel

# Install Flex (lexer generator)
pacman -S flex

# Install Bison (parser generator)
pacman -S bison

# Install GCC compiler (if not already installed)
pacman -S gcc

# Verify installations
flex --version
bison --version
gcc --version
```

### Option 2: Install Specific Packages

If you want to install only what's needed:

```bash
pacman -S flex bison gcc make
```

### Option 3: Using MinGW-w64

If you're using MinGW-w64 instead of MSYS2:

```bash
pacman -S mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-flex
pacman -S mingw-w64-x86_64-bison
```

## After Installation

Once installed, navigate to your project directory and build:

```bash
cd ~/Barnomala
make clean
make
```

## Troubleshooting

### "bison: command not found"
- Make sure you ran the installation commands above
- Restart your MSYS64 terminal after installation
- Check if bison is in your PATH: `which bison`

### "flex: command not found"
- Install flex using: `pacman -S flex`

### Permission Issues
- Run MSYS64 as administrator if you get permission errors during installation

## Testing Your Installation

Create a test to verify everything works:

```bash
# Check flex
flex --version

# Check bison
bison --version

# Check gcc
gcc --version

# Build the compiler
cd ~/Barnomala
make clean
make

# Run test
./barnomala test_simple.bn.txt
```

## Expected Output

After successful installation and build:
```
✓ Compilation successful! Executable: barnomala
```

Then when you run a program:
```
=== Parsing Bangla Program ===

Declaration: ...
Print statement
...

✓ Program parsed successfully!

=== Parsing Complete ===
```
