#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "tree.h"
#include "transform.h"

int main(void)
{
    Token tokens[256];
    size_t tokens_qty = 0;

    Token token;
    token_next(&token);

    while (token.type != FINAL) {
        tokens[tokens_qty] = token;
        token_next(&token);
        tokens_qty++;
    }

    Tree tree = tree_create(tokens, 0, tokens_qty - 1);

    printf("\nExpression tree:\n");
    tree_print(tree, 0);

    tree_transform(&tree);

    printf("\nSemitransformed expression tree:\n");
    tree_print(tree, 0);

    printf("\nTree's infix linearization:\n");
    tree_infix(tree);
    printf("\n");

    return 0;
}