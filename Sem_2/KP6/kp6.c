#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


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


int char_to_int(char c) {
    return c - '0';
}


int power_10(int order) {
    int res = 1;
    while (order > 0) {
        res *= 10;
        order--;
    }
    return res;
}


void db_searsh(FILE *f, int points) {
    char s[100];
    bool  flag = false;
    while (fscanf(f, "%s", s) != EOF) {
        int delimiter_cnt = 0;
        int db_points = 0;
        int order = 0;
        for (int i = strlen(s) - 1; i >= 0; --i) {
            if (s[i] == ';')
                delimiter_cnt++;
            if (delimiter_cnt >= 0 && delimiter_cnt < 3) {
                if (s[i] != ';') {
                    db_points += char_to_int(s[i]) * power_10(order);
                    order++;      
                } else
                    order = 0;
            } else if (delimiter_cnt >= 3)
                break;
        }
        delimiter_cnt = 0;
        if (db_points >= points) {
            flag = true;
            printf("Инициалы: ");
            int j;
            for (int i = 0; i < strlen(s); ++i) {
                if (s[i] == ';') {
                    j = i + 1;
                    break;
                }
                else
                    printf("%c", s[i]);
            }
            printf(" | Баллы: %d | Дельта: %d\n", db_points, db_points - points);
        }
    }
    if (!flag)
        printf("Ничего не найдено\n");
}


void check_args(int argc, char **argv) {
    if (argc < 2) {
        printf("Параметры не переданы\n");
        exit(0);
    }
    if (str_to_int(argv[1]) < 0) {
        printf("Переданы некорректные параметры\n");
        exit(0);
    }
}


int main(int argc, char **argv) {
    check_args(argc, argv);
    int points =  str_to_int(argv[1]);

    FILE *f;
    char name[] = "students.db";
    if ((f = fopen(name, "rb")) == NULL) {
        printf("Не удалось открыть файл\n");
        return 0;
    }
    char str[100];
    printf("База данных:\n");
    printf("----------------\n");
    while(fscanf(f, "%s", str) != EOF) {
        printf("%s\n", str);
    }
    printf("----------------\n\n");
    fclose(f);
    f = fopen(name, "rb");

    printf("Резельтаты поиска(>=%d):\n", points);
    printf("################\n");
    db_searsh(f, points);
    printf("################\n");
    fclose(f);
}