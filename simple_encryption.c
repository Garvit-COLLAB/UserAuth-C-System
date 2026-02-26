/*
    User Registration System with Basic Password Encryption
    Author: Garvit Jain
    Description:
    A file-based user registration system that ensures unique usernames
    and stores encrypted passwords using Caesar cipher logic.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERS 100
#define MAX_LEN 50
#define SHIFT 3

typedef struct {
    char username[MAX_LEN];
    char password[MAX_LEN];
} User;

void encrypt_password(char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (isalpha(password[i])) {
            char base = isupper(password[i]) ? 'A' : 'a';
            password[i] = ((password[i] - base + SHIFT) % 26) + base;
        }
    }
}

void load_users(User users[], int *count) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        *count = 0;
        return;
    }

    *count = 0;
    while (fscanf(file, "%49s %49s", users[*count].username, users[*count].password) == 2) {
        (*count)++;
        if (*count >= MAX_USERS)
            break;
    }
    fclose(file);
}

void save_user(User *user) {
    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%s %s\n", user->username, user->password);
    fclose(file);
}

int is_username_unique(User users[], int count, char *username) {
    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].username, username) == 0)
            return 0;
    }
    return 1;
}

int main() {
    User users[MAX_USERS];
    int total_users = 0;

    load_users(users, &total_users);

    if (total_users >= MAX_USERS) {
        printf("User limit reached.\n");
        return 1;
    }

    User new_user;

    // Username input
    while (1) {
        printf("Enter username (3-7 characters): ");
        scanf("%49s", new_user.username);

        int len = strlen(new_user.username);

        if (len < 3 || len > 7) {
            printf("Invalid username length.\n");
            continue;
        }

        if (!is_username_unique(users, total_users, new_user.username)) {
            printf("Username already exists.\n");
            continue;
        }

        break;
    }

    // Password input
    while (1) {
        printf("Enter password (3-7 characters): ");
        scanf("%49s", new_user.password);

        int len = strlen(new_user.password);

        if (len < 3 || len > 7) {
            printf("Invalid password length.\n");
            continue;
        }

        break;
    }

    encrypt_password(new_user.password);

    save_user(&new_user);

    printf("User '%s' registered successfully.\n", new_user.username);
    printf("Password stored securely (encrypted).\n");

    return 0;
}