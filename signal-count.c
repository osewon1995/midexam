  1 /* signal-count.c */
  2
  3 #include <stdio.h>
  4 #include <stdlib.h>
  5 #include <errno.h>
  6 #include <sys/types.h>
  7 #include <sys/wait.h>
  8 #include <unistd.h>
  9 #include <signal.h>
 10
 11 static int no_sigusr1;
 12 static int no_sigusr2;
 13
 14 /* user signal handler */
 15 static void sig_usr(int signo) {
 16     if(signo == SIGUSR1) {
 17         no_sigusr1++;
 18         printf("%d of SIGUSR1 msgs received from its child\n", no_sigusr1);
 19     }
 20     else if(signo == SIGUSR2) {
 21         no_sigusr2++;
 22         printf("%d of SIGUSR2 msgs received from its child\n", no_sigusr2);
 23     }
 24 }
 25
 26 int main(void)
 27 {
 28     /* 자식 프로세스 */
 29     if(!fork()) {
 30         int ppid;
 31         int i;
 32
 33         ppid = getppid();
 34
 35         for(i = 0; i < 5; i++) {
 36             kill(ppid, SIGUSR1);
 37             kill(ppid, SIGUSR2);
 38
 39             sleep(3);
 40         }
 41
 42         printf("child exiting\n");
 43
 44         exit(0);
 45     }
 46
 47     /* 부모 프로세스 */
 48     else {
 49
 50         /* signal handler registration */
 51         if(signal(SIGUSR1, sig_usr) == SIG_ERR)
 52             perror("cannot catch SIGUSR1\n");
 53         if(signal(SIGUSR2, sig_usr) == SIG_ERR)
 54             perror("cannot catch SIGUSR2\n");
 55
 56         /* 자식 프로세스의 종료를 기다리기 */
 57         wait(NULL);
 58
 59         printf("parent exiting\n");
 60
 61     }
 62     return 0;
 63 }
