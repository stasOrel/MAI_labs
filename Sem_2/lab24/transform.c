#include "tree.h"
#include "transform.h"
#include <math.h>

int match_sum(Tree *t)
{
    return (
        ((*t) != NULL) && ((*t)->node.type == OPERATOR) && ((*t)->node.data.operator_name == '+')
    );
}

void deep_transform_sum(Tree *firt_slog, Tree *prev, bool is_left, Tree *curr_t) { //is_left определяем с какой стороны оператор '+'

    if (curr_t != NULL) {;
        //Если с двух сторон стоят +
        if ((*curr_t)->left->node.type == OPERATOR && (*curr_t)->left->node.data.operator_name == '+' && (*curr_t)->right->node.type == OPERATOR && (*curr_t)->right->node.data.operator_name == '+') {
            deep_transform_sum(firt_slog, curr_t, true, &(*curr_t)->left);
            deep_transform_sum(firt_slog, curr_t, false, &(*curr_t)->right);
        }

        //Если слева +, справа хрень
        else if ((*curr_t)->left->node.type == OPERATOR && (*curr_t)->left->node.data.operator_name == '+' && (*curr_t)->right->node.type != INTEGER) {
            deep_transform_sum(firt_slog, curr_t, true, &(*curr_t)->left);
        }

        //Если слева хрень, справа +
        else if ((*curr_t)->left->node.type != INTEGER && (*curr_t)->right->node.type == OPERATOR && (*curr_t)->right->node.data.operator_name == '+') {
            deep_transform_sum(firt_slog, curr_t, false, &(*curr_t)->right);
        }

        //Если с двух сторон стоят инты
        else if ((*curr_t)->left->node.type == INTEGER && (*curr_t)->right->node.type == INTEGER) {
            (*curr_t)->node.type = INTEGER;
            (*curr_t)->node.data.value_int = (*curr_t)->left->node.data.value_int + (*curr_t)->right->node.data.value_int;
            (*curr_t)->right = NULL; (*curr_t)->left = NULL; 
        }

        //Если слева инт
        else if ((*curr_t)->left->node.type == INTEGER) {
            (*firt_slog)->node.data.value_int += (*curr_t)->left->node.data.value_int;
            if (is_left)
                (*prev)->left = (*curr_t)->right;
            else
                (*prev)->right = (*curr_t)->right;
        }

        //Если справа инт
        else if ((*curr_t)->right->node.type == INTEGER) {
            (*firt_slog)->node.data.value_int += (*curr_t)->right->node.data.value_int;
            if (is_left)
                (*prev)->left = (*curr_t)->left;
            else
                (*prev)->right = (*curr_t)->left;
        }
    }

}


void transform_sum(Tree *t)
{
    
    if ((*t)->node.type == OPERATOR && (*t)->node.data.operator_name == '+') {

        //С двух сторон инты
        if ((*t)->left->node.type == INTEGER && (*t)->right->node.type == INTEGER) {
            (*t)->node.type = INTEGER;
            (*t)->node.data.value_int = (*t)->left->node.data.value_int + (*t)->right->node.data.value_int;
            (*t)->right = NULL; (*t)->left = NULL; 
        }

        //слева инт, справа +
        else if ((*t)->left->node.type == INTEGER && (*t)->right->node.type == OPERATOR && (*t)->right->node.data.operator_name == '+') {
            deep_transform_sum(&(*t)->left, t, false, &(*t)->right);
        }
        //слева +, справа инт
        else if ((*t)->left->node.type == OPERATOR && (*t)->left->node.data.operator_name == '+' && (*t)->right->node.type == INTEGER) {
            deep_transform_sum(&(*t)->right, t, true, &(*t)->left);
        }

    }
}


void tree_transform(Tree *t)
{
    if ((*t) != NULL) {

        tree_transform(&((*t)->left));
        tree_transform(&((*t)->right));

        if (match_sum(t)) {
            transform_sum(t);;
        }
    }
}
