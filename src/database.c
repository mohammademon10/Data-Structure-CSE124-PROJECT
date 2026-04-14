/**
 * @file database.c
 * @brief File I/O operations for persistent student data storage.
 *
 * Saves and loads student records in CSV format to/from data/students.txt.
 *
 * Course: CSE 124 - Data Structure Lab
 */

#include <stdio.h>
#include <string.h>

#include "../include/database.h"

/* Data file path — relative to where the executable runs */
#define DATA_FILE "data/students.txt"

/* ──────────────────────── Save to File ──────────────────────── */

/**
 * Write every student record from the linked list to the data file.
 * Overwrites the existing file content each time.
 *
 * CSV Format: name,id,email,bloodGroup,contactNumber
 */
void save_to_file(Node *head) {
    FILE *file = fopen(DATA_FILE, "w");
    if (file == NULL) {
        printf("\n\t\t\t\t[ERROR] Failed to open file for writing.\n");
        printf("\t\t\t\tMake sure the 'data/' directory exists.\n");
        return;
    }

    Node *temp = head;
    while (temp != NULL) {
        fprintf(file, "%s,%s,%s,%s,%s\n",
                temp->info.name,
                temp->info.id,
                temp->info.email,
                temp->info.bg,
                temp->info.cell);
        temp = temp->next;
    }

    fclose(file);
    printf("\t\t\t\tData saved successfully.\n");
}

/* ──────────────────────── Load from File ──────────────────────── */

/**
 * Read student records from the data file and rebuild the linked list.
 *
 * Uses fscanf with field-width limiters to prevent buffer overflows:
 *   - %99[^,]  → reads up to 99 chars, stops at comma
 *   - %9[^,]   → reads up to 9 chars for blood group
 *   - %19[^\n] → reads up to 19 chars for contact
 */
Node *load_from_file(Node *head) {
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("\t\t\t\tNo data file found. Starting with an empty database.\n");
        return head;
    }

    stInfo info;
    int count = 0;

    while (fscanf(file, "%99[^,],%99[^,],%99[^,],%9[^,],%19[^\n]\n",
                  info.name, info.id, info.email, info.bg, info.cell) == 5) {
        head = addInfo(head, info);
        count++;
    }

    fclose(file);

    if (count > 0)
        printf("\t\t\t\tLoaded %d student record(s) from database.\n", count);

    return head;
}
