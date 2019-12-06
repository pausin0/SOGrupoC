#include <stdio.h>
#include <stdlib.h>

int main(){
	
  int a=0;
  int i;
  int j;
  sleep(0);
  for( i=0;i<200;i++){
    for( j=0;j<200000000;j++){
      a=i;
    }	
    printf("Se esta ejecutando un proceso administracion largo con PID: %d\n", getpid() );
  }	
  printf("Fin proceso largo\n");
	
  return;
}
