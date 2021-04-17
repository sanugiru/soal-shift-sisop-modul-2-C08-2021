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

int main(int argc, char* argv[]){

    int stat;
    FILE* kill;
    kill = fopen("killer.sh", "w");
    fprintf(kill, "#!/bin/bash\nkill %d\nkill %d\necho \'Killed program.\'\nrm \"$0\"", getpid() + 2, getpid() + 3);
    fclose(kill);
    pid_t chillid;
    chillid = fork();
    if(chillid < 0) 
        exit(0);
    if(chillid == 0)
    {
        char *killargv[] = {"chmod", "u+x", "killer.sh", NULL};
        execv("/bin/chmod", killargv);
    }

    while(wait(&stat) > 0);

    daemonMode();

    int stat_direct,stat_download,stat_zip,stat_enkripsi;
    char currenT1[50], currentT3[50], currenT2[50], link[50];
    int x;
    while(1){
        pid_t chillid1, chillid2, chillid3, chillid4, chillid5;
        time_t time1 = time(NULL);
        struct tm* loc1 = localtime(&time1);
        strftime(currenT1, 50, "%Y-%m-%d_%H:%M:%S", loc1);

        chillid1 = fork();
        if(chillid1<0){
            exit(0);
        }
        if(chillid1==0){
            char *direcargv[] = {"mkdir",currenT1, NULL};
            execv("/bin/mkdir",direcargv);
        }
        
        while(wait(&stat_direct)>0);

        chillid2 = fork();
        if(chillid2<0){
            exit(0);
        }
        if(chillid2 == 0){
            if(argv[1][1] == 'z') prctl(PR_SET_PDEATHSIG, SIGHUP);
            chdir(currenT1);
            for(x=0;x<10;x++){
                time_t time2 = time(NULL);
                struct tm* loc2 = localtime(&time2);
                
                sprintf(link, "https://picsum.photos/%ld", (time2 % 1000) + 50);
                strftime(currenT2, 50, "%Y-%m-%d_%H:%M:%S", loc2);
                
                chillid3 = fork();
                if(chillid3 <0)
                    exit(0);
                if(chillid3 == 0){
                    char *linkargv[] = {"wget", link, "-O", currenT2, "-o", "/dev/null", NULL};
                    execv("/usr/bin/wget",linkargv);
                }
                sleep(5);
            }
            while(wait(&stat_download)>0);
            char sukses[30] = "Download Succes";
            caes_ciph(sukses, 5);
            FILE* encrypt = fopen("status.txt", "w");
            fprintf(encrypt,"%s",sukses);
            fclose(encrypt);
            
        }
            while(wait(&stat_enkripsi)>0);
            chdir("..");
            strcpy(currentT3, currenT1);
            strcat(currentT3, ".zip");

            chillid4 = fork();
            if(chillid4 <0)
                exit(0);
            if(chillid4 == 0){
                char *zippyargv[] = {"zip", "-r", currentT3, currenT1, NULL};
                execv("/usr/bin/zip", zippyargv);
            }

            while(wait(&stat_zip)>0);
            chillid5 = fork();
            if(chillid5<0)
                exit(0);
            if(chillid5==0){
                char *delargv[] = {"rm", "-r", currenT1, NULL};
                execv("/bin/rm", delargv);
            }
        sleep(40);
    }
}
