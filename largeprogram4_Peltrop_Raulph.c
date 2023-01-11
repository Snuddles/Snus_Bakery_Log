// Raulph Peltrop
// Dr. Steinberg
// COP3223C Section 1
// Large Program 4

// Creates a database of 'cupcake' records with pre-existing users that can be outputted to a .txt file

// Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Typedef Structure
typedef struct addCustomer_t{
    char fname[20];
    char lname[20];
    char flavor[20];
    int amount;    
}addCustomer_t;

// Function Prototypes
void menu();
addCustomer_t existingCustomers(addCustomer_t id, addCustomer_t database[]);
addCustomer_t addingCustomer(addCustomer_t id);
int verifyCustomer(char fnameTest[], char lnameTest[], char flavorTest[], int amountTest, addCustomer_t database[], int position);
void removeCustomer(int position, addCustomer_t database[], int remove);
void displayList(int position, addCustomer_t database[]);

// Main Function
int main()
{
    // Needed array, option selection, and current position for each customer created
    addCustomer_t database[30];
    addCustomer_t id; 
    char option; 
    int position = 6;
    // Welcome message 
    puts("Welcome to Snu's Bakery Log!");
    // Adding existing customers to the database
    existingCustomers(id, database);
    while (option != 'E' && option != 'e')
    {
        // Displays menu
        menu();
        scanf(" %c", &option);
        // Fail safe
        while (!(isalpha(option)))
        {
            printf("\nThis is an invalid option. Please select from given options.\n");
            menu();
            scanf(" %c", &option);
        }
        // Options from menu selection
        // Adding Customer
        if (option == 'A' || option == 'a')
        {
            if (position > 30)
            {
                  printf("You have too many orders on file! Please remove an order to continue.");
            }
            else
            {
                database[position] = addingCustomer(id);
                position++;
            }
        }
        // Verifying Customer
        else if (option == 'V' || option == 'v')
        {
            // Comparison arrays and variable needed
            char fnameTest[20] = "";
            char lnameTest[20] = "";
            char flavorTest[20] = "";
            int amountTest = 0;
            // Collecting user input for verifications
            printf("Please enter the first name of the client: ");
            scanf(" %s", fnameTest);
            printf("Please enter the last name of the client: ");
            scanf(" %s", lnameTest);
            printf("Please be sure to type in the correct flavor from the list:\nVanilla\nChocolate\nStrawberry\n");
            printf("Please enter the flavor the client requested: ");
            scanf(" %s", flavorTest);
            // Failsafe
            while(strcmp(flavorTest, "Vanilla") != 0 && strcmp(flavorTest, "Chocolate") != 0 && strcmp(flavorTest, "Strawberry") != 0)
            {
                printf("This is not part of the flavor list.\nPlease type the correct flavor from: Vanilla, Chocolate, or Strawberry.\n");
                printf("Please enter the flavor the client requested: ");
                scanf(" %s", flavorTest);
            }
            printf("Please enter the amount they requested: ");
            scanf("%d", &amountTest);
            // Failsafe
            while(amountTest <= 0)
            {
                fflush(stdin);
                printf("Invalid input.\nPlease type in an amount greater then zero.\n");
                printf("Please enter the amount they requested: ");
                scanf("%d", &amountTest);
            }
            // Checking user input towards database
            int testingTotal = verifyCustomer(fnameTest, lnameTest, flavorTest, amountTest, database, position);
            // Exists or does not exist in database     
            if (testingTotal == 4)
            {
                printf("Successfully verified\n");
            }
            else
            {
                printf("The order does not exist\n");
            }
        }
        // Removing Customer
        else if (option == 'R' || option == 'r')
        {
            // If no orders currently exist in the database
            if (position == 0)
            {
                printf("There are currently no orders to be removed.\n");
                printf("Please add an order before you can remove one.\n");
            }
            else
            {
                // Displays all current orders that can be removed and collects user's decision
                int remove = 0;
                displayList(position, database);
                printf("Whose order would you like to remove? ");
                scanf("%d", &remove);
                // Failsafe
                while(remove > position || remove < 0)
                {
                    printf("This is an invalid selection. Please try again.\n");
                    displayList(position, database);
                    printf("Whose order would you like to remove? ");
                    scanf("%d", &remove);
                }
                // Calling removeCustomer function and subtracting from total position by 1
                removeCustomer(position, database, remove);
                position--; 
            }
        }
        // Displaying Database
        else if (option == 'D' || option == 'd')
        {
            // Displays current database
            if (position == 0)
            {
                printf("There is no order currently placed. Please add an order.\n");
            }
            else
            {
                displayList(position, database);
            }
        }
        // Exiting Database && Failsafe for incorrect inputs for menu
        else
        {
            // Breaks out of the menu loop
            if (option == 'e' || option == 'E')
            {
                break;
            }
            // If an invalid selection is selected
            else
            {
                printf("This is an invalid option. Please select from given options.\n");
            }
        }
    }
    // File creation
    printf("Thank you for coming. See you soon! :)\n");
    FILE *fptr = fopen("Records.txt", "w");
    // Fail safe
    if (fptr == NULL)
    {
        printf("Records.txt was not successfully created.\n");
        return 1;
    }
    else
    {
        int start = 0;
        // Heading of file
        fprintf(fptr, "Snu's Bakery Record Log\n");
        while(start < position)
        {
            // Prints the entire list
            fprintf(fptr, "***********************************************\n");
            fprintf(fptr, "First name: %s\n", (database + start)->fname);
            fprintf(fptr, "Last name: %s\n", (database + start)->lname);
            fprintf(fptr, "Flavor: %s\n", (database + start)->flavor);
            fprintf(fptr, "Amount: %d\n", (database + start)->amount);
            start++;
            fprintf(fptr, "\n");
        }
        // Closes file
        fclose(fptr);
    }
    return 0;
}
// Function Definition's
// Displays menu
void menu()
{
    printf("What would you like today?\n");
    printf("A: Add a customer\n");
    printf("V: Verify order\n");
    printf("R: Remove an order\n");
    printf("D: Display all current orders\n");
    printf("E: Exit Snu's Bakery Log\n");
    printf("Choice: ");
}
// Creates existing customers
addCustomer_t existingCustomers(addCustomer_t id, addCustomer_t database[])
{
    // Arrays needed for first and last name strings
    char eCustFname[6][20] = {"Tom", "Brad", "Shirelle", "Frank", "Karen", "Elizabeth"};
    char eCustLname[6][20] = {"Brady", "Pitt", "Vega", "Ocean", "Jones", "Washington"};
    // Loop through the id and populate the database with first, last, flavor, and amount requested
    for (int i = 0; i < 6; i++)
    {
        strcpy(id.fname, eCustFname[i]);
        strcpy(id.lname, eCustLname[i]);
        if (i < 2)
        {
            strcpy(id.flavor, "Vanilla");
        }
        else if (i >= 2 && i <= 4)
        {
            strcpy(id.flavor, "Chocolate");
        }
        else if (i < 4)
        {
            strcpy(id.flavor, "Strawberry");
        }
        // Randomly picks an amount number for existing customers
        id.amount = rand() % (1 - 50);
        database[i] = id;
    }
    return database[0];
}
// Adds customers to the database
addCustomer_t addingCustomer(addCustomer_t id)
{ 
    char option;
    int create = 0;
    // Acquiring clients information
    printf("What is the first name of the order? ");
    scanf(" %s", id.fname);
    printf("What is the last name of the order? ");
    scanf(" %s", id.lname);
    printf("What flavor would you like to order for your cupcake?\n");
    printf("V: Vanilla\n");
    printf("C: Chocolate\n");
    printf("S: Strawberry\n");
    printf("Choice: ");
    scanf(" %c", &option);
    // Fail safe
    while (option != 'c' && option != 'v' && option != 's' && option != 'C' && option != 'V' && option != 'S')
    {
        puts("This is an invalid option. Please try again");
        printf("What flavor would you like to order for your cupcake?\n");
        printf("V: Vanilla\n");
        printf("C: Chocolate\n");
        printf("S: Strawberry\n");
        printf("Choice: ");
        scanf(" %c", &option);
    }
    if (option == 'v' || option == 'V')
    {
        strcpy(id.flavor, "Vanilla");
    }
    else if (option == 'c' || option == 'C')
    {
        strcpy(id.flavor, "Chocolate");
    }
    else if (option == 's' || option == 'S')
    {
        strcpy(id.flavor, "Strawberry");
    }
    printf("Excellent choice! How many would you like to order today? ");
    scanf("%d", &create);
    // Fail safe
    while (create <= 0)
    {
        fflush(stdin);
        printf("Invalid input. Please select a value greater then zero.\n");
        printf("How many would you like to order today? ");
        scanf(" %d", &create);
    }
    id.amount = create;
    return id;
}
// Verification for existing clients
int verifyCustomer(char fnameTest[], char lnameTest[], char flavorTest[], int amountTest, addCustomer_t database[], int position)
{
    // Running total
    int testingTotal = 0;
    for (int i = 0; i < position; i++)
    {
        // Checking first name
        if(strcmp(fnameTest, database[i].fname) == 0)
        {
            testingTotal++;
            // Checking last name
            if(strcmp(lnameTest, database[i].lname) == 0)
            {
                testingTotal++;
                // Checking correct flavor
                if(strcmp(flavorTest, database[i].flavor) == 0)
                {
                    testingTotal++;
                    // Checking correct amount
                    if(amountTest == database[i].amount)
                    {
                        testingTotal++;
                        // If client exists, testingTotal returns 4
                         return testingTotal;
                    }
                    else
                    {
                        testingTotal = 0;
                    }
                }
                else
                {
                    testingTotal = 0;
                }
            }
            else
            {
                testingTotal = 0;
            }
        }
        else
        {
            testingTotal = 0;
        }
    }
    // If client does not exist
    return testingTotal;
}
// Deletes customers in the database
void removeCustomer(int position, addCustomer_t database[], int remove)
{
    // Removing existing index
    for (int i = 0; i < position; i++)
    {
        database[remove] = database[remove + 1];
    }
}
// Displays existing customers in the database
void displayList(int position, addCustomer_t database[])
{
    // For Loop to print current existing database
    for (int i = 0; i < position; i++)
    {
        printf("***********************************\n");
        printf("Customer \t%d\n", i);
        printf("First Name:\t%s\n", database[i].fname);
        printf("Last Name:\t%s\n", database[i].lname);
        printf("Flavor:\t\t%s\n", database[i].flavor);
        printf("Requested:\t%d\n", database[i].amount);
        printf("\n");
    }
    printf("***********************************\n");
}
