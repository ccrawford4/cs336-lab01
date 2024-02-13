#define _GNU_SOURCE
#define FILE_PATH "./credential_file"
#define BUFFER_LEN 256
#define ADMIN_PASS "s#1Pa5"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// User struct
struct user {
  char username[50];
  char password[256];
  char firstname[50];
  char lastname[50];
  int admin;
};

// Hash function
char *cs336Hash(const char *password) { return crypt(password, "00"); }

// Counts the number of lines in the file and creates a user struct based on
// this size.
struct user *createUsers(int *count) {
  FILE *fp = fopen(FILE_PATH, "r");

  if (fp == NULL) {
    printf("ERROR! File can't be opened\n");
    exit(EXIT_FAILURE);
  }

  int ch;
  while ((ch = fgetc(fp)) != EOF) {
    if (ch == '\n') {
      *count = *count + 1;
    }
  }

  fclose(fp);

  struct user *users = (struct user *)malloc(*count);
  return users;
}

// Populates the users array based on the file info
void populateUsers(struct user *users) {
  FILE *fp = fopen(FILE_PATH, "r");
  if (fp == NULL) {
    printf("ERROR Opening file %s\n", FILE_PATH);
    exit(EXIT_FAILURE);
  }
  char line[BUFFER_LEN];

  int count = 0;
  int index = 0;
  while (fscanf(fp, "%s", line) == 1) {
    int len = strnlen(line, sizeof(line));
    line[len] = '\0';
    switch (index) {
    case 0:
      snprintf(users[count].firstname, sizeof(users[count].firstname), "%s",
               line);
      break;
    case 1:
      snprintf(users[count].lastname, sizeof(users[count].lastname), "%s",
               line);
      break;
    case 2:
      snprintf(users[count].username, sizeof(users[count].username), "%s",
               line);
      break;
    case 3:
      snprintf(users[count].password, sizeof(users[count].password), "%s",
               line);
      break;
    case 4:
      int value = atoi(line);
      if (value == 0 && line[0] != '0') {
        printf("ERROR! %s is an invalid number.\n", line);
        exit(EXIT_FAILURE);
      }
      users[count].admin = value;
      index = 0; // Reset the index and increase the count
      count++;
      break;
    default:
      break;
    }
  }
  fclose(fp);
}

// Validates if the password entered is the same as the admin password
int checkAdminPassword(char *password, struct user *users, int count) {
  for (int i = 0; i < count; ++i) {
    if (strcmp((users + i)->username, "admin") == 0) {
      const char *const_password = password;
      char *hash = cs336Hash(const_password);

      if (strcmp((users + i)->password, hash) == 0) {
        return 1;
      } else {
        return 0;
      }
    }
  }
  return 0;
}

// Adds a user to the user struct array given the necessary information
struct user *addUser(struct user *users, int *count, char *username,
                     char *password, char *firstname, char *lastname,
                     int admin) {
  strncpy(users[*count].username, username, sizeof(users[*count].username));
  const char *const_password = password;
  char *hash = cs336Hash(const_password);
  strncpy(users[*count].password, hash, sizeof(users[*count].password));
  strncpy(users[*count].firstname, firstname, sizeof(users[*count].firstname));
  strncpy(users[*count].lastname, lastname, sizeof(users[*count].lastname));
  users[*count].admin = admin;

  *count = *count + 1;

  return users;
}

// Saves the users (including the new ones) to the file
void saveUsers(struct user *users, int count) {
  FILE *fp = fopen(FILE_PATH, "w");
  if (!fp) {
    printf("ERROR! Could not open file %s\n", FILE_PATH);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < count; i++) {
    char *firstname = users[i].firstname;
    char *lastname = users[i].lastname;
    char *username = users[i].username;
    char *password = users[i].password;
    int admin = users[i].admin;
    fprintf(fp, "%s\t%s\t%s\t%s\t%d\t\n", firstname, lastname, username,
            password, admin);
  }
  fclose(fp);
}

int main(void) {
  int user_count = 0;
  struct user *users = createUsers(&user_count);
  if (users == NULL) {
    return EXIT_FAILURE;
  }
  populateUsers(users);

  printf("Enter admin password to add new users:");
  char entered_admin_password[50];
  scanf("%s", entered_admin_password);
  if (checkAdminPassword(entered_admin_password, users, user_count)) {
    struct user new_user;
    printf("Enter username:");
    scanf("%s", new_user.username);
    printf("Enter first name:");
    scanf("%s", new_user.firstname);
    printf("Enter last name:");
    scanf("%s", new_user.lastname);
    printf("Enter password:");
    scanf("%s", new_user.password);
    printf("Enter admin level:");
    scanf("%d", &(new_user.admin));
    users = addUser(users, &user_count, new_user.username, new_user.password,
                    new_user.firstname, new_user.lastname, new_user.admin);
    if (users == NULL) {
      return EXIT_FAILURE;
    }
  }
  saveUsers(users, user_count);
  free(users);
  return EXIT_SUCCESS;
}
