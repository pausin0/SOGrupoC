#include <stdio.h>
#include <unistd.h>

int main(){
	
  int a=0;
  int j;
  int i;
	       
  sleep(2);
  for( i=0;i<20;i++){
    for( j= 0;j<50000000;j++){
      a=i;
    }	
    printf("Se esta ejecutando un proceso reservas con PID: %d\n", getpid() );
  }	
		
  return;
}
