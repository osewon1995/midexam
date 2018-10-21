  1 /*
  2  * main.c -- C Test App.
  3  *
  4  * Copyright (C) 2012-2013, 2013 heesoon.kim <chipmaker.tistory.com>
  5  *
  6  * This program is free software; you can redistribute it and/or modify
  7  * it under the terms of the GNU General Public License as published by
  8  * the Free Software Foundation; version 2 of the License.
  9  *
 10  * This program is distributed in the hope that it will be useful,
 11  * but WITHOUT ANY WARRANTY; without even the implied warranty of
 12  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 13  * GNU General Public License for more details.
 14  *
 15  * You should have received a copy of the GNU General Public License along
 16  * with this program; if not, write to the Free Software Foundation, Inc.,
 17  */
 18
 19 #include <stdio.h>
 20 #include <stdlib.h>
 21 #include <string.h>
 22 #include <errno.h>
 23 #include <signal.h>
 24 #include <unistd.h>
 25
 26 #define MAX_SLEEP_TIME 2
 27
 28 static int sigCnt[NSIG];
 29 static volatile sig_atomic_t gotSigint = 0;
 30
 31 // print out about the signal setting info
 32 void printSigSet(FILE *of, const char *prefix, const sigset_t *sigset)
 33 {
 34     int sig, cnt;
 35
 36     cnt = 0;
 37
 38     for(sig = 1; sig < NSIG /*32*/; sig++)
 39     {
 40         if(sigismember(sigset, sig))
 41         {
 42             cnt++;
 43
 44             fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
 45         }
 46     }
 47
 48     if(cnt == 0)
 49         fprintf(of, "%s<empty signal set>\n", prefix);
 50 }
 51
 52 // signal handler for SIGINT, SIGUSR2
 53 void signal_handler(int sig)
 54 {
 55     sigset_t pendingMask;
 56
 57     // in case of SIGINT
 58     if(sig == SIGINT)
 59         gotSigint = 1;
 60
 61     // others
 62     else
 63     {
 64         sigCnt[sig]++;
 65
 66         if(sigpending(&pendingMask) == -1)
 67             fprintf(stderr, "sigpending\n");
 68
 69         // call for the print function (signal setting info)
 70         printSigSet(stdout, "\t\t", &pendingMask);
 71
 72         sleep(MAX_SLEEP_TIME);
 73     }
 74 }
 75
 76 int main(int argc, char *argv[])
 77 {
 78     int i;
 79     struct sigaction sigact;
 80     //sigset_t pendingMask;
 81
 82     printf("%s: PID is %ld\n", argv[0], (long)getpid());
 83
 84     // setting for the sigaction structure
 85     sigact.sa_handler = signal_handler;
 86     sigfillset(&sigact.sa_mask);
 87     // sigact.sa_flags = SA_RESETHAND | SA_RESTART;
 88     sigact.sa_flags = SA_RESTART;
 89
 90     sigaction(SIGUSR2, &sigact, NULL);
 91     sigaction(SIGUSR1, &sigact, NULL);
 92     sigaction(SIGINT, &sigact, NULL);
 93
 94     while(!gotSigint)
 95         continue;
 96
 97     for(i = 1; i < NSIG; i++)
 98     {
 99         if(sigCnt[i] != 0)
100             printf("%s: signal %d caught %d time%s \n", argv[0], i, sigCnt[i], (sigCnt[i] == 1) ? "" : "s");
101     }
102
103     return 0;
104 }
