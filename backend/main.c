// Code Owner -> Emon -> Daffodil International Univers
// project Name: STUDENT DATABASE MANAGEMENT SYSTEM(Admin Pannel Use)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure Definitions
typedef struct studentInfo {
  char name[100];
  char id[100];
  char email[100];
  char bg[5];
  char cell[20];

} stInfo;

typedef struct Node {
  stInfo info;
  struct Node *next;
} Node;

Node *head = NULL;

// Function Prototypes
void welcome();
int main_menu();
Node *addInfo(Node *head, stInfo info);
Node *addStudentInfo(Node *head);
int isDuplicateEmail(Node *head, char *email);
int isDuplicateCell(Node *head, char *cell);
Node *delete_student_info(Node *head);
void student_details(stInfo info);
void show_info(Node *head);
int count_students(Node *head);

Node *update_student_info(Node *head);
void search_student(Node *head); // Separate search function prototype
Node *search_student_by_id(Node *head, char *id);

void save_to_file(Node *head);
Node *load_from_file(Node *head);

// Main Function
int main() {

  int choice;
  welcome();

  head = load_from_file(head); // Load student data from the file

  while (1) {
    system("color 3F"); // Changing terminal color.
    system("cls");

    choice = main_menu();

    switch (choice) {
    case 1:
      system("cls");
      head = addStudentInfo(head);
      break;
    case 2:
      system("cls");
      head = delete_student_info(head);
      break;
    case 3:
      system("cls");
      show_info(head);
      break;
    case 4:
      system("cls");
      printf("\t\t\t\tTotal number of students: %d\n", count_students(head));
      break;
    case 5: // Update option
      system("cls");
      head = update_student_info(head);
      break;
    case 6: // Search option
      system("cls");
      search_student(head);
      break;
    case 0:
      printf("\n\t\t\tExiting program. Goodbye!\n");
      exit(0);
    default:
      printf("\n\t\t\tInvalid choice! Please try again.\n");
      break;
    }
    printf("\n\t\t\tPress Enter to return to main menu\n");
    getchar(); // Wait for user input
  }

  return 0;
}

void welcome() {
  system("color 1F"); // Navy blue background with white text
  system("cls");      // Clear the screen//
  printf("\n\n\n\n\t\t\t\tWelcome To The Daffodil International University "
         "Student Database Management System Program\n\n\t\t\t\t\t             "
         "        ");
  system("pause"); // Wait for user input

  system("cls");
  printf("\n\t\t\t\t\t\tACKNOWLEDGEMENT\n");
  printf("\t\t\t\t\t\t---------------\n");
  printf("\nWe are grateful to our respectable Ms. Faria Nishat Khan(Ma'am), "
         "whose insightful leadership and knowledge benefited us to complete "
         "this project successfully.\nWe are thankful to her for his "
         "continuous support and presence whenever needed.\n\n");
  printf("We would also like to extend our sincere thanks to all the team "
         "members, who tirelessly & dedicatedly works for the completion of "
         "the programs.\n\n");
  printf("\t\t\t\t\t\tThank You so much!\n\n\t\t\t\t\t   ");
  system("pause");

  system("cls"); //
  printf("\n\t\t\t\t\t\t     TEAM MEMBERS\n");
  printf("\t\t\t\t\t\t     ------------\n");

  printf("\t\t\t\t\t  ___________________________________\n");
  printf("\t\t\t\t\t |  ID NO.            NAME           |\n");
  printf("\t\t\t\t\t |-----------------------------------|\n");
  printf("\t\t\t\t\t |  232-15-818       MD. Emon Hossain|\n");
  printf("\t\t\t\t\t |-----------------------------------|\n");
  printf("\t\t\t\t\t |  241-15-196    Tousiq imdad Mehedi|\n");
  printf("\t\t\t\t\t |-----------------------------------|\n");
  printf("\t\t\t\t\t |  241-15-860       Nabila Hossain  |\n");
  printf("\t\t\t\t\t |-----------------------------------|\n");
  printf("\t\t\t\t\t |  241-15-106       Sakin Bin Jabed |\n");
  printf("\t\t\t\t\t |-----------------------------------|\n");
  printf("\t\t\t\t\t |  241-15-095       NaZmus Shakib   |\n");
  printf("\t\t\t\t\t |___________________________________|\n\n");
  printf("\t\t\t\t\t   ");
  system("pause");
}

// Function to Display the Main Menu
int main_menu() {
  int choice;
  printf("\t\t\t\t\t\t\t\t\tMain Menu\n");
  printf("\t\t\t\t\t\t\t\t-------------------------\n");
  printf("\t\t\t\t\t\t\t\t1. Add student info\n");
  printf("\t\t\t\t\t\t\t\t2. Remove student info\n");
  printf("\t\t\t\t\t\t\t\t3. Show student info\n");
  printf("\t\t\t\t\t\t\t\t4. Count Students\n");
  printf("\t\t\t\t\t\t\t\t5. Update student info\n");
  printf("\t\t\t\t\t\t\t\t6. Search student by ID\n");
  printf("\t\t\t\t\t\t\t\t0. Exit\n\n");

  printf("\t\t\t\t\t\t\t\tEnter your choice: ");
  scanf("%d", &choice);
  getchar();
  return choice;
}

// part-01

// Function to Add Student Info with Validation
Node *addStudentInfo(Node *head) {
  stInfo info;
  printf("\t\t\t\t\tAdd Info\n");
  printf("\t\t\t\t-------------------------\n");

  printf("\t\t\t\tEnter your name: ");
  fgets(info.name, sizeof(info.name), stdin);
  info.name[strcspn(info.name, "\n")] = NULL;

  printf("\t\t\t\tEnter your ID: ");
  fgets(info.id, sizeof(info.id), stdin);
  info.id[strcspn(info.id, "\n")] = NULL;

  while (head != NULL) {
    Node *tmp = head;
    int dup = 0;
    while (tmp != NULL) {
      if (strcmp(tmp->info.id, info.id) == 0) {
        dup = 1;
        break;
      }
      tmp = tmp->next;
    }
    if (dup) {
      printf("\t\t\t\tThis student ID is already taken. Enter a new ID: ");
      fgets(info.id, sizeof(info.id), stdin);
      info.id[strcspn(info.id, "\n")] = '\0';
    } else {
      break;
    }
  }

  printf("\t\t\t\tEnter your email: ");
  fgets(info.email, sizeof(info.email), stdin);
  info.email[strcspn(info.email, "\n")] = '\0';

  char validDomain[] = "@diu.edu.bd";
  while (strstr(info.email, validDomain) == NULL ||
         isDuplicateEmail(head, info.email)) {
    if (strstr(info.email, validDomain) == NULL) {
      printf(
          "\t\t\t\tInvalid email! Must contain '@diu.edu.bd'. Enter again: ");
    } else {
      printf("\t\t\t\tThis email is already taken. Enter a new email: ");
    }
    fgets(info.email, sizeof(info.email), stdin);
    info.email[strcspn(info.email, "\n")] = '\0';
  }

  printf("\t\t\t\tEnter your blood group: ");
  fgets(info.bg, sizeof(info.bg), stdin);
  info.bg[strcspn(info.bg, "\n")] = '\0';

  printf("\t\t\t\tEnter your contact number: ");
  fgets(info.cell, sizeof(info.cell), stdin);
  info.cell[strcspn(info.cell, "\n")] = '\0';

  while (isDuplicateCell(head, info.cell)) {
    printf(
        "\t\t\t\tThis contact number is already taken. Enter a new number: ");
    fgets(info.cell, sizeof(info.cell), stdin);
    info.cell[strcspn(info.cell, "\n")] = '\0';
  }

  head = addInfo(head, info);

  save_to_file(head); // Save the updated student list to file

  printf("\n\t\t\t\tStudent Added Successfully Into The Database\n");
  return head;
}

// Function to Check for Duplicate Email
int isDuplicateEmail(Node *head, char *email) {
  while (head != NULL) {
    if (strcmp(head->info.email, email) == 0)
      return 1;
    head = head->next;
  }
  return 0;
}

// Function to Check for Duplicate Cell Number
int isDuplicateCell(Node *head, char *cell) {
  while (head != NULL) {
    if (strcmp(head->info.cell, cell) == 0)
      return 1;
    head = head->next;
  }
  return 0;
}
// Function to Add Student Information to the Linked List
Node *addInfo(Node *head, stInfo info) {
  Node *newInfo = (Node *)malloc(sizeof(Node));
  newInfo->info = info;
  newInfo->next = NULL;

  if (head == NULL) {
    return newInfo;
  } else {
    Node *tmp = head;
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = newInfo;
  }
  return head;
}

// part-02
//  Function to Delete Student Info
Node *delete_student_info(Node *head) {
  char id[100];
  printf("\t\t\t\t\tDelete Info\n");
  printf("\t\t\t\t-------------------------\n");
  printf("\t\t\t\tEnter the ID of the student you want to remove: ");
  fgets(id, sizeof(id), stdin);
  id[strcspn(id, "\n")] = '\0';

  Node *tmp = head, *prev = NULL;

  while (tmp != NULL && strcmp(tmp->info.id, id) != 0) {
    prev = tmp;
    tmp = tmp->next;
  }

  if (tmp == NULL) {
    printf("\n\t\t\t\tStudent not found\n");
    return head;
  }

  if (prev == NULL) {
    head = head->next;
  } else {
    prev->next = tmp->next;
  }
  free(tmp);

  save_to_file(head); // Save the updated student list to file

  printf("\t\t\t\tRecord deleted from database\n");
  return head;
}

// part-03
//  Function to Display Student Details
void student_details(stInfo info) {
  printf("\n\t\t\t\tName: %s\n", info.name);
  printf("\t\t\t\tID: %s\n", info.id);
  printf("\t\t\t\tEmail: %s\n", info.email);
  printf("\t\t\t\tBlood Group: %s\n", info.bg);
  printf("\t\t\t\tContact Information: %s\n", info.cell);
}

// Function to Show All Student Info
void show_info(Node *head) {
  printf("\t\t\t\tShow Info\n");
  printf("\t\t\t\t-------------------------\n");
  if (head == NULL) {
    printf("\t\t\t\tNo student information found.\n");
    return;
  }

  Node *temp = head;
  int serial = 1; // Initialize serial number

  while (temp != NULL) {
    // Display serial number along with student details
    printf("\t\t\t\tStudent %d\n", serial);
    student_details(temp->info);
    serial++; // Increment serial number
    temp = temp->next;
  }
}

// part-04
//  Function to Count Students
int count_students(Node *head) {
  int count = 0;
  while (head != NULL) {
    count++;
    head = head->next;
  }
  return count;
}

// part-05

Node *update_student_info(Node *head) {
  char id[100];
  printf("\t\t\t\t\tUpdate Info\n");
  printf("\t\t\t\t-------------------------\n");

  printf("\t\t\t\tEnter student ID to update: ");
  fgets(id, sizeof(id), stdin);
  id[strcspn(id, "\n")] = '\0';

  Node *student = search_student_by_id(head, id);

  if (student == NULL) {
    printf("\t\t\t\tStudent with ID %s not found.\n", id);
    return head;
  }

  printf("\n\t\t\t\tUpdating information for student %s:\n",
         student->info.name);

  // Update Name
  printf("\t\t\t\tEnter new name (or press Enter to keep current): ");
  char newName[100];
  fgets(newName, sizeof(newName), stdin);
  if (newName[0] != '\n') { // Check if the user entered something
    newName[strcspn(newName, "\n")] = '\0';
    strcpy(student->info.name, newName);
  }

  // Update Email
  printf("\t\t\t\tEnter new email (or press Enter to keep current): ");
  char newEmail[100];
  fgets(newEmail, sizeof(newEmail), stdin);
  if (newEmail[0] != '\n') {
    newEmail[strcspn(newEmail, "\n")] = '\0';
    while (isDuplicateEmail(head, newEmail)) {
      printf("\t\t\t\tThis email is already taken. Enter a new email: ");
      fgets(newEmail, sizeof(newEmail), stdin);
      newEmail[strcspn(newEmail, "\n")] = '\0';
    }
    strcpy(student->info.email, newEmail);
  }

  // Update Blood Group
  printf("\t\t\t\tEnter new blood group (or press Enter to keep current): ");
  char newBg[5];
  fgets(newBg, sizeof(newBg), stdin);
  if (newBg[0] != '\n') {
    newBg[strcspn(newBg, "\n")] = '\0';
    strcpy(student->info.bg, newBg);
  }

  // Update Contact Number
  printf("\t\t\t\tEnter new contact number (or press Enter to keep current): ");
  char newCell[20];
  fgets(newCell, sizeof(newCell), stdin);
  if (newCell[0] != '\n') {
    newCell[strcspn(newCell, "\n")] = '\0';
    while (isDuplicateCell(head, newCell)) {
      printf(
          "\t\t\t\tThis contact number is already taken. Enter a new number: ");
      fgets(newCell, sizeof(newCell), stdin);
      newCell[strcspn(newCell, "\n")] = '\0';
    }
    strcpy(student->info.cell, newCell);
  }

  // Update ID
  printf("\t\t\t\tEnter new ID (or press Enter to keep current): ");
  char newId[100];
  fgets(newId, sizeof(newId), stdin);
  if (newId[0] != '\n') {
    newId[strcspn(newId, "\n")] = '\0';
    Node *tmp = head;
    int dup = 0;
    while (tmp != NULL) {
      if (tmp != student && strcmp(tmp->info.id, newId) == 0) {
        dup = 1;
        break;
      }
      tmp = tmp->next;
    }
    while (dup) {
      printf("\t\t\t\tThis student ID is already taken. Enter a new ID: ");
      fgets(newId, sizeof(newId), stdin);
      newId[strcspn(newId, "\n")] = '\0';
      dup = 0;
      tmp = head;
      while (tmp != NULL) {
        if (tmp != student && strcmp(tmp->info.id, newId) == 0) {
          dup = 1;
          break;
        }
        tmp = tmp->next;
      }
    }
    strcpy(student->info.id, newId);
  }

  save_to_file(head); // Save changes
  printf("\t\t\t\tStudent record updated successfully!\n");

  return head;
}

void search_student(Node *head) {
  char id[100];
  printf("\t\t\t\t\tSearch Info\n");
  printf("\t\t\t\t-------------------------\n");

  printf("\t\t\t\tEnter student ID to search: ");
  fgets(id, sizeof(id), stdin);
  id[strcspn(id, "\n")] = '\0';

  Node *student = search_student_by_id(head, id);

  if (student == NULL) {
    printf("\t\t\t\tStudent with ID %s not found.\n", id);
  } else {
    student_details(student->info);
  }
}

Node *search_student_by_id(Node *head, char *id) {
  while (head != NULL) {
    if (strcmp(head->info.id, id) == 0) {
      return head;
    }
    head = head->next;
  }
  return NULL;
}

void save_to_file(Node *head) {
  FILE *file = fopen("data/students.txt", "w");
  if (file == NULL) {
    printf("\t\t\t\tFailed to open file for writing.\n");
    return;
  }

  Node *temp = head;
  while (temp != NULL) {
    fprintf(file, "%s,%s,%s,%s,%s\n", temp->info.name, temp->info.id,
            temp->info.email, temp->info.bg, temp->info.cell);
    temp = temp->next;
  }

  fclose(file);
  printf("\t\t\t\tData saved successfully.\n");
}

Node *load_from_file(Node *head) {
  FILE *file = fopen("data/students.txt", "r");
  if (file == NULL) {
    printf("\t\t\t\tNo data file found. Starting with an empty list.\n");
    return head;
  }

  stInfo info;
  while (fscanf(file, "%99[^,],%99[^,],%99[^,],%4[^,],%19[^\n]\n", info.name,
                info.id, info.email, info.bg, info.cell) == 5) {
    head = addInfo(head, info);
  }

  fclose(file);
  return head;
}
"this code bassi"