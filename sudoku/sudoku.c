#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static int sk[9][9];
static int t[9][9][9];
static int count;

static void display(void)
{
    int x, y;

    printf("\nsudoku : \n");
    for (y = 0; y < 9; y++) {
        for (x = 0; x < 9; x++) {
            printf("%d ", sk[y][x]);
            if (2 == x % 3)
                printf(" ");
        }
        printf("\n");
        if (2 == y % 3)
            printf("\n");
    }
    printf("\n");
}

static void do_t(int s[9][9])
{
    int i, j, x, y;

    memset(t, 0, sizeof(t));

    for (y = 0; y < 9; y++)
        for (x = 0; x < 9; x++) {
            if (0 == s[y][x]) {
                for (i = 0; i < 9; i++) {
                    if (s[y][i] > 0)
                        t[y][x][s[y][i] - 1] = 1;
                    if (s[i][x] > 0)
                        t[y][x][s[i][x] - 1] = 1;

                }
                for (i = (y / 3) * 3; i < (y / 3) * 3 + 3; i++)
                    for (j = (x / 3) * 3; j < (x / 3) * 3 + 3; j++)
                        if (s[i][j] > 0)
                            t[y][x][s[i][j] - 1] = 1;
            }
        }
}

static bool check(int s[9][9])
{
    int i, j, x, y;
    int t[9];

    for (i = 0; i < 9; i++) {
        memset(t, 0, sizeof(t));
        for (j = 0; j < 9; j++) {
            if (0 == s[i][j])
                continue;
            if (0 == t[s[i][j] - 1])
                t[s[i][j] - 1] = 1;
            else
                return false;
        }
    }

    for (i = 0; i < 9; i++) {
        memset(t, 0, sizeof(t));
        for (j = 0; j < 9; j++) {
            if (0 == s[j][i])
                continue;
            if (0 == t[s[j][i] - 1])
                t[s[j][i] - 1] = 1;
            else
                return false;
        }
    }

    for (y = 0; y < 9; y += 3)
        for (x = 0; x < 9; x += 3) {
            memset(t, 0, sizeof(t));
            for (i = 0; i < 3; i++)
                for (j = 0; j < 3; j++) {
                    if (0 == s[y + i][x + j])
                        continue;
                    if (0 == t[s[y + i][x + j] - 1])
                        t[s[y + i][x + j] - 1] = 1;
                    else
                        return false;
                }
        }

    return true;
}

static int do_s(int s[9][9])
{
    int i, j, x, y;

    for (y = 0; y < 9; y++)
        for (x = 0; x < 9; x++) {
            if (0 == s[y][x]) {
                j = 0;
                for (i = 0; i < 9; i++)
                    j += t[y][x][i];
                if (8 == j) {
                    for (i = 0; i < 9; i++)
                        if (0 == t[y][x][i]) {
                            s[y][x] = i + 1;
                            printf("<y,x>=<%d,%d>    value=%d\n", y, x, i + 1);
                            if (!check(s)) {
                                printf("check failed\n");
                                return -1;
                            }
                        }
                } else if (9 == j) {
                    return -1;
                }
            }
        }

    return 0;
}

static int do_ss(int s[9][9])
{
    int i, j, k, l, x, y;

    for (y = 0; y < 9; y += 3)
        for (x = 0; x < 9; x += 3) {
            for (l = 0; l < 9; l++) {
                k = 0;
                for (i = 0; i < 3; i++)
                    for (j = 0; j < 3; j++)
                        if (0 == s[y + i][x + j])
                            if (0 == t[y + i][x + j][l])
                                if (++k > 1)
                                    goto tag;

                if (1 == k)
                    for (i = 0; i < 3; i++)
                        for (j = 0; j < 3; j++)
                            if (0 == s[y + i][x + j])
                                if (0 == t[y + i][x + j][l]) {
                                    s[y + i][x + j] = l + 1;
                                    printf("<y,x>=<%d,%d>    value=%d\n", y + i, x + j, l + 1);
                                    if (!check(s)) {
                                        printf("check failed\n");
                                        return -1;
                                    }
                                }
 tag:          k = 0;
            }

        }

    return 0;
}

static int find(int s[9][9], int *px, int *py, int *px2, int *py2, int *pv)
{
    int i, j, k, l, x, y;

    for (y = 0; y < 9; y += 3)
        for (x = 0; x < 9; x += 3) {
            for (l = 0; l < 9; l++) {
                k = 0;
                for (i = 0; i < 3; i++)
                    for (j = 0; j < 3; j++)
                        if (0 == s[y + i][x + j])
                            if (0 == t[y + i][x + j][l]) {
                                k++;
                                if (1 == k) {
                                    *px = x + j;
                                    *py = y + i;
                                } else if (2 == k) {
                                    *px2 = x + j;
                                    *py2 = y + i;
                                } else {
                                    goto tag;
                                }
                            }

                if (2 == k) {
                    *pv = l + 1;
                    return 0;
                }
 tag:          k = 0;
            }

        }

    printf("\nWhat's up ???\n");

    return -1;
}

static bool is_right(void)
{
    int i, j, x, y;
    int t[9];

    for (i = 0; i < 9; i++) {
        memset(t, 0, sizeof(t));
        for (j = 0; j < 9; j++)
            t[sk[i][j] - 1] = 1;
        for (j = 0; j < 9; j++)
            if (0 == t[j])
                return false;

    }

    for (i = 0; i < 9; i++) {
        memset(t, 0, sizeof(t));
        for (j = 0; j < 9; j++)
            t[sk[j][i] - 1] = 1;
        for (j = 0; j < 9; j++)
            if (0 == t[j])
                return false;

    }

    for (y = 0; y < 9; y += 3)
        for (x = 0; x < 9; x += 3) {
            memset(t, 0, sizeof(t));
            for (i = 0; i < 3; i++)
                for (j = 0; j < 3; j++)
                    t[sk[y + i][x + j] - 1] = 1;
            for (j = 0; j < 9; j++)
                if (0 == t[j])
                    return false;

        }

    return true;
}

static bool is_ok(void)
{
    int x, y;

    for (y = 0; y < 9; y++)
        for (x = 0; x < 9; x++) {
            if (0 == sk[y][x]) {
                return false;
            }
        }

    if (is_right())
        printf("Success!!!\n");
    else
        printf("Wrong!!!\n");

    return true;
}

static int sudoku(void)
{
    int s[9][9];
    int x, y, x2, y2, v;

    count++;
    printf("\ncount = %d\n", count);

    memcpy(s, sk, sizeof(sk));

    do_t(s);
    if (do_s(s) == -1)
        return -1;
    memcpy(sk, s, sizeof(sk));
    display();
    if (is_ok())
        return 0;

    do_t(s);
    do_ss(s);
    memcpy(sk, s, sizeof(sk));
    display();
    if (is_ok())
        return 0;

    do_t(s);
    if (do_s(s) == -1)
        return -1;
    memcpy(sk, s, sizeof(sk));
    display();
    if (is_ok())
        return 0;

    do_t(s);
    if (find(sk, &x, &y, &x2, &y2, &v) == -1) {
        printf("\n\n\n\n\n");
        return -1;
    }
    printf("<x,y>=<%d,%d> <x2,y2>=<%d,%d>  value=%d\n", x, y, x2, y2, v);

    sk[y][x] = v;
    if (sudoku() == -1) {
        printf("try other\n");
        memcpy(sk, s, sizeof(sk));
        sk[y][x] = 0;
        sk[y2][x2] = v;
        if (sudoku() == -1) {
            memcpy(sk, s, sizeof(sk));
            sk[y2][x2] = 0;
            printf("both wrong, return\n\n\n");
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
#if 0
    int s[9][9] = { 
    {0, 5, 0, 8, 1, 0, 0, 0, 9},
    {8, 0, 2, 0, 0, 7, 1, 0, 5},
    {0, 6, 0, 3, 0, 0, 7, 0, 0},
    {0, 0, 0, 0, 7, 0, 2, 0, 3},
    {0, 1, 0, 5, 0, 6, 0, 8, 0},
    {3, 0, 7, 0, 9, 0, 0, 0, 0},
    {0, 0, 5, 0, 0, 3, 0, 1, 0},
    {1, 0, 8, 7, 0, 0, 5, 0, 6},
    {6, 0, 0, 0, 2, 5, 0, 7, 0}
    };
#endif
#if 0
    int s[9][9] = { 
    {0, 0, 0, 0, 0, 0, 8, 0, 0},
    {4, 0, 0, 2, 0, 8, 0, 5, 1},
    {0, 8, 3, 9, 0, 0, 0, 0, 7},
    {0, 4, 0, 5, 0, 0, 0, 8, 2},
    {0, 0, 5, 0, 0, 0, 4, 0, 0},
    {8, 7, 0, 0, 0, 9, 0, 3, 0},
    {2, 0, 0, 0, 0, 7, 1, 6, 0},
    {3, 6, 0, 1, 0, 5, 0, 0, 4},
    {0, 0, 4, 0, 0, 0, 0, 0, 0}
    };
#endif
    int s[9][9] = { 
    {0, 0, 0, 9, 0, 0, 1, 0, 2},
    {4, 0, 0, 1, 0, 6, 0, 0, 0},
    {0, 8, 0, 0, 2, 0, 0, 0, 5},
    {6, 3, 0, 0, 0, 0, 5, 0, 0},
    {0, 0, 4, 5, 0, 7, 9, 0, 0},
    {0, 0, 5, 0, 0, 0, 0, 3, 1},
    {9, 0, 0, 0, 6, 0, 0, 1, 0},
    {0, 0, 0, 8, 0, 9, 0, 0, 7},
    {7, 0, 6, 0, 0, 2, 0, 0, 0}
    };

    memcpy(sk, s, sizeof(sk));
    display();

    sudoku();

    return 0;
}
