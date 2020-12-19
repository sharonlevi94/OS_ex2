# OS_ex2
// OS- semester A- class B2 
//login:- barif 
//login:- sharonlevi 
// ex0 
// Date - November 30th, 2020
********************************************************************************** 
ALL PROGRAMS ARE EXECUTED VIA UNIX TERMINAL 
ex2A COMPILED VIA TERMINAL- USING COMMAND "gcc -Wall (filename.cc) -o (runfilename) -ln( for sqrt) 
ex2b COMPILED VIA TERMINAL- USING COMMAND "gcc -Wall (filename.cc) -o (runfilename)
Programs are executed via terminal. './<runFileName>.
**********************************************************************************
ex2a:
 this program creates a child that generates 10 random prime numbers.
 there is no user input. only play and watch the miracle.
 the child gets 3 seconds to find 10 different prime numbers.
 child is dead if he's unable to provide 3 different prime numbers in
 3 seconds. in this case the output will be "bad boy"
 if the child comes up with 10 numbers, it prints them.
 output will be: 1. 10 prime numbers seperated by '\n', followed by "good boy"
                 2. "bad boy"
**********************************************************************************
ex2b:
 In this program we create a process.
 * the dad and his son raffle numbers in loop.
 * if the number smaller then 3 they finish.
 * if doesn't, one send a signal to the other,
 * and wait 5 sec for signal.
 * if the signal came within 5 sec,
 * they continue to next round in the loop.
 * else- he is quit.
 *
 * there is race situations of outputs in this program:
 * 1.dad & son raffle numbers one by one until one ends, the another 
 *   wait 5 sec to the another and then quit.
 * 2.they are blocking each other and wait to signal.
         
