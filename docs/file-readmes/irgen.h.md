# বর্ণমালা (Barnomala) — IR Generator Header Detailed Explanation (irgen.h)

This header exposes the AST-to-TAC lowering entrypoint.

---

## Header guard and includes

```c
#ifndef IRGEN_H
#define IRGEN_H
#include "ast.h"
#include "tac.h"
...
#endif
```
Purpose:
- standard include protection.
- binds input AST type and output TAC type.

---

## Public function

```c
void tac_generate_from_ast(const AstNode *root, TacProgram *out);
```
Purpose:
- converts full AST rooted at `root` into TAC instructions appended into `out`.

Caller contract:
- initialize `out` before call.
- free `out` after use.
