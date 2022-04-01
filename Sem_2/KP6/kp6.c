//Фамилия;инициалы;пол;номер школы;наличие медали;оценка 1;оценка 2;оценка 3;зачет/незачет за соч
//оценки 1-4 c конца ;
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
            if (delimiter_cnt >= 1 && delimiter_cnt < 4) {
                if (s[i] != ';') {
                    db_points += char_to_int(s[i]) * power_10(order);
                    order++;      
                } else
                    order = 0;
            } else if (delimiter_cnt >= 4)
                break;
        }
        delimiter_cnt = 0;
        if (points == db_points) {
            flag = true;
            printf("Фамилия: ");
            int j;
            for (int i = 0; i < strlen(s); ++i) {
                if (s[i] == ';') {
                    j = i + 1;
                    break;
                }
                else
                    printf("%c", s[i]);
            }
            
            printf(" | Инициалы: ");
            for (; j < 100; ++j) {
                if (s[j] == ';') {
                    printf(" | Баллы: %d", points);
                    break;
                }
                else
                    printf("%c", s[j]);    
            }
            printf("\n");
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
    if ((f = fopen(name, "r")) == NULL) {
        printf("Не удалось открыть файл\n");
        return 0;
    }

    db_searsh(f, points);

    fclose(f);
}