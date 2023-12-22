#ifndef FT_INVENTORY_H
# define FT_INVENTORY_H

#  define CLEAR_SCREEN() system("clear")
#  define MAX_ITEMS 100
#  define MAX_NAME 20
#  define MAX_CATEGORY 20
#  define MAX_USERS 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

enum UserType
{
    NORMAL_USER,
    ADMIN_USER
};

struct User
{
    char    username[MAX_NAME];
    char    password[MAX_NAME];
    enum    UserType userType;
};

struct Item
{
    int     id;
    char    name[MAX_NAME];
    float   price;
    int     quantity;
    char    category[MAX_CATEGORY];
};

struct InventoryData
{
    struct  Item *inventory;
    int     itemCount;
    struct  User *users;
    int     userCount;
};
struct UserFunctions
{
    int (*countUsers)(const char *filename);
    int (*countAdmins)(const char *filename);
};

void    displayLoginMenu();
void    displayMainMenu();
void    addUser(struct InventoryData *data);
void    displayUsers(struct InventoryData *data);
void    displayUsers(struct InventoryData *data);
void    removeUser(struct InventoryData *data);
int     authenticateUser(struct InventoryData *data, char *username, char *password);
void    displayUserMenu(struct InventoryData *data);
void    displayAdminMenu(struct InventoryData *data);
void    displayMenu();
void    addItem(struct InventoryData *data);
void    addItemDoublePointer(struct InventoryData **data);
void    removeItem(struct InventoryData *data);
void    sortInventoryById(struct InventoryData *data);
void    displayInventory(struct InventoryData *data);
int     showItemDetails(struct InventoryData *data);
void    updateItem(struct InventoryData *data);
void    calculateInventoryTotal(struct InventoryData *data);
void    saveToFile(struct InventoryData *data);
void    loadFromFile(struct InventoryData *data);
void    loadUsersFromFile(struct InventoryData *data);
void    saveUsersToFile(struct InventoryData *data);
int     countUsers(const char *filename);
int     countAdmins(const char *filename);
void    countUsersInFile(struct UserFunctions *userFunctions, const char *filename);

#endif
