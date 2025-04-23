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
                displayCombinedMenu(menuItems, itemPrices, drinkItems, drinkPrices, MAX_ITEMS + MAX_DRINK_ITEMS);
                printf("\nEnter the number of the item you want to add: ");
                int addItemChoice;
                scanf("%d", &addItemChoice);

                if (addItemChoice < 1 || addItemChoice > MAX_ITEMS + MAX_DRINK_ITEMS) {
                    printf("Invalid choice. Returning to menu.\n");
                    continue;
                }

                printf("Enter the quantity for the new item: ");
                int addItemQuantity;
                scanf("%d", &addItemQuantity);

                if (addItemChoice <= MAX_ITEMS) {
                    // Add food item
                    orderQuantities[addItemChoice - 1] += addItemQuantity;
                } else {
                    // Add drink item
                    drinkQuantities[addItemChoice - MAX_ITEMS - 1] += addItemQuantity;
                }
            }
        }
    } while (tolower(changeOrder) == 'y');
}

int main(void) {
    user();
    tel();
    char menuItems[MAX_ITEMS][MAX_ITEM_NAME_LENGTH] = {"Shio Ramen", "Shoyu Ramen", "Miso Ramen", "Tonkatsu Ramen", "Ramen Kobe", "Hakodate Ramen", "Kitakata Ramen"};
    float itemPrices[MAX_ITEMS] = {199, 209, 219, 229, 239, 249, 250};
    int orderQuantities[MAX_ITEMS] = {0};

    char drinkItems[MAX_DRINK_ITEMS][MAX_ITEM_NAME_LENGTH] = {
        "Red Tea", "Cola", "Iced Tea", "Lemonade", "Orange Juice", "Mango Smoothie", "Melon Soda"
    };
    float drinkPrices[MAX_DRINK_ITEMS] = {20, 30, 25, 35, 40, 50, 50};
    int drinkQuantities[MAX_DRINK_ITEMS] = {0};

    int choice, quantity;
    float serviceFee = 0;
    float totalCost = 0, amountPaid = 0;
    char seniorConfirm = 'N';
    char AnotherOrder = 'Y';
    char resetter = 'Y';
    do {
        printf("---------------------------> Welcome to Show You Ramen  <---------------------------\n");
        displayCombinedMenu(menuItems, itemPrices, drinkItems, drinkPrices, MAX_ITEMS);
        
        printf("\nPress 0 to skip");
        printf("\nPlease Enter a Value from (1 to 7): ");
        
        scanf("%d", &choice);

        if (choice == 0) {
            printf("Are you sure you want to skip? (Y/N): ");
            scanf(" %c", &resetter);
            if (tolower(resetter) == 'n') {
                printf("restarting menu...");
                continue;
            } else {
                break;
            }
        }

        if (choice < 1 || choice > MAX_ITEMS) {
            printf("Invalid choice. Try again.\n");
            continue;
        }

        printf("Enter quantity: ");
        scanf("%d", &quantity);

        if (quantity < 0) {
            printf("Invalid quantity. Try again.\n");
            continue;
        }

        orderQuantities[choice - 1] += quantity;

        printf("\n\n======== Current Order Summary =========\n");
        for (int i = 0; i < MAX_ITEMS; i++) {
            if (orderQuantities[i] > 0) {
                printf("%-30s x%d   ₱%.2f\n", menuItems[i], orderQuantities[i], itemPrices[i] * orderQuantities[i]);
            }
        }

        for (int i = 0; i < MAX_DRINK_ITEMS; i++) {
            if (drinkQuantities[i] > 0) {
                printf("%-30s x%d   ₱%.2f\n", drinkItems[i], drinkQuantities[i], drinkPrices[i] * drinkQuantities[i]);
            }
        }
        printf("________________________________________\n");

        printf("\nWant to Add another order? (Y/N): ");
        scanf(" %c", &AnotherOrder);

        if (tolower(AnotherOrder) != 'y' && tolower(AnotherOrder) != 'n') {
            printf("Invalid input... Returning to menu.\n");
        }

    } while (tolower(AnotherOrder) == 'y');

    char drinkreset = 'Y';
    char orderDrinks = 'N';
    int drinksMenuShown = 0;

    printf("\nWould you like to order drinks? (Y/N): ");
    scanf(" %c", &orderDrinks);

    if (tolower(orderDrinks) == 'y' && !drinksMenuShown) {
        displayCombinedMenu(menuItems, itemPrices, drinkItems, drinkPrices, MAX_DRINK_ITEMS);
        drinksMenuShown = 1;

        do {
            printf("\nPress 0 to skip: ");
            printf("\nPlease Enter a Drink Item from (8 to 14): ");
            scanf("%d", &choice);

            if (choice == 0) {
                printf("Are you sure you want to skip? (Y/N): ");
                scanf(" %c", &drinkreset);
                if (tolower(drinkreset) == 'n') {
                    printf("restarting menu...");
                    continue;
                } else {
                    break;
                }
            }

            if (choice < 8 || choice > 14) {
                printf("Invalid choice. Try again.\n");
                continue;
            }

            printf("Enter quantity: ");
            scanf("%d", &quantity);

            if (quantity < 0) {
                printf("Invalid quantity. Try again.\n");
                continue;
            }

            drinkQuantities[choice - 8] += quantity;

            printf("\n\n======== Current Order Summary =========\n");
            for (int i = 0; i < MAX_ITEMS; i++) {
                if (orderQuantities[i] > 0) {
                    printf("%-30s x%d   ₱%.2f\n", menuItems[i], orderQuantities[i], itemPrices[i] * orderQuantities[i]);
                }
            }

            for (int i = 0; i < MAX_DRINK_ITEMS; i++) {
                if (drinkQuantities[i] > 0) {
                    printf("%-30s x%d   ₱%.2f\n", drinkItems[i], drinkQuantities[i], drinkPrices[i] * drinkQuantities[i]);
                }
            }
            printf("________________________________________\n");

            printf("\nWant to Add another order? Y or N?: ");
            scanf(" %c", &AnotherOrder);

            if (tolower(AnotherOrder) != 'y' && tolower(AnotherOrder) != 'n') {
                printf("Invalid input... Returning to menu.\n");
            }

        } while (tolower(AnotherOrder) == 'y');
    }

    float totalFoodCost = calculateTotalCost(itemPrices, orderQuantities, MAX_ITEMS);
    float totalDrinkCost = calculateTotalCost(drinkPrices, drinkQuantities, MAX_DRINK_ITEMS);

    totalCost = totalFoodCost + totalDrinkCost;
    
    float discountCost, serviceTotal;
    float change;
    
    printf("\nAre you a senior citizen or PWD? (Y/N): ");
    scanf(" %c", &seniorConfirm);

    if (tolower(seniorConfirm) == 'y') {
        printf("\nCongratulations! You've got a 20%% discount.\n");
    }


    manageFinalOrder(menuItems, itemPrices, orderQuantities, drinkItems, drinkPrices, drinkQuantities);

    printf("\n============= Food Order Summary ============\n");
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (orderQuantities[i] > 0) {
            printf("%-30s x%d   ₱%.2f\n", menuItems[i], orderQuantities[i], itemPrices[i] * orderQuantities[i]);
        }
    }

    printf("\n============= Drink Order Summary ============\n");
    for (int i = 0; i < MAX_DRINK_ITEMS; i++) {
        if (drinkQuantities[i] > 0) {
            printf("%-30s x%d   ₱%.2f\n", drinkItems[i], drinkQuantities[i], drinkPrices[i] * drinkQuantities[i]);
        }
    } 
    
    totalFoodCost = calculateTotalCost(itemPrices, orderQuantities, MAX_ITEMS);
    totalDrinkCost = calculateTotalCost(drinkPrices, drinkQuantities, MAX_DRINK_ITEMS);
    totalCost = totalFoodCost + totalDrinkCost;
    serviceFee = 0.08 * totalCost;
    serviceTotal = serviceFee + totalCost;
    discountCost = serviceTotal*0.8;
    
    

    
    printf("________________________________________\n");
    printf("Total Food Cost: ₱%.2f\n", totalFoodCost);
    printf("Total Drink Cost: ₱%.2f\n", totalDrinkCost);

    printf("\nService Fee (8%% of total cost): ₱%.2f\n", serviceFee);
    printf("\nTotal Cost with Service Fee: ₱%.2f\n", serviceTotal);
    if (seniorConfirm == 'y'){
        printf("\nOverall Cost through pwd discount: ₱%.2f\n", discountCost);
    }
    
    printf("\nEnter Amount Paid: ₱");
    scanf("%f", &amountPaid);
    
    if (tolower(seniorConfirm) == 'y'){
        while (amountPaid < discountCost) {
            printf("Amount paid is less than the total cost. Please enter a sufficient amount: ₱");
            scanf("%f", &amountPaid);
        }   
        change = amountPaid - discountCost;
        printf("Change: ₱%.2f\n", change);
    }else{
        while (amountPaid < totalCost) {
            printf("Amount paid is less than the total cost. Please enter a sufficient amount: ₱");
            scanf("%f", &amountPaid);
        }
        change = amountPaid - totalCost;
        printf("Change: ₱%.2f\n", change);
    }

    printf("\n****Thank You for Purchasing****\n");

    return 0;
}
