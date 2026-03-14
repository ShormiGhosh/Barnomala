# INSTALL.md Detailed Explanation

This guide explains each part of INSTALL.md and how it maps to a working build environment.

---

## 1) Prerequisites section

Lists required tools:
- Flex (scanner generator)
- Bison (parser generator)
- GCC (C compiler)
- Make (build runner)

These are not optional because build pipeline depends on generated lexer/parser C files.

---

## 2) Option 1 (recommended full setup)

Command sequence:
- pacman -Syu
- install base-devel
- install flex, bison, gcc
- verify with --version commands

Why this path is preferred:
- Gives consistent toolchain and common Unix build utilities in MSYS64.

---

## 3) Option 2 (minimal install)

Installs only required compiler-chain packages in one command.

Use when:
- You already have shell tooling and just need language build dependencies.

---

## 4) Option 3 (MinGW-w64 specific)

Uses mingw-w64 package names.

Use when:
- You target MinGW runtime and want matching toolchain variants.

---

## 5) Post-install build verification

The documented commands validate both tool availability and project build success.

Recommended sequence:
1. version checks
2. make clean
3. make
4. run sample program

---

## 6) Troubleshooting section interpretation

Each error note maps to a probable environment issue:
- command not found -> package missing or PATH context mismatch.
- permission issues -> shell privilege/package database state.

If commands work in MSYS64 but not PowerShell:
- run inside MSYS64 shell, or prepend MSYS tool paths in PowerShell environment.

