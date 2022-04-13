#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

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


// int readstudent(student *s) {
//     return scanf("%[^\t]\t%d\t%d\t%d\n", s->initials, s->mark1, s->mark2, s->mark3) == 4;
// }


int main(int argc, char **argv) {   
    srand(time(NULL));
    int r = rand() % 10;
    if (argc > 1) {
        FILE *f;
        char name[] = "students.db";
        if ((f = fopen(name, "wb")) == NULL) {
            printf("Не удалось открыть файл\n");
            return 0;
        }
        int cnt = str_to_int(argv[1]);
        if (cnt <= 0) {
            printf("Переданны неверные входные данные\n");
            return 0;
        }
        for (int i = 0; i < cnt; ++i) {
            student s;
            for (int i = 0; i < 3; ++i)
                s.initials[i] = (char)(rand() % 25 + 65);
            s.mark1 = rand() % 100;
            s.mark2 = rand() % 100;
            s.mark3 = rand() % 100;
            // fprintf(f, "%s %d %d %d\n", s.initials, s.mark1, s.mark2, s.mark3);
            fwrite(&s, sizeof(s), 1, f);
        }
        fclose(f);
    } else {
        printf("Входные данные не переданы\n");
    }
}