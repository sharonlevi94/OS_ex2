/*
 * ex2a.c
 *
 *  Created on: Nov 29, 2020
 *      Author: sharonlevi
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
//------------------------------------------------------------------------
void do_dad(pid_t status);
void do_son();
void terminate ();

void catch_alarm(int sig_num,pid_t son_pid);
void catch_sigterm(int sig_num,int arr[]);

int is_prime(int num);
int same_number_exist(int arr[],int size,int num);
void print_numbers(int arr[]);
//------------------------------------------------------------------------
int main () {

signal(SIGALRM,catch_alarm);
	srand(17);

	pid_t status;
	status=fork();

	if(status<0)
		terminate();

	if(status>0)
		do_dad(status);
	else
		do_son();

	return EXIT_SUCCESS;
}

//========================================================================
void terminate(){
	perror ("error in fork()");
			exit(EXIT_FAILURE);
}
//------------------------------------------------------------------------
void do_dad (pid_t son_pid) {
alarm(3);
pause();
alarm(0);

if(WEXITSTATUS(son_pid)==0)
	printf("good boy\n");
else
	printf("bad boy\n");
}
//------------------------------------------------------------------------
void do_son () {
	struct sigaction act;
	int arr[10];
	int num,i;

	act.sa_handler=catch_sigterm;
	sigfillset(&act.sa_mask);
	act.sa_flags=0;
	sigaction(SIGTERM,&act,NULL);

	for(i=0; i<10 ; i++)
	{
		num = rand();
		while(is_prime(num) && same_number_exist(arr,i,num) ){
		     num = rand();
		}
		arr[i]=num;
	}
	
	exit (EXIT_SUCCESS);
}
//------------------------------------------------------------------------
void catch_alarm(int sig_num,pid_t son_pid) {
	kill(son_pid,SIGTERM);
}
//------------------------------------------------------------------------
int is_prime(int num) {
	int i;
	for(i=2 ; i< sqrt(num) ; i++) {
		if(num%i==0)
			return FALSE;
	}
	return TRUE;
}
//------------------------------------------------------------------------
int same_number_exist(int arr[],int size,int num) {
	int i;
	for(i=0 ; i<size ; i++){
		if(arr[i]==num)
			return FALSE;
	}
	return TRUE;
}
//------------------------------------------------------------------------
void print_numbers(int arr[]) {
	int i;
	for(i=0 ; i<10 ; i++) {
		printf("%d ",arr[i]);
	}
}
//------------------------------------------------------------------------
void catch_sigterm(int sig_num,int arr[]) {
	print_numbers(arr);
}
