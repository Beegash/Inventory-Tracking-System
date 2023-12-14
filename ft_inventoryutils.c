#include "ft_inventory.h"

void addItem(struct InventoryData *data)
{
    CLEAR_SCREEN();
    printf("\nEnter item details:\n");
    if (data->itemCount >= MAX_ITEMS)
    {
        printf("Error: Maximum number of items exceeded.\n");
        return;
    }
    printf("ID: ");
    int newId;
    while (scanf("%d", &newId) != 1 || newId < 0)
    {
        CLEAR_SCREEN();
        printf("Invalid input. Please enter a non-negative number for ID.\n\n");
        printf("Enter item details:\n");
        printf("ID: ");
        while (getchar() != '\n')
            ;
    }
    for (int i = 0; i < data->itemCount; i++)
    {
        if (data->inventory[i].id == newId)
        {
            CLEAR_SCREEN();
            printf("Error: An item with the same ID already exists. Item not added.\n");
            return;
        }
    }

    printf("Name: ");
    char *newName = malloc(MAX_NAME * sizeof(char));
    scanf("%s", newName);
    for (int i = 0; i < data->itemCount; i++)
    {
        if (strcmp(data->inventory[i].name, newName) == 0 || strcmp(data->inventory[i].name, newName) == 32 || strcmp(data->inventory[i].name, newName) == -32)
        {
            CLEAR_SCREEN();
            printf("Error: An item with the same name already exists. Item not added.\n");
            return;
        }
    }

    printf("Price: ");
    while (scanf("%f", &data->inventory[data->itemCount].price) != 1 || data->inventory[data->itemCount].price < 0)
    {
        CLEAR_SCREEN();
        printf("Invalid input. Please enter a non-negative number for Price.\n\n");
        printf("Enter item details:\n");
        printf("ID: %d\n", newId);
        printf("Name: %s\n", newName);
        printf("Price: ");
        while (getchar() != '\n')
            ;
    }

    printf("Quantity: ");
    while (scanf("%d", &data->inventory[data->itemCount].quantity) != 1 || data->inventory[data->itemCount].quantity < 0)
    {
        CLEAR_SCREEN();
        printf("Invalid input. Please enter a non-negative number for Quantity.\n\n");
        printf("Enter item details:\n");
        printf("ID: %d\n", newId);
        printf("Name: %s\n", newName);
        printf("Price: %.2f\n", data->inventory[data->itemCount].price);
        printf("Quantity: ");
        while (getchar() != '\n')
            ;
    }

    printf("Category: ");
    scanf("%s", data->inventory[data->itemCount].category);
    data->inventory[data->itemCount].id = newId;
    strcpy(data->inventory[data->itemCount].name, newName);
    (data->itemCount)++;

    CLEAR_SCREEN();
    printf("Item added successfully!\n");
}

void removeItem(struct InventoryData *data)
{
	CLEAR_SCREEN();
	if (data->itemCount == 0)
	{
		printf("Inventory is empty. Nothing to remove.\n");
		return;
	}

	printf("\nEnter the ID of the item to remove: ");
	int idToRemove;
	while (scanf("%d", &idToRemove) != 1)
	{
		CLEAR_SCREEN();
		printf("Invalid input. Please enter a number for ID.\n\n");
		printf("Enter the ID of the item to remove: ");
		while (getchar() != '\n')
			;
	}

	int foundIndex = -1;

	for (int i = 0; i < data->itemCount; i++)
	{
		if (data->inventory[i].id == idToRemove)
		{
			foundIndex = i;
			break;
		}
	}

	if (foundIndex != -1)
	{
		for (int i = foundIndex; i < data->itemCount - 1; i++)
		{
			data->inventory[i] = data->inventory[i + 1];
		}

		(data->itemCount)--;
		CLEAR_SCREEN();
		printf("Item removed successfully!\n");
	}
	else
	{
		CLEAR_SCREEN();
		printf("Item not found.\n");
	}
}

void sortInventoryById(struct InventoryData *data)
{
	int i, j;
	struct Item temp;

	for (i = 0; i < data->itemCount - 1; i++)
	{
		for (j = 0; j < data->itemCount - i - 1; j++)
		{
			if (data->inventory[j].id > data->inventory[j + 1].id)
			{
				temp = data->inventory[j];
				data->inventory[j] = data->inventory[j + 1];
				data->inventory[j + 1] = temp;
			}
		}
	}
}

void displayInventory(struct InventoryData *data)
{
	CLEAR_SCREEN();
	if (data->itemCount == 0)
	{
		printf("Inventory is empty.\n");
		return;
	}

	sortInventoryById(data);

	printf("\n==== Inventory ====\n");
	for (int i = 0; i < data->itemCount; i++)
	{
		printf("ID: %d\n", data->inventory[i].id);
		printf("Name: %s\n", data->inventory[i].name);
		printf("Price: %.2f\n", data->inventory[i].price);
		printf("Quantity: %d\n", data->inventory[i].quantity);
		printf("Category: %s\n", data->inventory[i].category);
		printf("--------------------\n");
	}
}

int showItemDetails(struct InventoryData *data)
{
	CLEAR_SCREEN();
	if (data->itemCount == 0)
	{
		printf("Inventory is empty.\n");
		return 0;
	}

	int idToSearch;
	printf("Enter the ID of the item to show details: ");
	while (scanf("%d", &idToSearch) != 1)
	{
		CLEAR_SCREEN();
		printf("Invalid input. Please enter a number for ID.\n\n");
		printf("Enter the ID of the item to show details: ");
		while (getchar() != '\n')
			;
	}

	int foundIndex = -1;

	for (int i = 0; i < data->itemCount; i++)
	{
		if (data->inventory[i].id == idToSearch)
		{
			foundIndex = i;
			break;
		}
	}

	if (foundIndex != -1)
	{
		CLEAR_SCREEN();
		printf("\n==== Item Details ====\n");
		printf("ID: %d\n", data->inventory[foundIndex].id);
		printf("Name: %s\n", data->inventory[foundIndex].name);
		printf("Price: %.2f\n", data->inventory[foundIndex].price);
		printf("Quantity: %d\n", data->inventory[foundIndex].quantity);
		printf("Category: %s\n", data->inventory[foundIndex].category);
	}
	else
	{
		CLEAR_SCREEN();
		printf("Item not found.\n");
	}
	return idToSearch;
}

void updateItem(struct InventoryData *data)
{
    int itemId = showItemDetails(data);

    for (int i = 0; i < data->itemCount; i++)
    {
        if (data->inventory[i].id == itemId)
        {
            printf("Enter new details for item with ID %d:\n", itemId);

            printf("Name: ");
            char newName[MAX_NAME];
            scanf("%s", newName);
            for (int j = 0; j < data->itemCount; j++)
            {
                if (((strcmp(data->inventory[j].name, newName) == 0 || strcmp(data->inventory[j].name, newName) == 32 || strcmp(data->inventory[j].name, newName) == -32) && data->inventory[j].id != itemId))
                {
                    CLEAR_SCREEN();
                    printf("Error: An item with the same name exist or invalid name character. Item not updated.\n");
                    return;
                }
            }
            strcpy(data->inventory[i].name, newName);

            printf("Price: ");
            while (scanf("%f", &data->inventory[i].price) != 1 || data->inventory[i].price < 0)
            {
                CLEAR_SCREEN();
                printf("Invalid input. Please enter a non-negative number for Price.\n\n");
                printf("Enter new details for item with ID %d:\n", itemId);
                printf("Name: %s\n", data->inventory[i].name);
                printf("Price: ");
                while (getchar() != '\n')
                    ;
            }

            printf("Quantity: ");
            while (scanf("%d", &data->inventory[i].quantity) != 1 || data->inventory[i].quantity < 0)
            {
                CLEAR_SCREEN();
                printf("Invalid input. Please enter a non-negative number for Quantity.\n\n");
                printf("Enter new details for item with ID %d:\n", itemId);
                printf("Name: %s\n", data->inventory[i].name);
                printf("Price: %.2f\n", data->inventory[i].price);
                printf("Quantity: ");
                while (getchar() != '\n')
                    ;
            }

            printf("Category: ");
            scanf("%s", data->inventory[i].category);

            printf("Item details updated successfully!\n");
            return;
        }
    }

    printf("Item with ID %d not found.\n", itemId);
}

void calculateInventoryTotal(struct InventoryData *data)
{
	int totalItems = 0;
	float totalValue = 0.0;

	for (int i = 0; i < data->itemCount; i++)
	{
		totalItems += data->inventory[i].quantity;
		totalValue += data->inventory[i].price * data->inventory[i].quantity;
	}
	CLEAR_SCREEN();
	printf("Total number of items in inventory: %d\n", totalItems);
	printf("Total value of inventory: %.2f$\n", totalValue);
}

void saveToFile(struct InventoryData *data)
{
	CLEAR_SCREEN();
	FILE *file = fopen("/Users/ifozmen/Documents/CP3/LabProject/inventory.txt", "w");
	if (file == NULL)
	{
		printf("Error opening file for writing.\n");
		return;
	}
	sortInventoryById(data);

	for (int i = 0; i < data->itemCount; i++)
	{
		if (fprintf(file, "%d %s %.2f %d %s\n", data->inventory[i].id,
					data->inventory[i].name, data->inventory[i].price,
					data->inventory[i].quantity, data->inventory[i].category) < 0)
		{
			printf("Error writing to file.\n");
			fclose(file);
			return;
		}
	}

	fclose(file);
	printf("Inventory saved to file successfully!\n");
}

void loadFromFile(struct InventoryData *data)
{
	FILE *file = fopen("/Users/ifozmen/Documents/CP3/LabProject/inventory.txt", "r");
	if (file == NULL)
	{
		printf("No existing inventory file found.\n");
		return;
	}
	data->inventory = malloc(MAX_ITEMS * sizeof(struct Item));
	if (data->inventory == NULL)
	{
		printf("Error: Memory allocation failed.\n");
		fclose(file);
		exit(EXIT_FAILURE);
	}

	while (fscanf(file, "%d %s %f %d %s", &data->inventory[data->itemCount].id,
				  data->inventory[data->itemCount].name, &data->inventory[data->itemCount].price,
				  &data->inventory[data->itemCount].quantity, data->inventory[data->itemCount].category) == 5)
	{
		(data->itemCount)++;
		if (data->itemCount >= MAX_ITEMS)
		{
			printf("Error: Maximum number of items exceeded.\n");
			fclose(file);
			return;
		}
		struct Item *temp = realloc(data->inventory, (data->itemCount + 1) * sizeof(struct Item));
		if (temp == NULL)
		{
			printf("Error: Memory reallocation failed.\n");
			fclose(file);
			exit(EXIT_FAILURE);
		}
		data->inventory = temp;
	}

	if (ferror(file))
	{
		printf("Error reading from file.\n");
		fclose(file);
		return;
	}

	fclose(file);
	printf("Inventory loaded from file.\n");
}
