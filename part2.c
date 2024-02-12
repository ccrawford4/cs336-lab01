#define _GNU_SOURCE
#define FILE_PATH "./credential_file"
#define BUFFER_LEN 256
#define ADMIN_PASS "s#1Pa5"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct user {
  char username[50];
  char password[256];
  char firstname[50];
  char lastname[50];
  int admin;
};

char *cs336Hash(const char *password) { return crypt(password, "00"); }

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

// ASK IF WE CAN CHANGE THIS TOO (ORIGINALLY WAS VOID* USERS)
void populateUsers(struct user *users) {
  FILE *fp = fopen(FILE_PATH, "r");
  if (fp == NULL) {
    printf("ERROR Opening file %s\n", FILE_PATH);
    exit(EXIT_FAILURE);
  }
  char line[100];

  int count = 0;
  char *token;
  while (fgets(line, sizeof(line), fp)) {
    int len = strlen(line);
    line[len - 1] = '\0';

    token = strtok(line, "\t");
    int index = 0;
    while (token != NULL) {
      switch (index) {
      case 0:
        snprintf(users[count].firstname, sizeof(users[count].firstname), "%s",
                 token);
        break;
      case 1:
        snprintf(users[count].lastname, sizeof(users[count].lastname), "%s",
                 token);
        break;
      case 2:
        snprintf(users[count].username, sizeof(users[count].username), "%s",
                 token);
        break;
      case 3:
        snprintf(users[count].password, sizeof(users[count].password), "%s",
                 token);
        break;
      case 4:
        int value = atoi(token);
        if (value == 0 && token[0] != '0') {
          printf("ERROR! %s is an invalid number.\n", token);
          exit(EXIT_FAILURE);
        }
        users[count].admin = value;
        break;
      default:
        break;
      }
      token = strtok(NULL, "\t");
      index++;
    }

    count++;
  }
}

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

void saveUsers(struct user *users, int count) {
  FILE *fp = fopen(FILE_PATH, "a");
  if (!fp) {
    printf("ERROR! Could not open file %s\n", FILE_PATH);
    exit(EXIT_FAILURE);
  }
  int i = count - 1;
  char *firstname = users[i].firstname;
  char *lastname = users[i].lastname;
  char *username = users[i].username;
  char *password = users[i].password;
  int admin = users[i].admin;
  fprintf(fp, "%s\t%s\t%s\t%s\t%d\t\n", firstname, lastname, username, password,
          admin);
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
