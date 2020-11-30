
//ex2a
// this program creates a child that generates 10 random prime numbers.
// there is no user input. only play and watch the miracle.
// the child gets 3 seconds to find 10 different prime numbers.
// child is dead if he's unable to provide 3 different prime numbers in
// 3 seconds. in this case the output will be "kill kid"
// if the child comes up with 10 numbers, it prints them.

// we may get the wanted output- 10 numbers & good boy
// we may get "bad boy"
// if the child is dead we will get "kill kid"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <math.h>

// acts as bool
#define TRUE 1
#define FALSE 0

pid_t proccessID;
//------------------------------------------------------------------------
void do_dad(pid_t );
void do_son(void);
void terminate (void);

void catch_alarm(int);
void * catch_sigterm(int arr[]);    // * to pass the array
void child_handler(int );
int is_prime(int num);
int same_number_exist(const int arr[],int size,int num);
void print_numbers(int arr[]);
//------------------------------------------------------------------------
int main () {
    signal(SIGALRM, catch_alarm);
    signal(SIGCHLD, child_handler);
    srand(17);

    proccessID = fork();

    if (proccessID < 0){
        terminate();
    }
    if (proccessID > 0){
        do_dad(proccessID);
    }else{
        do_son();
    }
    return EXIT_SUCCESS;
}

//========================================================================
void terminate() {
    perror ("error in fork()");
    exit(EXIT_FAILURE);
}
//------------------------------------------------------------------------
void do_dad (pid_t son_pid) {
    alarm(3);
    pause();
    alarm(0);

    if(!WEXITSTATUS(son_pid)) {
        printf("bad boy\n");
    }
}
//------------------------------------------------------------------------
void do_son () {
    struct sigaction act;
    int arr[10];
    int num,i;
    for(i = 0; i < 10 ; i++) {
        num = rand();
        while(!is_prime(num) && same_number_exist(arr, i, num) ){
            num = rand();
        }
        arr[i]=num;
    }
    act.sa_handler = catch_sigterm(arr);
    sigfillset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGTERM,&act,NULL);
    exit (EXIT_SUCCESS);
}
//------------------------------------------------------------------------
void catch_alarm(int signum) {
    puts("Kill Kid\n");
    kill(proccessID,SIGTERM);
}
//------------------------------------------------------------------------
int is_prime(int num) {
    int i;
    for(i = 2 ; i <= sqrt(num) ; i++) {
        if(num % i == 0)
            return FALSE;
    }
    return TRUE;
}
//------------------------------------------------------------------------
int same_number_exist(const int arr[],int size,int num) {
    int i;
    for(i = 0 ; i < size ; i++){
        if(arr[i]==num)
            return FALSE;
    }
    return TRUE;
}
//------------------------------------------------------------------------
void print_numbers(int arr[]) {
    int i;
    for(i = 0 ; i < 10 ; i++) {
        printf("%d ",arr[i]);
    }
}
//------------------------------------------------------------------------
void * catch_sigterm(int arr[]) {
    void * a;
    print_numbers(arr);
    return a;
}
//------------------------------------------------------------------------
void child_handler(int signum){
    printf("good boy\n");
}
//------------------------------------------------------------------------
