#include <stdio.h>
#include <string.h>

struct Textile {
    int id;                 // Unique ID for each product
    char name[50];
    char type[30];
    int quantity;
    float costPrice;
    float sellPrice;
};

void addItem(struct Textile items[], int *n);
void displayItems(struct Textile items[], int n);
void searchItem(struct Textile items[], int n);
void updateItem(struct Textile items[], int n);
void deleteItem(struct Textile items[], int *n);
void saveData(struct Textile items[], int n);

int main() {
    struct Textile items[100];
    int n = 0, choice;

    while (1) {
        printf("\n====================================\n");
        printf("     TEXTILE SHOP MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Record\n");
        printf("2. Display Records\n");
        printf("3. Search Record by ID\n");
        printf("4. Update Record\n");
        printf("5. Delete Record\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1: addItem(items, &n); break;
            case 2: displayItems(items, n); break;
            case 3: searchItem(items, n); break;
            case 4: updateItem(items, n); break;
            case 5: deleteItem(items, &n); break;
            case 6:
                saveData(items, n);
                printf("\n? Data saved successfully! Exiting...\n");
                return 0;
            default:
                printf("\n? Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// -----------------------------------------------------

void addItem(struct Textile items[], int *n) {
    items[*n].id = *n + 1; // auto assign ID

    printf("\nEnter Item Name: ");
    fgets(items[*n].name, 50, stdin);
    items[*n].name[strcspn(items[*n].name, "\n")] = 0;

    printf("Enter Type (Cotton/Silk/Polyester): ");
    fgets(items[*n].type, 30, stdin);
    items[*n].type[strcspn(items[*n].type, "\n")] = 0;

    printf("Enter Quantity: ");
    scanf("%d", &items[*n].quantity);

    printf("Enter Cost Price per unit: ");
    scanf("%f", &items[*n].costPrice);

    printf("Enter Selling Price per unit: ");
    scanf("%f", &items[*n].sellPrice);
    getchar();

    (*n)++;
    printf("\n? Record added successfully! (ID = %d)\n", items[*n - 1].id);
}

// -----------------------------------------------------

void displayItems(struct Textile items[], int n) {
    if (n == 0) {
        printf("\nNo records to display!\n");
        return;
    }

    printf("\n------ Textile Records ------\n");
    printf("%-5s %-20s %-15s %-10s %-10s %-10s\n",
           "ID", "Name", "Type", "Qty", "Cost", "Sell");
    printf("---------------------------------------------------------------\n");
    int i;
    for ( i = 0; i < n; i++) {
        printf("%-5d %-20s %-15s %-10d %-10.2f %-10.2f\n",
               items[i].id, items[i].name, items[i].type,
               items[i].quantity, items[i].costPrice, items[i].sellPrice);
    }
}

// -----------------------------------------------------

void searchItem(struct Textile items[], int n) {
    if (n == 0) {
        printf("\nNo records available!\n");
        return;
    }

    int id;
    printf("\nEnter ID to search: ");
    scanf("%d", &id);
    getchar();
	int i;
    for (i = 0; i < n; i++) {
        if (items[i].id == id) {
            printf("\nRecord Found:\n");
            printf("ID: %d\nName: %s\nType: %s\nQuantity: %d\nCost: %.2f\nSell: %.2f\n",
                   items[i].id, items[i].name, items[i].type,
                   items[i].quantity, items[i].costPrice, items[i].sellPrice);
            return;
        }
    }
    printf("\n? Record with ID %d not found!\n", id);
}

// -----------------------------------------------------

void updateItem(struct Textile items[], int n) {
    if (n == 0) {
        printf("\nNo records to update!\n");
        return;
    }

    int id;
    printf("\nEnter ID to update: ");
    scanf("%d", &id);
    getchar();
	int i;
    for (i = 0; i < n; i++) {
        if (items[i].id == id) {
            printf("\nEditing Record ID %d\n", id);

            printf("Enter New Name: ");
            fgets(items[i].name, 50, stdin);
            items[i].name[strcspn(items[i].name, "\n")] = 0;

            printf("Enter New Type: ");
            fgets(items[i].type, 30, stdin);
            items[i].type[strcspn(items[i].type, "\n")] = 0;

            printf("Enter New Quantity: ");
            scanf("%d", &items[i].quantity);

            printf("Enter New Cost Price: ");
            scanf("%f", &items[i].costPrice);

            printf("Enter New Selling Price: ");
            scanf("%f", &items[i].sellPrice);
            getchar();

            printf("\n? Record updated successfully!\n");
            return;
        }
    }
    printf("\n? Record with ID %d not found!\n", id);
}

// -----------------------------------------------------

void deleteItem(struct Textile items[], int *n) {
    if (*n == 0) {
        printf("\nNo records to delete!\n");
        return;
    }

    int id, found = 0;
    printf("\nEnter ID to delete: ");
    scanf("%d", &id);
    getchar();
	int i;
    for (i = 0; i < *n; i++) {
        if (items[i].id == id) {
        	int j;
            for (j = i; j < *n - 1; j++) {
                items[j] = items[j + 1];
                items[j].id = j + 1; // reassign IDs
            }
            (*n)--;
            found = 1;
            printf("\n? Record deleted successfully!\n");
            break;
        }
    }
    if (!found)
        printf("\n? Record with ID %d not found!\n", id);
}

// -----------------------------------------------------

void saveData(struct Textile items[], int n) {
    FILE *fp = fopen("textile_data.txt", "w");
    if (fp == NULL) {
        printf("Error saving data!\n");
        return;
    }

    fprintf(fp, "ID\tName\tType\tQuantity\tCost\tSell\n");
    int i;
    for (i = 0; i < n; i++) {
        fprintf(fp, "%d\t%s\t%s\t%d\t%.2f\t%.2f\n",
                items[i].id, items[i].name, items[i].type,
                items[i].quantity, items[i].costPrice, items[i].sellPrice);
    }

    fclose(fp);
}
