#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include<time.h>
#include <wait.h>

// sudo date --set="2021-04-19 16:21:59"


char cwd[]= "/home/sena/SISOP/Modul2/soalShift/";

// char * getTime(char * string){
//     time_t rawtime;
//     struct tm *info;

//     time( &rawtime );

//     info = localtime( &rawtime );

//     strftime(string,80,"%d/%m %X", info);

//     return string;
// }

void makeDirectory() {
  pid_t pid;
  int status;
  pid = fork();

  if ((chdir(cwd)) < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid == 0){
    char *argv[] = {"mkdir", "Musyik", "Pyoto", "Fylm", NULL};
    execv("/bin/mkdir", argv);
  } else {
    while((wait(&status)) > 0);          
  }
}

void downloadAndUnzip () {
  pid_t pid;
  int status;
  pid = fork();

  char url[3][100];
  char fileName[3][25];
            
  strcpy(url[0],"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download");
  strcpy(url[1],"https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download");
  strcpy(url[2],"https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download");

  strcpy(fileName[0], "Foto_for_Stevany.zip");
  strcpy(fileName[1], "Musik_for_Stevany.zip");
  strcpy(fileName[2], "Film_for_Stevany.zip");

  if ((chdir(cwd)) < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid == 0){                  // child process -- download FOTO
    char *argv[] = {"wget", "--no-check-certificate", url[0], "-O", fileName[0], NULL};
    execv("/usr/bin/wget", argv);
  } else {
      while((wait(&status)) > 0);
      if (fork() == 0)            // child process -- download MUSIK
      {
        char *argv[] = {"wget", "--no-check-certificate", url[1], "-O", fileName[1], NULL};
        execv("/usr/bin/wget", argv);
      } else {
          while((wait(&status)) > 0);
          if (fork() == 0)        // child process -- download FILM
          {
            char *argv[] = {"wget", "--no-check-certificate", url[2], "-O", fileName[2], NULL};
            execv("/usr/bin/wget", argv);
          } else {                // parent process -- unzip all files
              while((wait(&status)) > 0);
              char *argv[] = {"unzip", "-q", "*.zip", NULL};
              execv("/usr/bin/unzip", argv);
            }
        }
    }
}

int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  int status;

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir(cwd)) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    
    pid_t pid;
    int status;
    pid = fork();

    if ((chdir(cwd)) < 0) {
      exit(EXIT_FAILURE);
    }

    if (pid == 0){
      makeDirectory();
      downloadAndUnzip();
    } else {
  
      while((wait(&status)) > 0);          
    }
    
    sleep(30);
  }
}