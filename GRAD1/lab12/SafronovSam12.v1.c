#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
struct studCard
{
    char SurName[20];
    char Name[20];
    struct adres
    {
        char city[20];
        char street[20];
        int house;
        int flat;
    } adr;
    char section[20];
    int ball;
};
struct Town
{
    char city[20];
    int count;
};
void func1(int n, struct studCard stud[n], char m[20], int *pr)
{

    int sum = 0;
    int count = 0;
    for (int i = 0; i < n; i++)
        if (strcmp(stud[i].section, m) == 0)
        {
            sum += stud[i].ball;
            count++;
        }
    float a = sum / (count * (1.0));
    printf("%s %.1f\n", m, a);
}

void func2(int n, int pr, struct studCard stud[n], char m[20])
{
    int max = -1;
    int count_of_winners = 0;
    for (int i = 0; i < n; i++)
        if (strcmp(stud[i].section, m) == 0)
            if (max <= stud[i].ball)
                max = stud[i].ball;

    for (int i = 0; i < n; i++)
        if (strcmp(stud[i].section, m) == 0)
            if (max == stud[i].ball)
                count_of_winners++;

    struct studCard winners[count_of_winners];
    int index = 0;
    for (int i = 0; i < n; i++)
        if (strcmp(stud[i].section, m) == 0)
            if (max == stud[i].ball)
                winners[index++] = stud[i];
    printf("%s", m);
    index = 0;
    do
    {
        printf(" ");
        printf("%s", winners[index++].SurName);
    } while (index < count_of_winners);
    printf("\n");
}

void func3(int n, struct studCard stud[n])
{
    char *towns[n];
    int index = 0;
    // Получим уникальный набор всех городов
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < index; j++)
        {
            if (strcmp(stud[i].adr.city, towns[j]) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found) towns[index++] = stud[i].adr.city;
    }

    // найдем максимум баллов для каждого города
    for (int i = 0; i < index; i++)
    {
        int max = -1;
        for (int j = 0; j < n; j++)
            if (strcmp(stud[j].adr.city, towns[i]) == 0)
                if (stud[j].ball >= max) max = stud[j].ball;
        int count_of_maxs = 0;
        for (int j = 0; j < n; j++)
            if (stud[j].ball == max && strcmp(stud[j].adr.city, towns[i]) == 0)
                count_of_maxs++;
        struct studCard best_in_towns[count_of_maxs];
        int t = 0;
        for (int j = 0; j < n; j++)
            if (stud[j].ball == max && strcmp(stud[j].adr.city, towns[i]) == 0)
                best_in_towns[t++] = stud[j];
        t = 0;
        printf("%s", towns[i]);
        do
        {
            printf(" ");
            printf("%s", best_in_towns[t++].SurName);
        } while (t < count_of_maxs);
        printf("\n");
    }
}
int func4(int n, struct studCard stud[n])
{
    char *towns[n];
    int index = 0;
    // Получим уникальный набор всех городов
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < index; j++)
        {
            if (strcmp(stud[i].adr.city, towns[j]) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found) towns[index++] = stud[i].adr.city;
    }
    struct Town towns_data[n];
    for (int i = 0; i < index; i++) //для каждого города
    {
        
    }

}
int main()
{
    int n;
    scanf("%d", &n);
    int pr1, pr2, pr3;
    struct studCard stud[n];

    /*
    FILE *f;
    f=fopen("file.txt", "r");
    int n=0; while(!feof(f)){
        fscanf(f, "%s", stud[n].SurName);
        fscanf(f, "%s", stud[n].Name);
        fscanf(f, "%s", stud[n].adr.city);
        fscanf(f, "%s", stud[n].adr.street);
        fscanf(f, "%d", &stud[n].adr.house);
        fscanf(f, "%d", &stud[n].adr.flat);
        fscanf(f, "%s", stud[n].section);
        fscanf(f, "%d", &stud[n].ball);
        n++;
    }
    fclose(f);
    */

    for (int i = 0; i < n; i++)
    {
        scanf("%s", stud[i].SurName);
        scanf("%s", stud[i].Name);
        scanf("%s", stud[i].adr.city);
        scanf("%s", stud[i].adr.street);
        scanf("%d", &stud[i].adr.house);
        scanf("%d", &stud[i].adr.flat);
        scanf("%s", stud[i].section);
        scanf("%d", &stud[i].ball);
    }

    func1(n, stud, "Physics", &pr1);
    func1(n, stud, "Biology", &pr2);
    func1(n, stud, "History", &pr3);
    printf("\n");

    func2(n, pr1, stud, "Physics");
    func2(n, pr2, stud, "Biology");
    func2(n, pr3, stud, "History");
    printf("\n");
    func3(n, stud);
    printf("\n");
    
    return 0;
}
/*Пример
15
Ivanov Alex Moscow Lenina 1 2 Physics 95
Petrov Boris Saint-Petersburg Nevskaya 2 3 History 63
Sidorov Dmitry Moscow Tverskaya 3 4 Biology 95
Kuznetsov Elena Kazan Kazanskaya 4 5 Physics 95
Popov Sergey Moscow Presnenskaya 5 6 History 85
Morozova Anna Sochi Sochinskaya 6 7 Biology 91
Novikov Ivan Moscow Arbatskaya 7 8 Physics 76
Fedorova Maria Novosibirsk Novosibirskaya 8 9 History 94
Egorov Alexey Moscow Kutuzovckaya 9 10 Biology 69
Volkova Anastasia Samara Samarskaya 10 11 Physics 70
Smirnov Dmitry Moscow Lenina 11 12 History 94
Kuznetsova Maria Saint-Petersburg Nevskaya 12 13 Biology 55
Ivanova Anastasia Moscow Tverskaya 13 14 Physics 72
Petrova Elena Kazan Kazanskaya 14 15 History 94
Sidorova Anna Moscow Presnenskaya 15 16 Biology 67
*/