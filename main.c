#include <stdio.h>

void getPuzzle(char *puzzle);
void printPuzzle(char *puzzle, char x, char y);

int main()
{
    int c;
    char x, y;
    x = y = 0;

    char puzzle[50][50];
    char *ppuzzle = &(puzzle[0][0]);
    getPuzzle(ppuzzle);
    printPuzzle(ppuzzle, x, y);

    while ((c = getchar()) != 'q') {
        printPuzzle(ppuzzle, x, y);
        switch (c) {
            case 'w':
                if (y > 0)
                    y--;
                break;
            case 'a':
                if (x > 0)
                    x--;
                break;
            case 's':
                if (y < 49)
                    y++;
                break;
            case 'd':
                if (x < 49)
                    x++;
                break;
        }
    }

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

void printPuzzle(char *puzzle, char x, char y)
{
    int i, j;

    // Print puzzle
    system("clear");
    for (i = 0; i < 50; ++i) {
        for (j = 0; j < 50; ++j)
            if (i == y && j == x)
                printf("\x1b[31m%c\x1b[0m ", puzzle[i*50+j]);
            else
                printf("%c ", puzzle[i*50+j]);
        printf("\n");
    }
}
