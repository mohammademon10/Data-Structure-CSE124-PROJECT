/**
 * @file utils.h
 * @brief Input validation and utility function prototypes.
 *
 * Course: CSE 124 - Data Structure Lab
 * Project: Student Database Management System
 * Institution: Daffodil International University
 */

#ifndef UTILS_H
#define UTILS_H

#include "student.h"

/* ──────────────────────── Duplicate Checks ──────────────────────── */

/** Return 1 if the email already exists in the list, 0 otherwise. */
int isDuplicateEmail(Node *head, char *email);

/** Return 1 if the cell number already exists in the list, 0 otherwise. */
int isDuplicateCell(Node *head, char *cell);

/** Return 1 if the student ID already exists in the list, 0 otherwise. */
int isDuplicateId(Node *head, char *id);

/* ──────────────────────── Format Validation ──────────────────────── */

/** Return 1 if the email contains '@diu.edu.bd', 0 otherwise. */
int isValidEmail(char *email);

/** Return 1 if bg matches a known blood group, 0 otherwise. */
int isValidBloodGroup(char *bg);

/** Return 1 if the contact number contains only digits and '+'. */
int isValidContact(char *cell);

/* ──────────────────────── Safe Input ──────────────────────── */

/**
 * Read an integer menu choice safely using fgets + sscanf.
 * Returns -1 on invalid input instead of leaving garbage.
 */
int getValidMenuChoice(void);

/** Trim trailing newline from a string read by fgets. */
void trimNewline(char *str);

#endif /* UTILS_H */
