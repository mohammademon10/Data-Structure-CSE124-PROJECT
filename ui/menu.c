/**
 * @file menu.c
 * @brief Console UI — welcome screen, acknowledgement, team display, and main menu.
 *
 * Separated from main.c to follow the Separation of Concerns principle.
 *
 * Course: CSE 124 - Data Structure Lab
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/menu.h"
#include "../include/utils.h"

/* ──────────────────────── Welcome Screen ──────────────────────── */

void welcome(void) {
#ifdef _WIN32
    system("color 1F"); /* Navy blue background with white text */
    system("cls");
#else
    system("clear");
#endif

    printf("\n\n\n");
    printf("\t\t\t╔═══════════════════════════════════════════════════════════════╗\n");
    printf("\t\t\t║                                                             ║\n");
    printf("\t\t\t║       STUDENT DATABASE MANAGEMENT SYSTEM                    ║\n");
    printf("\t\t\t║       Daffodil International University                     ║\n");
    printf("\t\t\t║                                                             ║\n");
    printf("\t\t\t║       Course: CSE 124 - Data Structure Lab                  ║\n");
    printf("\t\t\t║                                                             ║\n");
    printf("\t\t\t╚═══════════════════════════════════════════════════════════════╝\n\n");
    printf("\t\t\t\t\t   ");

#ifdef _WIN32
    system("pause");
    system("cls");
#else
    printf("Press Enter to continue...\n");
    getchar();
    system("clear");
#endif

    /* ── Acknowledgement ── */
    printf("\n\t\t\t\t\t  ACKNOWLEDGEMENT\n");
    printf("\t\t\t\t\t  ===============\n\n");
    printf("\tWe are grateful to our respectable Ms. Faria Nishat Khan (Ma'am),\n");
    printf("\twhose insightful leadership and knowledge benefited us to complete\n");
    printf("\tthis project successfully.\n\n");
    printf("\tWe are thankful to her for her continuous support and presence\n");
    printf("\twhenever needed.\n\n");
    printf("\tWe would also like to extend our sincere thanks to all the team\n");
    printf("\tmembers, who tirelessly & dedicatedly worked for the completion\n");
    printf("\tof this project.\n\n");
    printf("\t\t\t\t\t  Thank You!\n\n\t\t\t\t\t   ");

#ifdef _WIN32
    system("pause");
    system("cls");
#else
    printf("Press Enter to continue...\n");
    getchar();
    system("clear");
#endif

    /* ── Team Members ── */
    printf("\n\t\t\t\t\t     TEAM MEMBERS\n");
    printf("\t\t\t\t\t     ============\n\n");
    printf("\t\t\t\t  ╔═══════════════╦══════════════════════════╗\n");
    printf("\t\t\t\t  ║  Student ID   ║  Name                    ║\n");
    printf("\t\t\t\t  ╠═══════════════╬══════════════════════════╣\n");
    printf("\t\t\t\t  ║  232-15-818   ║  MD. Emon Hossain  (TL)  ║\n");
    printf("\t\t\t\t  ╠═══════════════╬══════════════════════════╣\n");
    printf("\t\t\t\t  ║  241-15-196   ║  MD. Toushiq Imdad       ║\n");
    printf("\t\t\t\t  ╠═══════════════╬══════════════════════════╣\n");
    printf("\t\t\t\t  ║  241-15-106   ║  Sakin Bin Jabed          ║\n");
    printf("\t\t\t\t  ╠═══════════════╬══════════════════════════╣\n");
    printf("\t\t\t\t  ║  241-15-095   ║  Nazmus Sakib             ║\n");
    printf("\t\t\t\t  ╠═══════════════╬══════════════════════════╣\n");
    printf("\t\t\t\t  ║  241-15-860   ║  Nabila Hossain           ║\n");
    printf("\t\t\t\t  ╚═══════════════╩══════════════════════════╝\n\n");
    printf("\t\t\t\t\t   ");

#ifdef _WIN32
    system("pause");
#else
    printf("Press Enter to continue...\n");
    getchar();
#endif
}

/* ──────────────────────── Main Menu ──────────────────────── */

int main_menu(void) {
    printf("\n");
    printf("\t\t\t\t  ╔═════════════════════════════════════╗\n");
    printf("\t\t\t\t  ║           MAIN MENU                 ║\n");
    printf("\t\t\t\t  ╠═════════════════════════════════════╣\n");
    printf("\t\t\t\t  ║  1. Add Student Info                ║\n");
    printf("\t\t\t\t  ║  2. Remove Student Info             ║\n");
    printf("\t\t\t\t  ║  3. Show All Students               ║\n");
    printf("\t\t\t\t  ║  4. Count Students                  ║\n");
    printf("\t\t\t\t  ║  5. Update Student Info             ║\n");
    printf("\t\t\t\t  ║  6. Search Student by ID            ║\n");
    printf("\t\t\t\t  ║  0. Exit                            ║\n");
    printf("\t\t\t\t  ╚═════════════════════════════════════╝\n\n");

    printf("\t\t\t\t  Enter your choice: ");
    return getValidMenuChoice();
}
