#include <stdio.h>
#include <stdbool.h>

void printTable(__uint8_t *);
char * returnBinary(int);
bool verifyVictory(__uint8_t * rows);

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

        // printf("inst 1/   %s\n", returnBinary((i % 2 == 0 ? 0x01 : 0x02) << ((position % 10) - 1) * 2));
        // printf("inst 2/   %s\n", returnBinary(rows[(position % 10) - 1]));
        
        // printf("inst 3/   %s\n", returnBinary((i % 2 == 0 ? 0x01 : 0x02) << ((position % 10) - 1) * 2 | rows[(position % 10) - 1]));

        // ---------- debugging breakpoints ------------
        // rowIndex = (position / 10) - 1;
        // mask = (i % 2 == 0 ? 0x01 : 0x02);
        // shiftedMask = mask << (((position % 10) - 1) * 2);
        // result = ((i % 2 == 0 ? 0x01 : 0x02) << (((position % 10) - 1) * 2)) | rows[(position / 10) - 1];
        // row = &rows[(position / 10) - 1];
        // ---------------------------------------------

        rows[(position / 10) - 1] = ((i % 2 == 0 ? 0x01 : 0x02) << (((position % 10) - 1) * 2)) | rows[(position / 10) - 1];

        //since the least amount of steps to victory is 5 the victory check is only only done from the 5th round foward
        if(i >= 4){
            if(verifyVictory(rows)){
                printf("vitoria\n");
                printTable(rows);
                break;
            }
        }

        // printf("number on rows %s\n", returnBinary(rows[(position / 10) - 1]));

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

bool verifyVictory(__uint8_t * rows){

    // if the middle row is less than 4 all of the possibilities of a win from the middle are impossible
    // if middle row is at least 4 the binary look like  00 00 (01) 00 which is a mark for player 1

    //next are the other 3 horizontals since they can be read from the row itself
    //the win condition on horizontal for X is to be 21 since  00 01 01 01 which is X X X
    //the win condition on horizontal for O is to be 63 since  00 11 11 11 which is O O O
    
    for(__uint8_t i = 0; i < 3; i++){
        if(rows[i] == 21 || rows[i] == 63){
            printf("victory on the horizontal %u\n" , i+1);
            return true;
        }
    }

    if(rows[1] >= 4){
        //making the middle vertical first 
        //0x0c -> 12 in binary mask 00001100 
        // if masked middle columns of the 3 gives the same value and are not 0 than is a victory situation
        if((rows[0] & 0x0c) != 00 && ((rows[0] & 0x0c) == (rows[1] & 0x0c)) && (rows[1] & 0x0c) == (rows[2] & 0x0c) ){
            printf("victory on the middle vertical");
            return true;
        }

        //left to right diagonal position (1, 1) to (3, 3)
        //top row masked as 48    -> 00 11 00 00
        //middle row masked as 12 -> 00 00 11 00
        //bottom row masked as 3  -> 00 00 00 11
        //now shifting is necessary since 00 11 00 00 != 00 00 11 00 != 00 00 00 11

        if(((rows[0] & 0x30) != 00) && (((rows[0] & 0x30 >> 4)) == ((rows[1] & 0x0c) >> 2)) && ((rows[1] & 0x0c) >> 2) == (rows[2] & 0x03) ){
            printf("victory on the left to right diagonal\n");
            return true;
        }

        //right to left diagonal position (1, 3) to (3, 1)
        //top row masked as 48    -> 00 00 00 11
        //middle row masked as 12 -> 00 00 11 00
        //bottom row masked as 3  -> 00 11 00 00
        if((rows[0] & 0x03) != 00 && ((rows[0] & 0x03) == ((rows[1] & 0x0c) >> 2)) && ((rows[1] & 0x0c) >> 2) == ((rows[2] & 0x30) >> 4) ){
            printf("%d\n", (rows[0] & 0x03));
            printf("%d\n", ((rows[1] & 0x0c) >> 2));
            printf("%d\n", ((rows[2] & 0x30) >> 4));
            printf("victory on the right to left diagonal\n");
            return true;
        }
    }

    //now its only the other 2 verticals that are left
    //verticals masked as 3   -> 00 00 00 11
    //----------------------- -> 00 00 00 11
    //----------------------- -> 00 00 00 11
    if((rows[0] & 0x03) != 00 && ((rows[0] & 0x03) == (rows[1] & 0x03)) && (rows[1] & 0x03) == (rows[2] & 0x03)){
        printf("victory on the right vertical");
        return true;
    }

    //verticals masked as 48  -> 00 11 00 00
    //----------------------- -> 00 11 00 00
    //----------------------- -> 00 11 00 00
    if((rows[0] & 0x30) != 00 && ((rows[0] & 0x30) == (rows[1] & 0x30)) && (rows[1] & 0x30) == (rows[2] & 0x30)){
        printf("victory on the left vertical");
        return true;
    }

    return false;
}