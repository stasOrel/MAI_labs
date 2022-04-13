#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "student.h"


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


// int char_to_int(char c) {
//     return c - '0';
// }


void db_searsh(FILE *f, int points) {
    bool flag = true;
    student s;
    // while (fscanf(f, "%s %d %d %d", s.initials, &s.mark1, &s.mark2, &s.mark3) != EOF) {
    while (fread(&s, sizeof(s), 1, f) == 1) {
        int db_points = s.mark1 + s.mark2 + s.mark3;
        if (db_points >= points) {
            flag = false;
            printf("Инициалы: %s | Баллы: %d | Разница: %d\n", s.initials, db_points, db_points - points);
        }
    }
    if (flag)
        printf("По заданным параметрам ничего не найдено\n");
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
    student s;
    // while(fscanf(f, "%s", s.initials) != EOF) {
        // fscanf(f, "%d", &s.mark1);
        // fscanf(f, "%d", &s.mark2);
        // fscanf(f, "%d", &s.mark3);
    while (fread(&s, sizeof(s), 1, f) == 1) {
        printf("%s | %d | %d | %d\n", s.initials, s.mark1, s.mark2, s.mark3);
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