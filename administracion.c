#include <stdio.h>
#include <unistd.h>

int main(){
	
  int a=0;
  int i;
  int j;    
  
  sleep(2);
  for( i=0;i<20;i++){
    for( j= 0;j<50000000;j++){
      a=i;
    }	
    printf("Se esta ejecutando un proceso administracion con PID: %d\n", getpid() );
  }	
  
  return;
}
