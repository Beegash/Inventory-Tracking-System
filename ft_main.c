#include "ft_inventory.h"

int main()
{
	struct InventoryData data;
	struct UserFunctions userFunctions;
	userFunctions.countUsers = countUsers;
	userFunctions.countAdmins = countAdmins;
	data.inventory = malloc(MAX_ITEMS * sizeof(struct Item));
	if (data.inventory == NULL)
	{
		printf("Memory allocation failed. Exiting program.\n");
		return -1;
	}

	data.userCount = 0;
	data.itemCount = 0;

	CLEAR_SCREEN();
	loadFromFile(&data);
	loadUsersFromFile(&data);

	int choice;

	do
	{
		displayLoginMenu();
		printf("Enter your choice: ");
		while (scanf("%d", &choice) != 1)
		{
			printf("Invalid input. Please enter a number.\n\n");
			displayLoginMenu();
			printf("Enter your choice: ");
			while (getchar() != '\n')
				;
		}

		switch (choice)
		{
		case 1:
			addUser(&data);
			break;
		case 2:
			CLEAR_SCREEN();
			printf("Enter your username: ");
			char username[MAX_NAME];
			scanf("%s", username);
			printf("Enter your password: ");
			char password[MAX_NAME];
			scanf("%s", password);

			int userIndex = authenticateUser(&data, username, password);

			if (userIndex != -1)
			{
				CLEAR_SCREEN();
				if (data.users[userIndex].userType == NORMAL_USER)
					displayUserMenu(&data);
				else if (data.users[userIndex].userType == ADMIN_USER)
					displayAdminMenu(&data);
				CLEAR_SCREEN();
			}
			else
			{
				CLEAR_SCREEN();
				printf("Authentication failed. Invalid username or password.\n");
			}
			break;
		case 3:
			CLEAR_SCREEN();
			countUsersInFile(&userFunctions, "/Users/ifozmen/Documents/CP3/LabProject/users.txt");
			break;
		default:
			CLEAR_SCREEN();
			printf("Invalid choice. Please try again.\n");
		}

	} while (choice != 4);

	saveUsersToFile(&data);
	free(data.inventory);
	CLEAR_SCREEN();
	printf("Exiting program.\n");
	return 0;
}
