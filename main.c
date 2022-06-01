/**
 * @file main.c
 * @author Bernardo Neves (a23494@alunos.ipca.pt)
 * @brief calls the main menu
 * @date 2022-06-01
 */
#include <stdio.h>
#include <stdlib.h>
#include "headers/menus.h"

/**
 * @brief calls the main menu
 * @return void
 */
void main()
{
    FILE *ProcessPlan;
    system("cls");
    mainMenu(ProcessPlan);
}
