#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct user{
    char username[50];
    char password[50];
    int admin;
};

struct user* createUsers(int max_number_of_users) {
    struct user* user_array  = malloc(max_number_of_users * sizeof(struct user));
    return user_array;
}

// MAKE SURE TO ASK IF ALLOWED TO CHANGE THIS FROM VOID* USERS TO struct user* users
void initUsers(struct user* users, int max_number_of_users) {
    for (int i = 0; i < max_number_of_users; i++) {
        strncpy(users[i].username, "default", sizeof(users[i].username));
        strncpy(users[i].password, "default", sizeof(users[i].password));
        users[i].admin = 0;
    }
}

void addUser1(struct user* users, char* username, char* password,
    int admin, int* count) {
    strncpy(users[*count].username, username, sizeof(users[*count].username));
    strncpy(users[*count].password, password, sizeof(users[*count].password));
    users[*count].admin = admin;
    *count++;
}

void addUser2(struct user* users, struct user* newUser, int* count) {
    //Your code goes here
}

void printUser(struct user* users, int number_of_users) {
    //Your code goes here
}

int main(void) {
    struct user* users = createUsers(10);
    if(users == NULL) {
        return 0;
    }
    int userCount = 0;
    initUsers(users, 10);
    addUser1(users, "admin", "s#1Pa5", 1, &userCount);
    addUser1(users, "vahab", "fgH!12", 0, &userCount);

    struct user u1;
    u1.admin = 2;
    strcpy(u1.username, "usf");
    strcpy(u1.password, "gA24?m");
    addUser2(users, &u1, &userCount);
    printUser(users, userCount);
    free(users);
    return 0;
}
