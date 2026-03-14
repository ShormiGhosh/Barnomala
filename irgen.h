#ifndef IRGEN_H
#define IRGEN_H

#include "ast.h"
#include "tac.h"

void tac_generate_from_ast(const AstNode *root, TacProgram *out);

#endif /* IRGEN_H */
