#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>
#include <sys/prctl.h>
#include <stdbool.h>
#include <syslog.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int sign;

void daemonMode()
{
	pid_t pid, sid;
    pid = fork();
    if(pid < 0) exit(EXIT_FAILURE);
    if(pid > 0) exit(EXIT_SUCCESS);
    umask(0);
    sid = setsid();
    if(sid < 0) exit(EXIT_FAILURE);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}


void caes_ciph(char* sukses, int shift){
    char huruf;
    int x;
    for(x=0;sukses[x]!='\0';x++){
        huruf = sukses[x];
        if(huruf>='a'&&huruf<='z'){
            huruf+=shift;
            if(huruf>'z')
                huruf = huruf - 'z' + 'a' - 1;
            sukses[x] =  huruf;
        }
        else if (huruf >= 'A' && huruf <= 'Z')
        {
            huruf+=shift;
            if(huruf>'Z')
                huruf = huruf - 'Z' + 'A' - 1;
            sukses[x] =  huruf;
        }
        
    }
}
void changSIGN(){
    sign = 0;
}

int main(int argc, char* argv[]){
    int stat;
    if(argv[1][1]=='x'){
        FILE* kill;
        kill = fopen("killer.sh", "w");
        fprintf(kill, "#!/bin/bash\nkillall -15 no3\necho \'Killed program.\'\nrm killer.sh");
        fclose(kill);
        signal(SIGTERM,changSIGN);
    }
    if(argv[1][1]=='z'){
        FILE* kill;
        kill = fopen("killer.sh", "w");
        fprintf(kill, "#!/bin/bash\nkillall no3\necho \'Killed program.\'\nrm killer.sh");
        fclose(kill);
    }

    pid_t chillid;
    chillid = fork();
    if(chillid < 0) 
        exit(0);
    if(chillid = 0)
    {
        char *argv[] = {"chmod", "u+x", "killer.sh", NULL};
        execv("/bin/chmod", argv);
    }

    while(wait(&stat) > 0);

    daemonMode();

    int stat_direct,stat_download,stat_zip,stat_enkripsi;
    char currenT1[50], currentT3[50], currenT2[50], link[50];
    sign = 1;
    while(sign){
        pid_t chillid1, chillid2, chillid3, chillid4, chillid5;
        time_t time1 = time(NULL);
        struct tm* loc1 = localtime(&time1);
        strftime(currenT1, 50, "%Y-%m-%d_%H:%M:%S", loc1);

        chillid1 = fork();
        if(chillid1<0){
            exit(0);
        }
        if(chillid1==0){
            if(fork() == 0){
            char *argv[] = {"mkdir",currenT1, NULL};
            execv("/bin/mkdir",argv);
            } else {
                while(wait(&stat_direct)>0);

                chillid2 = fork();
                if(chillid2<0){
                    exit(0);
                }
                if(chillid2 == 0){
                    chdir(currenT1);
                    for(int x=0;x<10;x++){
                        time_t time2 = time(NULL);
                        struct tm* loc2 = localtime(&time2);
                    
                        strftime(currenT2, 40, "%Y-%m-%d_%H:%M:%S", loc2);
                        sprintf(link, "https://picsum.photos/%ld", (time2 % 1000) + 50);
                        
                        
                        chillid3 = fork();
                        if(chillid3 <0){
                            exit(0);
                        }
                        if(chillid3 == 0){
                            char *argv[] = {"wget", link, "-O", currenT2, "-o", "/dev/null", NULL};
                            execv("/usr/bin/wget",argv);
                        }
                        sleep(5);
                    }
                    while(wait(&stat_download)>0);
                    char sukses[30] = "Download Succes";
                    caes_ciph(sukses, 5);
                    FILE* encrypt = fopen("status.txt", "w");
                    fprintf(encrypt,"%s",sukses);
                    fclose(encrypt);

                    while(wait(&stat_enkripsi)>0);
                    chdir("..");
                    strcpy(currentT3, currenT1);
                    strcat(currentT3, ".zip");

                    chillid4 = fork();
                    if(chillid4 <0)
                        exit(0);
                    if(chillid4 == 0){
                        char *argv[] = {"zip", "-r", currentT3, currenT1, NULL};
                        execv("/usr/bin/zip", argv);
                    }

                    while(wait(&stat_zip)>0);
                    chillid5 = fork();
                    if(chillid5<0)
                        exit(0);
                    if(chillid5==0){
                        char *argv[] = {"rm", "-r", currenT1, NULL};
                        execv("/bin/rm", argv);
                    }
                } 
                if (sign==0) break;
            }
        }
        sleep(40);
    }
}
