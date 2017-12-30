#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void    wait_to_exit(void)
{
    printf("\nPress Enter To Exit.\n");
    getchar(); //'eat' \n from the scanf
    getchar(); 
    return;
}

bool CheckItemWhitelist(int itemID)
{
    int maxID;
    int chk;
    int exception = itemID;

    exception &= 0x6000;
    if (exception == 0x4000) //If item is wrapping paper / Any item ID between 0x4000 - 0x5FFF
    goto ItemIsInventoryWhitelisted;

    maxID = 0x172B; //Real Max ID is 0x372B (exclude wrap paper) but for checks game -= 0x2000 from orig item ID
    itemID = itemID & ~0x8000;
    chk = itemID - 0x2000; //To cover items lower than 0x2000 (Enviroment Items)

    if (chk < maxID) //If item passes this check, it's 'valid'
    goto ItemIsInventoryWhitelisted;

    else if (chk >= maxID) //If item passes this check, it's 'invalid'
    goto ItemNotInventoryWhitelisted;

    ItemIsInventoryWhitelisted:
    return true;

    ItemNotInventoryWhitelisted:
    return false;
}

int main()
{
    char inputid[20];
    int itemid;
    int inputidlength;
    printf("\n~~ ACNL Item ID Validator by Slattz ~~\n\n");
    printf("Input the item ID [in hex w/ 0x] below:\n");
    scanf("%s", inputid);
    printf("\n");

    if (inputid[0] != '0' || inputid[1] != 'x')
    {
        printf("Inputted item ID has no 0x!\n");
        goto error;
    }

    inputidlength = strlen(inputid);
    if (inputidlength != 6) //'0xABCD' format expected
    {
        printf("Inputted item ID is incorrect size.\n");
        goto error;
    }

    itemid = strtol(inputid, NULL, 0);
    bool valid = CheckItemWhitelist(itemid);
    printf("Item ID 0x%X is %s\n\n", itemid, valid == true ? "Valid!" : "Invalid!");

    wait_to_exit();
    return 0;

    error:
    wait_to_exit();
    return -1;   
}
