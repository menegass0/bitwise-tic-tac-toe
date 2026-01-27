#include <stdio.h>

int main()
{
    __uint8_t rows[3] = {0, 0, 0};
    __uint8_t position;
    char leitura[2];

    printf("  1   2   3\n");
    printf("1   |   |  \n");
    printf("  ---------\n");
    printf("2   |   |  \n");
    printf("  ---------\n");
    printf("3   |   |  \n");

    printf("choose a row and a column like 21 (2nd row, 1st column): ");
    scanf("%2s", leitura);

    // converting the string into uint8
    sscanf(leitura, "%2hhu", &position);

    if (position / 10 > 3 || position % 10 > 3)
    {
        printf("invalid value\n");

        return 0;
    }

    // shifting 1 which is a binary pair (00000001) (3 << column * 2) -> (00010000) ( 01 mask for player 1)
    // shifting 3 which is a binary pair (00000011) (3 << column * 2) -> (00110000) ( 11 mask for player 2)

    rows[(position / 10) - 1] = (0x01 << ((position % 10) - 1) * 2) | rows[(position % 10) - 1];

    printf("number on rows %d\n", rows[(position / 10) - 1]);

    printf("  1   2   3\n");
    for (__uint8_t i = 0; i < 5; i++)
    {
        if (i % 2 == 0)
        {
            printf("%d", (i / 2) + 1);
            for (__uint8_t j = 0; j < 3; j++)
            {
                printf(" %s |", (rows[i / 2] >> (j * 2) & 0x03) == 3 ? "11" : (rows[i / 2] >> (j * 2) & 0x03) == 1 ? "01"
                                                                                                                   : "00");
            }
            printf("\n");
        }
    }

    printf("row %d\n", (position / 10));
    printf("column %d\n", (position % 10));

    printf("You entered: %2s\n", leitura);
    printf("value of position: %u\n", position);
    return 0;
}