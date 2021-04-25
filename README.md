# Soal Shift Sisop Modul 2 C08 2021  

Anggota:
- 05111940000112 Deka Julian Arrizki	    
- 05111940000141 Muhammad Farhan Haykal	
- 05111940000158 Shahnaaz Anisa Firdaus

## Daftar Isi
  * [SOAL 1](#soal-1)
    + [**Pembahasan**](#--pembahasan--)
    + [**Screenshot Output**](#--screenshot-output--)
    + [**Kendala**](#--kendala--)
  * [SOAL 2](#soal-2)
    + [**Pembahasan**](#--pembahasan---1)
    + [**Screenshot Output**](#--screenshot-output---1)
    + [**Kendala**](#--kendala---1)
  * [SOAL 3](#soal-3)
    + [**Kendala**](#--kendala---2)

## SOAL 1   
Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi.

a. Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg.  

b. untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga.  

        Foto  : https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/view
        Musik : https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view
        Film  : https://drive.google.com/file/d/1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp/view  
    
c. Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload serta,  

d. memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan).  

e. Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany).   

f. Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip).

### **Pembahasan**
- **NOMOR 1A**
  ```c
  char cwd[]= "/home/sena/SISOP/Modul2/soalShift/soal1/";
  char *fileStevany[] = {"Pyoto", "Musyik", "Fylm"};
  char *url[]={"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
               "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
               "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
  char *fileZip[] = {"Foto_for_Stevany.zip", "Musik_for_Stevany.zip", "Film_for_Stevany.zip"};
  char *fileUnzip[] = {"FOTO", "MUSIK", "FILM"};
  ```
  - Pertama-tama inisialisasi array yang diisi dengan nama-nama folder yang nantinya akan dibuat dan link download file musik, film, dan foto.
  - `cwd` menyimpan path program ini, `fileStevany` menyimpan nama file yang akan dibuat, `url` menyimpan link download, `fileZip` menyimpan nama dari file zip yang didownload, `fileUnzip` menyimpan nama folder hasil extract zip yang sudah didownload.
  ```c
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
  ```
  - Buat fungsi `makeDirectory` yang akan membuat folder baru.
  - Memanggil `fork()` untuk membuat child process.
  - Jika process merupakan child process, maka `execv` akan mengeksekusi argumen dalam `argv[]` dan membuat folder baru dengan nama Pyoto, Musyik, dan Fylm.
  - jika process adalah parent, maka parent akan menunggu sampai child process selesai kemudian akan return ke fungsi `main`.
- **NOMOR 1B**
  ```c
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
  ```
  - Untuk nomor 1B, dibuat fungsi untuk mendownload file zip.
  - `fork()` dipanggil untuk membuat child process, jika proses merupakan child process, maka kode dalam if akan dieksekusi, di dalam if memanggil kembali `fork()` untuk membuat proses lagi yang akan mendownload file zip foto menggunakan `wget` dan `execv` 
  - kemudian proses akan menunggu sampai file selesai terdownload baru akan memanggil `fork()` kembali untuk memulai proses baru yang akan mendownload file zip musik.
  - selanjutnya sama seperti sebelumnya, pemanggilan `fork()` setelah proses download sebelumnya selesai baru mendownload file  zip film menggunakan `wget` dan `execv`
- **NOMOR 1C**
  ```c
  else { 
     while((wait(&status)) > 0);
     char *argv[] = {"unzip", "-q", "*.zip", NULL};
     execv("/usr/bin/unzip", argv);
  }
  ```
  - melanjutkan dari numor sebelumnya, apabila semua proses download sudah selesai, kode dalam else akan tereksekusi dan akan mengunzip semua files yang memiliki ekstensi `.zip`
  - unzip menggunakan `unzip` dan `execv`
- **NOMOR 1D**
  ```c
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
  ```
  - untuk memindahkan files dibuat fungsi `moveFiles`
  - pemanggilan `fork()`  untuk membuat child process, jika `pid==0` atau proses tersebut merupakan child process, kode dalam if akan tereksekusi.
  - di dalam if yang pertama dilakukan kembali pemanggilan `fork()`, untuk memindahkan files.
  - memindahkan files menggunakan `find source_path -type f -exec mv {} destination_path ;` yang akan mencari files dari source path kemudian `mv` memindahkannya ke destination path
  - kemudian jika telah selesai memindahkan files dari file FOTO ke file Pyoto, selanjutnya akan memanggil `fork()` kembali untuk memindahkan files dari file MUSIK ke file Musyik dengan command yang sama seperti sebelumnya
  - dan terakhir, setelah proses sebelumnya selesai, akan mengeksekusi kode dalam else yang akan memindahkan files dari file FILM ke file Fylm.
- **NOMOR 1E**
  ```c
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
  ```
  - karena diperintahakn agar proses berjalan dibackground, maka digunakan template untuk membuat daemon process
  - supaya proses otomatis berjalan otomatis 6 jam sebelum ulang tahun Stevany, dibuat dahulu variabel now bertipe `time_t` untuk mendapatkan waktu system, kemudian dibuat conditional-if yang akan mengecek apabila waktu sekarang adalah 09 April pukul 16:22:00, maka panggil fungsi yang sudah dibuat di nomor sebelumnya yaitu fungsi `makeDirectory()`, `downloadandUnzip`, dan `moveFiles`
- **NOMOR 1F**
  ```c
  else if (local->tm_mon+1==4 && local->tm_mday == 9 && local->tm_hour == 22 && local->tm_min == 22 && local->tm_sec == 0){
    zipFiles();
    removeFolder();
  }
  ```
  - selanjutnya apabila waktu sekarang adalah ulang tahun Stevany, yaitu 09 April pukul 22:22:00 maka fungsi `zipFiles()` dan `removeFolder()` akan dipanggil
  ```c
  void zipFiles() {
    pid_t pid;
    int status;
    pid = fork();

    if(pid == 0) {
      char *argv[] = {"zip", "-q", "-r", "-m", "Lopyu_Stevany.zip", fileStevany[0], fileStevany[1], fileStevany[2], NULL};
      execv("/usr/bin/zip", argv);
    }

    else {
      while(wait(&status) > 0);
      return;
    }
  }
  ```
  - di dalam fungsi `zipFiles` akan dipanggil `fork()` untuk membuat child process yang akan men-zip folder Pyoto, Musyik, dan Fylm kedalam Lopyu_Stevany.zip
  - zip menggunakan `execv` dan `zip [options]  zipFIle  fileDir/fileList`, `-r` untuk men-zip files secarar recursive, `-m` untuk menghapus original files setelah di zip.
  - apabila sudah selesai menzip, akan kembali ke fungsi main.
  ```c
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
  ```
  - terakhir, untuk menghapus folder yang ada, dalam fungsi `removeFolder()` dipanggil `fork()` kembali untuk membuat child process
  - untuk menghuapus folder menggunakan `execv` dan `rm [OPTION] FILE`, `-d` untuk menghapus directory
  - setelah selesai menghapus folder FILM, MUSIK, dan FILM selanjutnya kembali ke fungsi main.
### **Screenshot Output**
- output pada saat 09 April pukul 16:22:00
![162200](https://user-images.githubusercontent.com/72660860/115996641-460be300-a60a-11eb-9323-4afc4b0b1c17.png)
- output pada saaat 09 April pukul 22:22:00
![222200](https://user-images.githubusercontent.com/72660860/115996580-0f35cd00-a60a-11eb-98ab-f8eb11e2ec36.png)
- isi dari Lopyu_Stevany.zip
![isizip](https://user-images.githubusercontent.com/72660860/115996872-3b9e1900-a60b-11eb-8f62-823ceb105685.png)

### **Kendala**
- sempat bingung dengan penggunaan fork dan exec, jadinya saat do-run fungsi `moveFiles()` tidak terpanggil karena proses berhenti di fungsi `downloadAndUnzip` dan tidak kembali ke fungsi main untuk mengeksekusi kode setelahnya.
- file zip yang di download gagal terdownload menjadi zip, alhasil tidak ada file yang bisa di unzip, jadi harus berkali-kali coba di-run dan ditunggu sampai bisa terdownload.

## SOAL 2

a. Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. Karena bos Loba teledor, dalam zip tersebut bisa berisi folder-folder yang tidak penting, maka program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.

b. Foto peliharaan perlu dikategorikan sesuai jenis peliharaan, maka kamu harus membuat folder untuk setiap jenis peliharaan yang ada dalam zip. Karena kamu tidak mungkin memeriksa satu-persatu, maka program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip.
Contoh: Jenis peliharaan kucing akan disimpan dalam “/petshop/cat”, jenis peliharaan kura-kura akan disimpan dalam “/petshop/turtle”.

c. Setelah folder kategori berhasil dibuat, programmu akan memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.
Contoh: “/petshop/cat/joni.jpg”. 

d. Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. Contoh: foto dengan nama “dog;baro;1_cat;joni;2.jpg” dipindah ke folder “/petshop/cat/joni.jpg” dan “/petshop/dog/baro.jpg”.

e. Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut. Format harus sesuai contoh.
nama : joni
umur  : 3 tahun

nama : miko
umur  : 2 tahun

### **Pembahasan**
- **NOMOR 2a**
```c
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
```
- pertama saya membuat fork, kemudian untuk child_id bernilai 0 dilakukan perintah unzip zip file yang diberikan oleh soal
```c
if (child_id1 == 0) {
   execl("/usr/bin/unzip", "unzip", "pets.zip", NULL); 
}
```
- kemudian menghapus semua folder yang tidak penting, karena folder maka ciri utama dalam penamaan tidak memakai titik (.) sehingga saya mengakali dengan nama. setiap nama yang tidak ada titik (.) maka itu folder dan apabila ada maka itu termasuk file yang digunakan pada proses selanjutnya.
```c
d = opendir("/home/deka/modul2/petshop/");
while ((dir = readdir(d)) != NULL){
char *temp1 = strchr(dir->d_name,';');
char *temp2 = strchr(dir->d_name, '.');    
```
- setelah mengetahui mana yang folder dan mana yang file maka tinggal hapus folder yang diperoleh
```c
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
```
- **NOMOR 2b**
```c
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
```
- saya looping semua file yang ada di folder /home/deka/modul2/petshop/ dan membuat namanya seperti filename dimana filename adalah variable yang saya buat untuk menyimpan jenis-jenis hewan
- **NOMOR 2c**
```c
if (child_id3 > 0){
        while ((wait(&flag2))>0);
        child_id4 = fork();
        if (child_id4 < 0) exit(EXIT_FAILURE);
        else if (child_id4 == 0){
                char *argv[] = {"find", "/home/deka/modul2/petshop/." ,"-type", "f", "-name", strcat(filename,"*jpg"), "-exec", "mv", "-nt", folder, "{}", "+", NULL};
                execv("/usr/bin/find", argv);
        }
```
- langkah diatas digunakan untuk membuat folder sebanyak dan senama dengan semua jenis hewan yang ada di folder petshop
```c
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
```
- setelah semua folder dengan nama jenis hewan berhasil dibuat maka semua file akan dipindah ke folder dengan jenis masing-masing. akan tetapi pada langkah ini hanya untuk file yang tidak double jenis dan nama hewannya
- **NOMOR 2d**
```c
if (child_id5 > 0){
        while((wait(&flag2))>0);
        if (nameee && nameee[0]){            
                child_id6 = fork();
                if (child_id6<0) exit(EXIT_FAILURE);
                if (child_id6==0){
                        char *argv[] = {"find", folder, "-type", "f", "-name", star , "-exec", "cp", "{}", filename_double, ";", NULL};
                        execv("/usr/bin/find", argv);
                }
        }
}
```
- pertama saya copy file yang double ke folder jenis hewan yang double
```c
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
```
- kemudian saya ganti namanya sesuai dengna nama jenis hewan yang double
- **NOMOR 2e**
```c
if (child_id7 > 0){
        while((wait(&flag2))>0);
        child_id8 = fork();
        if (child_id8 < 0) exit(EXIT_FAILURE);
        else if (child_id8==0){
                execl("/usr/bin/touch", "touch", "keterangan.txt", NULL);
        }
}
```
- pertama saya buat file keterangan.txt yang isinya kosong di directory petshop
```c
if (child_id8 > 0){
        while ((wait(&flag2))>0);
        child_id9 = fork();
        if (child_id9<0) exit(EXIT_FAILURE);
        else if (child_id9==0){
                char *argv[] = {"find", "/home/deka/modul2/petshop/", "-type", "f", "-name", "keterangan.txt" , "-exec", "cp", "nt","{}", folder_keterangan, ";", NULL};
                execv("/usr/bin/find", argv);
        }
}
```
- kemudian saya copy file keterangan.txt ke semua folder jenis hewan
```c
if (child_id9 > 0){
        while ((wait(&flag2))>0);
        child_id10 = fork();
        if (child_id10 <0) exit(EXIT_FAILURE);
        else if (child_id10==0){
                execl("/usr/bin/rm","rm", "keterangan.txt", NULL);
        }
}
```
- sebelum mengisi keterangan.txt saya hapus terlebih dahulu file keterangan.txt yang ada di directory petshop
- kemudian saya isi setiap file keterangan.txt di tiap folder jenis hewan dengan nama dan umur dari hewan tersebut
```c
FILE *file = fopen(directory_keterangan, "a");
if (file){
        if (nameee && nameee[0]){
                fprintf(file, "nama : %s\numur : %s tahun\n\n", namee, umur_double_pertama);
                fprintf(file, "nama : %s\numur : %s tahun\n\n", name_double_a, umur_double);
        }
        else 
                fprintf(file, "nama : %s\numur : %s tahun\n\n", namee, umur);
        }
fclose(file);
```

### **Screenshot Output**
![1](https://user-images.githubusercontent.com/55046884/115991813-7e082b80-a5f4-11eb-9dd0-95e83be6cb47.png)
![2](https://user-images.githubusercontent.com/55046884/115991817-82ccdf80-a5f4-11eb-9e2b-fb0b53fd694d.png)
isi keterangan.txt dari folder parrot


![3](https://user-images.githubusercontent.com/55046884/115991821-86606680-a5f4-11eb-8e69-b5f67d1e6617.png)

### **Kendala**
1. kesulitan searching syntax dari beberapa instruksi sehingga banyak waktu terbuang hanya untuk mencari syntax yang benar
2. saya menggunakan fork setiap pergantian proses sehingga membutuhkan code yang banyak

## SOAL 3
a. Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].

b.Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.

c.Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.

d.Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin program tersebut akan men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan program bash.

e.Pembimbing magang Ranora juga ingin nantinya program utama yang dibuat Ranora dapat dijalankan di dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dsdengan argumen -z, dan Ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).

###**Pembahasan**

-**Nomor 3a**
```c
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
        }
        ....
        sleep(40);
```
Untuk nomor 3a akan dibuat folder dengan nama time stamp, dimana timestamp akan dihasilkan dengan pengambilan localtime dan dimasukkan ke dalam variabel currenT1 (pada code di atas) dan selanjutnya akan dilakukan `fork()` untuk membuat proses baru dan `"mkdir"` untuk membuat direktori, dan `sleep(40)` berguna agar folder dibuat sebanyak 40 detik sekali seperti gambar di bawah ini :

![prooo](https://user-images.githubusercontent.com/70801807/115993506-4487ee00-a5fd-11eb-9e4a-e8a45753a743.PNG)


-**Nomor 3b**
```c
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
```
Untuk nomor 3b dibutuhkan `link` untuk mendownload, `(time2 & 1000) + 50` untuk ukuran foto, serta `currenT2` time stamp untuk penamaan foto, dan `sleep(5)` digunakan agar foto didownload sebanyak 5 detik sekali. Untuk hasilnya foto akan didownload pada folder yang telah dibuat selama 5 detik sekali dan akan ditunjukkan pada gambar di bawah  ini :

![-xproof](https://user-images.githubusercontent.com/70801807/115993359-9c722500-a5fc-11eb-9344-be4f09ad44d9.PNG)

-**Nomor 3c**
```c
                    while(wait(&stat_download)>0);
                    char sukses[30] = "Download Succes";
                    caes_ciph(sukses, 5);
                    FILE* encrypt = fopen("status.txt", "w");
                    fprintf(encrypt,"%s",sukses);
                    fclose(encrypt);
```
Fungsi Caesar Cipher :
```c
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
```
Setelah folder berisikan 10 foto maka program akan membuat file `status.txt` dimana berisikan pesan Download Succes yang dienkripsi dengan teknik Caesar Cipher Shift 5, hasilnya akan ditampilkan dalam gambar di bawah ini:

![stat](https://user-images.githubusercontent.com/70801807/115993612-ca0b9e00-a5fd-11eb-91b1-ea7827409116.PNG)
![caes](https://user-images.githubusercontent.com/70801807/115993618-ce37bb80-a5fd-11eb-8828-2bc58ad03e07.PNG)

```c
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
```
Untuk melakukan zip, pertama akan dilakukan string copy currenT1 ke currentT3 {dimana currenT1 adalah nama folder yang sudah dibuat}, tujuan string copy ini agar nama folder sesudah dizip tetap sama dengan nama folder sesudah di zip, lalu akan dibuat sebuah proses baru dengan fork dan jika tersedia maka akan dibuat zip dengan nama currentT3.

```c
                    while(wait(&stat_zip)>0);
                    chillid5 = fork();
                    if(chillid5<0)
                        exit(0);
                    if(chillid5==0){
                        char *argv[] = {"rm", "-r", currenT1, NULL};
                        execv("/bin/rm", argv);
                    }
```
Untuk melakukan delete, pertama akan menunggu proses zip selesai lalu membuat proses baru dengan fork dan selanjutnya folder yang telah di zip di delete dengan command "rm"

**Nomor 3d**
```c
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
```
Dengan adanya 2 command yang diminta pada soal dimana yang pertama terdapat command `-x` dimana command `-x` akan membuat program killer membunuh parent proses sedangkan membiarkan child proses bekerja hingga selesai, sedangkan untuk command `-z` program killer akan membunuh semua proses yang sedang berjalan sehingga program akan berhenti sesaat setelah program kille dijalankan

**Nomor 3e**

Dengan adanya 2 command yaitu `-x` & `-z`, maka akan dihasilkan 2 output yang berbeda ketika killer dijalankan yang akan ditampilkan dalam gambar sebagai berikut :

-Command `-x`:

![-x](https://user-images.githubusercontent.com/70801807/115993127-99c30000-a5fb-11eb-8b43-4fe06cd2e57f.PNG)
![-xproof](https://user-images.githubusercontent.com/70801807/115993168-cd058f00-a5fb-11eb-84c3-05d0e5ef55ac.PNG)
![-xprooof](https://user-images.githubusercontent.com/70801807/115993177-d55dca00-a5fb-11eb-8487-b8f533d58fc6.PNG)



Dari foto di atas terlihat bahwa sesaat setelah killer dijalankan program masih meneruskan tugasnya hingga melakukan zip dan delete folder



-Commmand `-z`:

![-z](https://user-images.githubusercontent.com/70801807/115993195-ed354e00-a5fb-11eb-8b5f-42a34189f9fc.PNG)
![-zprooooff](https://user-images.githubusercontent.com/70801807/115993201-f58d8900-a5fb-11eb-99ed-aae12c9d3655.PNG)

Dari foto di atas terlihat bahwa sesaat setelah killer dijalakan program menghentikan prosesnya.

### **Kendala**
1. Kurang paham dalam pembuatan killer.sh sehingga berdampak pada gagalnya program mode -x dijalankan
2. Salah penempatan proses zip dan delete yang mengakibatkan folder dibuat lebih lama dari 40 detik

