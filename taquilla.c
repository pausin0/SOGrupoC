/*
 *  Pablo Ausin Roman
 *  Daniel Sanchez Louzan
 *  Marcos Cordeiro
 */
/*****************************************************************/
/***************** SISTEMAS OPERATIVOS 2019 **********************/
/*****************************************************************/

#include <linux/taquilla.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/syscalls.h>

/*****************************************************************/
/*funcion que sera llamada desde scheduler_tick(),es una funcion */
/*del kernel dentro core.c que es llamada por el sistema cada 1 hz -> */
/*1s por lo que la nuestra calculara el tiempo de cada proceso   */
/*de nuestro sistema cada 1s,matara los proceso que superan T_MAX*/
/*****************************************************************/
void calcular_tiempo(){
  struct task_struct *pcb;
  
  for_each_process(pcb){
    if(cputime_to_secs(pcb->utime)>=T_MAX){
      if(pcb->prioridad>0){
	printk("Tiempo del proceso en cpu excedido(%d s), se eliminara el proceso con PID: %d de prioridad: %d\n",T_MAX,pcb->pid,pcb->prioridad);
	kill_pid(find_vpid(pcb->pid),SIGKILL,1);
      }
    }
  }
  
}
/*****************************************************************/
/*funcion que contara los procesos de nuestro sistema, es decir  */
/*procesos con campo de prioridad, anadido en el task_struct,    */
/*mayores que 0 y devolvera 0 si el sistema admite aun procesos, */
/*maximo definido por N_MAX,o 1 si el sistema esta lleno,*********/
/*****************************************************************/
int contar_procesos(){

  struct task_struct *pcb;
  int contador = 0;

  for_each_process(pcb){
    if(pcb->prioridad>0){
      contador++;
    }
  }//fin del foreachprocess

  printk("Hay %d procesos en el sistema \n",contador-1);

  if(contador < N_MAX+1){
    return 0;
  }
  else{
    return 1;
  }
} //fin contar procesos

/******************************************************************/
/*funcion que buscara un reemplazo para un proceso que se quiera  */
/*anadir al sistema,se le pasara un entero prioridad, recorrera   */
/*la lista de procesos comparando el entero que se le pasa como   */
/*parametro con el campo prioridad del proceso actual dentro del  */
/*for_each_process,una variable contador determinara que prioridad*/
/*se buscara en cada momento empezando por la prioridad mas baja 1*/
/*una vez que encuentra un proceso que se pueda reemplazar se     */
/*eliminara del sistema dejando espacio para el nuevo proceso******/
/******************************************************************/
int buscar_reemplazo(int prioridad){

  struct task_struct *pcb;
  int contador=1;

  if(prioridad == 1){
    return 1; //si es 1 no va a haber nada menor
  }

  while(1){

    for_each_process(pcb){
      if(pcb->prioridad == contador){
	printk("El proceso %s con PID: %d va a ser reemplazado\n",pcb->comm,pcb->pid);
	kill_pid( find_vpid(pcb->pid), SIGKILL, 1);
	return 0;
      }
    }//fin foreachprocess

    contador++;
    if(contador==prioridad){
      printk("No hay procesos de menor prioridad,no se puede añadir \n");
      return 1;
    }//fin del if

  }//fin del while

  return 0;
}//fin buscar reemplazo


/*****************************************************************/
/*funcion que anadira a nuestro sistema los procesos que le      */
/*pertenecen, para identificar los procesos de nuestro sistema   */
/*del resto de procesos se anadira un campo prioridad en el      */
/*task_struct, esta funcion 'anadira' a  nuestro sistema las     */
/*prioridades del 1 al 4 y 0 para los procesos fuera de nuestro  */
/*sistema, esta funcion es la que modifica el campo prioridad    */
/*****************************************************************/
void anadir_proceso(struct task_struct *pcb){

  if(strcmp(pcb->comm,"administracion")==0){
    pcb->prioridad = 4;
  }
  else if(strcmp(pcb->comm,"largo")==0){
    pcb->prioridad = 4;
  }
  else if(strcmp(pcb->comm,"pago")==0){
    pcb->prioridad = 3;
  }
  else if(strcmp(pcb->comm,"reserva")==0){
    pcb->prioridad = 2;
  }
  else if(strcmp(pcb->comm,"anulacion")==0){
    pcb->prioridad = 2;
  }
  else if(strcmp(pcb->comm,"consulta")==0){
    pcb->prioridad = 1;
  }
  else{
    pcb->prioridad = 0;
    return;
  }
  anadir_a_cola(pcb);
  return;
}
/****************************************************************/
/*funcion que anadira a los thread disponibles de linux nuestros*/
/*procesos, dependiendo del campo de prioridad cada proceso ira */
/*a una cola diferente con una diciplina especifica,FIFO o RR,y */
/*una prioridad dentro de las colas definido por sched_param    */
/*definida la prioridad de las colas de 0, la cola predeterminada*/
/*, a 99 siendo 99 la cola de maxima prioridad*******************/
/****************************************************************/
void anadir_a_cola(struct task_struct *pcb){

  int policy;
  struct sched_param nodo;

  if(contar_procesos() != 0 ){ //si esta lleno buscamos victima
    printk("El sistema esta lleno, se buscara un reemplazo\n");
    if(buscar_reemplazo(pcb->prioridad) == 1){ //se acaba la funcion porque no puede reemplazar
      printk("No hay procesos de prioridad menor que %d,no se puede añadir, se rechaza en el sistema el proceso PID: %d\n",pcb-> prioridad,pcb->pid);
      kill_pid( find_vpid(pcb->pid), SIGKILL, 1);
      return;
    }
  }

  switch(pcb->prioridad){
    
     case 4 : nodo.sched_priority = 85;
              policy=SCHED_RR;
	      break;
  
     case 3 : nodo.sched_priority = 80;
              policy=SCHED_FIFO;
	      break;
  
     case 2 : nodo.sched_priority = 75;
              policy=SCHED_FIFO;
	      break;
  
     case 1 : nodo.sched_priority = 70;
              policy=SCHED_RR;
     	      break;

     default : break;

  }

  if(sched_setscheduler(pcb, policy, &nodo)<0){
    printk("Error en setScheduler %d\n",-1);
  }
  else{
    printk("Se ha anadido un proceso con PID: %d de tipo %s\n", pcb->pid, pcb->comm);
  }

  return; //tuvo exito
}
