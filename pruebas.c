/*
 *  Pablo Ausin Roman
 *  Daniel Sanchez Louzan
 *  Marcos Cordeiro
 */
/*****************************************************************/
/***************** SISTEMAS OPERATIVOS 2019 **********************/
/*****************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>

extern int pruebaanadirOnetoOne(int position[], int NumP, int Nsleep);

const char *NamesProcess[6] = {"largo", "consulta", "reserva", "anulacion", "pago", "administracion"};

int main(int argc, char *argv[])
{

	int num_prueba;
	num_prueba = atoi(argv[1]);
	struct sched_param nodo;
	nodo.sched_priority = 99;
	if (sched_setscheduler(0, SCHED_FIFO, &nodo) != 0)
		printf("Error al asignar prioridad a pruebas\n");

	switch (num_prueba)
	{

	case 1:
	{
		int procesos[4] = {4, 4, 4, 4};
		printf(" PRUEBA 1\n Inicialmente con el sistema vacio\n Añadimos 4 procesos de PAGO\n");
		sleep(3);
		pruebaanadirOnetoOne(procesos, 3, 2);
		break;
	}

	case 2:
	{
		int procesos[4] = {2, 2, 2, 2};
		printf(" PRUEBA 2\n Inicialmente con el sistema vacio\n Añadimos 4 procesos de RESERVAS\n");
		sleep(3);
		pruebaanadirOnetoOne(procesos, 4, 2);
		break;
	}

	case 3:
	{
		int procesos[5] = {5, 4, 3, 2, 1};
		printf(" PRUEBA 3\n Inicialmente con el sistema vacio\n Añadimos 5 procesos: ADMINISTRACION, PAGO, ANULACION, RESERVA, CONSULTA\n");
		sleep(5);
		pruebaanadirOnetoOne(procesos, 4, 2);
		break;
	}

	case 4:
	{
		int procesos[5] = {1, 4, 4, 5, 4};
		printf(" PRUEBA 4\n Inicialmente con el sistema vacio\n Añadimos 5 procesos: CONSULTAS, PAGOS PAGOS, ADMINISTRACION, PAGOS\n");
		sleep(5);
		pruebaanadirOnetoOne(procesos, 4, 2);
		break;
	}

	case 5:
	{
		int procesos[4] = {1, 1, 1, 1};
		printf(" PRUEBA 5\n Inicialmente con el sistema vacio\n Añadimos 4 procesos de CONSULTAS\n");
		sleep(5);
		pruebaanadirOnetoOne(procesos, 3, 2);
		break;
	}

	case 6:
	{
		int procesos[4] = {3, 3, 3, 3, 3, 3};
		printf(" PRUEBA 6\n Inicialmente, el sistema lleno de procesos ANULACION\n Añadimos uno con la MISMA prioridad\n");
		sleep(5);
		pruebaanadirOnetoOne(procesos, 5, 2);
		break;
	}

	case 7:
	{
		int procesos[4] = {4, 4, 4, 4, 4, 5};
		printf(" PRUEBA 7\n Inicialmente, el sistema lleno de procesos PAGOS\n Añadimos uno con MAYOR prioridad, ADMINISTRACION\n");
		sleep(5);
		pruebaanadirOnetoOne(procesos, 5, 2);
		break;
	}

	case 8:
	{
		int procesos[6] = {5, 5, 5, 5, 5, 3};
		printf(" PRUEBA 8\n Inicialmente, el sistema lleno de procesos ADMINISTRACION\n Añadimos uno con MENOR prioridad, ANULACION\n");
		sleep(5);
		pruebaanadirOnetoOne(procesos, 5, 2);
		break;
	}

	case 9:
	{
		int procesos[6] = {4, 4, 4, 4, 4, 3};
		printf(" PRUEBA 9\n Inicialmente, el sistema lleno de PAGOS \n Añadimos uno con MENOR prioridad, ANULACION\n");
		sleep(5);
		pruebaanadirOnetoOne(procesos, 5, 2);
		break;
	}

	case 10:
	{
		int procesos[4] = {1, 1, 1, 5};
		printf(" PRUEBA 10\n Inicialmente con el sistema vacio \n Añadimos 3 de CONSULTAS y 1 de ADMINISTRACION\n");
		sleep(5);
		pruebaanadirOnetoOne(procesos, 3, 2);
		break;
	}

	case 11:
	{
		int procesos[3] = {5, 4, 3};
		printf(" PRUEBA 11\n Inicialmente con el sistema vacio \n Añadimos 3 procesos: ADMINISTRACION, PAGOS, ANULACIONES\n");
		sleep(5);
		pruebaanadirOnetoOne(procesos, 2, 4);
		break;
	}
	case 12:
	{
		int position[1] = {0};
		printf(" PRUEBA 12\n Inicialmente con el sistema vacio \n Añadimos un proceso que dure mas de 10 segundos\n");
		sleep(5);
		pruebaanadirOnetoOne(position, 0, 0);
		break;
	}

	default:
		printf("Selecciona una prueba al invocar\n");
		break;
	}
	printf("Acaba la prueba\n");
	return 0;
}

int pruebaanadirOnetoOne(int position[], int NumP, int Nsleep)
{
	int i;
	pid_t PID;
	for (i = 0; i < NumP; i++)
	{
		PID = fork();

		switch (PID)
		{
		case -1:
			printf("Error al crear el proceso hijo\n");
			exit(1);
			break;
		case 0:
			execl(NamesProcess[position[i]], NULL);
			break;
		default:
			break;
		}
	}

	PID = fork();

	switch (PID)
	{
	case -1:
		printf("Error al crear el proceso hijo\n");
		exit(1);
		break;
	case 0:
		sleep(Nsleep);
		execl(NamesProcess[position[NumP]], NULL);
		break;
	default:
		break;
	}
	while ((PID = wait(NULL)) > 0)
	{
	}

	return 0;
}
