# Barnomala Compiler Working Flow Diagram

```mermaid
flowchart TD
    A[Bangla Source File .bn.txt] --> B[normalize_input in bparser.y]
    B --> C[Lexer blexer.l / internal_yylex]
    C --> D[Token Stream]
    D --> E[Parser bparser.y / yyparse]
    E --> F[AST Construction]

    F --> G[Optional IR Generation]
    G --> H[irgen.c lowers AST to TAC]
    H --> I[tac.c stores and prints TAC]
    I --> J[Write IR File with --ir]

    F --> K[Interpreter Runtime ast.c]
    K --> L[symtable.c scoped symbols + types]
    K --> M[Function table in ast.c]
    K --> N[Program Output]

    O[Build System Makefile] --> P[bison -d bparser.y]
    O --> Q[flex blexer.l]
    O --> R[gcc link ast+symtable+tac+irgen]
    P --> E
    Q --> C
    R --> S[barnomala executable]
    S --> A
```

## Runtime flow summary
1. Input is normalized for specific Bengali Unicode cases.
2. Lexer tokenizes Bangla syntax and indentation into parser tokens.
3. Parser validates grammar and builds AST.
4. If --ir is enabled, AST is lowered into TAC and written to file.
5. AST is interpreted directly for program execution.
