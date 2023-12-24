#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void swap_pointers(char **p1, char **p2) {
    char *temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
void sort_pointers(char **arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcasecmp(arr[i], arr[j]) > 0) {
                swap_pointers(&arr[i], &arr[j]);
            }
        }
    }
}
void print_pointers(char **arr, int n) {
    for (int i = 0; i < n; i++) printf("%s\n", arr[i]);
}
void input_data(char *buffer, char **pointers, int n) {
    for (int i = 0; i < n; i++) {
        scanf("%s", buffer);
        pointers[i] = buffer; 
        buffer += strlen(buffer) + 1;
    }
}
void read_data(char *buffer, char **pointers, int n, char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла %s\n", filename);
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        fgets(buffer, 256, file);
        buffer[strcspn(buffer, "\n")] = '\0';
        pointers[i] = buffer;
        buffer += strlen(buffer) + 1;
    }
    fclose(file);
}
void divide_participants(char **pointers, int n) {
    int count[26] = {0}; 
    for (int i = 0; i < n; i++) { 
        char first_letter = toupper(pointers[i][0]);
        count[first_letter - 'A']++;
    }
    int total = 0; 
    for (int i = 0; i < 26; i++) total += count[i];
    int target = total / 4;
    int part1 = 0, part2 = 0, part3 = 0, part4 = 0;
    int index1 = 0, index2 = 0, index3 = 0, index4 = 0; 
    for (int i = 0; i < 26; i++) { 
        if (part1 < target) { 
            part1 += count[i]; 
            index1 = i; 
        } else if (part2 < target) { 
            part2 += count[i]; 
            index2 = i; 
        } else if(part3 < target) { 
            part3 += count[i]; 
            index3 = i; 
        }else{
            part4 += count[i];
            index4 = i;
        }
    }
    printf("A-%c %d\n", 'A' + index1, part1);
    printf("%c-%c %d\n", 'A' + index1 + 1, 'A' + index2, part2);
    printf("%c-%c %d\n", 'A' + index2 + 1,'A' + index3, part3);
    printf("%c-Z %d\n", 'A' + index3 + 1, part4);
}
int main() {
    int n = 50;
    char buffer[256 * n]; 
    char *pointers[n];
    input_data(buffer, pointers, n);
    sort_pointers(pointers, n);
    print_pointers(pointers, n); 
    printf("\n");
    divide_participants(pointers, n); 
    return 0;
}
