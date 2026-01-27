#include <stdio.h>

int main()
{
    __uint8_t l1;
    __uint8_t l2;
    __uint8_t l3;
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

    sscanf(leitura, "%2hhu", &position);

    printf("linha %d\n", (position / 10));
    printf("coluna %d\n", (position % 10));

    // switch (position / 10)
    // {
    // case 1:
    //     printf("row 1\n");
    //     break;

    // case 2:
    //     printf("row 2\n");
    //     break;

    // case 3:
    //     printf("row 3\n");
    //     break;

    // default:
    //     break;
    // }

    printf("You entered: %2s\n", leitura);
    printf("value of position: %u\n", position);
    return 0;
}