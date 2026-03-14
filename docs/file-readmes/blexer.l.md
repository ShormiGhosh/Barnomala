# বর্ণমালা (Barnomala) — Lexer File Study Guide (blexer.l)

This file contains the same scanner source explained in full detail in the root file LEXER_README.md.

To avoid duplicating a very large document in two places, use this reading path:

1. Read LEXER_README.md for full line-by-line explanation.
2. Keep blexer.l open side-by-side and follow each section in order.

## Quick section-to-section map

### Prologue block
- Includes and shared token header.
- Indentation state globals.
- Helper functions: push_indent, pop_indent, get_current_indent, init_indent.
- YY_DECL redefinition for wrapper scanner pattern.

### Flex directives
- COMMENT exclusive state.
- noyywrap option.
- yylineno tracking option.

### Rules block
- Newline rule with indentation lookahead logic.
- Whitespace and CR skipping.
- Parenthesis/bracket depth tracking.
- Bangla keywords and operator aliases.
- Number literal conversion (Bangla digits -> ASCII digits).
- Comment mode transitions.
- Identifier regex.
- Unknown-character catch-all.
- EOF dedent draining.

### User code block
- yylex wrapper that emits pending INDENT/DEDENT before delegating to internal_yylex.

## Why this file is critical
- It is responsible for indentation-as-syntax behavior.
- It enforces token normalization between symbolic and Bangla operator forms.
- It ensures parser sees clean token stream with consistent UTF-8 handling.

