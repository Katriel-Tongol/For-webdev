#include <stdio.h>
#include <ctype.h>

#define MAX_ITEMS 7
#define MAX_DRINK_ITEMS 7
#define MAX_ITEM_NAME_LENGTH 50

float totalDrinkCost, totalFoodCost;

float calculateTotalCost(float prices[], int quantities[], int numItems) {
    float total = 0;
    for (int i = 0; i < numItems; i++) {
        total += prices[i] * quantities[i];
    }
    return total;
}

void displayCombinedMenu(char foodItems[][MAX_ITEM_NAME_LENGTH], float foodPrices[], char drinkItems[][MAX_ITEM_NAME_LENGTH], float drinkPrices[], int menuSize) {
    printf("================================== Food & Drink Menu ==============================\n");
    printf("         =========== Food ===========                    ========= Drinks ========\n");
    for (int i = 0; i < MAX_ITEMS; i++) {
        printf("%d. %-30s ₱%.2f\t\t\t%d. %-30s ₱%.2f\n", i + 1, foodItems[i], foodPrices[i], i + MAX_ITEMS + 1, drinkItems[i], drinkPrices[i]);
    }
    printf("_____________________n____________________________________________________________________\n");
}

void user(void) {
    char custname[20] = {};
    char nameconfirm = 'Y';

    do {
        printf("Enter your username (no space):\n");
        scanf("%s", custname);

        printf("Is your username correct? Please confirm (Y/N): ");
        scanf(" %c", &nameconfirm);

        if (tolower(nameconfirm) == 'n') {
            printf("Restarting...\n");
        } 
        else if (tolower(nameconfirm) != 'n' && tolower(nameconfirm) != 'y') {
            printf("Error... invalid input\nRestarting... \n\n");
        }

    } while (tolower(nameconfirm) != 'y');

    printf("Your username is %s\n\n", custname);
}

void tel(void) {
    int num1, num2, num3;
    int count;
    char numconfirm = 'Y';

    do {
        printf("Enter phone number [XXX XXX XXXX]:\n");
        count = scanf("%d %d %d", &num1, &num2, &num3);
        if (count == 3) {
            printf("You entered %d-%d-%d \n", num1, num2, num3);
            printf("Is this correct? Please confirm (Y/N)\n");
            scanf(" %c", &numconfirm);
            if (tolower(numconfirm) == 'n') {
                printf("Restarting...\n");
            }
        } else {
            printf("Input not in the correct format.\n");
        }
    } while (tolower(numconfirm) == 'n');
    printf("Your contact number is (+63) %d-%d-%d\n\n", num1, num2, num3);
}

void manageFinalOrder(char menuItems[][MAX_ITEM_NAME_LENGTH], float itemPrices[], int orderQuantities[], char drinkItems[][MAX_ITEM_NAME_LENGTH], float drinkPrices[], int drinkQuantities[]) {
    char changeOrder = 'N';
    int changeChoice;
    char finality = 'Y';
    do {
        printf("\n\n======== Current Order Summary =========\n");
        for (int i = 0; i < MAX_ITEMS; i++) {
            if (orderQuantities[i] > 0) {
                printf("%d. %-30s x%d   ₱%.2f\n", i + 1, menuItems[i], orderQuantities[i], itemPrices[i] * orderQuantities[i]);
            }
        }

        for (int i = 0; i < MAX_DRINK_ITEMS; i++) {
            if (drinkQuantities[i] > 0) {
                printf("%d. %-30s x%d   ₱%.2f\n", i + MAX_ITEMS + 1, drinkItems[i], drinkQuantities[i], drinkPrices[i] * drinkQuantities[i]);
            }
        }
        printf("________________________________________\n");

        printf("\nDo you want to change your order? (Y/N): ");
        scanf(" %c", &changeOrder);

        if (tolower(changeOrder) == 'y') {
            printf("Enter the number of the item you want to change or remove (0 to exit):");
            printf("\n(1-7 for ramen) (8-14 for drinks): ");
            scanf("%d", &changeChoice);

            if (changeChoice == 0) {
                printf("Is your order finalized? (Y/N): ");
                scanf(" %c", &finality);
                if (tolower(finality) == 'n') {
                    printf("restarting menu...");
                    continue;
                } else {
                    break;
                }
            }

            if (changeChoice < 1 || changeChoice > MAX_ITEMS + MAX_DRINK_ITEMS) {
                printf("Invalid choice. Try again.\n");
                continue;
            }

            if (changeChoice <= MAX_ITEMS) {
                // Change or remove food item
                int foodIndex = changeChoice - 1;
                printf("Enter the new quantity for %s (enter 0 to remove): ", menuItems[foodIndex]);
                scanf("%d", &orderQuantities[foodIndex]);
            } else {
                // Change or remove drink item
                int drinkIndex = changeChoice - MAX_ITEMS - 1;
                printf("Enter the new quantity for %s (enter 0 to remove): ", drinkItems[drinkIndex]);
                scanf("%d", &drinkQuantities[drinkIndex]);
            }

            printf("\nWant to add another item? Y or N?: ");
            char addAnotherItem;
            scanf(" %c", &addAnotherItem);

            if (tolower(addAnotherItem) == 'y') {
                displayCombinedMenu(menuItems, itemPrices, drinkItems,
