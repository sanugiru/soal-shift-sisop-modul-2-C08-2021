#include <stdio.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

char filename[1000];
char filename2[100];
char filename3[100];
char namee[100]; //untuk menyimpan nama hewan
char nameee[100]; //penanda kalau ada yang double digambar 
char star[100]; //untuk mendapatkan nama file double yang akan di copy
char star2[100]; //untuk mendapatkan nama file yang akan di rename
char filename_double[100]; //lokasi folder yang memiliki file double
char folder[1000]; //lokasi folder tiap jenis hewan
char folder_copy[1000]; //lokasi copy 
char name_double[100];
char unimportant_folder[100]; //folder yang tidak penting
char folder_keterangan[100];

int main(){
    pid_t child_id1, child_id2, child_id3, child_id4, child_id5, child_id6, child_id7, child_id8, child_id9, child_id10;
    DIR *d;
    struct dirent *dir;
    int flag, flag2;
    child_id1 = fork();
    if (child_id1 < 0) exit(EXIT_FAILURE);
    if (child_id1 == 0) {
        execl("/usr/bin/unzip", "unzip", "pets.zip", NULL); 
    }
    if (child_id1 > 0) {
        while ((wait(&flag)) > 0);
        d = opendir("/home/deka/modul2/petshop/");
        while ((dir = readdir(d)) != NULL){
        char *temp1 = strchr(dir->d_name,';');
        char *temp2 = strchr(dir->d_name, '.');              
        if (!temp1 && !temp2) {
                strcpy(unimportant_folder, dir->d_name);
                child_id2 = fork();
                if (child_id2 < 0) exit(EXIT_FAILURE);
                if (child_id2 == 0){
                    char *argv[] = {"find", "/home/deka/modul2/petshop/.", "-type", "d", "-name", unimportant_folder, "-exec", "rm", "-r", "{}", "+", NULL};
                    execv("/usr/bin/find", argv);
                }
            }
        }
        
        if (child_id2 > 0) {
            while((wait(&flag))>0);
            d = opendir("/home/deka/modul2/petshop/");
            while ((dir = readdir(d)) != NULL){
                char *temp1 = strchr(dir->d_name,';');                
                if (!temp1) ;
                else {
                    strcpy(filename2, dir->d_name);
                    strcpy(filename3, dir->d_name);
                    memset(namee,0,sizeof(namee));
                    memset(nameee,0,sizeof(nameee));
                    memset(star,0,sizeof(star));
                    memset(folder,0,sizeof(folder));
                    memset(folder_copy,0,sizeof(folder_copy));
                    memset(name_double,0,sizeof(name_double));
                    memset(filename_double, 0 ,sizeof(filename_double));
                    memset(folder_keterangan,0,sizeof(folder_keterangan));
                    
                    for (int i=0 ; i<strlen(filename2) ; i++){
                        int k = 0;
                        if (filename2[i]==';'){
                            int j = i+1;
                            k = 0;
                            while (filename2[j]!=';'){
                                namee[k]=filename2[j];
                                k++;
                                j++;
                            }
                            break;
                        }
                        if (k!=0) break;
                    }
                    for (int i=0 ; i<strlen(filename3) ; i++){
                        int k = 0, l=0, j;
                        if (filename3[i]=='_'){
                            int j = i+1;
                            k = 0;
                            while (filename3[j]!=';'){
                                nameee[k]=filename3[j];
                                k++;
                                j++;
                            }
                            if (nameee && nameee[0]){
                                j+=1;
                                while (filename3[j]!=';'){
                                    name_double[l] = filename3[j];
                                    l++;
                                    j++;
                                }
                            }
                            break;
                        }
                        if (k!=0) break;
                    }
                   
                    
                    *temp1 = 0;
                    strcpy(filename, dir->d_name);
                    DIR* check_dir = opendir(filename);

                    strcpy(star, "*_");
                    strcat(star,nameee);
                    strcat(star,";");
                    strcat(star,name_double);
                    strcat(star,"*");
                    if (nameee && nameee[0]){
                        strcpy(filename_double, "/home/deka/modul2/petshop/");
                        strcat(filename_double, nameee);
                        strcat(filename_double, "/");
                        strcat(name_double, ".jpg");
                    }
                    
                    
                    strcpy(folder, "/home/deka/modul2/petshop/");
                    strcat(folder,filename);
                    strcat(folder,"/.");
                    strcpy(star2, "*");
                    strcat(star2, namee);
                    strcat(star2, "*");
                    strcpy(folder_copy, "/home/deka/modul2/petshop/");
                    strcat(folder_copy, filename);
                    strcat(folder_copy, "/");
                    strcat(folder_copy,namee);

                    strcat(filename_double, name_double);
                    strcat(folder_keterangan, "/home/deka/modul2/petshop/");
                    strcat(folder_keterangan,filename);
                    strcat(folder_keterangan, "/");
                    strcat(folder_keterangan, "keterangan.txt");

                    if (check_dir) {
                        closedir(check_dir);
                    }
                    else if (ENOENT == errno){
                        child_id3 = fork();
                        if (child_id3 <0 ) exit(EXIT_FAILURE);
                        if (child_id3 == 0){
                            execl("/usr/bin/mkdir", "mkdir", filename , NULL);
                        }
                    }
                    if (child_id3 > 0){
                        while ((wait(&flag2))>0);
                        child_id4 = fork();
                        if (child_id4 < 0) exit(EXIT_FAILURE);
                        else if (child_id4 == 0){
                            char *argv[] = {"find", "/home/deka/modul2/petshop/." ,"-type", "f", "-name", strcat(filename,"*jpg"), "-exec", "mv", "-nt", folder, "{}", "+", NULL};
                            execv("/usr/bin/find", argv);
                        }
                    }
                    if (child_id4 > 0){
                        while((wait(&flag2))>0);
                        if (nameee && !nameee[0]){  
                            child_id5 = fork();
                            if (child_id5 < 0) exit(EXIT_FAILURE);
                            else if (child_id5 == 0){   
                                char *argv[] = {"find", folder, "-type", "f", "-name", star2 , "-exec", "mv","{}", strcat(folder_copy, ".jpg"),";" , NULL};
                                execv("/usr/bin/find", argv);   
                            }
                        }
                    }
                    if (child_id5 > 0){
                        while((wait(&flag2))>0);
                        if (nameee && nameee[0]){            
                            child_id6 = fork();
                            if (child_id6<0) exit(EXIT_FAILURE);
                            if (child_id6==0){
                                char *argv[] = {"find", folder, "-type", "f", "-name", star , "-exec", "cp", "{}", strcat(filename_double,name_double), ";", NULL};
                                execv("/usr/bin/find", argv);
                            }
                        }
                    }
                    
                    if (child_id6 > 0){
                        while((wait(&flag2))>0);
                        if (nameee && nameee[0]){  
                            child_id7 = fork();
                            if (child_id7 < 0) exit(EXIT_FAILURE);
                            else if (child_id7 == 0){   
                                char *argv[] = {"find", folder, "-type", "f", "-name", star , "-exec", "mv","{}", strcat(folder_copy, ".jpg"),";" , NULL};
                                execv("/usr/bin/find", argv);   
                            }
                        }
                    }
                    if (child_id7 > 0){
                        while((wait(&flag2))>0);
                        child_id8 = fork();
                        if (child_id8 < 0) exit(EXIT_FAILURE);
                        else if (child_id8==0){
                            execl("/usr/bin/touch", "touch", "keterangan.txt", NULL);
                        }
                    }
                    if (child_id8 > 0){
                        while ((wait(&flag2))>0);
                        child_id9 = fork();
                        if (child_id9<0) exit(EXIT_FAILURE);
                        else if (child_id9==0){
                            char *argv[] = {"find", "/home/deka/modul2/petshop/", "-type", "f", "-name", "keterangan.txt" , "-exec", "cp" ,"{}", folder_keterangan, ";", NULL};
                            execv("/usr/bin/find", argv);
                        }
                    }
                    // if (child_id9 > 0){
                    //     while ((wait(&flag2))>0);
                    //     child_id10 = fork();
                    //     if (child_id10 <0) exit(EXIT_FAILURE);
                    //     else if (child_id10==0){
                    //         char *argv[] = {"find", "/home/deka/modul2/petshop/.", "-type", "f", "-name", "keterangan.txt", "-exec", "rm", "-rf", "{}", ";", NULL};
                    //         execv("/usr/bin/find", argv);
                    //     }
                    // }
                }
            }
            closedir(d);
        }
    }
    return 0;
}
