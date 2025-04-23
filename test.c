#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для товару веломагазину
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

// Прототипы функций
void freeProducts(Product* head);
void displayMenu();
Product* createProduct(char manufacturer[], char bike_brand[], int quantity, char delivery_date[], float unit_price, int sold_quantity);
void addProduct(Product** head, Product** tail, char manufacturer[], char bike_brand[], int quantity, char delivery_date[], float unit_price, int sold_quantity);
void printProducts(Product* head);
void deleteProduct(Product** head, char bike_brand[]);
void editProduct(Product* head, char bike_brand[], char new_manufacturer[], char new_bike_brand[], int new_quantity, char new_delivery_date[],
float new_unit_price, int new_sold_quantity);
void searchByManufacturer(Product* head, char manufacturer[]);
void searchByDate(Product* head, char delivery_date[]);
void searchByBikeBrand(Product* head, char bike_brand[]);
void printAvailableProducts(Product* head);
float calculateTotalCostByManufacturer(Product* head, char manufacturer[]);   
float calculateTotalSoldCost(Product* head);
void sortByPrice(Product** head);
void swapNodes(Product* a, Product* b);
// 
// Функция для создания нового товара
Product* createProduct(char manufacturer[], char bike_brand[], int quantity, char delivery_date[], float unit_price, int sold_quantity) {
    Product* newProduct = (Product*)malloc(sizeof(Product));
    if (!newProduct) {
        printf("Ошибка выделения памяти\n");
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

// Функция для добавления товара в конец списка
void addProduct(Product** head, Product** tail, char manufacturer[], char bike_brand[], int quantity, char delivery_date[], float unit_price, int sold_quantity) {
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

// Функция для вывода всех товаров
void printProducts(Product* head) {
    if (head == NULL) {
        printf("Список товаров пуст\n");
        return;
    }
    Product* temp = head;
    while (temp != NULL) {
        printf("Производитель: %s\n", temp->manufacturer);
        printf("Марка велосипеда: %s\n", temp->bike_brand);
        printf("Количество: %d\n", temp->quantity);
        printf("Дата поставки: %s\n", temp->delivery_date);
        printf("Цена за единицу: %.2f\n", temp->unit_price);
        printf("Количество проданного товара: %d\n\n", temp->sold_quantity);
        temp = temp->next;
    }
}

// Функция для удаления товара по марке велосипеда
void deleteProduct(Product** head, char bike_brand[]) {
    Product* temp = *head;
    while (temp != NULL && strcmp(temp->bike_brand, bike_brand) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Товар с маркой %s не найден\n", bike_brand);
        return;
    }
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        *head = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
    printf("Товар %s удален\n", bike_brand);
}

// Функция для редактирования данных товара
void editProduct(Product* head, char bike_brand[], char new_manufacturer[], char new_bike_brand[], int new_quantity, char new_delivery_date[], float new_unit_price, int new_sold_quantity) {
    Product* temp = head;
    while (temp != NULL && strcmp(temp->bike_brand, bike_brand) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Товар с маркой %s не найден\n", bike_brand);
        return;
    }
    
    strcpy(temp->manufacturer, new_manufacturer);
    strcpy(temp->bike_brand, new_bike_brand);
    temp->quantity = new_quantity;
    strcpy(temp->delivery_date, new_delivery_date);
    temp->unit_price = new_unit_price;
    temp->sold_quantity = new_sold_quantity;
    printf("Данные товара %s обновлены\n", bike_brand);
}

// Функция для поиска товаров по производителю
void searchByManufacturer(Product* head, char manufacturer[]) {
    Product* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->manufacturer, manufacturer) == 0) {
            printf("Производитель: %s\n", temp->manufacturer);
            printf("Марка велосипеда: %s\n", temp->bike_brand);
            printf("Количество: %d\n", temp->quantity);
            printf("Дата поставки: %s\n", temp->delivery_date);
            printf("Цена за единицу: %.2f\n", temp->unit_price);
            printf("Количество проданного товара: %d\n\n", temp->sold_quantity);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found)
        printf("Товары производителя %s не найдены\n", manufacturer);
}

// Функция для поиска товаров по дате поставки
void searchByDate(Product* head, char delivery_date[]) {
    Product* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->delivery_date, delivery_date) == 0) {
            printf("Производитель: %s\n", temp->manufacturer);
            printf("Марка велосипеда: %s\n", temp->bike_brand);
            printf("Количество: %d\n", temp->quantity);
            printf("Дата поставки: %s\n", temp->delivery_date);
            printf("Цена за единицу: %.2f\n", temp->unit_price);
            printf("Количество проданного товара: %d\n\n", temp->sold_quantity);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found)
        printf("Товары с датой поставки %s не найдены\n", delivery_date);
}

// Функция для поиска товара по марке велосипеда
void searchByBikeBrand(Product* head, char bike_brand[]) {
    Product* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->bike_brand, bike_brand) == 0) {
            printf("Производитель: %s\n", temp->manufacturer);
            printf("Марка велосипеда: %s\n", temp->bike_brand);
            printf("Количество: %d\n", temp->quantity);
            printf("Дата поставки: %s\n", temp->delivery_date);
            printf("Цена за единицу: %.2f\n", temp->unit_price);
            printf("Количество проданного товара: %d\n\n", temp->sold_quantity);
            return;
        }
        temp = temp->next;
    }
    printf("Товар с маркой %s не найден\n", bike_brand);
}

// Функция для вывода товаров, которые есть в наличии
void printAvailableProducts(Product* head) {
    Product* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (temp->quantity > 0) {
            printf("Производитель: %s\n", temp->manufacturer);
            printf("Марка велосипеда: %s\n", temp->bike_brand);
            printf("Количество: %d\n", temp->quantity);
            printf("Дата поставки: %s\n", temp->delivery_date);
            printf("Цена за единицу: %.2f\n", temp->unit_price);
            printf("Количество проданного товара: %d\n\n", temp->sold_quantity);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found)
        printf("Нет товаров в наличии\n");
}

// Функция для подсчета общей стоимости товаров заданного производителя
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

// Функция для подсчета общей стоимости проданных товаров
float calculateTotalSoldCost(Product* head) {
    Product* temp = head;
    float total = 0.0;
    while (temp != NULL) {
        total += temp->unit_price * temp->sold_quantity;
        temp = temp->next;
    }
    return total;
}

// Функция для обмена двух узлов
void swapNodes(Product* a, Product* b) {
    Product temp = *a;
    
    // Копируем данные из b в a
    strcpy(a->manufacturer, b->manufacturer);
    strcpy(a->bike_brand, b->bike_brand);
    a->quantity = b->quantity;
    strcpy(a->delivery_date, b->delivery_date);
    a->unit_price = b->unit_price;
    a->sold_quantity = b->sold_quantity;
    
    // Копируем данные из temp (исходный a) в b
    strcpy(b->manufacturer, temp.manufacturer);
    strcpy(b->bike_brand, temp.bike_brand);
    b->quantity = temp.quantity;
    strcpy(b->delivery_date, temp.delivery_date);
    b->unit_price = temp.unit_price;
    b->sold_quantity = temp.sold_quantity;
}

// Функция для сортировки списка по цене (пузырьковая сортировка)
void sortByPrice(Product** head) {
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

// Функция для освобождения памяти
void freeProducts(Product* head) {
    Product* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Функция для отображения меню
void displayMenu() {
    printf("\nМеню:\n");
    printf("1. Добавить товар\n");
    printf("2. Вывести все товары\n");
    printf("3. Удалить товар\n");
    printf("4. Редактировать данные товара\n");
    printf("5. Сформировать список товаров заданного производителя\n");
    printf("6. Вывести список товаров, которые поступили в заданный день\n");
    printf("7. Вывести полную информацию о товаре по введенной марке велосипеда\n");
    printf("8. Подсчитать общую стоимость товаров заданного производителя\n");
    printf("9. Подсчитать общую стоимость проданных товаров\n");
    printf("10. Сформировать список товаров, которые есть в наличии в магазине\n");
    printf("11. Сортировать по цене\n");
    printf("12. Выход\n");
    printf("Выберите действие: ");
}

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
        while (getchar() != '\n'); // Очистка буфера ввода

        switch (choice) {
            case 1:
                printf("Введите производителя: ");
                fgets(manufacturer, sizeof(manufacturer), stdin);
                manufacturer[strcspn(manufacturer, "\n")] = '\0';
                
                printf("Введите марку велосипеда: ");
                fgets(bike_brand, sizeof(bike_brand), stdin);
                bike_brand[strcspn(bike_brand, "\n")] = '\0';
                
                printf("Введите количество: ");
                scanf("%d", &quantity);
                
                while (getchar() != '\n'); // Очистка буфера
                
                printf("Введите дату поставки: ");
                fgets(delivery_date, sizeof(delivery_date), stdin);
                delivery_date[strcspn(delivery_date, "\n")] = '\0';
                
                printf("Введите цену за единицу: ");
                scanf("%f", &unit_price);
                
                printf("Введите количество проданного товара: ");
                scanf("%d", &sold_quantity);
                
                addProduct(&head, &tail, manufacturer, bike_brand, quantity, delivery_date, unit_price, sold_quantity);
                break;
                
            case 2:
                printProducts(head);
                break;
                
            case 3:
                printf("Введите марку велосипеда для удаления: ");
                fgets(bike_brand, sizeof(bike_brand), stdin);
                bike_brand[strcspn(bike_brand, "\n")] = '\0';
                deleteProduct(&head, bike_brand);
                break;
                
            case 4:
                printf("Введите марку велосипеда для редактирования: ");
                fgets(bike_brand, sizeof(bike_brand), stdin);
                bike_brand[strcspn(bike_brand, "\n")] = '\0';
                
                printf("Введите нового производителя: ");
                fgets(new_manufacturer, sizeof(new_manufacturer), stdin);
                new_manufacturer[strcspn(new_manufacturer, "\n")] = '\0';
                
                printf("Введите новую марку велосипеда: ");
                fgets(new_bike_brand, sizeof(new_bike_brand), stdin);
                new_bike_brand[strcspn(new_bike_brand, "\n")] = '\0';
                
                printf("Введите новое количество: ");
                scanf("%d", &new_quantity);
                
                while (getchar() != '\n');
                
                printf("Введите новую дату поставки: ");
                fgets(new_delivery_date, sizeof(new_delivery_date), stdin);
                new_delivery_date[strcspn(new_delivery_date, "\n")] = '\0';
                
                printf("Введите новую цену за единицу: ");
                scanf("%f", &new_unit_price);
                
                printf("Введите новое количество проданного товара: ");
                scanf("%d", &new_sold_quantity);
                
                editProduct(head, bike_brand, new_manufacturer, new_bike_brand, new_quantity, new_delivery_date, new_unit_price, new_sold_quantity);
                break;
                
            case 5:
                printf("Введите производителя для поиска: ");
                fgets(search_manufacturer, sizeof(search_manufacturer), stdin);
                search_manufacturer[strcspn(search_manufacturer, "\n")] = '\0';
                searchByManufacturer(head, search_manufacturer);
                break;
                
            case 6:
                printf("Введите дату поставки для поиска: ");
                fgets(search_date, sizeof(search_date), stdin);
                search_date[strcspn(search_date, "\n")] = '\0';
                searchByDate(head, search_date);
                break;
                
            case 7:
                printf("Введите марку велосипеда для поиска: ");
                fgets(search_bike_brand, sizeof(search_bike_brand), stdin);
                search_bike_brand[strcspn(search_bike_brand, "\n")] = '\0';
                searchByBikeBrand(head, search_bike_brand);
                break;
                
            case 8:
                printf("Введите производителя для подсчета стоимости: ");
                fgets(search_manufacturer, sizeof(search_manufacturer), stdin);
                search_manufacturer[strcspn(search_manufacturer, "\n")] = '\0';
                printf("Общая стоимость товаров производителя %s: %.2f\n", 
                      search_manufacturer, calculateTotalCostByManufacturer(head, search_manufacturer));
                break;
                
            case 9:
                printf("Общая стоимость проданных товаров: %.2f\n", calculateTotalSoldCost(head));
                break;
                
            case 10:
                printAvailableProducts(head);
                break;
                
            case 11:
                sortByPrice(&head);
                printf("Список отсортирован по цене\n");
                break;
                
            case 12:
                freeProducts(head);
                printf("Программа завершена\n");
                return 0;
                
            default:
                printf("Неправильный выбор\n");
        }
    }
}