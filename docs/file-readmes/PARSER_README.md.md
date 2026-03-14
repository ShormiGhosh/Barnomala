# PARSER_README.md Detailed Explanation

This file is the long-form educational guide for bparser.y and Bison behavior.

---

## 1) What this readme explains

- Bison file structure and generated outputs.
- semantic value flow using %union and typed tokens.
- precedence declarations and ambiguity resolution.
- grammar construction patterns for statements and expressions.
- parser/runtime interaction model.

---

## 2) How to read it effectively

Recommended workflow:
1. Open bparser.y side-by-side.
2. Read declaration sections first.
3. Follow grammar in top-down parse order.
4. Trace one sample input through program -> statements -> expression rules.

---

## 3) Why this file matters

For this project, parser is not only syntax checker:
- It builds executable AST.
- It triggers AST execution entrypoint.
- It optionally triggers AST -> TAC emission in --ir mode.

So understanding parser guide means understanding both syntax and runtime orchestration.

---

## 4) Core topics to focus on

### Token typing and non-terminal typing
- explains why semantic fields must match YYSTYPE variants.

### Precedence lines
- explains why they remove shift/reduce ambiguity in expressions.

### Statement chaining
- explains left-recursive N_SEQ construction and execution order.

### Block suites
- shows how INDENT/DEDENT token stream maps to nested AST bodies.

### Function and array grammar
- details parameter/argument list shape and right-linked list behavior.

### CLI integration
- ties grammar output to main function run lifecycle and IR writing logic.

