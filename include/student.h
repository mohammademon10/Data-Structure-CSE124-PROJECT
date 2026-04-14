/**
 * @file student.h
 * @brief Student data structure definitions and CRUD function prototypes.
 *
 * Course: CSE 124 - Data Structure Lab
 * Project: Student Database Management System
 * Institution: Daffodil International University
 */

#ifndef STUDENT_H
#define STUDENT_H

/* ──────────────────────── Structure Definitions ──────────────────────── */

/**
 * @brief Holds all information about a single student.
 */
typedef struct studentInfo {
    char name[100];
    char id[100];
    char email[100];
    char bg[10];   /* Blood group — increased from 5 to 10 for safety */
    char cell[20]; /* Contact number */
} stInfo;

/**
 * @brief Singly-linked list node wrapping a student record.
 */
typedef struct Node {
    stInfo info;
    struct Node *next;
} Node;

/* ──────────────────────── CRUD Function Prototypes ──────────────────── */

/** Append a student record to the linked list. */
Node *addInfo(Node *head, stInfo info);

/** Interactive: prompt the user and add a new student. */
Node *addStudentInfo(Node *head);

/** Interactive: delete a student by ID. */
Node *delete_student_info(Node *head);

/** Interactive: update a student's fields by ID. */
Node *update_student_info(Node *head);

/** Print a single student's details. */
void student_details(stInfo info);

/** Display all students in the linked list. */
void show_info(Node *head);

/** Return the total number of students. */
int count_students(Node *head);

/** Interactive: search and display a student by ID. */
void search_student(Node *head);

/** Return the node matching the given ID, or NULL. */
Node *search_student_by_id(Node *head, char *id);

/** Free every node in the linked list. */
void freeList(Node *head);

#endif /* STUDENT_H */
