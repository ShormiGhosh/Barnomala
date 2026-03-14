# README.md Detailed Explanation

This document explains each major section of README.md and what it means for users and contributors.

---

## 1) Title and project summary

The first lines declare:
- Project name: Barnomala.
- High-level goal: Bangla-syntax programming language compiler/interpreter.

Why this matters:
- Sets user expectation that the language itself uses Bengali keywords and syntax.

---

## 2) Project structure section

The tree block lists key files so a new user knows where lexer, parser, and build config live.

Interpretation:
- blexer.l: lexical phase definition.
- bparser.y: grammar and parser entrypoint.
- sample input files: quick run demos.
- Makefile: build automation.

---

## 3) Features and syntax model

The README feature sections are the language contract presented to end users.

### Indentation-based blocks
- Explains block syntax similar to Python.
- Clarifies spaces/tabs consistency requirements.

### Data types
- Lists five primary Bangla data types mapped to runtime behavior.

### Control structures and functions
- Introduces conditional, loop, and function constructs.

### I/O and operators
- Documents user-facing keywords and symbolic aliases.

### Math functions
- Describes built-in operations lowered to runtime math behavior.

---

## 4) Build instructions

README gives platform-specific command sequences.

Important usage:
- On MSYS64, build inside the project directory.
- Make targets encapsulate code-generation and compilation steps.

---

## 5) Run instructions

Core execution modes:
- Standard parse+execute run.
- --ir mode for TAC output file generation.

This section connects directly to bparser.y CLI logic.

---

## 6) Example programs

The example blocks are practical grammar references.

How to use them for learning:
- Start with small declaration/input/if snippets.
- Move to loop/function/array and builtin math examples.

---

## 7) Compiler phase status

This section communicates current implementation maturity.

Current meaning in repo state:
- Lexer and parser are implemented.
- Semantic and IR/TAC generation are active work areas and implemented in significant parts.

---

## 8) Development utility targets

Commands like clean, rebuild, and test are documented for contributor workflow.

Tip:
- `make clean; make` ensures parser/lexer generated artifacts are fresh after grammar/scanner edits.

