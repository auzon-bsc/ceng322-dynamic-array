// This code written for C99
#include <stdio.h>
#include <stdlib.h>
/*
Product struct that has name, price and quantity
*/
typedef struct
{
    char *name;
    double price;
    int quantity;

} Product;

/*
Prints the products for a given Product array
Implemented for choice 1 and 3
*/
void print_products(Product product_array[], int size)
{
    // Iterates all elements in Product array
    for(int i = 0; i < size; i++)
    {
        char *name = product_array[i].name;
        double price = product_array[i].price;
        int quantity = product_array[i].quantity;
        printf("Product name:%s,Unit price:%g,Quantity:%d\n", name, price, quantity);
    }
}

/*
Prints main menu
*/
void print_menu()
{
    char menu[5][50] = 
        {
            "---- MAIN MENU ----\n",
            "Buy a product\n",
            "List all products\n",
            "Shopping summary\n",
            "Exit\n",
        };

    printf("%s", menu[0]);
    // Iterates for all menu options
    for(int i = 1; i < 5; i++)
    {
        printf("%d- %s", i, menu[i]);
    }
}
/*
Copies elements from a char array to another char array
*/
void arr_copy(char** from, char** to)
{
    int from_length = sizeof(*from) / sizeof(char);
    // Iterates for all elements in from array
    for(int i = 0; i < from_length; i++)
    {
        (*to)[i] = (*from)[i];
    }
}
/*
Doubles size of array and preserves its contents 
*/
void extend_array(char** dynamic_input_ptr, unsigned long* dynamic_input_size)
{
    *dynamic_input_size *= 2;
    char* new_array;
    new_array = (char*) malloc(*dynamic_input_size);
    arr_copy(dynamic_input_ptr, &new_array);
    free(*dynamic_input_ptr);
    *dynamic_input_ptr = (char*) malloc(*dynamic_input_size);
    arr_copy(&new_array, dynamic_input_ptr);
    free(new_array);
}
/*
String input function that uses dynamic array
*/
int string_input(char** dynamic_input_ptr, unsigned long dynamic_input_size)
{
    char char_buffer;
    int input_size = 0;

    scanf("%c", &char_buffer);
    // Iterate all characters from input stream
    while(char_buffer != '\n')
    {
        input_size++;
        if (input_size > 50) // Max allowed input size of 50 characters exceeded.
        {
            printf("Invalid Input: Input size cannot exceed 50 characters\n");
            while ((getchar()) != '\n'); // Empty the character stream.
            return -1; // Indicates input operation failed.
        }
        else if (input_size > dynamic_input_size) // If input stream size is bigger than dynamic array size
        {
            extend_array(dynamic_input_ptr, &dynamic_input_size);
        }
        (*dynamic_input_ptr)[input_size - 1] = char_buffer;
        scanf("%c", &char_buffer);
    }
    return 1; // Input operation success
}
/*
Calculates total price of an inventory(Product array)
*/
double calculate_total(Product product_array[], int size)
{
    double sum = 0;
    // Iterate all elements
    for(int i = 0; i < size; i++)
    {
        sum += product_array[i].price * product_array[i].quantity;
    }
    return sum;
}

/*
Compares two strings
If they are equal it returns 1
If they are not equal it returns 0
*/
int string_compare(char* string1, char* string2)
{
    int i = 0;
    // Compare characters one by one
    while(string1[i] != '\0' && string2[i] != '\0') // If strings ends exit the loop 
    {
        // Exit from loop and return 0 when any mismatch occurs between paralel characters
        if(string1[i] != string2[i])
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int main()
{
    int size = 10;
    Product product_array[size];
    Product buyer_inventory[size];

    // Data of the products
    char name_array[10][50] = {"Bread", "Egg", "Pasta", "Fish", "Milk", "Water Small", "Hand Sanitizer", "Toothpaste", "Pizza", "Chocolate"};
    double price_array[10] = {3.5, 2.82, 2.79, 15.98, 10.26, 1.55, 20.55, 10.83, 15.30, 5.21};
    int quantity_array[10] = {10, 30, 15, 25, 10, 35, 20, 15, 10, 40};

    // Initializing shop
    Product prod;
    for(int i = 0; i < size; i++)
    {
        prod.name = &(name_array[i][0]);
        prod.price = price_array[i];
        prod.quantity = quantity_array[i];
        product_array[i] = prod;
    }
    // Initializing buyer inventory
    for(int i = 0; i < size; i++)
    {
        prod.name = &(name_array[i][0]);
        prod.price = price_array[i];
        prod.quantity = 0;
        buyer_inventory[i] = prod;
    }

    // Printing main menu
    print_menu();

    // I/O Initializations
    char buffer_dump = '-';
    int choice = 0;
    int int_input = 0;
    
    unsigned long dynamic_input_size = 5;
    char* dynamic_input = (char*)malloc(dynamic_input_size); // Dynamic char array with size of 5 bytes
    char** dynamic_input_ptr;
    dynamic_input_ptr = &dynamic_input;
    
    // Main interactions betweeen user and program
    do
    {
        printf("Enter the choice:\n");
        scanf("%d", &choice);
        scanf("%c", &buffer_dump);
        // 1- Buy a product
        if(choice == 1)
        {
            // Asking for product name
            printf("Name of the product:\n");
            if(string_input(dynamic_input_ptr, dynamic_input_size) != 1) // Control for invalid input
            {
                continue;
            }
            // Searching for product
            int product_location = -1;
            for(int i = 0; i < size; i++)
            {
                if(string_compare(dynamic_input, product_array[i].name))
                {
                    product_location = i;
                    break;
                }
            }
            
            if(product_location == -1)
            {
                printf("Product not found\n");
                continue;
            }
            else
            {
                printf("Product found\n");
            }
            // Asking for quantity of product
            printf("Quantity of product:\n");
            scanf("%d", &int_input);
            scanf("%c", &buffer_dump);
            // If there is not enough quantity of an item
            if(int_input > product_array[product_location].quantity)
            {
                printf("There is not enough %s!\n", product_array[product_location].name);
            }
            else // Product-Inventory quantity calculation
            {
                product_array[product_location].quantity -= int_input;
                buyer_inventory[product_location].quantity += int_input;
                printf("You bought %d %s!\n", int_input, product_array[product_location].name);
            }
        }
        // 2- Print products
        if(choice == 2)
        {
            printf("----------- Product List -----------\n");
            print_products(product_array, size);
        }
        // 3- Shopping summary
        if(choice == 3)
        {
            printf("------ Shopping Summary ------\n");
            print_products(buyer_inventory, size);
            printf("------------------------------\n");
            double total_price = calculate_total(buyer_inventory, size);
            printf("Total price: %g\n", total_price);
        }
    } while (choice != 4);

    free(dynamic_input);
    return 0;
}