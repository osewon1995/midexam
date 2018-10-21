  1 // sigaction3-receiver.c
  2
  3 #include <stdio.h>
  4 #include <stdlib.h>
  5 #include <string.h>
  6 #include <errno.h>
  7 #include <signal.h>
  8 #include <unistd.h>
  9
 10 #define MAX_SLEEP_TIME 30
 11
 12 static int sigCnt[NSIG];
 13 static volatile sig_atomic_t gotSigint = 0;
 14
 15 void printSigSet(FILE *of, const char *prefix, const sigset_t *sigset)
 16 {
 17     int sig, cnt;
 18
 19     cnt = 0;
 20
 21     for(sig = 1; sig < NSIG /*32*/; sig++)
 22     {
 23         if(sigismember(sigset, sig))
 24         {
 25             cnt++;
 26
 27             fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
 28         }
 29     }
 30
 31     if(cnt == 0)
 32         fprintf(of, "%s<empty signal set >\n", prefix);
 33 }
 34
 35 void signal_handler(int sig)
 36 {
 37     if(sig == SIGINT)
 38         gotSigint = 1;
 39     else
 40         sigCnt[sig]++;
 41
 42 }
 43
 44 int main(int argc, char *argv[])
 45 {
 46     int n;
 47     sigset_t pendingMask, blockingMask, emptyMask;
 48
 49     printf("%s: PID is %ld\n", argv[0], (long)getpid());
 50
 51     for(n = 1; n < NSIG; n++)
 52         (void) signal(n, signal_handler);
 53
 54     sigfillset(&blockingMask);
 55     if(sigprocmask(SIG_SETMASK, &blockingMask, NULL) == -1)
 56         fprintf(stderr, "sigprocmask\n");
 57
 58     printf("%s : sleeping for %d seconds\n", argv[0], MAX_SLEEP_TIME);
 59     sleep(MAX_SLEEP_TIME);
 60
 61     if(sigpending(&pendingMask) == -1)
 62         fprintf(stderr, "sigpending\n");
 63
 64     printf("%s : pending signals ars : \n", argv[0]);
 65     printSigSet(stdout, "\t\t",  &pendingMask);
 66
 67     sigemptyset(&emptyMask);
 68     if(sigprocmask(SIG_SETMASK, &emptyMask, NULL) == -1)
 69         fprintf(stderr, "sigprocmask\n");
 70
 71     while(!gotSigint)
 72         continue;
 73
 74     for(n = 1; n < NSIG; n++)
 75         if(sigCnt[n] != 0)
 76             printf("%s: signal %d caught %d time%s \n", argv[0], n, sigCnt[n], (sigCnt[n] == 1) ? "" : "s");
 77
 78     exit(EXIT_SUCCESS);
 79
 80     return 0;
 81 }
