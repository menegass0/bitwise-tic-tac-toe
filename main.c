#include <stdio.h>

void printTable(__uint8_t *);
char * returnBinary(int);

int main()
{
    __uint8_t rows[3] = {0, 0, 0};
    __uint8_t position;
    char leitura[3];

    // ------------debugging variables----------
    // int mask = 0;
    // int shiftedMask = 0;
    // __uint8_t * row ;
    // int rowIndex = 0;
    // int result = 0;
    // ----------------------------------------

    printTable(rows);

    for (__uint8_t i = 0; i < 9; i++) {
        printf("%s choose a row and a column like 21 (2nd row, 1st column): ", i % 2 == 0 ? "Player 1" : "Player 2");
        scanf("%2s", leitura);

        // converting the string into uint8
        sscanf(leitura, "%2hhu", &position);

        if (position / 10 < 1 || position / 10 > 3 ||
            position % 10 < 1 || position % 10 > 3)
        {
            printf("invalid value\n");
            i--;
            continue;  
        }
        // shifting 1 which is a binary pair (00000001) (2 << column * 2) -> (00010000) ( 01 mask for player 1 )
        // shifting 2 which is a binary pair (00000010) (2 << column * 2) -> (00110000) ( 11 mask for player 2 )

        printf("inst 1/   %s\n", returnBinary((i % 2 == 0 ? 0x01 : 0x02) << ((position % 10) - 1) * 2));
        printf("inst 2/   %s\n", returnBinary(rows[(position % 10) - 1]));
        
        printf("inst 3/   %s\n", returnBinary((i % 2 == 0 ? 0x01 : 0x02) << ((position % 10) - 1) * 2 | rows[(position % 10) - 1]));

        // ---------- debugging breakpoints ------------
        // rowIndex = (position / 10) - 1;
        // mask = (i % 2 == 0 ? 0x01 : 0x02);
        // shiftedMask = mask << (((position % 10) - 1) * 2);
        // result = ((i % 2 == 0 ? 0x01 : 0x02) << (((position % 10) - 1) * 2)) | rows[(position / 10) - 1];
        // row = &rows[(position / 10) - 1];
        // ---------------------------------------------

        rows[(position / 10) - 1] = ((i % 2 == 0 ? 0x01 : 0x02) << (((position % 10) - 1) * 2)) | rows[(position / 10) - 1];

        printf("number on rows %s\n", returnBinary(rows[(position / 10) - 1]));

        printTable(rows);
    }

    return 0;
}

void printTable(__uint8_t * rows){
    printf("  1   2   3\n");
    for (__uint8_t i = 0; i < 5; i++)
    {
        if (i % 2 == 0)
        {
            printf("%d", (i / 2) + 1);
            for (__uint8_t j = 0; j < 3; j++)
            {
                printf(" %s |", (rows[i / 2] >> (j * 2) & 0x03) == 2 ? "O" : (rows[i / 2] >> (j * 2) & 0x03) == 1 ? "X"
                                                                                                                   : " ");
            }
            printf("\n");
        }
    }
}

char * returnBinary(int num) {
    static char bin[9]; // 32 bits + null terminator
    int i;

    for (i = 7; i >= 0; i--) {
        bin[7 - i] = ((num >> i) & 1) + '0';
    }
    bin[8] = '\0';
    
    return bin;
}
