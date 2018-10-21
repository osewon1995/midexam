  1 #include <stdio.h>
  2 #include <stdlib.h>
  3 #include <unistd.h>
  4 #include <signal.h>
  5
  6 /* user signal handler */
  7 static void sig_usr(int signo) {
  8     if(signo == SIGUSR1)
  9         printf("received SIGUSR1: %d\n", signo);
 10     else if(signo == SIGUSR2)
 11         printf("received SIGUSR2: %d\n", signo);
 12     else if(signo == SIGTERM)
 13         printf("received SIGTERM, die hard!!! ;) \n");
 14 }
 15
 16 int main(void) {
 17     /* signal handler registration */
 18     if(signal(SIGUSR1, sig_usr) == SIG_ERR)
 19         perror("cannot catch SIGUSR1\n");
 20     if(signal(SIGUSR2, sig_usr) == SIG_ERR)
 21         perror("cannot catch SIGUSR2\n");
 22     if(signal(SIGTERM, sig_usr) == SIG_ERR)
 23         perror("cannot catch SIGTERM\n");
 24
 25     for(;;)
 26         sleep(60);
 27
 28     return(0);
 29 }
