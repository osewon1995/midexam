  1 /* sigaction1.c */
  2
  3 #include <signal.h>
  4 #include <unistd.h>
  5 #include <string.h>
  6 #include <stdio.h>
  7 #include "sigaction1.h"
  8
  9 void sig_int(int signo);
 10 void sig_usr(int signo);
 11
 12 int main(void)
 13 {
 14     int i = 0;
 15
 16     // structures for sigaction
 17     struct sigaction intsig, usrsig;
 18
 19     // let them know what we are going to do by putting info. in the structu    re members
 20     intsig.sa_handler = sig_int; // handler function for sig_int
 21     sigemptyset(&intsig.sa_mask);
 22     intsig.sa_flags = 0;
 23
 24     usrsig.sa_handler = sig_usr; // handler function for sig_usr
 25     sigemptyset(&usrsig.sa_mask);
 26     usrsig.sa_flags = 0;
 27
 28
 29     // handler registration
 30     // interested in SIGINT, SIGUSR1 & 2
 31     if (sigaction(SIGINT, &intsig, 0) == -1)
 32     {
 33         perror("signal(SIGINT) error");
 34         return -1;
 35     }
 36
 37     if (sigaction(SIGUSR1, &usrsig, 0) == -1)
 38     {
 39         perror("signal(SIGUSR1) error");
 40         return -1;
 41     }
 42     if (sigaction(SIGUSR2, &usrsig, 0) == -1)
 43     {
 44         perror("signal(SIGUSR2) error");
 45         return -1;
 46     }
 47
 48     // main function's operations here
 49     while(1)
 50     {
 51         printf("%d: %d\n", getpid(), i);
 52         i++;
 53         sleep(1);
 54     }
 55 }
