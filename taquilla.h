/*
 *  Pablo Ausin Roman
 *  Daniel Sanchez Louzan
 *  Marcos Cordeiro
 */
/*****************************************************************/
/***************** SISTEMAS OPERATIVOS 2019 **********************/
/*****************************************************************/

#ifndef _GESTION_H
#define _GESTION_H
#define N_MAX 5
#define T_MAX 10

#include<linux/sched.h> 

void calcular_tiempo(void);
int contar_procesos(void);
int buscar_reemplazo(int);
void anadir_proceso(struct task_struct *pcb);
void anadir_a_cola(struct task_struct *pcb);

#endif
