#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

struct new_user {
    char username[50];
    char password[50];
    bool write;
    bool read;
    bool execute;
};

typedef unsigned char bitmap8;

struct user {
    char username[50];
    char password[50];
    bitmap8 permissions;
};

void compare() {
    printf("The size of new_user is %d.\n", sizeof(struct new_user));
    printf("The size of user is %d.\n", sizeof(struct user));
}

void grantPermission(int bitIndex, struct user* user) {
    unsigned char bit = 1 << bitIndex;
    user->permissions = user->permissions | bit;
}

void revokePermission(int bitIndex, struct user* user) {
    unsigned char bit = 1 << bitIndex;
    user->permissions = user->permissions ^ bit;
}

int checkPermission(int bitIndex, struct user* user) {
    unsigned char bit = 1 << bitIndex;
    if (user->permissions & bit) {
        return 1;
    }
    return 0;
}

void printPermissions(struct user* user) {
    if(checkPermission(0, user)) {
        printf("%s has write permission.\n", user->username);
    }
    else {
        printf("%s doesn't have write permission.\n", user->username);
    }
    if(checkPermission(1, user)) {
        printf("%s has read permission.\n", user->username);
    }
    else {
        printf("%s doesn't have read permission.\n", user->username);
    }
    if(checkPermission(2, user)) {
        printf("%s has execute permission.\n", user->username);
    }
    else {
        printf("%s doesn't have execute permission.\n", user->username);
    }
}

void setPermissions(int new_permissions, struct user* user) {
     user->permissions = new_permissions;
}

int main(int argc, char** argv) {
    struct user user;
    strcpy(user.username, "admin");
    strcpy(user.password, "s#1Pa5");
    user.permissions = 0; //Sets the permissions to 0
    
    for (int i = 1; i < argc; i++) {
        int value = atoi(argv[i]);
        if (value < 0) {
            value = value * -1;
            revokePermission(value, &user);
        }
        else {
            grantPermission(value &user);
        }
    }

    printPermissions(&user);

    return EXIT_SUCCESS;
}
