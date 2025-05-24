#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для продукту у веломагазині
typedef struct Product {
    char manufacturer[100];
    char bike_brand[100];
    int quantity;
    char delivery_date[20]; // Формат РРРР-ММ-ДД
    float unit_price;
    int sold_quantity;
    struct Product* prev;
    struct Product* next;
} Product;

// --- Прототипи функцій ---
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
void saveToFile(Product* head, const char* filename);
void loadFromFile(Product** head, Product** tail, const char* filename);


// --- Функція для створення нового продукту ---
Product* createProduct(char manufacturer[], char bike_brand[], int quantity, char delivery_date[], float unit_price, int sold_quantity) {
    Product* newProduct = (Product*)malloc(sizeof(Product));
    if (!newProduct) {
        printf("Помилка виділення пам'яті!\n");
        exit(1); // Аварійне завершення програми у випадку критичної помилки
    }
    // Перевірка коректності введених даних
    if (quantity < 0 || unit_price < 0 || sold_quantity < 0) {
        printf("Помилка: Кількість, ціна або продана кількість не можуть бути від'ємними. Продукт не буде створено.\n");
        free(newProduct); // Звільняємо виділену пам'ять
        return NULL; // Повертаємо NULL, щоб вказати на помилку
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

// --- Функція для додавання продукту на початок дека ---
void addToHead(Product** head, Product** tail, char manufacturer[], char bike_brand[], int quantity, char delivery_date[], float unit_price, int sold_quantity) {
    Product* newProduct = createProduct(manufacturer, bike_brand, quantity, delivery_date, unit_price, sold_quantity);
    if (newProduct == NULL) { // Перевірка, чи створення продукту було успішним
        return;
    }

    if (*head == NULL) {
        *head = newProduct;
        *tail = newProduct;
    } else {
        newProduct->next = *head;
        (*head)->prev = newProduct;
        *head = newProduct;
    }
    printf("Продукт '%s' успішно додано до початку списку.\n", bike_brand);
}

// --- Функція для додавання продукту в кінець дека ---
void addToTail(Product** head, Product** tail, char manufacturer[], char bike_brand[], int quantity, char delivery_date[], float unit_price, int sold_quantity) {
    Product* newProduct = createProduct(manufacturer, bike_brand, quantity, delivery_date, unit_price, sold_quantity);
    if (newProduct == NULL) { // Перевірка, чи створення продукту було успішним
        return;
    }

    if (*head == NULL) {
        *head = newProduct;
        *tail = newProduct;
    } else {
        (*tail)->next = newProduct;
        newProduct->prev = *tail;
        *tail = newProduct;
    }
    printf("Продукт '%s' успішно додано до кінця списку.\n", bike_brand);
}

// --- Функція для виведення всіх продуктів ---
void printProducts(Product* head) {
    if (head == NULL) {
        printf("Список продуктів порожній.\n");
        return;
    }
    printf("\n--- Всі продукти в магазині ---\n");
    Product* temp = head;
    int i = 1;
    while (temp != NULL) {
        printf("Продукт %d:\n", i++);
        printf("  Виробник: %s\n", temp->manufacturer);
        printf("  Бренд велосипеда: %s\n", temp->bike_brand);
        printf("  Кількість: %d\n", temp->quantity);
        printf("  Дата доставки: %s\n", temp->delivery_date);
        printf("  Ціна за одиницю: %.2f грн\n", temp->unit_price);
        printf("  Продана кількість: %d\n\n", temp->sold_quantity);
        temp = temp->next;
    }
    printf("-------------------------------\n");
}

// --- Функція для видалення продукту з початку дека ---
void deleteFromHead(Product** head, Product** tail) {
    if (*head == NULL) {
        printf("Список продуктів порожній. Нічого видаляти.\n");
        return;
    }
    Product* temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    } else {
        *tail = NULL; // Список став порожнім
    }
    free(temp);
    printf("Продукт з початку списку успішно видалено.\n");
}

// --- Функція для видалення продукту з кінця дека ---
void deleteFromTail(Product** head, Product** tail) {
    if (*head == NULL) {
        printf("Список продуктів порожній. Нічого видаляти.\n");
        return;
    }
    Product* temp = *tail;
    *tail = (*tail)->prev;
    if (*tail != NULL) {
        (*tail)->next = NULL;
    } else {
        *head = NULL; // Список став порожнім
    }
    free(temp);
    printf("Продукт з кінця списку успішно видалено.\n");
}

// --- Функція для видалення продукту за брендом велосипеда ---
void deleteByBikeBrand(Product** head, Product** tail, char bike_brand[]) {
    Product* temp = *head;
    // Обробка порожнього списку
    if (temp == NULL) {
        printf("Список продуктів порожній. Нічого видаляти.\n");
        return;
    }

    // Пошук продукту за брендом
    while (temp != NULL && strcmp(temp->bike_brand, bike_brand) != 0) {
        temp = temp->next;
    }

    // Якщо продукт не знайдено
    if (temp == NULL) {
        printf("Продукт з брендом велосипеда '%s' не знайдено для видалення.\n", bike_brand);
        return;
    }

    // Підтвердження видалення
    char confirm;
    printf("Ви дійсно хочете видалити продукт '%s'? (y/n): ", bike_brand);
    scanf(" %c", &confirm); // Пробіл перед %c для пропуску символів нового рядка
    while (getchar() != '\n'); // Очистити буфер вводу

    if (confirm != 'y' && confirm != 'Y') {
        printf("Видалення скасовано.\n");
        return;
    }

    // Зміна голови, якщо видаляється перший вузол
    if (temp->prev == NULL) { // Якщо це голова
        *head = temp->next;
    } else {
        temp->prev->next = temp->next;
    }

    // Зміна хвоста, якщо видаляється останній вузол
    if (temp->next == NULL) { // Якщо це хвіст
        *tail = temp->prev;
    } else {
        temp->next->prev = temp->prev;
    }

    free(temp);
    printf("Продукт '%s' успішно видалено.\n", bike_brand);
}

// --- Функція для редагування продукту ---
void editProduct(Product* head, char bike_brand[], char new_manufacturer[], char new_bike_brand[], int new_quantity, char new_delivery_date[], float new_unit_price, int new_sold_quantity) {
    Product* temp = head;
    while (temp != NULL && strcmp(temp->bike_brand, bike_brand) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Продукт з брендом велосипеда '%s' не знайдено для редагування.\n", bike_brand);
        return;
    }

    // Перевірка коректності нових даних
    if (new_quantity < 0 || new_unit_price < 0 || new_sold_quantity < 0) {
        printf("Помилка: Нова кількість, ціна або продана кількість не можуть бути від'ємними. Редагування скасовано.\n");
        return;
    }

    strcpy(temp->manufacturer, new_manufacturer);
    strcpy(temp->bike_brand, new_bike_brand);
    temp->quantity = new_quantity;
    strcpy(temp->delivery_date, new_delivery_date);
    temp->unit_price = new_unit_price;
    temp->sold_quantity = new_sold_quantity;
    printf("Продукт '%s' успішно оновлено.\n", bike_brand);
}

// --- Функція для пошуку продуктів за виробником ---
void searchByManufacturer(Product* head, char manufacturer[]) {
    if (head == NULL) {
        printf("Список продуктів порожній. Пошук неможливий.\n");
        return;
    }
    Product* temp = head;
    int found = 0;
    printf("\n--- Результати пошуку за виробником '%s' ---\n", manufacturer);
    while (temp != NULL) {
        if (strcmp(temp->manufacturer, manufacturer) == 0) {
            printf("  Виробник: %s\n", temp->manufacturer);
            printf("  Бренд велосипеда: %s\n", temp->bike_brand);
            printf("  Кількість: %d\n", temp->quantity);
            printf("  Дата доставки: %s\n", temp->delivery_date);
            printf("  Ціна за одиницю: %.2f грн\n", temp->unit_price);
            printf("  Продана кількість: %d\n\n", temp->sold_quantity);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found)
        printf("Продукти від виробника '%s' не знайдено.\n", manufacturer);
    printf("------------------------------------------\n");
}

// --- Функція для пошуку продуктів за датою доставки ---
void searchByDate(Product* head, char delivery_date[]) {
    if (head == NULL) {
        printf("Список продуктів порожній. Пошук неможливий.\n");
        return;
    }
    Product* temp = head;
    int found = 0;
    printf("\n--- Результати пошуку за датою доставки '%s' ---\n", delivery_date);
    while (temp != NULL) {
        if (strcmp(temp->delivery_date, delivery_date) == 0) {
            printf("  Виробник: %s\n", temp->manufacturer);
            printf("  Бренд велосипеда: %s\n", temp->bike_brand);
            printf("  Кількість: %d\n", temp->quantity);
            printf("  Дата доставки: %s\n", temp->delivery_date);
            printf("  Ціна за одиницю: %.2f грн\n", temp->unit_price);
            printf("  Продана кількість: %d\n\n", temp->sold_quantity);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found)
        printf("Продукти з датою доставки '%s' не знайдено.\n", delivery_date);
    printf("---------------------------------------------\n");
}

// --- Функція для пошуку повної інформації про продукт за брендом велосипеда ---
void searchByBikeBrand(Product* head, char bike_brand[]) {
    if (head == NULL) {
        printf("Список продуктів порожній. Пошук неможливий.\n");
        return;
    }
    Product* temp = head;
    printf("\n--- Повна інформація про продукт '%s' ---\n", bike_brand);
    while (temp != NULL) {
        if (strcmp(temp->bike_brand, bike_brand) == 0) {
            printf("  Виробник: %s\n", temp->manufacturer);
            printf("  Бренд велосипеда: %s\n", temp->bike_brand);
            printf("  Кількість: %d\n", temp->quantity);
            printf("  Дата доставки: %s\n", temp->delivery_date);
            printf("  Ціна за одиницю: %.2f грн\n", temp->unit_price);
            printf("  Продана кількість: %d\n\n", temp->sold_quantity);
            printf("-----------------------------------------\n");
            return;
        }
        temp = temp->next;
    }
    printf("Продукт з брендом велосипеда '%s' не знайдено.\n", bike_brand);
    printf("-----------------------------------------\n");
}

// --- Функція для виведення доступних продуктів ---
void printAvailableProducts(Product* head) {
    if (head == NULL) {
        printf("Список продуктів порожній. Немає доступних продуктів.\n");
        return;
    }
    Product* temp = head;
    int found = 0;
    printf("\n--- Доступні продукти в магазині ---\n");
    while (temp != NULL) {
        if (temp->quantity > 0) {
            printf("  Виробник: %s\n", temp->manufacturer);
            printf("  Бренд велосипеда: %s\n", temp->bike_brand);
            printf("  Кількість: %d\n", temp->quantity);
            printf("  Дата доставки: %s\n", temp->delivery_date);
            printf("  Ціна за одиницю: %.2f грн\n", temp->unit_price);
            printf("  Продана кількість: %d\n\n", temp->sold_quantity);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found)
        printf("Наразі немає доступних продуктів.\n");
    printf("------------------------------------\n");
}

// --- Функція для розрахунку загальної вартості за виробником ---
float calculateTotalCostByManufacturer(Product* head, char manufacturer[]) {
    if (head == NULL) {
        return -1.0; // Порожній список, повертаємо спеціальне значення
    }
    Product* temp = head;
    float total = 0.0;
    int found_manufacturer = 0; // Прапорець для перевірки, чи знайдено хоча б один продукт цього виробника
    while (temp != NULL) {
        if (strcmp(temp->manufacturer, manufacturer) == 0) {
            total += temp->unit_price * temp->quantity;
            found_manufacturer = 1;
        }
        temp = temp->next;
    }
    return found_manufacturer ? total : -1.0; // Повертаємо -1.0, якщо виробника не знайдено
}

// --- Функція для розрахунку загальної вартості проданих продуктів ---
float calculateTotalSoldCost(Product* head) {
    if (head == NULL) {
        return 0.0; // Порожній список
    }
    Product* temp = head;
    float total = 0.0;
    while (temp != NULL) {
        total += temp->unit_price * temp->sold_quantity;
        temp = temp->next;
    }
    return total;
}

// --- Функція для обміну даними двох вузлів (для сортування) ---
void swapNodes(Product* a, Product* b) {
    // Створюємо тимчасову структуру для зберігання даних вузла 'a'
    Product temp_data;

    // Копіюємо дані з 'a' до temp_data
    strcpy(temp_data.manufacturer, a->manufacturer);
    strcpy(temp_data.bike_brand, a->bike_brand);
    temp_data.quantity = a->quantity;
    strcpy(temp_data.delivery_date, a->delivery_date);
    temp_data.unit_price = a->unit_price;
    temp_data.sold_quantity = a->sold_quantity;

    // Копіюємо дані з 'b' до 'a'
    strcpy(a->manufacturer, b->manufacturer);
    strcpy(a->bike_brand, b->bike_brand);
    a->quantity = b->quantity;
    strcpy(a->delivery_date, b->delivery_date);
    a->unit_price = b->unit_price;
    a->sold_quantity = b->sold_quantity;

    // Копіюємо дані з temp_data (оригінальні дані 'a') до 'b'
    strcpy(b->manufacturer, temp_data.manufacturer);
    strcpy(b->bike_brand, temp_data.bike_brand);
    b->quantity = temp_data.quantity;
    strcpy(b->delivery_date, temp_data.delivery_date);
    b->unit_price = temp_data.unit_price;
    b->sold_quantity = temp_data.sold_quantity;
}

// --- Функція для сортування дека за ціною за допомогою бульбашкового сортування ---
void sortByPrice(Product** head, Product** tail) {
    if (*head == NULL || (*head)->next == NULL) {
        printf("Список занадто короткий для сортування або порожній.\n");
        return;
    }

    int swapped;
    Product* ptr1;
    Product* lptr = NULL; // Вказівник на останній елемент, який вже знаходиться на своєму місці

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (ptr1->unit_price > ptr1->next->unit_price) {
                // Якщо ціна поточного вузла більша за ціну наступного вузла, обміняйте їхні дані
                swapNodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1; // Після одного проходу останній елемент знаходиться на своєму правильному місці
    } while (swapped);
    printf("Список продуктів успішно відсортовано за ціною (за зростанням).\n");
}

// --- Функція для звільнення всієї виділеної пам'яті для списку продуктів ---
void freeProducts(Product* head) {
    Product* current = head;
    Product* next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    printf("Вся виділена пам'ять успішно звільнена.\n");
}

// --- Функція для збереження даних у файл ---
void saveToFile(Product* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Помилка: Не вдалося відкрити файл '%s' для запису.\n", filename);
        return;
    }

    Product* current = head;
    while (current != NULL) {
        fprintf(file, "%s;%s;%d;%s;%.2f;%d\n",
                current->manufacturer,
                current->bike_brand,
                current->quantity,
                current->delivery_date,
                current->unit_price,
                current->sold_quantity);
        current = current->next;
    }

    fclose(file);
    printf("Дані успішно збережено у файл '%s'.\n", filename);
}

// --- Функція для завантаження даних з файлу ---
void loadFromFile(Product** head, Product** tail, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Помилка: Файл '%s' не знайдено або не вдалося відкрити для читання.\n", filename);
        return;
    }

    // Підтвердження очищення поточного списку
    char confirm_clear;
    printf("Завантаження даних очистить поточний список. Продовжити? (y/n): ");
    scanf(" %c", &confirm_clear);
    while (getchar() != '\n'); // Очистити буфер

    if (confirm_clear != 'y' && confirm_clear != 'Y') {
        printf("Завантаження скасовано.\n");
        fclose(file);
        return;
    }

    freeProducts(*head); // Очистити поточний список перед завантаженням
    *head = NULL;
    *tail = NULL;

    char line[500]; // Достатній розмір для рядка даних
    char manufacturer[100], bike_brand[100], delivery_date[20];
    int quantity, sold_quantity;
    float unit_price;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Розбір рядка за допомогою sscanf
        if (sscanf(line, "%99[^;];%99[^;];%d;%19[^;];%f;%d",
                   manufacturer, bike_brand, &quantity, delivery_date, &unit_price, &sold_quantity) == 6) {
            // Перевірка на коректність даних при завантаженні (негативні значення)
            if (quantity >= 0 && unit_price >= 0 && sold_quantity >= 0) {
                // Використовуємо addToTail для додавання елементів з файлу
                // Тут ми не виводимо повідомлення "Продукт додано", щоб не засмічувати вивід при завантаженні великих файлів
                Product* newProduct = createProduct(manufacturer, bike_brand, quantity, delivery_date, unit_price, sold_quantity);
                if (newProduct != NULL) {
                    if (*head == NULL) {
                        *head = newProduct;
                        *tail = newProduct;
                    } else {
                        (*tail)->next = newProduct;
                        newProduct->prev = *tail;
                        *tail = newProduct;
                    }
                }
            } else {
                printf("Помилка: Виявлено некоректні дані (від'ємні значення) у файлі. Пропущено рядок: %s", line);
            }
        } else {
            printf("Помилка: Некоректний формат рядка у файлі. Пропущено: %s", line);
        }
    }

    fclose(file);
    printf("Дані успішно завантажено з файлу '%s'.\n", filename);
}


// --- Функція для відображення меню ---
void displayMenu() {
    printf("\n--- Меню управління веломагазином ---\n");
    printf("1. Додати новий продукт\n");
    printf("2. Переглянути всі продукти\n");
    printf("3. Видалити продукт за брендом велосипеда\n");
    printf("4. Редагувати інформацію про продукт\n");
    printf("5. Знайти продукти за назвою виробника\n");
    printf("6. Знайти продукти за датою доставки\n");
    printf("7. Показати повну інформацію про продукт за брендом велосипеда\n");
    printf("8. Розрахувати загальну вартість товарів заданого виробника\n");
    printf("9. Розрахувати загальну вартість проданих товарів\n");
    printf("10. Переглянути список доступних продуктів\n");
    printf("11. Сортувати продукти за вартістю (ціною)\n");
    printf("12. Зберегти дані в файл\n");
    printf("13. Завантажити дані з файлу\n");
    printf("14. Вихід з програми\n");
    printf("--------------------------------------\n");
    printf("Оберіть дію (введіть номер): ");
}

// --- Головна функція ---
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
    char filename[100]; // Для назви файлу

    printf("Ласкаво просимо до системи управління веломагазином!\n");

    while (1) {
        displayMenu();
        // Перевірка, чи успішно scanf прочитав ціле число
        if (scanf("%d", &choice) != 1) {
            printf("Помилка введення: Будь ласка, введіть числове значення для вибору пункту меню.\n");
            while (getchar() != '\n'); // Очистити невірний ввід з буфера
            continue; // Повернутися до відображення меню
        }
        while (getchar() != '\n'); // Очистити залишок вхідного буфера (символ нового рядка)

        switch (choice) {
            case 1: // Додати продукт
                printf("--- Додавання нового продукту ---\n");
                printf("Введіть виробника: ");
                fgets(manufacturer, sizeof(manufacturer), stdin);
                manufacturer[strcspn(manufacturer, "\n")] = '\0';

                printf("Введіть бренд велосипеда: ");
                fgets(bike_brand, sizeof(bike_brand), stdin);
                bike_brand[strcspn(bike_brand, "\n")] = '\0';

                printf("Введіть кількість: ");
                if (scanf("%d", &quantity) != 1 || quantity < 0) {
                    printf("Помилка введення: Невірна кількість. Будь ласка, введіть невід'ємне ціле число.\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');

                printf("Введіть дату доставки (формат РРРР-ММ-ДД): ");
                fgets(delivery_date, sizeof(delivery_date), stdin);
                delivery_date[strcspn(delivery_date, "\n")] = '\0';

                printf("Введіть ціну за одиницю (грн): ");
                if (scanf("%f", &unit_price) != 1 || unit_price < 0) {
                    printf("Помилка введення: Невірна ціна. Будь ласка, введіть невід'ємне число.\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');

                printf("Введіть продану кількість: ");
                if (scanf("%d", &sold_quantity) != 1 || sold_quantity < 0) {
                    printf("Помилка введення: Невірна продана кількість. Будь ласка, введіть невід'ємне ціле число.\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');

                addToTail(&head, &tail, manufacturer, bike_brand, quantity, delivery_date, unit_price, sold_quantity);
                break;

            case 2: // Вивести всі продукти
                printProducts(head);
                break;

            case 3: // Видалити продукт
                printf("--- Видалення продукту ---\n");
                printf("Введіть бренд велосипеда для видалення: ");
                fgets(bike_brand, sizeof(bike_brand), stdin);
                bike_brand[strcspn(bike_brand, "\n")] = '\0';
                deleteByBikeBrand(&head, &tail, bike_brand);
                break;

            case 4: // Редагувати продукт
                printf("--- Редагування продукту ---\n");
                printf("Введіть бренд велосипеда продукту, який потрібно редагувати: ");
                fgets(bike_brand, sizeof(bike_brand), stdin);
                bike_brand[strcspn(bike_brand, "\n")] = '\0';

                // Перевіряємо, чи існує продукт, перш ніж запитувати нові дані
                Product* product_to_edit = head;
                while (product_to_edit != NULL && strcmp(product_to_edit->bike_brand, bike_brand) != 0) {
                    product_to_edit = product_to_edit->next;
                }
                if (product_to_edit == NULL) {
                    printf("Продукт з брендом велосипеда '%s' не знайдено для редагування.\n", bike_brand);
                    break;
                }

                printf("Введіть нового виробника (залиште пустим, щоб не змінювати: %s): ", product_to_edit->manufacturer);
                fgets(new_manufacturer, sizeof(new_manufacturer), stdin);
                new_manufacturer[strcspn(new_manufacturer, "\n")] = '\0';
                if (strlen(new_manufacturer) == 0) strcpy(new_manufacturer, product_to_edit->manufacturer); // Зберегти старе значення

                printf("Введіть новий бренд велосипеда (залиште пустим, щоб не змінювати: %s): ", product_to_edit->bike_brand);
                fgets(new_bike_brand, sizeof(new_bike_brand), stdin);
                new_bike_brand[strcspn(new_bike_brand, "\n")] = '\0';
                if (strlen(new_bike_brand) == 0) strcpy(new_bike_brand, product_to_edit->bike_brand); // Зберегти старе значення

                printf("Введіть нову кількість (поточна: %d): ", product_to_edit->quantity);
                if (scanf("%d", &new_quantity) != 1 || new_quantity < 0) {
                    printf("Помилка введення: Невірна кількість. Будь ласка, введіть невід'ємне ціле число.\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');

                printf("Введіть нову дату доставки (РРРР-ММ-ДД) (поточна: %s): ", product_to_edit->delivery_date);
                fgets(new_delivery_date, sizeof(new_delivery_date), stdin);
                new_delivery_date[strcspn(new_delivery_date, "\n")] = '\0';
                if (strlen(new_delivery_date) == 0) strcpy(new_delivery_date, product_to_edit->delivery_date); // Зберегти старе значення

                printf("Введіть нову ціну за одиницю (грн) (поточна: %.2f): ", product_to_edit->unit_price);
                if (scanf("%f", &new_unit_price) != 1 || new_unit_price < 0) {
                    printf("Помилка введення: Невірна ціна. Будь ласка, введіть невід'ємне число.\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');

                printf("Введіть нову продану кількість (поточна: %d): ", product_to_edit->sold_quantity);
                if (scanf("%d", &new_sold_quantity) != 1 || new_sold_quantity < 0) {
                    printf("Помилка введення: Невірна продана кількість. Будь ласка, введіть невід'ємне ціле число.\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');

                editProduct(head, bike_brand, new_manufacturer, new_bike_brand, new_quantity, new_delivery_date, new_unit_price, new_sold_quantity);
                break;

            case 5: // Переглянути продукти за виробником
                printf("--- Пошук продуктів за виробником ---\n");
                printf("Введіть назву виробника для пошуку: ");
                fgets(search_manufacturer, sizeof(search_manufacturer), stdin);
                search_manufacturer[strcspn(search_manufacturer, "\n")] = '\0';
                searchByManufacturer(head, search_manufacturer);
                break;

            case 6: // Переглянути продукти за датою доставки
                printf("--- Пошук продуктів за датою доставки ---\n");
                printf("Введіть дату доставки для пошуку (формат РРРР-ММ-ДД): ");
                fgets(search_date, sizeof(search_date), stdin);
                search_date[strcspn(search_date, "\n")] = '\0';
                searchByDate(head, search_date);
                break;

            case 7: // Повна інформація про продукт за брендом велосипеда
                printf("--- Пошук повної інформації про продукт за брендом ---\n");
                printf("Введіть бренд велосипеда для пошуку: ");
                fgets(search_bike_brand, sizeof(search_bike_brand), stdin);
                search_bike_brand[strcspn(search_bike_brand, "\n")] = '\0';
                searchByBikeBrand(head, search_bike_brand);
                break;

            case 8: // Розрахувати загальну вартість за виробником
                printf("--- Розрахунок загальної вартості за виробником ---\n");
                printf("Введіть виробника для розрахунку загальної вартості: ");
                fgets(search_manufacturer, sizeof(search_manufacturer), stdin);
                search_manufacturer[strcspn(search_manufacturer, "\n")] = '\0';
                float total_cost_by_manufacturer = calculateTotalCostByManufacturer(head, search_manufacturer);
                if (total_cost_by_manufacturer == -1.0) { // Перевірка на "не знайдено"
                    printf("Продукти від виробника '%s' не знайдено.\n", search_manufacturer);
                } else {
                    printf("Загальна вартість продуктів від виробника '%s': %.2f грн\n",
                           search_manufacturer, total_cost_by_manufacturer);
                }
                break;

            case 9: // Розрахувати загальну вартість проданих продуктів
                printf("--- Розрахунок загальної вартості проданих продуктів ---\n");
                float total_sold_cost = calculateTotalSoldCost(head);
                if (head == NULL) {
                     printf("Список продуктів порожній. Загальна вартість проданих товарів: 0.00 грн.\n");
                } else {
                     printf("Загальна вартість проданих продуктів: %.2f грн\n", total_sold_cost);
                }
                break;

            case 10: // Переглянути доступні продукти
                printAvailableProducts(head);
                break;

            case 11: // Сортувати за ціною
                sortByPrice(&head, &tail);
                break;

            case 12: // Зберегти дані в файл
                printf("--- Збереження даних у файл ---\n");
                printf("Введіть назву файлу для збереження (наприклад, data.txt): ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                saveToFile(head, filename);
                break;

            case 13: // Завантажити дані з файлу
                printf("--- Завантаження даних з файлу ---\n");
                printf("Введіть назву файлу для завантаження (наприклад, data.txt): ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                loadFromFile(&head, &tail, filename);
                break;

            case 14: // Вихід
                freeProducts(head); // Виклик функції звільнення пам'яті
                printf("Дякуємо за використання програми! Програму завершено.\n");
                return 0;

            default:
                printf("Помилка: Невірний вибір. Будь ласка, введіть число від 1 до 14.\n");
        }
    }
}
