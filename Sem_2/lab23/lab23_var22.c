#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>


typedef struct _node {
    struct _node* parent;
    int value;
    int current_cnt;
    int available_cnt;
    struct _node** children;
} node;


int STANDART_ARRAY_SIZE = 5;
int vertex_cnt = 0;
node* genesis_node;
bool* borders;


int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}


void create_node(node* u, int v) {
    node* nd = malloc(sizeof(node));
    nd->parent = u;
    nd->value = v;
    nd->current_cnt = 0;
    nd->available_cnt = STANDART_ARRAY_SIZE;
    nd->children = malloc(sizeof(node) * STANDART_ARRAY_SIZE);
    if(u->current_cnt == u->available_cnt - 1) {
        u->children = realloc(u->children, sizeof(node) * u->available_cnt * 2);
        u->available_cnt *= 2;
    }
    u->children[u->current_cnt] = nd;
    u->current_cnt++;
}


node* create_genesis_node(int v) {
    node* nd = malloc(sizeof(node));
    nd->parent = NULL;
    nd->value = v;
    nd->current_cnt = 0;
    nd->available_cnt = STANDART_ARRAY_SIZE;
    nd->children = malloc(sizeof(node) * STANDART_ARRAY_SIZE);
    return nd;
}


void delete_node(node* v) {
    for (int i = v->current_cnt - 1; i >= 0; --i) {
        delete_node(v->children[i]);
    }
    node* v_parent = v->parent;
    int del_index = 0;
    for (int i = 0; i < v_parent->current_cnt; ++i) {
        if (v_parent->children[i]->value == v->value) {
            del_index = i;
            vertex_cnt--;
            free(v);
            break;
        }
    }
    for (int i = del_index + 1; i < v_parent->current_cnt; ++i) {
        v_parent->children[i - 1] = v_parent->children[i];
    }
    v_parent->current_cnt--;
}


node* find_vertex(node* u, int vertex) {
    if (u->value == vertex)
        return u;
    node* vertex_address = NULL;
    for (int i = 0; i < u->current_cnt; ++i) {
        vertex_address = find_vertex(u->children[i], vertex);
        if (vertex_address != NULL && vertex_address->value == vertex)
            break;
    }
    return vertex_address;
}


int str_to_int(char* s) {
    int ans = 0;
    for (int i = 0; i < strlen(s); ++i) {
        if (s[i] >= '0' && s[i] <= '9') {
            ans = ans * 10 + (s[i] - '0');
        } else {
            return -2022;
        }
    }
    return ans;
}


void print_tree(node* u, int space_cnt) {
    printf("%d\n", u->value);

    if (sizeof(borders) / sizeof(bool) - 1 < space_cnt)
        borders = realloc(borders, sizeof(borders) * 2);
    borders[space_cnt] = true;

    for (int i = 0; i < u->current_cnt; ++i) {

        if (i == u->current_cnt - 1) 
            borders[space_cnt] = false;

        for (int j = 0; j < space_cnt; ++j) {
            if (borders[j])
                printf("|");
            else
                printf(" ");
        }

        printf("|\n");
        for (int j = 0; j < space_cnt; ++j) {
            if (borders[j])
                printf("|");
            else
                printf(" ");
        }

        printf("+");
        printf("----");

        print_tree(u->children[i], space_cnt + 5);
    }

    borders[space_cnt] = false;
}


void print_info(bool first_print) {
    if (first_print) {
        printf("    Доступные операции:\n");
        printf("0 - Вывести справку\n");
        printf("1 - Добавить ребро в дерево\n");
        printf("2 - Удалить ребро из дерева\n");
        printf("3 - Вывести дерево\n");
        printf("4 - Вывести количество вершин в дереве\n");
    } else {
        printf("Сначала в отдельной строке вводится номер операции 0-4\n");
        printf("После чело для операции 1 - 2 вершины,\n");
        printf("           для операции 2 - 1 вершина,\n");
        printf("           для операций 3 и 4 дополнительные входные данный не требуются.\n");
    }
}


int main() {
    borders = malloc(sizeof(bool) * 30);
    bool is_genesis = true;
    char str[100];
    print_info(true);
    while (true) {
        printf("Операция: ");
        scanf("%s", str);
        int op = str_to_int(str);
        if (op < 0 || op > 4) {
            printf("Введенные данные некорректны\n");
            continue;
        }

        if(op == 0) {
            print_info(false);
        } else if (op == 1) {
            int u, v;
            char u1[100], v1[100];
            scanf("%s %s", u1, v1);
            u = str_to_int(u1);
            v = str_to_int(v1);
            if (u < 0 || v < 0) {
                printf("Введены некоректные данные, допустимы только целочесленные неотрицательные значения вершин\n");
                continue;
            }
            if (is_genesis) {
                is_genesis = false;
                genesis_node = create_genesis_node(u);
                create_node(genesis_node, v);
                vertex_cnt += 2;
            } else {
                node* u_address = find_vertex(genesis_node, u);
                if (u_address == NULL) {
                    printf("Вершина %d отсутсвует в дереве\n", u);
                    continue;
                }
                node* v_address = find_vertex(genesis_node, v);
                if (v_address == NULL) {
                    create_node(u_address, v);
                    vertex_cnt++;
                } else {
                    printf("Такая вершина уже есть в дереве\n");
                }
            }
        } else if (op == 2) {
            char u_str[100];
            int u;
            scanf("%s", u_str);
            u = str_to_int(u_str);
            node* v = find_vertex(genesis_node, u);
            if (v == NULL)
                printf("Введены некорректные данные\n");
            else
                delete_node(v);
        } else if (op == 3) {
            print_tree(genesis_node, 0);
        } else if (op == 4) {
            printf("Вершин в дереве: %d\n", vertex_cnt);
        }
    }
}