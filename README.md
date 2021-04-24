# Soal Shift Sisop Modul 2 C08 2021  

Anggota:
- 05111940000112 Deka Julian Arrizki	    
- 05111940000141 Muhammad Farhan Haykal	
- 05111940000158 Shahnaaz Anisa Firdaus

## SOAL 1   
Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi.
a. Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg.  

b. untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga.  

    ``` Foto  : https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/view
        Musik : https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view
        Film  : https://drive.google.com/file/d/1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp/view  
    ```
    
c. Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload serta,  

d. memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan).  

e. Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany).   

f. Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip).


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

## **Pembahasan**
- **NOMOR 2a**
```
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
```
if (child_id1 == 0) {
   execl("/usr/bin/unzip", "unzip", "pets.zip", NULL); 
}
```
- kemudian menghapus semua folder yang tidak penting, karena folder maka ciri utama dalam penamaan tidak memakai titik (.) sehingga saya mengakali dengan nama. setiap nama yang tidak ada titik (.) maka itu folder dan apabila ada maka itu termasuk file yang digunakan pada proses selanjutnya.
```
d = opendir("/home/deka/modul2/petshop/");
while ((dir = readdir(d)) != NULL){
char *temp1 = strchr(dir->d_name,';');
char *temp2 = strchr(dir->d_name, '.');    
```
- setelah mengetahui mana yang folder dan mana yang file maka tinggal hapus folder yang diperoleh
```
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
```
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

- **NOMOR 2d**
- **NOMOR 2e**
