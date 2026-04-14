/**
 * @file utils.c
 * @brief Input validation and utility functions.
 *
 * Provides duplicate detection, format validation, and safe input
 * handling to prevent crashes from invalid user input.
 *
 * Course: CSE 124 - Data Structure Lab
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/utils.h"

/* ──────────────────────── String Helpers ──────────────────────── */

/**
 * Remove trailing newline character left by fgets().
 */
void trimNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

/* ──────────────────────── Duplicate Checks ──────────────────────── */

int isDuplicateEmail(Node *head, char *email) {
    while (head != NULL) {
        if (strcmp(head->info.email, email) == 0)
            return 1;
        head = head->next;
    }
    return 0;
}

int isDuplicateCell(Node *head, char *cell) {
    while (head != NULL) {
        if (strcmp(head->info.cell, cell) == 0)
            return 1;
        head = head->next;
    }
    return 0;
}

int isDuplicateId(Node *head, char *id) {
    while (head != NULL) {
        if (strcmp(head->info.id, id) == 0)
            return 1;
        head = head->next;
    }
    return 0;
}

/* ──────────────────────── Format Validation ──────────────────────── */

/**
 * Validate that the email contains the institutional domain.
 */
int isValidEmail(char *email) {
    const char *validDomain = "@diu.edu.bd";
    return (strstr(email, validDomain) != NULL);
}

/**
 * Validate blood group against known types.
 * Accepts: A+, A-, B+, B-, AB+, AB-, O+, O-
 */
int isValidBloodGroup(char *bg) {
    const char *validGroups[] = {
        "A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"
    };
    int count = sizeof(validGroups) / sizeof(validGroups[0]);

    for (int i = 0; i < count; i++) {
        if (strcmp(bg, validGroups[i]) == 0)
            return 1;
    }
    return 0;
}

/**
 * Validate that a contact number contains only digits, '+', and '-'.
 * Must be at least 7 characters long.
 */
int isValidContact(char *cell) {
    int len = (int)strlen(cell);
    if (len < 7) return 0; /* Too short for a valid phone number */

    for (int i = 0; i < len; i++) {
        if (!isdigit((unsigned char)cell[i]) && cell[i] != '+' && cell[i] != '-')
            return 0;
    }
    return 1;
}

/* ──────────────────────── Safe Input ──────────────────────── */

/**
 * Read a menu choice safely using fgets + sscanf.
 * Returns -1 if the user types non-numeric input, preventing the
 * infinite loop that raw scanf("%d") would cause.
 */
int getValidMenuChoice(void) {
    char buffer[32];
    int choice;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return -1;

    if (sscanf(buffer, "%d", &choice) != 1)
        return -1;

    return choice;
}
