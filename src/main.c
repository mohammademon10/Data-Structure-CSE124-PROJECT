/**
 * @file main.c
 * @brief Entry point for the Student Database Management System.
 *
 * This file contains only the main loop and program initialization.
 * All business logic is separated into dedicated modules.
 *
 * Course: CSE 124 - Data Structure Lab
 * Project: Student Database Management System
 * Institution: Daffodil International University
 *
 * Team:
 *   MD. Emon Hossain    (232-15-818) — Team Leader
 *   MD. Toushiq Imdad   (241-15-196)
 *   Sakin Bin Jabed      (241-15-106)
 *   Nazmus Sakib         (241-15-095)
 *   Nabila Hossain       (241-15-860)
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/student.h"
#include "../include/database.h"
#include "../include/utils.h"
#include "../include/menu.h"

/* ──────────────────────── Main Function ──────────────────────── */

int main(void) {
    Node *head = NULL; /* Head of the student linked list */
    int choice;

    welcome(); /* Display splash screen */

    head = load_from_file(head); /* Load persisted data */

    while (1) {
#ifdef _WIN32
        system("color 3F"); /* Cyan background with white text (Windows) */
        system("cls");
#else
        system("clear");
#endif

        choice = main_menu();

        switch (choice) {
            case 1:
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                head = addStudentInfo(head);
                break;

            case 2:
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                head = delete_student_info(head);
                break;

            case 3:
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                show_info(head);
                break;

            case 4:
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                printf("\n\t\t\t\tTotal number of students: %d\n",
                       count_students(head));
                break;

            case 5:
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                head = update_student_info(head);
                break;

            case 6:
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                search_student(head);
                break;

            case 0:
                printf("\n\t\t\tExiting program. Goodbye!\n");
                save_to_file(head); /* Final save before quit */
                freeList(head);     /* Free all allocated memory */
                return 0;

            default:
                printf("\n\t\t\tInvalid choice! Please try again.\n");
                break;
        }

        printf("\n\t\t\tPress Enter to return to main menu...\n");
        getchar(); /* Wait for user input */
    }

    return 0;
}
