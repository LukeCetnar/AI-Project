
#include <stdio.h>
#include <string.h>

#define MAXN 25
struct TABLE { int LEN; int WHERE; int POS; int LIST[MAXN]; } BLOCK[MAXN];

void move_block(int B) {
    int I, A, P, L;
    A = BLOCK[B].WHERE;
    P = BLOCK[B].POS + 1;
    L = BLOCK[A].LEN;
    for (I = P; I < L; I++) {
        B = BLOCK[A].LIST[I];
        BLOCK[B].WHERE = B;
        BLOCK[B].POS = BLOCK[B].LEN;
        BLOCK[B].LIST[BLOCK[B].LEN++] = B;
    }
    BLOCK[A].LEN = P;
}

void move(int B1, int B2) {
    int I, A, B, P, L, T;
    A = BLOCK[B1].WHERE;
    B = BLOCK[B2].WHERE;
    P = BLOCK[B1].POS;
    L = BLOCK[A].LEN;
    for (I = P; I < L; I++) {
        T = BLOCK[A].LIST[I];
        BLOCK[T].WHERE = B;
        BLOCK[T].POS = BLOCK[B].LEN;
        BLOCK[B].LIST[BLOCK[B].LEN++] = T;
    }
    BLOCK[A].LEN = P;
}

int main() {
    int N, I, A, B;
    char AC[5], WH[5];
    scanf("%d", &N);
    for (I = 0; I < N; I++) {
        BLOCK[I].LEN = 1;
        BLOCK[I].WHERE = I;
        BLOCK[I].POS = 0;
        BLOCK[I].LIST[0] = I;
    }

    while (scanf("%s", AC)) {
        if (strcmp(AC, "quit") == 0)
            break;
        scanf("%d%s%d", &A, WH, &B);

        if (A < 0 || A >= N || B < 0 || B >= N)
            continue;
        if (BLOCK[A].WHERE == BLOCK[B].WHERE)
            continue;

        if (strcmp(AC, "move") == 0)
            move_block(A);

        if (strcmp(WH, "onto") == 0)
            move_block(B);

        move(A, B);

    }

    for (I = 0; I < N; I++) {
        printf("%d:", I);
        for (A = 0; A < BLOCK[I].LEN; A++)
            printf(" %d", BLOCK[I].LIST[A]);
        printf("\n");
    }

    return 0;
}