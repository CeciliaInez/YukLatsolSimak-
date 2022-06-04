#include <stdio.h>  //Deklarasi library yang digunakan yaitu standart input dan output
#include <stdlib.h>
#include <string.h>  //Deklarasi library yang digunakan yaitu untuk string
#include <stdbool.h> //deklarasi library untuk melakukan operasi boolean
#include <assert.h> //Deklarasi library untuk memverifikasi asumsi yang dibuat program dan memprint jika asumption salah
#include <conio.h>

#define CHAR_MAX_LOGIN 100
#define CHAR_MAX_PERTANYAAN (CHAR_MAX_LOGIN)
#define CHAR_MAX_PG 50
#define CHAR_MAX_PELAJARAN (CHAR_MAX_PG)
#define CHAR_MAX_JAWABAN 2
#define CHAR_MAX_SOAL (CHAR_MAX_PELAJARAN + CHAR_MAX_PERTANYAAN + (CHAR_MAX_PG * 4) + CHAR_MAX_JAWABAN)
#define CHAR_MAX_NAMA (CHAR_MAX_PG)
#define CHAR_MAX_JAWABAN_SISWA (CHAR_MAX_NAMA + 50 + CHAR_MAX_PELAJARAN)

#define DELIMITER ";"//untuk memisahkan data dengan data lainnya

//DEFINE FILE NAME
#define NAME_LOGIN "login.txt"
#define NAME_SOAL "soal.txt"
#define NAME_JAWABAN_SISWA "jawabansiswa.txt"

#define BANYAK_SOAL_DIBERIKAN 10
#define isspace(c) ((c) == ' ')

typedef struct {
    char pelajaran[CHAR_MAX_PELAJARAN];
    char pertanyaan[CHAR_MAX_PERTANYAAN];
    char A[CHAR_MAX_PG];
    char B[CHAR_MAX_PG];
    char C[CHAR_MAX_PG];
    char D[CHAR_MAX_PG];
    char jawaban[CHAR_MAX_JAWABAN]; // A, B, C, D
} isiSoal;

typedef struct S {
    isiSoal isi;
    struct S *next;
} soal;

typedef struct {
    char nama[CHAR_MAX_NAMA];
    int score;
} isiJawabanSiswa;

typedef struct J {
    isiJawabanSiswa jawaban;
    struct J *next;
} jawabanSiswa;

typedef struct {
    char username[CHAR_MAX_LOGIN];
    char password[CHAR_MAX_LOGIN];
} loginAdmin;

/* deklarasi function */
void opening();
double toDouble(const char *s, int start, int stop);  //Untuk merubah String (array of char) menjadi double<br>
int toInt(const char *string);  //Untuk merubah string (array of char) menjadi integer (int)
char *inputString(char message[], int size);  //Fungsi untuk melakukan input string (array of char)
int inputInt(char message[], int min, int max);  //Fungsi untuk melakukan input integer (int)
int randint(int n);  //menghasilkan random int secara acak
isiSoal getSoal(soal *headSoal, int index);  //untuk insert soal
int countSoal(soal *headSoal);  //untuk menghitung banyaknya soal
soal *bacaSoal(soal *head);  //fungsi mengambil soal dari txt
jawabanSiswa *bacaJawabanSiswa(jawabanSiswa *head);  //membaca jawaban siswa dalam file txt
void rewriteSoal(soal * head);  //menyimpan soal di txt
//bool = tipe data yang dapat menyimpan true/false. true = nilai bukan 0, false = nilai 0
bool isSoalSudahDiberikan(int const soalSudahDiberikan[], int cur);  //memeriksa agar soal tidak ada yang keluar sama

/* void menu siswa */
void siswa(soal *headSoal, jawabanSiswa *headJawabanSiswa);  //function menampilkan menu siswa
void panduan();  //informasi permainan
int soalLatihan(isiSoal isi);  //menampilkan soal dan jawaban (menu siswa)
void mulaiLatihan(soal *headSoal, jawabanSiswa *headJawabanSiswa);  //fungsi siswa mengerjakan soal
int countJawabanSiswa(jawabanSiswa *headJawabanSiswa);  //menghitung jawaban siswa

/* void menu admin */
void menuAdmin(soal *headSoal, jawabanSiswa *headJawabanSiswa);  //function menampilkan menu Admin
void admin(soal *headSoal, jawabanSiswa *headJawabanSiswa);  //function untuk register akun
void signUp();  //function sign up admin
void signIn(soal *headSoal, jawabanSiswa *headJawabanSiswa);  //function sign in admin
bool isUsernameAndPasswordAvail(char const username[], char const password[]);  //mengecek akun admin di file login txt
void printSoal(soal *head);  //fungsi soal dalam menu admin
void printJawaban(jawabanSiswa *head);  //menampilkan soal dan jawaban (menu admin)
soal *tambahSoal(soal *head);  //function untuk menambahkan soal
soal *editSoal(soal *head);  //function mengedit soal
soal *hapusSoal(soal *head);  //function menghapus soal
void menampilkanHighScore(jawabanSiswa *headJawabanSiswa);  //function menampilkan highscore siswa

void opening(){
	system("cls"); system("color F0");
	#pragma omp master
	{
	printf("\n\n\n\t\t\t-------------------------------------------------");
	printf("\n\t\t\t|\t\tYuk Latsol Simak\t\t|\n");
	printf("\t\t\t| --------------------------------------------- |");
	printf("\n\t\t\t|\t\t    Made by :\t\t\t|\n");
	printf("\t\t\t|\t\t\t\t\t\t|\n");
	printf("\t\t\t|   1. Cecilia Inez Reva Manurung 2106636994\t|\n");
	printf("\t\t\t|   2. Shabrina Kamiliya Wiyana 2106733894\t|\n");
	printf("\t\t\t|\t\t\t\t\t\t|\n");
	printf("\t\t\t-------------------------------------------------\n\n\n\n\n");
	}
	system("pause"); system("color 07");
}

int main(){
    int peran;
    soal *headSoal = NULL;
    jawabanSiswa *headJawabanSiswa = NULL;

    #pragma omp parallel sections
    {
    	#pragma omp section
    	headSoal = bacaSoal(headSoal);
    	
    	#pragma omp section
    	headJawabanSiswa = bacaJawabanSiswa(headJawabanSiswa);
	}
	opening();
    do {
        system("cls");
	    printf("\n\t\t\t================================================\n");
	    printf("\t\t\t   SELAMAT DATANG DI APLIKASI YUKLATSOLSIMAK!\n");
	    printf("\t\t\t------------------------------------------------\n");
	    printf("\t\t\t 1.  Masuk sebagai Siswa\n");
	    printf("\t\t\t 2.  Masuk sebagai Admin\n");
	    printf("\t\t\t 3.  Keluar             \n");
	    printf("\t\t\t------------------------------------------------\n");
	    printf("\t\t\tPilih : ");
	    scanf("\t\t\t%d", &peran);

        switch (peran) {
            case 1:
                siswa(headSoal, headJawabanSiswa);
                break;
            case 2:
                admin(headSoal, headJawabanSiswa);
                break;
            case 3:
            	system("cls"); system("color 0D");
            	printf("\n\n\t\t\tTerima kasih telah menggunakan aplikasi kami!\n\n\n\n");
                break;
            default :
                printf("\n\t\t\tInput Error!\n");
                break;
        }
    } while(peran != 3);

    free(headSoal);
    free(headJawabanSiswa);

    return 0;
}

void siswa(soal *headSoal, jawabanSiswa *headJawabanSiswa){  //function menampilkan menu siswa
    int selectMenu;

    do{
        system("color 06"); system("cls");
	    printf("\n\t\t\t================  MENU SISWA  ================\n");
	    printf("\n\t\t\t   Silahkan Memilih Menu Yang Anda Inginkan\n");
	    printf("\n\t\t\t----------------------------------------------\n");
	    printf("\t\t\t 1.  Informasi Aplikasi\n");
	    printf("\t\t\t 2.  Memulai Mengerjakan\n");
	     printf("\t\t\t 3.  Menampilkan Highscore\n");
	    printf("\t\t\t 4.  Logout\n");
	    printf("\t\t\t----------------------------------------------\n");
    	printf("\t\t\tPilih : ");
        scanf("%d", &selectMenu);

        switch(selectMenu){
            case 1:
                panduan();
                break;
            case 2:
                mulaiLatihan(headSoal, headJawabanSiswa);
                break;
            case 3:
            	system("cls");
                menampilkanHighScore(headJawabanSiswa);
                break;
            case 4:
            	system("color 07");
                break;
        }
    }while (selectMenu != 4);
    
}

void panduan(){  //informasi permainan
    system("cls");
	
	#pragma omp parallel
	{
		int tid;
		tid = omp_get_thread_num();
		
		if (tid == 0){
			printf("\tProgram ini akan memberikan soal yang telah\n");
		    printf("\tdisimpan pada file, siswa dapat mulai mengerjakan\n");
		    printf("\tsoal yang diberikan, dan diakhir akan \n");
		    printf("\tditampilkan skor para peserta yang telah mengerjakan\n");
		}
		if(tid == 1){
			printf("\n\tPANDUAN PROGRAM\n");
		}
	}

    fflush(stdin);
    getchar();
}

int soalLatihan(isiSoal isi){  //menampilkan soal dan jawaban (menu siswa)
//menyimpan input ke struct isiSoal
	system("cls");
	printf("\n\nPelajaran  : %s\n", isi.pelajaran);
   	printf("\nPertanyaan : %s\n", isi.pertanyaan);
   	printf("A. %s\n", isi.A);
   	printf("B. %s\n", isi.B);
   	printf("C. %s\n", isi.C);
   	printf("D. %s\n", isi.D);	
	
    char jawaban[CHAR_MAX_JAWABAN] = "";

    strcpy(jawaban, inputString("\nJawaban    : ", CHAR_MAX_JAWABAN));
    if(strcmp(jawaban, isi.jawaban) == 0){
        printf("\nJawaban benar.\n");
        return 1;
    }
    return 0;
}

void mulaiLatihan(soal *headSoal, jawabanSiswa *headJawabanSiswa){  //fungsi siswa mengerjakan soal

    isiJawabanSiswa isiJawabanSiswa;

	system("cls");
    strcpy(isiJawabanSiswa.nama, inputString("\n\n\t\t\tMasukan nama : ", CHAR_MAX_NAMA));
    printf("\n\n\n\t\t\tSelamat Mengerjakan! Semangat!\n\n\n");
    system("pause");
    
    int soalSudahDiberikan[BANYAK_SOAL_DIBERIKAN];
    isiSoal isi;
    int banyakSoal = countSoal(headSoal);
    int jumlahBenar = 0;
    int i;
    for(i = 0; i < BANYAK_SOAL_DIBERIKAN; i++){
        int cur = randint(banyakSoal) + 1;

        if(!isSoalSudahDiberikan(soalSudahDiberikan, cur)){

            isi = getSoal(headSoal, cur); //mengisi soal
            // tampilkan soal
            if(soalLatihan(isi) == 1) {
                // jika jawaban benar
                jumlahBenar++;
            }
            soalSudahDiberikan[i] = cur;
            i++;
        }
    }
    
    isiJawabanSiswa.score = jumlahBenar * 10;  //nilai point
    
    FILE *f;
    f = fopen("jawabansiswa.txt", "a+");
    if(f == NULL){
        fputs("\nError membaca file!\n", stderr); 
        exit(1);
    }
    char data[CHAR_MAX_JAWABAN_SISWA];
    sprintf(data, "%s;%d\n", isiJawabanSiswa.nama, isiJawabanSiswa.score);
    //write to file 
    fputs(data, f);
    fclose(f);
    
    jawabanSiswa *temp = (jawabanSiswa *) malloc(sizeof(jawabanSiswa));
    temp->jawaban = isiJawabanSiswa;
    temp->next = NULL;

    if (headJawabanSiswa == NULL){
        headJawabanSiswa = temp;
    } else if (headJawabanSiswa->next == NULL){
        headJawabanSiswa->next = temp;
    } else{
        jawabanSiswa *x = headJawabanSiswa;
        while (x->next != NULL){
            x = x->next;
        }
        x->next = temp;
    }
	fflush(stdin);
    getchar();
}

int countJawabanSiswa(jawabanSiswa *headJawabanSiswa){  //menghitung jawaban siswa
    int count = 0;
    jawabanSiswa *q = headJawabanSiswa;
    
    while (q != NULL){
        count++;
        q = q->next;
    }
    return count;
}

isiSoal getSoal(soal *headSoal, int index){  //untuk mengisi soal
    int no = 1;
    isiSoal isi;
    soal *q = headSoal;
    
    while (q != NULL){
        if(no++ == index){
            isi = q->isi;
        }
        q = q->next;
    }
    return isi;
}

int countSoal(soal *headSoal){  //untuk menghitung banyaknya soal
    int count = 0;
    soal *q = headSoal;
    
    while (q != NULL){
        count++;
        q = q->next;
    }
    return count;
}

bool isSoalSudahDiberikan(int const soalSudahDiberikan[], int cur){  //memeriksa agar soal tidak ada yang keluar sama
	int i;
	
    for(i = 0; i < BANYAK_SOAL_DIBERIKAN; i++){
        if(soalSudahDiberikan[i] == cur){
            return true;  //true = jika soal sudah diberikan
        }
    }
    return false;  //false jika soal belum pernah diberikan
}

soal *bacaSoal(soal *head){  //fungsi mengambil soal dari txt

    FILE *f;
    f = fopen("soal.txt", "r");
    
    if (f == NULL){
        fputs("Error membaca file\n", stderr);
        exit(1);
    }

    //Penampung pembacaan satu baris dari file
    char buffer[CHAR_MAX_SOAL] = "";
    int idx;

    while (fgets(buffer, sizeof(buffer), f)){
        //Menghapus enter pada karakter terakhir
        buffer[strlen(buffer) - 1] = '\0';
        idx = 0;
        //Proses pemisahan antara data
        char *hasil = strtok(buffer, DELIMITER);
         //Setelah dipisahkan dari buffer, akan dimasukan kedalam struct soal
        soal *temp = (soal *) malloc(sizeof(soal) * 225);
        
        while (hasil){
            if (idx == 0){
                strcpy(temp->isi.pelajaran, hasil);
            } else if(idx == 1){
                strcpy(temp->isi.pertanyaan, hasil);
            } else if(idx == 2){
                strcpy(temp->isi.A, hasil);
            } else if(idx == 3){
                strcpy(temp->isi.B, hasil);
            } else if(idx == 4){
                strcpy(temp->isi.C, hasil);
            } else if(idx == 5){
                strcpy(temp->isi.D, hasil);
            } else if(idx == 6){
                strcpy(temp->isi.jawaban, hasil);
            }
            hasil = strtok(NULL, DELIMITER);
            idx++;
        }
        temp->next = NULL;

        if (head == NULL){
            head = temp;
        } else if (head->next == NULL) {
            head->next = temp;
        } else {
            soal *x = head;
            while (x->next != NULL) {
                x = x->next;
            }
            x->next = temp;
        }
    }
    fclose(f);
    return head;
}

jawabanSiswa *bacaJawabanSiswa(jawabanSiswa *head){  //membaca jawaban siswa dalam file txt

    FILE *f;
    f = fopen("jawabansiswa.txt", "r");

    if (f == NULL) {
        fputs("Error membaca file!\n", stderr);
        exit(1);
    }
    //Penampung pembacaan satu baris dari file
    char buffer[CHAR_MAX_JAWABAN_SISWA] = "";
    int idx;
    
    while (fgets(buffer, sizeof(buffer), f)){
        //Menghapus enter pada karakter terakhir
        buffer[strlen(buffer) - 1] = '\0';
        idx = 0;
        //Proses pemisahan antara data
        char *hasil = strtok(buffer, DELIMITER);
        //Setelah dipisahkan dari buffer, akan dimasukan kedalam struct jawaban_siswa
        jawabanSiswa *temp = (jawabanSiswa *) malloc(sizeof(jawabanSiswa) * 255);
        
        while (hasil){
            if (idx == 0) {
                strcpy(temp->jawaban.nama, hasil);
            } else if(idx == 1){
                temp->jawaban.score = toInt(hasil);
            }
            hasil = strtok(NULL, DELIMITER);
            idx++;
        }
        temp->next = NULL;

        if (head == NULL){
            head = temp;
        } else if(head->next == NULL){
            head->next = temp;
        } else{
            jawabanSiswa *x = head;
            while (x->next != NULL){
                x = x->next;
            }
            x->next = temp;
        }
    }
    fclose(f);

    return head;
}

void admin(soal *headSoal, jawabanSiswa *headJawabanSiswa){  //function untuk register akun
    int pilihan;
    
    do{
    	system("color 0A"); system("cls");
    	#pragma omp single
    	{
		printf("\n\t\t\t=============================\n");
	    printf("\t\t\t\tREGISTER AKUN\n");
	    printf("\t\t\t-----------------------------\n");
	    printf("\t\t\t 1.  Sign Up\n");
	    printf("\t\t\t 2.  Sign In\n");
	    printf("\t\t\t 3.  Sign Out\n");
	    printf("\t\t\t-----------------------------\n");
	    printf("\t\t\tPilih : ");
	    scanf("\t\t\t%d", &pilihan);
		}

        switch (pilihan){
            case 1:
                signUp();
                break;
            case 2:
                signIn(headSoal, headJawabanSiswa);
                break;
            case 3:
                //sign out
                break;
            default:
                printf("Pilih 1, 2 atau 3 saja!\n");
        }
    } while (pilihan != 3);
}

bool isUsernameAndPasswordAvail(char const username[], char const password[]){  //mengecek akun admin di file login txt
    FILE *f;
    f = fopen("login.txt", "r");
    if (f == NULL) {
        fputs("\nFile tidak ditemukan!\n", stderr);
        exit(1);
    }
    //Penampung pembacaan satu baris dari file
    char buffer[CHAR_MAX_LOGIN * 2] = "";

    //Setelah dipisahkan dari buffer, akan dimasukan kedalam struct login
    loginAdmin login;
    int idx;
    bool usernameAndPassAvail = false;  //false = tidak ditemukan akun dalam file txt

    while (fgets(buffer, sizeof(buffer), f)) {
        //Menghapus enter pada karakter terakhir
        buffer[strlen(buffer) - 1] = '\0';
        idx = 0;
        //Proses pemisahan antara username dan password
        char *hasil = strtok(buffer, DELIMITER);
        while (hasil){
            if (idx == 0) {
                strcpy(login.username, hasil);
            } else if (idx == 1){
                strcpy(login.password, hasil);
            }
            hasil = strtok(NULL, DELIMITER);
            idx++;
        }
        if ((strcmp(login.username, username) == 0) && strcmp(login.password, password) == 0) {
            usernameAndPassAvail = true;  //true = ditemukan akun dalam file txt
            break;
        }
    }
    fclose(f);
    return usernameAndPassAvail;
}

void signUp(){  //function sign up admin
    system("cls");

    FILE *f;
    f = fopen("login.txt", "a+");
    if (f == NULL) {
        fputs("\nError!", stderr);
        exit(1);
    }

    loginAdmin sign;

	#pragma omp task
	{
	printf("\n\t\t\t============================\n");
    printf("\t\t\t\t  Buat Akun\n");
    printf("\t\t\t----------------------------\n");
	}
		

    strcpy(sign.username, inputString("\t\t\tUsername : ", CHAR_MAX_LOGIN));
    strcpy(sign.password, inputString("\t\t\tPassword : ", CHAR_MAX_LOGIN));

    
    // true jika ditemukan atau sudah terdaftar
    if(isUsernameAndPasswordAvail(sign.username, sign.password)){
        printf("\n\nAkun telah terdaftar.\nSilahkan buat yang lain.\n");
    } else{

        char data[CHAR_MAX_LOGIN * 2];
        sprintf(data, "%s;%s\n", sign.username, sign.password);
        fputs(data, f);

        printf("\nprocessing...");
        sleep(5);
        printf("\n");
        printf("\nAkun Telah Terdaftar.");
    }
    fclose(f);
    
    fflush(stdin);
    getchar();
}

void signIn(soal *headSoal, jawabanSiswa *headJawabanSiswa){  //function sign in admin
    char username[CHAR_MAX_LOGIN];
    char password[CHAR_MAX_LOGIN];
    FILE *f;
    f = fopen("login.txt", "r");
    if (f == NULL) {
        fputs("\nFile tidak ditemukan!\n", stderr);
        exit(1);
    }
	
	system("cls");
    printf("\n\t\t\t============================================\n");
    printf("\t\t\t  Masukan Kombinasi Username dan Password\n");
    printf("\t\t\t--------------------------------------------\n");
    strcpy(username, inputString("\t\t\tUsername : ", CHAR_MAX_LOGIN));
    strcpy(password, inputString("\t\t\tPassword : ", CHAR_MAX_LOGIN));


    //Penampung pembacaan satu baris dari file
    char buffer[CHAR_MAX_LOGIN * 2] = "";
    //Setelah dipisahkan dari buffer, akan dimasukan kedalam struct login
    loginAdmin login;
    int idx;
    bool loginSuccess = false;

    while (fgets(buffer, sizeof(buffer), f)){
        // Menghapus enter pada karakter terakhir
        buffer[strlen(buffer) - 1] = '\0';

        idx = 0;

        //Proses pemisahan antara username dan password
        char *hasil = strtok(buffer, DELIMITER);
        
        while (hasil){
            if (idx == 0){
                strcpy(login.username, hasil);
            } else if (idx == 1) {
                strcpy(login.password, hasil);
            }
            hasil = strtok(NULL, DELIMITER);
            idx++;
        }

        if ((strcmp(login.username, username) == 0) && strcmp(login.password, password) == 0) {
            loginSuccess = true;
        }
    }

    fclose(f);

    if (!loginSuccess) {
        printf("\nAkun Tidak Terdaftar!\n");
        printf("Silahkan daftar terlebih dahulu");
        sleep(2);
    } else {
        printf("\nloading....");
        sleep(3);
        printf("\nLogin Success");
        menuAdmin(headSoal, headJawabanSiswa);
    }
}

void menuAdmin(soal *headSoal, jawabanSiswa *headJawabanSiswa){  //function menampilkan menu Admin
    int selectMenu;

    do{
		system("cls"); system("color 07");
		printf("\n\t\t\t================  MENU ADMIN  ================\n");
		printf("\n\t\t\t   Silahkan Memilih Menu Yang Anda Inginkan\n");
	    printf("\n\t\t\t----------------------------------------------\n");
        printf("\t\t\t 1.  Tambah Soal\n");
        printf("\t\t\t 2.  Edit Soal\n");
        printf("\t\t\t 3.  Hapus Soal\n");
        printf("\t\t\t 4.  Menampilkan Highscore\n");
        printf("\t\t\t 5.  Kembali ke Menu Utama\n");
        printf("\t\t\t----------------------------------------------\n");
        printf("\t\t\tPilih : ");
        scanf("%d", &selectMenu);

        switch (selectMenu) {
            case 1:
            	system("cls");
                headSoal = tambahSoal(headSoal);
                break;
            case 2:
            	system("cls");
                headSoal = editSoal(headSoal);
                break;
            case 3:
            	system("cls");
                headSoal = hapusSoal(headSoal);
                break;
            case 4:
            	system("cls");
                menampilkanHighScore(headJawabanSiswa);
                break;
            case 5:
                break;
        }
    } while (selectMenu != 5);
}

soal *tambahSoal(soal *head){  //function untuk menambahkan soal

     //Setelah dipisahkan dari buffer, akan dimasukan kedalam struct soal
    isiSoal isi;
    
    strcpy(isi.pelajaran, inputString("\n\nPelajaran  : ", CHAR_MAX_PELAJARAN));
    strcpy(isi.pertanyaan, inputString("\nPertanyaan : ", CHAR_MAX_PERTANYAAN));
    strcpy(isi.A, inputString("A : ", CHAR_MAX_PG));
    strcpy(isi.B, inputString("B : ", CHAR_MAX_PG));
    strcpy(isi.C, inputString("C : ", CHAR_MAX_PG));
    strcpy(isi.D, inputString("D : ", CHAR_MAX_PG));

    do{
        strcpy(isi.jawaban, inputString("\nJawaban    : ", CHAR_MAX_JAWABAN));
    } while((strcmp(isi.jawaban, "A") != 0) && (strcmp(isi.jawaban, "B") != 0) &&
			(strcmp(isi.jawaban, "C") != 0) && (strcmp(isi.jawaban, "D") != 0));

    FILE *f;
    f = fopen("soal.txt", "a+");

    if (f == NULL) {
        fputs("Error membaca file!\n", stderr);
        exit(1);
    }

    char data[CHAR_MAX_SOAL];
    sprintf(data, "%s;%s;%s;%s;%s;%s;%s\n", isi.pelajaran, isi.pertanyaan, isi.A, isi.B, isi.C, isi.D, isi.jawaban);
    fputs(data, f);

    fclose(f);

    soal *temp = (soal *) malloc(sizeof(soal) * 255);
    temp->isi = isi;
    temp->next = NULL;

    if (head == NULL){
        head = temp;
    } else if(head->next == NULL){
        head->next = temp;
    } else{
        soal *x = head;
        while (x->next != NULL){
            x = x->next;
        }
        x->next = temp;
    }
    printf("Data berhasil ditambahkan.\n\n\n");
    printSoal(head);
    return head;
}

void printSoal(soal *head){  //menampilkan soal soal dan jawaban (menu admin)
	
    if (head == NULL){
        printf("list is empty");
    } else{
        soal *q = head;
        printf("===============\n"
               "  TAMPIL DATA\n"
               "===============\n\n");
        int idx = 1;
        
        while (q != NULL){
            printf("\n%d. Pelajaran  : %s\n", idx++, q->isi.pelajaran);
            printf("Pertanyaan : %s\n", q->isi.pertanyaan);
            printf("A. %s\n", q->isi.A);
            printf("B. %s\n", q->isi.B);
            printf("C. %s\n", q->isi.C);
            printf("D. %s\n", q->isi.D);
            printf("Jawaban    : %s\n", q->isi.jawaban);
            q = q->next;
        }
        system("pause");
    }
}

void printJawaban(jawabanSiswa *head){  //fungsi soal dalam menu admin
    if (head == NULL){
        printf("list is empty");
    } else{
        jawabanSiswa *q = head;
        printf("===============\n"
               "TAMPIL DATA\n"
               "===============\n");
        while (q != NULL){
            printf("Nama       : %s\n", q->jawaban.nama);
            printf("Skor       : %d\n", q->jawaban.score);
            q = q->next;
        }
    }
}

void rewriteSoal(soal * head){  //menyimpan soal di txt
    FILE *f;
    f = fopen("soal.txt", "w");
    if (f == NULL) {
        fputs("\nError!", stderr);
        exit(1);
    }

    soal *q = head;
    char data[CHAR_MAX_SOAL];
    while (q != NULL) {

        sprintf(data, "%s;%s;%s;%s;%s;%s;%s\n", q->isi.pelajaran, q->isi.pertanyaan,
				q->isi.A, q->isi.B, q->isi.C, q->isi.D, q->isi.jawaban);
        fputs(data, f);
        q = q->next;
    }
    fclose(f);
}

soal *editSoal(soal *head){  //function mengedit soal
	
    printSoal(head);
    
    int soalDipilih;
    int banyakSoal = countSoal(head);

    char text[CHAR_MAX_LOGIN * 2];
    sprintf(text, "\nPilih [1 - %d]: ", banyakSoal);
    soalDipilih = inputInt(text, 0, banyakSoal);

    soal *q = head;
    int idx = 1;
    while (q != NULL){
        if(idx++ == soalDipilih){

            isiSoal isi;

            strcpy(isi.pelajaran, inputString("\n\nPelajaran  : ", CHAR_MAX_PELAJARAN));
            strcpy(isi.pertanyaan, inputString("\nPertanyaan : ", CHAR_MAX_PERTANYAAN));
            strcpy(isi.A, inputString("A : ", CHAR_MAX_PG));
            strcpy(isi.B, inputString("B : ", CHAR_MAX_PG));
            strcpy(isi.C, inputString("C : ", CHAR_MAX_PG));
            strcpy(isi.D, inputString("D : ", CHAR_MAX_PG));
            strcpy(isi.jawaban, inputString("\nJawaban    : ", CHAR_MAX_JAWABAN));

            q->isi = isi;
            printf("\n\nData berhasil dirubah.\n");
            break;
        }
        q = q->next;
    }
    rewriteSoal(head);
    return head;
}

soal *hapusSoal(soal *head){  //function menghapus soal

    printSoal(head);

    int soalDipilih;
    int banyakSoal = countSoal(head);

    char text[CHAR_MAX_LOGIN * 2];
    sprintf(text, "\nPilih [1 - %d]: ", banyakSoal);
    soalDipilih = inputInt(text, 0, banyakSoal);

    if(soalDipilih == 1){
        soal *temp = head;
        free(temp);
        head = head->next;
    } else{
        soal *q = head;
        int idx = 1;
        
        while (q->next != NULL){
            if (idx++ == soalDipilih - 1){
                soal *temp = q->next;
                free(temp);
                q->next = q->next->next;
                printf("\n\nData berhasil dihapus.\n");
                banyakSoal--;
                break;
            } else{
                q = q->next;
            }
        }
    }
    rewriteSoal(head);
    return head;
}

void menampilkanHighScore(jawabanSiswa *headJawabanSiswa){  //function highscore siswa

    jawabanSiswa *q = headJawabanSiswa;
    int banyakJawabanSiswa = countJawabanSiswa(headJawabanSiswa);

    isiJawabanSiswa listJawabanSiswa[banyakJawabanSiswa];
    int idx = 0;
    while (q != NULL){
        listJawabanSiswa[idx++] = q->jawaban;
        q = q->next;
    }

    //proses pengurutan menggunakan bubble sort
    int i;
    #pragma omp for
    
    for(i = 0; i < banyakJawabanSiswa-1; i++){
        int j;
        for(j = 0; j < banyakJawabanSiswa-i-1; j++){
            if(listJawabanSiswa[j].score < listJawabanSiswa[j+1].score){
                isiJawabanSiswa temp = listJawabanSiswa[j];
                listJawabanSiswa[j] = listJawabanSiswa[j+1];
                listJawabanSiswa[j+1] = temp;
            }
        }
    }

    printf("\n\n\n\t\t---------------------------------------------------------------------------------");
	printf("\n\t\t|\t\t\t\tH I G H S C O R E\t\t\t\t|\n");
	printf("\t\t| ----------------------------------------------------------------------------- |\n");

    for(i = 0; i < banyakJawabanSiswa; i++){
        printf("\n\t\t   Siswa dengan nama \"%s\" mendapatkan score \"%d\" \n", listJawabanSiswa[i].nama,
				listJawabanSiswa[i].score);
		if(listJawabanSiswa[i].score > 90){
			printf("\t\t   Rekomendasi jurusan = Pendidikan Dokter, Aktuaria, Ilmu Komputer \n");
		}
		else if(listJawabanSiswa[i].score >= 80 && listJawabanSiswa[i].score <= 90){
			printf("\t\t   Rekomendasi jurusan = Arsitektur Interior, Teknik Industri \n");
		}
		else if(listJawabanSiswa[i].score >= 60 && listJawabanSiswa[i].score <= 80){
			printf("\t\t   Rekomendasi jurusan = Matematika, Fisika \n");
		}
		else if(listJawabanSiswa[i].score < 60){
			printf("\t\t   Mohon ulang latihan lagi. \n");
		}
		printf("\t\t _______________________________________________________________________________\n");
    }

    fflush(stdin);
    getchar();
}


double toDouble(const char *s, int start, int stop){  //Untuk merubah String (array of char) menjadi double<br>
    unsigned long long int m = 1;
    double ret = 0;
    int i;
    for(i = stop; i >= start; i--){
        ret += (s[i] - '0') * m;
        m *= 10;
    }
    return ret;
}

int toInt(const char *string){  //Untuk merubah string (array of char) menjadi integer (int)
    int digit, isneg;
    int value;

    isneg = 0;
    value = 0;
    for(; isspace (*string); string++);    /* gobble up leading whitespace */

    /* do I have a sign? */
    if(*string == '-'){
    	isneg = 1;
        string++;
    } else if (*string == '+')
        string++;

    for(; *string; string++){
        if(*string >= '0' && *string <= '9')
        	digit = *string - '0';
        else
            break;
        value *= 10;
        value += digit;
    }

    if(isneg)
        value = 0 - value;
    return(value);
}

char *inputString(char message[], int size){  //Fungsi untuk melakukan input string (array of char)
    char *input = malloc(sizeof(input) * size);
    int len;

    do{
        fflush(stdin); // release buffer
        printf("%s", message);  //pesan kepada user (meminta jawaban)
        scanf("%[^\n]", input);

        len = (int) strlen(input);

        if(len == 0){
            printf("Input tidak boleh kosong!\n");
        } else if (len > size){  //ukuran atau panjang maksimal string
            printf("Input tidak boleh lebih dari %i karakter!\n", size);
        }
    } while(len < 0 || len > size);
    return input;
}

int inputInt(char message[], int min, int max){  //Fungsi untuk melakukan input integer (int)
    int hasil;
    int size = 15;
    char *input = malloc(sizeof(input) * size);
    int len;

    do{
        fflush(stdin); // release buffer
        printf("%s", message);  //isi pesan kepada user
        scanf("%[^\n]", input);

        len = (int) strlen(input);

        if(len == 0){
            printf("Input tidak boleh kosong!\n");
        } else if (len > size){
            printf("Input tidak boleh lebih dari %i karakter!\n", size);
        } else{
            hasil = toInt(input);

            if(hasil < min){  //input tidak boleh kurang dari...
                printf("Input tidak boleh kurang dari %d\n", min);
            } else if(hasil > max){  //input tidak boleh lebih dari...
                printf("Input tidak boleh lebih dari %d\n", max);
            }
        }
    } while(len < 0 || len > size || hasil < min || hasil > max);

    free(input);
    return hasil;
}

int randint(int n){  //menghasilkan random int secara acak
	
    if((n - 1) == RAND_MAX){
        return rand();
    } else{
        assert (n <= RAND_MAX);
        //untuk memeriksa kondisi tertentu saat runtime dan berguna saat men-debug program
        
        int end = RAND_MAX / n;
        assert (end > 0);
        end *= n;
        
        int r;
        while ((r = rand()) >= end);
        return r % n;  //return integer dalam range [0, n]
    }
}
