#include <stdio.h>
#include <string.h>

void getPuzzle(char *puzzle);
void printPuzzle(char *puzzle, int x, int y, int selection[8][2]);
void getMonths(char *months);
int verifySelection(int *selection, char *puzzle, char months[12][10]);

int main()
{
    int c;
    int i, j;
    int x, y;
    x = y = 0;

    int selection[8][2];
    for (i = 0; i < 8; ++i)
        selection[i][0] = -1;
    int selection_index = 0;

    char puzzle[50][50];
    char *ppuzzle = &(puzzle[0][0]);
    getPuzzle(ppuzzle);
    printPuzzle(ppuzzle, x, y, selection);

    char months[12][10];
    char *pmonths = &(months[0][0]);
    getMonths(pmonths);

    int monthsFound[12];
    for (i = 0; i < 12; ++i)
        monthsFound[i] = 0;  // No month found  |  Set to 1 for testing

    char message[200];
    char help[] = "\n\
INSTRUCTIONS\n\
Press enter after this keys:\n\
  h: show help\n\
  wasd: movement\n\
  ' ': select letter\n\
  c: clear selection\n\
  v: verify selection\n\n\
";
    strcpy(message, help);

    do {
        // Print puzzle
        printPuzzle(ppuzzle, x, y, selection);

        // Print message
        printf("%s", message);
        strcpy(message, "");

        // Print selection
        printf("Selection: ");
        for (i = 0; i < 8; ++i)
            if (selection[i][0] == -1)
                printf("_");
            else
                printf("%c", puzzle[selection[i][1]][selection[i][0]]);
        printf("\n");

        // Print months found
        printf("Months found: ");
        for (i = 0, j = 0; i < 12; ++i) {
            if (monthsFound[i]) {
                printf("%s ", months[i]);
                ++j;
            }
        }
        if (j < 12)
            printf("(%d/12)\n", j);
        else
            printf("(%d/12 :D)\n", j);

        // Keyboard input
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
            case ' ':  // Select letter
                if (selection_index <= 7) {
                    // Check if the letters are next to each other
                    if (    x == selection[selection_index-1][0]-1 ||
                            x == selection[selection_index-1][0]+1 ||
                            x == selection[selection_index-1][0]   ||
                            selection_index == 0) {
                        if (    y == selection[selection_index-1][1]-1 ||
                                y == selection[selection_index-1][1]+1 ||
                                y == selection[selection_index-1][1]   ||
                                selection_index == 0) {
                            selection[selection_index][0] = x;
                            selection[selection_index][1] = y;
                            ++selection_index;
                        } else {
                            strcpy(message, "\
\x1b[31m\
You have to select letters that are next to each other.\
\n\x1b[0m");
                        }
                    } else {
                        strcpy(message, "\
\x1b[31m\
You have to select letters that are next to each other.\
\n\x1b[0m");
                    }
                }
                break;
            case 'c':  // Clear selection
                for (i = 0; i < 8; ++i)
                    selection[i][0] = -1;
                selection_index = 0;
                break;
            case 'v':  // Verify selection
                i = verifySelection(&(selection[0][0]), ppuzzle, months);
                if (i >= 0)
                    monthsFound[i] = 1;
                break;
            case 'h': // Show help
                strcpy(message, help);
                break;
        }
    } while ((c = getchar()) != 'q');

    return 0;
}

void getPuzzle(char *puzzle)
{
    int c;
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

void printPuzzle(char *puzzle, int x, int y, int selection[8][2])
{
    int i, j, k;

    system("clear");
    for (i = 0; i < 50; ++i) {
        for (j = 0; j < 50; ++j) {
            if (i == y && j == x) {
                printf("\x1b[31m%c\x1b[0m ", puzzle[i*50+j]);
            } else {
                for (k = 0; k < 8; ++k) {
                    if (i == selection[k][1] && j == selection[k][0]) {
                        printf("\x1B[34m%c\x1b[0m ", puzzle[i*50+j]);
                        k = 9;
                    }
                }
                if (k < 9) {
                    printf("%c ", puzzle[i*50+j]);
                }
            }
        }
        printf("\n");
    }
}

void getMonths(char *months)
{
    int c;
    int i, j;
    i = j = 0;
    FILE *file;
    file = fopen("wordbank.txt", "r");

    while ((c = getc(file)) != EOF) {
        if (c != '\n') {
            months[i*10+j] = (char) c;
            ++j;
        } else {
            months[i*10+j] = '\0';
            ++i;
            j = 0;
        }
    }

    fclose(file);
}

int verifySelection(int *selection, char *puzzle, char months[12][10])
{
    int i;
    char str[9];

    int isequal = 0;

    // Pass selection to string
    for (i = 0; i < 8; ++i) {
        if (selection[i*2] == -1) {
            break;
        } else {
            str[i] = puzzle[selection[i*2+1]*50+selection[i*2]];
        }
    }
    str[i] = '\0';

    // Verify selection
    for (i = 0; i < 12; ++i)
        if ((isequal = !strcmp(str, months[i])) > 0)
            break;

    // Return month found or -1 (no month found)
    if (isequal) {
        return i;
    } else {
        return -1;
    }
}
