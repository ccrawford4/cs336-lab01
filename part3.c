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
      unsigned char bit = 0x00;
      switch (new_permissions) {
        case 0: break;
        case 1: 
            bit = bit | (1 << 0);
            user->permissions = user->permissions | bit;
            break;
       case 2:
            bit = bit | (1 << 1);
            user->permissions = user->permissions | bit;
            break;
       case 3:
            bit = bit | (1 << 0) | (1 << 1);
            user->permissions = user->permissions | bit;
            break;
      case 4:
            bit = bit | (1 << 2);
             user->permissions = user->permissions | bit;
            break;
      case 5:
            bit = bit | (1 << 0) | (1 << 2);
            user->permissions = user->permissions | bit;
            break;
      case 6:
            bit = bit | (1 << 1) | (1 << 2);
            user->permissions = user->permissions | bit;
            break;
      case 7:
            bit = bit | (1 << 0) | (1 << 1) | (1 << 2);
            user->permissions = user->permissions | bit;
            break;
      default:
         printf("ERROR! Invalid input. Value must be 0-7.\n");
         exit(EXIT_FAILURE);
      }
}

int main(int argc, char** argv) {
    struct user user;
    strcpy(user.username, "admin");
    strcpy(user.password, "s#1Pa5");
    user.permissions = 0; //Sets the permissions to 0
    
    char* command = argv[1];

    if (strcmp(command, "grant") == 0) {
        for (int i = 2; i < argc; i++) {
            int value = atoi(argv[i]);
            if (value < 0) {
                printf("ERROR: Negative permission values not allowed for grant. Use revoke instead.\n");
                return EXIT_FAILURE;
            }
            grantPermission(value, &user);
        }
    } else if (strcmp(command, "revoke") == 0) {
        for (int i = 2; i < argc; i++) {
            int value = atoi(argv[i]);
            if (value < 0) {
                printf("ERROR: Negative permission values not allowed for revoke. Use grant instead.\n");
                return EXIT_FAILURE;
            }
            revokePermission(value, &user);
        }
    } else if (strcmp(command, "set") == 0) {
        if (argc != 3) {
            printf("ERROR: Set command requires exactly one permission value.\n");
            return EXIT_FAILURE;
        }
        int value = atoi(argv[2]);
        setPermissions(value, &user);
    } else {
        printf("ERROR: Invalid command. Supported commands are grant, revoke, and set.\n");
        return EXIT_FAILURE;
    }

    printPermissions(&user);

    return EXIT_SUCCESS; 
}
