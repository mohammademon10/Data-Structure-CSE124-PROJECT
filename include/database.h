/**
 * @file database.h
 * @brief File I/O function prototypes for persistent storage.
 *
 * Course: CSE 124 - Data Structure Lab
 * Project: Student Database Management System
 * Institution: Daffodil International University
 */

#ifndef DATABASE_H
#define DATABASE_H

#include "student.h"

/** Save the entire linked list to data/students.txt (CSV format). */
void save_to_file(Node *head);

/** Load student records from data/students.txt into the linked list. */
Node *load_from_file(Node *head);

#endif /* DATABASE_H */
