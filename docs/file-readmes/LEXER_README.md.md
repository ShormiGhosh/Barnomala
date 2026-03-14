# LEXER_README.md Detailed Explanation

This file is the canonical full-depth explanation document for blexer.l.

How to use it effectively:
1. Keep blexer.l open in split view.
2. Read section-by-section in exact order.
3. Verify each regex rule and action pair against live source.

What this document already covers in depth:
- Flex 3-section file model.
- C prologue intent and shared-token dependencies.
- Indentation stack algorithm and why pending INDENT/DEDENT exists.
- YY_DECL wrapper trick for token emission ordering.
- Rule ordering details (longest-match + first-rule-wins behavior).
- Bangla UTF-8 literal/identifier/number regex strategies.
- Comment-state transitions.
- EOF dedent flushing.
- Wrapper yylex token-flow examples.

Why this is important for the project:
- Indentation correctness and token correctness start here.
- Parser quality and AST quality depend directly on lexer token stream quality.

