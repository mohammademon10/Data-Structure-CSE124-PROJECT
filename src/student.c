/**
 * @file student.c
 * @brief Student CRUD operations using a singly-linked list.
 *
 * Provides Add, Delete, Update, Search, Show, and Count functionality.
 * All user-facing functions include input validation via utils module.
 *
 * Course: CSE 124 - Data Structure Lab
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/student.h"
#include "../include/database.h"
#include "../include/utils.h"

/* ═══════════════════════════════════════════════════════════════════
 *  ADD OPERATIONS
 * ═══════════════════════════════════════════════════════════════════ */

/**
 * Append a student node to the end of the linked list.
 * Returns the (possibly new) head pointer.
 */
Node *addInfo(Node *head, stInfo info) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("\t\t\t\t[ERROR] Memory allocation failed!\n");
        return head;
    }
    newNode->info = info;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    /* Traverse to the last node */
    Node *tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = newNode;

    return head;
}

/**
 * Interactive function: prompts the user for all fields, validates input,
 * then adds the student to the list and saves to file.
 */
Node *addStudentInfo(Node *head) {
    stInfo info;

    printf("\t\t\t\t\tAdd Student Info\n");
    printf("\t\t\t\t===================================\n\n");

    /* ── Name ── */
    printf("\t\t\t\tEnter student name: ");
    fgets(info.name, sizeof(info.name), stdin);
    trimNewline(info.name);

    if (strlen(info.name) == 0) {
        printf("\t\t\t\t[ERROR] Name cannot be empty.\n");
        return head;
    }

    /* ── Student ID ── */
    printf("\t\t\t\tEnter student ID: ");
    fgets(info.id, sizeof(info.id), stdin);
    trimNewline(info.id);

    while (isDuplicateId(head, info.id)) {
        printf("\t\t\t\t[!] This student ID already exists. Enter a new ID: ");
        fgets(info.id, sizeof(info.id), stdin);
        trimNewline(info.id);
    }

    /* ── Email ── */
    printf("\t\t\t\tEnter DIU email: ");
    fgets(info.email, sizeof(info.email), stdin);
    trimNewline(info.email);

    while (!isValidEmail(info.email) || isDuplicateEmail(head, info.email)) {
        if (!isValidEmail(info.email)) {
            printf("\t\t\t\t[!] Invalid email. Must contain '@diu.edu.bd'. Try again: ");
        } else {
            printf("\t\t\t\t[!] This email is already registered. Enter a new email: ");
        }
        fgets(info.email, sizeof(info.email), stdin);
        trimNewline(info.email);
    }

    /* ── Blood Group ── */
    printf("\t\t\t\tEnter blood group (A+/A-/B+/B-/AB+/AB-/O+/O-): ");
    fgets(info.bg, sizeof(info.bg), stdin);
    trimNewline(info.bg);

    while (!isValidBloodGroup(info.bg)) {
        printf("\t\t\t\t[!] Invalid blood group. Valid: A+, A-, B+, B-, AB+, AB-, O+, O-\n");
        printf("\t\t\t\tEnter blood group: ");
        fgets(info.bg, sizeof(info.bg), stdin);
        trimNewline(info.bg);
    }

    /* ── Contact Number ── */
    printf("\t\t\t\tEnter contact number: ");
    fgets(info.cell, sizeof(info.cell), stdin);
    trimNewline(info.cell);

    while (!isValidContact(info.cell) || isDuplicateCell(head, info.cell)) {
        if (!isValidContact(info.cell)) {
            printf("\t\t\t\t[!] Invalid contact. Must be 7+ digits (digits, +, - only).\n");
            printf("\t\t\t\tEnter contact number: ");
        } else {
            printf("\t\t\t\t[!] This contact number is already registered. Enter a new one: ");
        }
        fgets(info.cell, sizeof(info.cell), stdin);
        trimNewline(info.cell);
    }

    /* ── Add to list and save ── */
    head = addInfo(head, info);
    save_to_file(head);

    printf("\n\t\t\t\t[SUCCESS] Student added to the database.\n");
    return head;
}

/* ═══════════════════════════════════════════════════════════════════
 *  DELETE OPERATIONS
 * ═══════════════════════════════════════════════════════════════════ */

/**
 * Delete a student record by ID.
 * Frees the node's memory and saves the updated list.
 */
Node *delete_student_info(Node *head) {
    char id[100];

    printf("\t\t\t\t\tDelete Student Info\n");
    printf("\t\t\t\t===================================\n\n");

    printf("\t\t\t\tEnter the student ID to remove: ");
    fgets(id, sizeof(id), stdin);
    trimNewline(id);

    Node *tmp = head, *prev = NULL;

    while (tmp != NULL && strcmp(tmp->info.id, id) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp == NULL) {
        printf("\n\t\t\t\t[!] Student with ID '%s' not found.\n", id);
        return head;
    }

    /* Show the student being deleted */
    printf("\n\t\t\t\tDeleting the following student:\n");
    student_details(tmp->info);

    if (prev == NULL) {
        head = head->next; /* Deleting the head node */
    } else {
        prev->next = tmp->next;
    }
    free(tmp);

    save_to_file(head);
    printf("\n\t\t\t\t[SUCCESS] Student record deleted from database.\n");
    return head;
}

/* ═══════════════════════════════════════════════════════════════════
 *  DISPLAY OPERATIONS
 * ═══════════════════════════════════════════════════════════════════ */

/**
 * Print a formatted display of a single student's information.
 */
void student_details(stInfo info) {
    printf("\n\t\t\t\t  +------------------------------------+\n");
    printf("\t\t\t\t  | Name    : %-25s|\n", info.name);
    printf("\t\t\t\t  | ID      : %-25s|\n", info.id);
    printf("\t\t\t\t  | Email   : %-25s|\n", info.email);
    printf("\t\t\t\t  | Blood   : %-25s|\n", info.bg);
    printf("\t\t\t\t  | Contact : %-25s|\n", info.cell);
    printf("\t\t\t\t  +------------------------------------+\n");
}

/**
 * Display all student records with serial numbers.
 */
void show_info(Node *head) {
    printf("\t\t\t\t\tAll Student Records\n");
    printf("\t\t\t\t===================================\n");

    if (head == NULL) {
        printf("\n\t\t\t\t[!] No student records found in the database.\n");
        return;
    }

    Node *temp = head;
    int serial = 1;

    while (temp != NULL) {
        printf("\n\t\t\t\t--- Student #%d ---", serial);
        student_details(temp->info);
        serial++;
        temp = temp->next;
    }

    printf("\n\t\t\t\tTotal: %d student(s)\n", serial - 1);
}

/* ═══════════════════════════════════════════════════════════════════
 *  COUNT OPERATION
 * ═══════════════════════════════════════════════════════════════════ */

/**
 * Count and return the total number of students in the linked list.
 */
int count_students(Node *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

/* ═══════════════════════════════════════════════════════════════════
 *  UPDATE OPERATIONS
 * ═══════════════════════════════════════════════════════════════════ */

/**
 * Update a student's information by ID.
 * For each field, pressing Enter without input keeps the current value.
 * Validates all updated fields (email, blood group, contact, ID).
 */
Node *update_student_info(Node *head) {
    char id[100];

    printf("\t\t\t\t\tUpdate Student Info\n");
    printf("\t\t\t\t===================================\n\n");

    printf("\t\t\t\tEnter student ID to update: ");
    fgets(id, sizeof(id), stdin);
    trimNewline(id);

    Node *student = search_student_by_id(head, id);

    if (student == NULL) {
        printf("\t\t\t\t[!] Student with ID '%s' not found.\n", id);
        return head;
    }

    printf("\n\t\t\t\tCurrent information:");
    student_details(student->info);
    printf("\n\t\t\t\t(Press Enter to keep the current value)\n\n");

    /* ── Update Name ── */
    printf("\t\t\t\tNew name: ");
    char newName[100];
    fgets(newName, sizeof(newName), stdin);
    if (newName[0] != '\n') {
        trimNewline(newName);
        strcpy(student->info.name, newName);
    }

    /* ── Update Email (with domain + duplicate validation) ── */
    printf("\t\t\t\tNew email: ");
    char newEmail[100];
    fgets(newEmail, sizeof(newEmail), stdin);
    if (newEmail[0] != '\n') {
        trimNewline(newEmail);

        /* Validate email domain */
        while (!isValidEmail(newEmail)) {
            printf("\t\t\t\t[!] Invalid email. Must contain '@diu.edu.bd'. Try again: ");
            fgets(newEmail, sizeof(newEmail), stdin);
            trimNewline(newEmail);
        }

        /* Check duplicate (excluding current student's own email) */
        Node *tmpNode = head;
        while (tmpNode != NULL) {
            if (tmpNode != student && strcmp(tmpNode->info.email, newEmail) == 0) {
                printf("\t\t\t\t[!] This email is already taken. Enter another: ");
                fgets(newEmail, sizeof(newEmail), stdin);
                trimNewline(newEmail);
                tmpNode = head; /* Restart check */
                continue;
            }
            tmpNode = tmpNode->next;
        }

        strcpy(student->info.email, newEmail);
    }

    /* ── Update Blood Group (with validation) ── */
    printf("\t\t\t\tNew blood group: ");
    char newBg[10];
    fgets(newBg, sizeof(newBg), stdin);
    if (newBg[0] != '\n') {
        trimNewline(newBg);
        while (!isValidBloodGroup(newBg)) {
            printf("\t\t\t\t[!] Invalid. Valid: A+, A-, B+, B-, AB+, AB-, O+, O-\n");
            printf("\t\t\t\tNew blood group: ");
            fgets(newBg, sizeof(newBg), stdin);
            trimNewline(newBg);
        }
        strcpy(student->info.bg, newBg);
    }

    /* ── Update Contact Number (with validation) ── */
    printf("\t\t\t\tNew contact number: ");
    char newCell[20];
    fgets(newCell, sizeof(newCell), stdin);
    if (newCell[0] != '\n') {
        trimNewline(newCell);
        while (!isValidContact(newCell)) {
            printf("\t\t\t\t[!] Invalid. Must be 7+ digits. Try again: ");
            fgets(newCell, sizeof(newCell), stdin);
            trimNewline(newCell);
        }
        /* Check duplicate */
        Node *tmpNode = head;
        int dup = 0;
        while (tmpNode != NULL) {
            if (tmpNode != student && strcmp(tmpNode->info.cell, newCell) == 0) {
                dup = 1;
                break;
            }
            tmpNode = tmpNode->next;
        }
        while (dup) {
            printf("\t\t\t\t[!] This contact is already taken. Enter another: ");
            fgets(newCell, sizeof(newCell), stdin);
            trimNewline(newCell);
            dup = 0;
            tmpNode = head;
            while (tmpNode != NULL) {
                if (tmpNode != student && strcmp(tmpNode->info.cell, newCell) == 0) {
                    dup = 1;
                    break;
                }
                tmpNode = tmpNode->next;
            }
        }
        strcpy(student->info.cell, newCell);
    }

    /* ── Update Student ID (with duplicate check) ── */
    printf("\t\t\t\tNew student ID: ");
    char newId[100];
    fgets(newId, sizeof(newId), stdin);
    if (newId[0] != '\n') {
        trimNewline(newId);
        Node *tmpNode = head;
        int dup = 0;
        while (tmpNode != NULL) {
            if (tmpNode != student && strcmp(tmpNode->info.id, newId) == 0) {
                dup = 1;
                break;
            }
            tmpNode = tmpNode->next;
        }
        while (dup) {
            printf("\t\t\t\t[!] This student ID already exists. Enter another: ");
            fgets(newId, sizeof(newId), stdin);
            trimNewline(newId);
            dup = 0;
            tmpNode = head;
            while (tmpNode != NULL) {
                if (tmpNode != student && strcmp(tmpNode->info.id, newId) == 0) {
                    dup = 1;
                    break;
                }
                tmpNode = tmpNode->next;
            }
        }
        strcpy(student->info.id, newId);
    }

    save_to_file(head);
    printf("\n\t\t\t\t[SUCCESS] Student record updated.\n");
    return head;
}

/* ═══════════════════════════════════════════════════════════════════
 *  SEARCH OPERATIONS
 * ═══════════════════════════════════════════════════════════════════ */

/**
 * Interactive: prompt for an ID and display the matching student.
 */
void search_student(Node *head) {
    char id[100];

    printf("\t\t\t\t\tSearch Student\n");
    printf("\t\t\t\t===================================\n\n");

    printf("\t\t\t\tEnter student ID to search: ");
    fgets(id, sizeof(id), stdin);
    trimNewline(id);

    Node *student = search_student_by_id(head, id);

    if (student == NULL) {
        printf("\n\t\t\t\t[!] Student with ID '%s' not found.\n", id);
    } else {
        printf("\n\t\t\t\tStudent found:");
        student_details(student->info);
    }
}

/**
 * Return the node with the matching student ID, or NULL if not found.
 */
Node *search_student_by_id(Node *head, char *id) {
    while (head != NULL) {
        if (strcmp(head->info.id, id) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

/* ═══════════════════════════════════════════════════════════════════
 *  MEMORY MANAGEMENT
 * ═══════════════════════════════════════════════════════════════════ */

/**
 * Free every node in the linked list to prevent memory leaks.
 * Should be called before program exit.
 */
void freeList(Node *head) {
    Node *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
