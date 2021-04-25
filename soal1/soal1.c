#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>

char cwd[]= "/home/sena/SISOP/Modul2/soalShift/soal1/";
char *fileStevany[] = {"Pyoto", "Musyik", "Fylm"};
char *url[]={"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
             "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
             "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
char *fileZip[] = {"Foto_for_Stevany.zip", "Musik_for_Stevany.zip", "Film_for_Stevany.zip"};
char *fileUnzip[] = {"FOTO", "MUSIK", "FILM"};

/*nomor 1a*/
void makeDirectory() {
  pid_t pid;
    int status;
    pid = fork();

    if ((chdir(cwd)) < 0) {
      exit(EXIT_FAILURE);
    }

    if (pid == 0){
      char *argv[] = {"mkdir", fileStevany[0], fileStevany[1], fileStevany[2], NULL};
      execv("/bin/mkdir", argv);
    } 
  else {
      while((wait(&status)) > 0);
    return;          
    }
}

/*nomor1b&1c*/
void downloadAndUnzip () {
  pid_t pid;
  int status;
    pid = fork();
  
  if ((chdir(cwd)) < 0) {
      exit(EXIT_FAILURE);
  }
  
  if(pid==0){
  
      if (fork() == 0) {              // child process -- download FOTO
        char *argv[] = {"wget", "--no-check-certificate", url[0], "-O", fileZip[0], NULL};
        execv("/usr/bin/wget", argv);
      } 
  
      else {
        while((wait(&status)) > 0);
  
        if (fork() == 0) {         // child process -- download MUSIK
            char *argv[] = {"wget", "--no-check-certificate", url[1], "-O", fileZip[1], NULL};
            execv("/usr/bin/wget", argv);
        } 
  
        else {
            while((wait(&status)) > 0);
  
            if (fork() == 0) {       // child process -- download FILM
              char *argv[] = {"wget", "--no-check-certificate", url[2], "-O", fileZip[2], NULL};
              execv("/usr/bin/wget", argv);
            } 
  
            else {                   // parent process -- unzip all files
              while((wait(&status)) > 0);
              char *argv[] = {"unzip", "-q", "*.zip", NULL};
              execv("/usr/bin/unzip", argv);
            }
        }
      }
  }
  else{
    while((wait(&status)) > 0);
    return;
  }
}

/*nomor 1d*/
void moveFiles() {
    pid_t pid;
    int status;
    pid = fork();
    
  if ((chdir(cwd)) < 0) {
      exit(EXIT_FAILURE);
  }

  if(pid==0){
      if(fork() == 0){
        char *find[] = {"find","/home/sena/SISOP/Modul2/soalShift/soal1/FOTO" , "-type", "f", "-exec", "mv", "{}", 
                        "/home/sena/SISOP/Modul2/soalShift/soal1/Pyoto", ";", NULL};
        execv("/usr/bin/find", find);
      }
  
      else {
        while((wait(&status)) > 0);
        if (fork() == 0) {
            char *find[] = {"find", "/home/sena/SISOP/Modul2/soalShift/soal1/MUSIK", "-type", "f", "-exec", "mv", "{}", 
                            "/home/sena/SISOP/Modul2/soalShift/soal1/Musyik", ";", NULL};
            execv("/usr/bin/find", find);
        }
  
        else {
            while((wait(&status)) > 0);
            char *find[] = {"find", "/home/sena/SISOP/Modul2/soalShift/soal1/FILM", "-type", "f", "-exec", "mv", "{}", 
                            "/home/sena/SISOP/Modul2/soalShift/soal1/Fylm", ";", NULL};
            execv("/usr/bin/find", find);
        }
      }
  }
  
  else{
      while((wait(&status)) > 0);
    return;
  }

}


/*nomor 1f*/
void zipFiles() {
  pid_t pid;
  int status;
  pid = fork();

  if(pid == 0) {
    char *argv[] = {"zip", "-q", "-r", "-m", "Lopyu_Stevany.zip", fileStevany[0], fileStevany[1], fileStevany[2], NULL};
    execv("/usr/bin/zip", argv);
  }

  else{
    while(wait(&status) > 0);
    return;
  }
}

void removeFolder() {
  pid_t pid;
  int status;
  pid = fork();

  if(pid == 0) {
    char *argv[] = {"rm", "-d", fileUnzip[0], fileUnzip[1], fileUnzip[2], NULL};
    execv("/usr/bin/rm", argv);
  }

  else{
    while(wait(&status) > 0);
    return;
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
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
  
  /*nomor 1e*/
  if (local->tm_mon+1==4 && local->tm_mday == 9 && local->tm_hour == 16 && local->tm_min == 22 && local->tm_sec == 0){
    makeDirectory();
    downloadAndUnzip();
    moveFiles();
  }
  
  /*nomor 1f*/
  else if (local->tm_mon+1==4 && local->tm_mday == 9 && local->tm_hour == 22 && local->tm_min == 22 && local->tm_sec == 0){
    zipFiles();
    removeFolder();
  }
    
    sleep(1);
  }
}
