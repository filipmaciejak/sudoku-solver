#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool validate(int *board, int pos) {

    int num = board[pos];
    if (num > 9) return false;

    /* row */
    for (int i = 0; i < 9; ++i) {
        int index = (pos / 9) * 9 + i;
        if (board[index] == num && index != pos) return false;
    }

    /* column */
    for (int i = 0; i < 9; ++i) {
        int index = i * 9 + (pos % 9);
        if (board[index] == num && index != pos) return false;
    }

    /* square */
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int index = ((pos / 27) * 3 + j) * 9 + (((pos / 3) % 3) * 3) + i;
            if (board[index] == num && index != pos) return false;
        }
    }

    return true;
}

bool solve(int *board, int *original) {

    int pos = 0;

    while (pos != 81) {
        if (board[pos] == 0) {
            board[pos] = 1;
            continue;
        }
        if (validate(board, pos)) {
            ++pos;
            continue;
        }
        if (board[pos] < 9) {
            ++board[pos];
            continue;
        }
        board[pos] = 0;
        --pos;
        while (original[pos] != 0) {
            --pos;
            if (pos < 0) {
                for (int i = 0; i < 81; ++i) board[i] = original[i];
                return false;
            }
        }
        ++board[pos];
    }

    return true;
}

int main(int argc, char *argv[]) {

    /* check inputs */
    if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        printf("Usage: sudosolve [OPTION] [DATA / FILENAME]\n");
        printf("Options:\n");
        printf("    -h, --help      This message.\n");
        printf("    -i, --inline    Use inline sudoku grid as input.\n");
        return 2;
    }
    if (argc < 2) {
        printf("Error, no arguments.\n");
        printf("Try sudosolve --help for more information\n");
        return 1;
    }
    if (strcmp(argv[1], "--inline") == 0 || strcmp(argv[1], "-i") == 0) {

        /* check for argument */
        if (argc != 3) {
            printf("Error, invalid number of arguments: %d (expected 2)\n", argc - 1);
            printf("Try sudosolve --help for more information\n");
            return 1;
        }
        
        /* check inline input length */
        int len = strlen(argv[2]);
        if (len != 81) {
            printf("Error, invalid input length: %d (expected 81)\n", len);
            printf("Try sudosolve --help for more information\n");
            return 3;
        }

        int *board = malloc(81 * sizeof(int));
        int *original = malloc(81 * sizeof(int));

        /* read data from argv */
        for (int i = 0; i < 81; ++i) {
            int tmp = argv[2][i] - '0';
            if (tmp <= 9 && tmp > 0) {
                board[i] = tmp;
                original[i] = tmp;
            }
            else {
                board[i] = 0;
                original[i] = 0;
            }
        }

        /* solve the puzzle */
        solve(board, original);

        /* print output */
        char *out = malloc(82 * sizeof(char));
        for (int i = 0; i< 81; ++i) {
            out[i] = board[i] + '0';
        }
        printf("\n\n%s\n", out);
        return 3;
    }

    printf("Error, option not recognized: %s\n", argv[1]);
    printf("Try sudosolve --help for more information\n");
    return 0;
}
