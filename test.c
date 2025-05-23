#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for the product in the bike shop
typedef struct Product {
    char manufacturer[100];
    char bike_brand[100];
    int quantity;
    char delivery_date[20];
    float unit_price;
    int sold_quantity;
    struct Product* prev;
    struct Product* next;
} Product;

// Function prototypes
Product* createProduct(char manufacturer[], char bike_brand[], int quantity, char delivery_date[], float unit_price, int sold_quantity);
void addToHead(Product** head, Product** tail, char manufacturer[], char bike_brand[], int quantity, char delivery_date[], float unit_price, int sold_quantity);
void addToTail(Product** head, Product** tail, char manufacturer[], char bike_brand[], int quantity, char delivery_date[], float unit_price, int sold_quantity);
void printProducts(Product* head);
void deleteFromHead(Product** head, Product** tail);
void deleteFromTail(Product** head, Product** tail);
void deleteByBikeBrand(Product** head, Product** tail, char bike_brand[]);
void editProduct(Product* head, char bike_brand[], char new_manufacturer[], char new_bike_brand[], int new_quantity, char new_delivery_date[], float new_unit_price, int new_sold_quantity);
void searchByManufacturer(Product* head, char manufacturer[]);
void searchByDate(Product* head, char delivery_date[]);
void searchByBikeBrand(Product* head, char bike_brand[]);
void printAvailableProducts(Product* head);
float calculateTotalCostByManufacturer(Product* head, char manufacturer[]);
float calculateTotalSoldCost(Product* head);
void sortByPrice(Product** head, Product** tail);
void swapNodes(Product* a, Product* b);
void freeProducts(Product* head);
void displayMenu();

// Function to create a new product
Product* createProduct(char manufacturer[], char bike_brand[], int quantity, char delivery_date[], float unit_price, int sold_quantity) {
    Product* newProduct = (Product*)malloc(sizeof(Product));
    if (!newProduct) {
        printf("Memory allocation error\n");
        exit(1);
    }
    strcpy(newProduct->manufacturer, manufacturer);
    strcpy(newProduct->bike_brand, bike_brand);
    newProduct->quantity = quantity;
    strcpy(newProduct->delivery_date, delivery_date);
    newProduct->unit_price = unit_price;
    newProduct->sold_quantity = sold_quantity;
    newProduct->prev = NULL;
    newProduct->next = NULL;
    return newProduct;
}

// Function to add a product to the head of the deque
void addToHead(Product** head, Product** tail, char manufacturer[], char bike_brand[], int quantity, char delivery_date[], float unit_price, int sold_quantity) {
    Product* newProduct = createProduct(manufacturer, bike_brand, quantity, delivery_date, unit_price, sold_quantity);
    if (*head == NULL) {
        *head = newProduct;
        *tail = newProduct;
    } else {
        newProduct->next = *head;
        (*head)->prev = newProduct;
        *head = newProduct;
    }
}

// Function to add a product to the tail of the deque
void addToTail(Product** head, Product** tail, char manufacturer[], char bike_brand[], int quantity, char delivery_date[], float unit_price, int sold_quantity) {
    Product* newProduct = createProduct(manufacturer, bike_brand, quantity, delivery_date, unit_price, sold_quantity);
    if (*head == NULL) {
        *head = newProduct;
        *tail = newProduct;
    } else {
        (*tail)->next = newProduct;
        newProduct->prev = *tail;
        *tail = newProduct;
    }
}

// Function to print all products
void printProducts(Product* head) {
    if (head == NULL) {
        printf("Product list is empty\n");
        return;
    }
    Product* temp = head;
    while (temp != NULL) {
        printf("Manufacturer: %s\n", temp->manufacturer);
        printf("Bike Brand: %s\n", temp->bike_brand);
        printf("Quantity: %d\n", temp->quantity);
        printf("Delivery Date: %s\n", temp->delivery_date);
        printf("Unit Price: %.2f\n", temp->unit_price);
        printf("Sold Quantity: %d\n\n", temp->sold_quantity);
        temp = temp->next;
    }
}

// Function to delete a product from the head of the deque
void deleteFromHead(Product** head, Product** tail) {
    if (*head == NULL) {
        printf("Product list is empty\n");
        return;
    }
    Product* temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    } else {
        *tail = NULL;
    }
    free(temp);
}

// Function to delete a product from the tail of the deque
void deleteFromTail(Product** head, Product** tail) {
    if (*head == NULL) {
        printf("Product list is empty\n");
        return;
    }
    Product* temp = *tail;
    *tail = (*tail)->prev;
    if (*tail != NULL) {
        (*tail)->next = NULL;
    } else {
        *head = NULL;
    }
    free(temp);
}

// Function to delete a product by bike brand
void deleteByBikeBrand(Product** head, Product** tail, char bike_brand[]) {
    Product* temp = *head;
    while (temp != NULL && strcmp(temp->bike_brand, bike_brand) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Product with bike brand %s not found\n", bike_brand);
        return;
    }
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        *head = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    } else {
        *tail = temp->prev;
    }
    free(temp);
    printf("Product %s deleted\n", bike_brand);
}

// Function to edit a product
void editProduct(Product* head, char bike_brand[], char new_manufacturer[], char new_bike_brand[], int new_quantity, char new_delivery_date[], float new_unit_price, int new_sold_quantity) {
    Product* temp = head;
    while (temp != NULL && strcmp(temp->bike_brand, bike_brand) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Product with bike brand %s not found\n", bike_brand);
        return;
    }
    strcpy(temp->manufacturer, new_manufacturer);
    strcpy(temp->bike_brand, new_bike_brand);
    temp->quantity = new_quantity;
    strcpy(temp->delivery_date, new_delivery_date);
    temp->unit_price = new_unit_price;
    temp->sold_quantity = new_sold_quantity;
    printf("Product %s updated\n", bike_brand);
}

// Function to search for products by manufacturer
void searchByManufacturer(Product* head, char manufacturer[]) {
    Product* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->manufacturer, manufacturer) == 0) {
            printf("Manufacturer: %s\n", temp->manufacturer);
            printf("Bike Brand: %s\n", temp->bike_brand);
            printf("Quantity: %d\n", temp->quantity);
            printf("Delivery Date: %s\n", temp->delivery_date);
            printf("Unit Price: %.2f\n", temp->unit_price);
            printf("Sold Quantity: %d\n\n", temp->sold_quantity);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found)
        printf("Products by manufacturer %s not found\n", manufacturer);
}

// Function to search for products by delivery date
void searchByDate(Product* head, char delivery_date[]) {
    Product* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->delivery_date, delivery_date) == 0) {
            printf("Manufacturer: %s\n", temp->manufacturer);
            printf("Bike Brand: %s\n", temp->bike_brand);
            printf("Quantity: %d\n", temp->quantity);
            printf("Delivery Date: %s\n", temp->delivery_date);
            printf("Unit Price: %.2f\n", temp->unit_price);
            printf("Sold Quantity: %d\n\n", temp->sold_quantity);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found)
        printf("Products with delivery date %s not found\n", delivery_date);
}

// Function to search for a product by bike brand
void searchByBikeBrand(Product* head, char bike_brand[]) {
    Product* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->bike_brand, bike_brand) == 0) {
            printf("Manufacturer: %s\n", temp->manufacturer);
            printf("Bike Brand: %s\n", temp->bike_brand);
            printf("Quantity: %d\n", temp->quantity);
            printf("Delivery Date: %s\n", temp->delivery_date);
            printf("Unit Price: %.2f\n", temp->unit_price);
            printf("Sold Quantity: %d\n\n", temp->sold_quantity);
            return;
        }
        temp = temp->next;
    }
    printf("Product with bike brand %s not found\n", bike_brand);
}

// Function to print available products
void printAvailableProducts(Product* head) {
    Product* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (temp->quantity > 0) {
            printf("Manufacturer: %s\n", temp->manufacturer);
            printf("Bike Brand: %s\n", temp->bike_brand);
            printf("Quantity: %d\n", temp->quantity);
            printf("Delivery Date: %s\n", temp->delivery_date);
            printf("Unit Price: %.2f\n", temp->unit_price);
            printf("Sold Quantity: %d\n\n", temp->sold_quantity);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found)
        printf("No products available\n");
}

// Function to calculate total cost by manufacturer
float calculateTotalCostByManufacturer(Product* head, char manufacturer[]) {
    Product* temp = head;
    float total = 0.0;
    while (temp != NULL) {
        if (strcmp(temp->manufacturer, manufacturer) == 0) {
            total += temp->unit_price * temp->quantity;
        }
        temp = temp->next;
    }
    return total;
}

// Function to calculate total cost of sold products
float calculateTotalSoldCost(Product* head) {
    Product* temp = head;
    float total = 0.0;
    while (temp != NULL) {
        total += temp->unit_price * temp->sold_quantity;
        temp = temp->next;
    }
    return total;
}

// Function to swap two nodes
void swapNodes(Product* a, Product* b) {
    Product temp = *a;

    // Copy data from b to a
    strcpy(a->manufacturer, b->manufacturer);
    strcpy(a->bike_brand, b->bike_brand);
    a->quantity = b->quantity;
    strcpy(a->delivery_date, b->delivery_date);
    a->unit_price = b->unit_price;
    a->sold_quantity = b->sold_quantity;

    // Copy data from temp (original a) to b
    strcpy(b->manufacturer, temp.manufacturer);
    strcpy(b->bike_brand, temp.bike_brand);
    b->quantity = temp.quantity;
    strcpy(b->delivery_date, temp.delivery_date);
    b->unit_price = temp.unit_price;
    b->sold_quantity = temp.sold_quantity;
}

// Function to sort the deque by price using bubble sort
void sortByPrice(Product** head, Product** tail) {
    if (*head == NULL || (*head)->next == NULL)
        return;

    int swapped;
    Product* ptr1;
    Product* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (ptr1->unit_price > ptr1->next->unit_price) {
                swapNodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Function to display the menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Add Product\n");
    printf("2. Print All Products\n");
    printf("3. Delete Product\n");
    printf("4. Edit Product\n");
    printf("5. List Products by Manufacturer\n");
    printf("6. List Products by Delivery Date\n");
    printf("7. Full Information of Product by Bike Brand\n");
    printf("8. Calculate Total Cost by Manufacturer\n");
    printf("9. Calculate Total Cost of Sold Products\n");
    printf("10. List Available Products\n");
    printf("11. Sort by Price\n");
    printf("12. Exit\n");
    printf("Select an action: ");
}

// Main function
int main() {
    Product* head = NULL;
    Product* tail = NULL;
    int choice;
    char manufacturer[100], bike_brand[100], delivery_date[20];
    int quantity, sold_quantity;
    float unit_price;
    char search_bike_brand[100];
    char search_manufacturer[100];
    char search_date[20];
    int new_quantity, new_sold_quantity;
    float new_unit_price;
    char new_manufacturer[100], new_bike_brand[100], new_delivery_date[20];

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        while (getchar() != '\n'); // Clear input buffer

        switch (choice) {
            case 1:
                printf("Enter manufacturer: ");
                fgets(manufacturer, sizeof(manufacturer), stdin);
                manufacturer[strcspn(manufacturer, "\n")] = '\0';
                
                printf("Enter bike brand: ");
                fgets(bike_brand, sizeof(bike_brand), stdin);
                bike_brand[strcspn(bike_brand, "\n")] = '\0';
                
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                
                while (getchar() != '\n'); // Clear input buffer
                
                printf("Enter delivery date: ");
                fgets(delivery_date, sizeof(delivery_date), stdin);
                delivery_date[strcspn(delivery_date, "\n")] = '\0';
                
                printf("Enter unit price: ");
                scanf("%f", &unit_price);
                
                printf("Enter sold quantity: ");
                scanf("%d", &sold_quantity);
                
                addToTail(&head, &tail, manufacturer, bike_brand, quantity, delivery_date, unit_price, sold_quantity);
                break;
                
            case 2:
                printProducts(head);
                break;
                
            case 3:
                printf("Enter bike brand to delete: ");
                fgets(bike_brand, sizeof(bike_brand), stdin);
                bike_brand[strcspn(bike_brand, "\n")] = '\0';
                deleteByBikeBrand(&head, &tail, bike_brand);
                break;
                
            case 4:
                printf("Enter bike brand to edit: ");
                fgets(bike_brand, sizeof(bike_brand), stdin);
                bike_brand[strcspn(bike_brand, "\n")] = '\0';
                
                printf("Enter new manufacturer: ");
                fgets(new_manufacturer, sizeof(new_manufacturer), stdin);
                new_manufacturer[strcspn(new_manufacturer, "\n")] = '\0';
                
                printf("Enter new bike brand: ");
                fgets(new_bike_brand, sizeof(new_bike_brand), stdin);
                new_bike_brand[strcspn(new_bike_brand, "\n")] = '\0';
                
                printf("Enter new quantity: ");
                scanf("%d", &new_quantity);
                
                while (getchar() != '\n');
                
                printf("Enter new delivery date: ");
                fgets(new_delivery_date, sizeof(new_delivery_date), stdin);
                new_delivery_date[strcspn(new_delivery_date, "\n")] = '\0';
                
                printf("Enter new unit price: ");
                scanf("%f", &new_unit_price);
                
                printf("Enter new sold quantity: ");
                scanf("%d", &new_sold_quantity);
                
                editProduct(head, bike_brand, new_manufacturer, new_bike_brand, new_quantity, new_delivery_date, new_unit_price, new_sold_quantity);
                break;
                
            case 5:
                printf("Enter manufacturer to search: ");
                fgets(search_manufacturer, sizeof(search_manufacturer), stdin);
                search_manufacturer[strcspn(search_manufacturer, "\n")] = '\0';
                searchByManufacturer(head, search_manufacturer);
                break;
                
            case 6:
                printf("Enter delivery date to search: ");
                fgets(search_date, sizeof(search_date), stdin);
                search_date[strcspn(search_date, "\n")] = '\0';
                searchByDate(head, search_date);
                break;
                
            case 7:
                printf("Enter bike brand to search: ");
                fgets(search_bike_brand, sizeof(search_bike_brand), stdin);
                search_bike_brand[strcspn(search_bike_brand, "\n")] = '\0';
                searchByBikeBrand(head, search_bike_brand);
                break;
                
            case 8:
                printf("Enter manufacturer to calculate total cost: ");
                fgets(search_manufacturer, sizeof(search_manufacturer), stdin);
                search_manufacturer[strcspn(search_manufacturer, "\n")] = '\0';
                printf("Total cost of products by manufacturer %s: %.2f\n", 
                      search_manufacturer, calculateTotalCostByManufacturer(head, search_manufacturer));
                break;
                
            case 9:
                printf("Total cost of sold products: %.2f\n", calculateTotalSoldCost(head));
                break;
                
            case 10:
                printAvailableProducts(head);
                break;
                
            case 11:
                sortByPrice(&head, &tail);
                printf("Product list sorted by price\n");
                break;
                
            case 12:
                freeProducts(head);
                printf("Program terminated\n");
                return 0;
                
            default:
                printf("Invalid choice\n");
        }
    }
}
