#include <stdio.h>

void getPuzzle(char *puzzle);
void printPuzzle(char *puzzle);

int main()
{
    char puzzle[50][50];
    char *ppuzzle = &(puzzle[0][0]);
    getPuzzle(ppuzzle);
    printPuzzle(ppuzzle);

    return 0;
}

void getPuzzle(char *puzzle)
{
    char c;
    int i, j;
    FILE *file;

    i = j = 0;
    file = fopen("puzzle.txt", "r");

    while ((c = getc(file)) != EOF)
    {
        if (c == '\t' || c == ' ') {
            continue;
        } else if (c == '\n') {
            ++j;
            i = 0;
        } else {
            puzzle[j*50+i] = c;
            i++;
        }
    }

    fclose(file);
}

void printPuzzle(char *puzzle)
{
    int i, j;

    // Print puzzle
    for (i = 0; i < 50; ++i) {
        for (j = 0; j < 50; ++j)
            printf("%c ", puzzle[i*50+j]);
        printf("\n");
    }
}
