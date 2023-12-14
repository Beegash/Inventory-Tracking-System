#include "ft_inventory.h"

void displayLoginMenu()
{
	printf("\n==== Login Menu ====\n");
	printf("1. Register\n");
	printf("2. Login\n");
	printf("3. Show User Info\n");
	printf("4. Exit\n");
}

void displayUserMenu(struct InventoryData *data)
{
	int choice;

	do
	{
		displayMainMenu();
		printf("6. Exit\n");

		printf("Enter your choice: ");
		while (scanf("%d", &choice) != 1)
		{
			CLEAR_SCREEN();
			printf("Invalid input. Please enter a number.\n\n");
			displayMainMenu();
			printf("6. Exit\n");
			printf("Enter your choice: ");
			while (getchar() != '\n')
				;
		}

		switch (choice)
		{
		case 1:
			addItem(data);
			break;
		case 2:
			removeItem(data);
			break;
		case 3:
			displayInventory(data);
			break;
		case 4:
			showItemDetails(data);
			break;
		case 5:
			saveToFile(data);
			break;
		case 6:
			printf("Logging out!");
			break;
		default:
			CLEAR_SCREEN();
			printf("Invalid choice. Please try again.\n");
		}

	} while (choice != 6);
}

void displayAdminMenu(struct InventoryData *data)
{
	int choice;
	do
	{
		displayMainMenu();
		printf("6. Show Total Value\n");
		printf("7. Update Item\n");
		printf("8. Remove User\n");
		printf("9. Exit\n");

		printf("Enter your choice: ");
		while (scanf("%d", &choice) != 1)
		{
			CLEAR_SCREEN();
			printf("Invalid input. Please enter a number.\n\n");
			displayMainMenu();
			printf("6. Show Total Value\n");
			printf("7. Update Item\n");
			printf("8. Remove User\n");
			printf("9. Exit\n");
			printf("Enter your choice: ");
			while (getchar() != '\n')
				;
		}

		switch (choice)
		{
		case 1:
			addItem(data);
			break;
		case 2:
			removeItem(data);
			break;
		case 3:
			displayInventory(data);
			break;
		case 4:
			showItemDetails(data);
			break;
		case 5:
			saveToFile(data);
			break;
		case 6:
			calculateInventoryTotal(data);
			break;
		case 7:
			updateItem(data);
			break;
		case 8:
			removeUser(data);
			break;
		case 9:
			printf("Logging out!");
			break;
		default:
			CLEAR_SCREEN();
			printf("Invalid choice. Please try again.\n");
		}

	} while (choice != 9);
}

void displayMainMenu()
{
	printf("\n==== Main Menu ====\n");
	printf("1. Add Item\n");
	printf("2. Remove Item\n");
	printf("3. Display Inventory\n");
	printf("4. Show Item Details\n");
	printf("5. Save to File\n");
}

void addUser(struct InventoryData *data)
{
	CLEAR_SCREEN();
	printf("\nEnter user details:\n");

	if (data->userCount >= MAX_USERS)
	{
		printf("Error: Maximum number of users exceeded.\n");
		return;
	}

	printf("Username: ");
	char newUsername[MAX_NAME];
	scanf("%s", newUsername);
	for (int i = 0; i < data->userCount; i++)
	{
		if (strcmp(data->users[i].username, newUsername) == 0)
		{
			CLEAR_SCREEN();
			printf("Error: Username already exists. Please choose another username.\n");
			return;
		}
	}

	printf("Password: ");
	char newPassword[MAX_NAME];
	scanf("%s", newPassword);

	enum UserType userType;
	printf("User Type (0 for Normal User, 1 for Admin User): ");
	int typeChoice;
	while (scanf("%d", &typeChoice) != 1 || (typeChoice != 0 && typeChoice != 1))
	{
		CLEAR_SCREEN();
		printf("Invalid input. Please enter 0 or 1 for User Type.\n\n");
		printf("User Type (0 for Normal User, 1 for Admin User): ");
		while (getchar() != '\n')
			;
	}
	userType = (typeChoice == 1) ? ADMIN_USER : NORMAL_USER;

	strcpy(data->users[data->userCount].username, newUsername);
	strcpy(data->users[data->userCount].password, newPassword);
	data->users[data->userCount].userType = userType;
	(data->userCount)++;

	CLEAR_SCREEN();
	printf("User added successfully!\n");
	saveUsersToFile(data);
}

void displayUsers(struct InventoryData *data)
{
	CLEAR_SCREEN();
	printf("\n==== Users ====\n");

	if (data->userCount == 0)
	{
		printf("No users available.\n");
		return;
	}

	printf("%-4s %-20s %-10s\n", "No", "Username", "User Type");
	printf("----------------------------\n");

	for (int i = 0; i < data->userCount; i++)
	{
		char *userTypeStr = (data->users[i].userType == ADMIN_USER) ? "Admin" : "Normal";
		printf("%-4d %-20s %-10s\n", i + 1, data->users[i].username, userTypeStr);
	}
}

void removeUser(struct InventoryData *data)
{
	displayUsers(data);

	if (data->userCount == 0)
	{
		return;
	}

	int userNumber;
	printf("\nEnter the number corresponding to the user to remove (0 to cancel): ");
	while (1)
	{
		if (scanf("%d", &userNumber) != 1 || userNumber < 0 || userNumber > data->userCount)
		{
			CLEAR_SCREEN();
			displayUsers(data);
			printf("Invalid input. Please enter a valid number.\n\n");
			printf("\nEnter the number corresponding to the user to remove (0 to cancel): ");
			while (getchar() != '\n')
				;
		}
		else
		{
			break;
		}
	}

	if (userNumber == 0)
	{
		CLEAR_SCREEN();
		printf("User removal canceled.\n");
		return;
	}

	int userIndex = userNumber - 1;

	if (data->users[userIndex].userType == ADMIN_USER)
	{
		CLEAR_SCREEN();
		printf("Error: Admin users cannot be removed.\n");
	}
	else
	{
		for (int i = userIndex; i < data->userCount - 1; i++)
		{
			data->users[i] = data->users[i + 1];
		}

		(data->userCount)--;
		CLEAR_SCREEN();
		printf("User removed successfully!\n");
	}
}

int authenticateUser(struct InventoryData *data, char *username, char *password)
{
	for (int i = 0; i < data->userCount; i++)
	{
		if (strcmp(data->users[i].username, username) == 0 &&
			strcmp(data->users[i].password, password) == 0)
		{
			return i;
		}
	}

	return -1;
}

void loadUsersFromFile(struct InventoryData *data)
{
	FILE *file = fopen("/Users/ifozmen/Documents/CP3/LabProject/users.txt", "r");
	if (file == NULL)
	{
		printf("No existing users file found.\n");
		return;
	}

	while (fscanf(file, "%s %s %d", data->users[data->userCount].username,
				  data->users[data->userCount].password, &data->users[data->userCount].userType) == 3)
	{
		(data->userCount)++;
		if (data->userCount >= MAX_USERS)
		{
			printf("Error: Maximum number of users exceeded.\n");
			fclose(file);
			return;
		}
	}

	if (ferror(file))
	{
		printf("Error reading from users file.\n");
		fclose(file);
		return;
	}

	fclose(file);
	printf("Users loaded from file.\n");
}

void saveUsersToFile(struct InventoryData *data)
{
	FILE *file = fopen("/Users/ifozmen/Documents/CP3/LabProject/users.txt", "w");
	if (file == NULL)
	{
		printf("Error opening users file for writing.\n");
		return;
	}
	for (int i = 0; i < data->userCount; i++)
	{
		if (fprintf(file, "%s %s %d\n", data->users[i].username,
					data->users[i].password, data->users[i].userType) < 0)
		{
			printf("Error writing to users file.\n");
			fclose(file);
			return;
		}
	}
	fclose(file);
	printf("Users status updated to file successfully!\n");
}

void displayMenu()
{
	printf("\n==== Inventory Tracking System ====\n");
	printf("1. Add Item\n");
	printf("2. Remove Item\n");
	printf("3. Display Inventory\n");
	printf("4. Show Item Details\n");
	printf("5. Save to File\n");
	printf("6. Exit\n");
}

int countUsers(const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (!file)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	int userCount = 0;
	struct User tempUser;

	while (fscanf(file, "%s %s %d\n", tempUser.username, tempUser.password, &tempUser.userType) == 3)
	{
		userCount++;
	}

	fclose(file);
	return userCount;
}

int countAdmins(const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (!file)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	int adminCount = 0;
	struct User tempUser;

	while (fscanf(file, "%s %s %d\n", tempUser.username, tempUser.password, &tempUser.userType) == 3)
	{
		if (tempUser.userType == ADMIN_USER)
		{
			adminCount++;
		}
	}

	fclose(file);
	return adminCount;
}

void countUsersInFile(struct UserFunctions *userFunctions, const char *filename)
{
	int totalUsers = userFunctions->countUsers(filename);
	int admins = userFunctions->countAdmins(filename);

	printf("Total Users: %d\n", totalUsers);
	printf("Admin Users: %d\n", admins);
}