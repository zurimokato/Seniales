#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#ifndef NUMHIJOS
#define NUMHIJOS 2
#endif
void manejador(int signal);

int main(){
	int numIteraciones=3;
	pid_t padre;
	pid_t hijos[NUMHIJOS],h1,h2;
	int i=0,contador=0;
	padre=getpid();
	signal(SIGUSR1,manejador);
	
	for(i=0;i<2;i++){
		hijos[i]=fork();
		if (hijos[i]==0){
			if(i==0){
				h1=fork();
				if(h1==0){
					h2=fork();
					if (h2==0){
						break;
					}
					
				}
			}
			break;
		}
	}
	
	
	for (int j = 0; j < numIteraciones; j++){	
		if(padre==getpid()){			
			sleep(1);
			printf("padre [%d]\n",padre);
			kill(hijos[i-1],SIGUSR1);
		}else{
			if(i==1){
				pause();
				printf("hijo 2 [%d]\n",getpid());
				kill(hijos[i-1],SIGUSR1);
			}else{
				pause();
				if(i==0 && h1!=0){
					printf("hijo 1 [%d]\n",getpid());
					kill(h1,SIGUSR1);
					pause();
					printf("hijo 1 [%d]\n",getpid());
					kill(getppid(),SIGUSR1);
					
				}else{
					if(h1==0&&h2!=0){
						printf("hijo 1.1 [%d]\n",getpid());
						kill(h2,SIGUSR1);
						pause();
						printf("hijo 1.1 [%d]\n",getpid());
						kill(getppid(),SIGUSR1);
						
					}else{
						if(h2==0){
							printf("hijo 1.2 [%d]\n",getpid());
							kill(getppid(),SIGUSR1);
						}
					}
				}
			}
		}
	}
	if(getpid() == padre){
		pause();
       for (int i = 0; i <NUMHIJOS ;i++){
            	wait(0);
        	}
    }
}



void manejador(int signal){
}