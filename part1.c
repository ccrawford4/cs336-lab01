#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User struct
struct user {
  char username[50];
  char password[50];
  int admin;
};

// Given a max number of users, dynamically allocates memory for an array of user structs
struct user *createUsers(int max_number_of_users) {
  struct user *user_array = malloc(max_number_of_users * sizeof(struct user));
  return user_array;
}

// Initalizes the values in the user struct array with default values
void initUsers(struct user *users, int max_number_of_users) {
  for (int i = 0; i < max_number_of_users; i++) {
    strncpy(users[i].username, "default", sizeof(users[i].username));
    strncpy(users[i].password, "default", sizeof(users[i].password));
    users[i].admin = 0;
  }
}

// Adds a new user to the structs array given the appropriate info 
void addUser1(struct user *users, char *username, char *password, int admin,
              int *count) {
  strncpy(users[*count].username, username, sizeof(users[*count].username));
  strncpy(users[*count].password, password, sizeof(users[*count].password));
  users[*count].admin = admin;
  *count = *count + 1;
}

// Adds a new user to the user structs array given a user struct
void addUser2(struct user *users, struct user *newUser, int *count) {
  users[*count] = *newUser;
  *count = *count + 1;
}

// Prints the users username & password from the array
void printUser(struct user *users, int number_of_users) {
  for (int i = 0; i < number_of_users; i++) {
    printf("username%d: %s\n", i, users[i].username);
    printf("password%d: %s\n", i, users[i].password);
  }
}

int main(void) {
  struct user *users = createUsers(10);
  if (users == NULL) {
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
