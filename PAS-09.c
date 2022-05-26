#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include <ctype.h>

typedef struct soal{
	char pertanyaan[100];
	char opsiA[25];
	char opsiB[25];
	char opsiC[25];
	char opsiD[25];
	char jawabanPilgan[10];
	struct soal *next;  //address next soal
}soal;

typedef struct siswa{
	char nama[100];
	double score;
	struct siswa *next;  //address next soal
}siswa;

struct login{ //deklarasi struct
	char username[100];
	char password[100];
};
soal *head;
siswa *data;

void game(soal *head, siswa **data){
	int urutan;
	int jumlahBenar = 0;
	char jawab[10];
	
	struct soal *currentSoal = head;
	struct siswa *currentData = malloc(sizeof(struct siswa));
	currentData->next = NULL;
	
	system("cls");
	printf("Nama : ");
	scanf(" %[^\n]s", currentData->nama);
	
	if (currentSoal != NULL){
		while (currentSoal != NULL && urutan != 5){
			printf("\n%s\n\n", currentSoal->pertanyaan);
			printf("A. %-10s C. %-10s\n", currentSoal->opsiA, currentSoal->opsiC);
			printf("B. %-10s D. %-10s\n", currentSoal->opsiB, currentSoal->opsiD);
			printf("Jawab : ");
			fflush(stdin);
			scanf("%s", jawab);

			//Mencocokkan input jawaban dengan jawaban soal
			if (strcmpi(jawab, currentSoal->jawabanPilgan) == 0){
				printf("\n\tBENAR!");
				jumlahBenar += 1;
				currentData->score = jumlahBenar * 10;
			}
			else{
				printf("\n\tSALAH!");
			}
			++urutan;
			getch();
			system("cls");
			currentSoal = currentSoal->next;
		}
	}
	else{
		printf("Maaf, soal tidak ditemukan \n");
	}
}

void create(soal *h){
	char pertanyaan[100];
	char opsiA[25];
	char opsiB[25];
	char opsiC[25];
	char opsiD[25];
	char jawabanPilgan[10];
	
	printf("Pertanyaan :");
	scanf(" %[^\n]s", pertanyaan);
	printf("Opsi A :");
	scanf(" %[^\n]s", opsiA);
	printf("Opsi B :");
	scanf(" %[^\n]s", opsiB);
	printf("Opsi C :");
	scanf(" %[^\n]s", opsiC);
	printf("Opsi D :");
	scanf(" %[^\n]s", opsiD);
	printf("Jawaban pilgan :");
	scanf(" %[^\n]s", jawabanPilgan);
	
	if(h == NULL){
		head = (soal*) malloc(sizeof(soal));
		strcpy(head->pertanyaan, pertanyaan);
		strcpy(head->opsiA, opsiA);
		strcpy(head->opsiB, opsiB);
		strcpy(head->opsiC, opsiC);
		strcpy(head->opsiD, opsiD);
		strcpy(head->jawabanPilgan, jawabanPilgan);
		head->next = NULL;
	} else{
		while (h->next != NULL)
			h = h->next;
		
		h->next=(soal*)malloc(sizeof(soal));
		strcpy(h->next->pertanyaan, pertanyaan);
		strcpy(h->next->opsiA, opsiA);
		strcpy(h->next->opsiB, opsiB);
		strcpy(h->next->opsiC, opsiC);
		strcpy(h->next->opsiD, opsiD);
		strcpy(h->next->jawabanPilgan, jawabanPilgan);
		h->next->next = NULL;
	}
}

void display(soal *h){
	while(h != NULL){
		printf("Soal: %s\n", h->pertanyaan);
		printf("Opsi jawaban A: %s\n", h->opsiA);
		printf("Opsi jawaban B: %s\n", h->opsiB);
		printf("Opsi jawaban C: %s\n", h->opsiC);
		printf("Opsi jawaban D: %s\n", h->opsiD);
		printf("Jawaban pilihan ganda: %s\n", h->jawabanPilgan);
		printf("\n");
		h = h->next;	
	}
}

int count(soal *h){
	int count = 0;
	while(h != NULL){
		h = h->next;
		count++;
	}
	return count;
}

void insert(soal *h){
	int posisi, n, i;
	n = count(h);
	char pertanyaan[100];
	char opsiA[25];
	char opsiB[25];
	char opsiC[25];
	char opsiD[25];
	char jawabanPilgan[10];
	
	printf("Ingin : ");
	scanf("%d", &posisi);
	
	if(posisi == n+1){
		create(head);
	} 
	else if(posisi > n){
		printf("Index out of Buonds...!");
		getch();
	}
	else if(posisi > 0){
		printf("Pertanyaan :");
		scanf(" %[^\n]s", pertanyaan);
		printf("Opsi A :");
		scanf(" %[^\n]s", opsiA);
		printf("Opsi B :");
		scanf(" %[^\n]s", opsiB);
		printf("Opsi C :");
		scanf(" %[^\n]s4", opsiC);
		printf("Opsi D :");
		scanf(" %[^\n]s", opsiD);
		printf("Jawaban pilgan :");
		scanf(" %[^\n]s", jawabanPilgan);
		
		for(i = 1; i < posisi - 1; i++)
			h = h->next;
			
		soal *temp = (soal*)malloc(sizeof(soal));
		strcpy(temp->pertanyaan, pertanyaan);
		strcpy(temp->opsiA, opsiA);
		strcpy(temp->opsiB, opsiB);
		strcpy(temp->opsiC, opsiC);
		strcpy(temp->opsiD, opsiD);
		strcpy(temp->jawabanPilgan, jawabanPilgan);
		temp->next = h->next;
		h->next = temp;
	}
}

void deletePos(soal *h){
	soal *temp;
	int n = count(head);
	int posisi, i;
	printf("Masukkan posisi untuk dicari: ");
	scanf("%d", &posisi);
	
	if (posisi > n){
		printf("\nSoal tidak mencapai nomor tersebut");
	}
	else if (posisi == 1){
		temp = h;
		head = h->next;
		free(temp);
		printf("Data berhasil terhapus");
	}
	else if(posisi > 0){
		for(i = 1; i < posisi-1; i++)
			h = h->next;	
		temp = h->next;
		h->next = h->next->next;
		free(temp);
		printf("Data berhasil terhapus");
	}
		
}
void write(soal *h){
	FILE *fp = fopen("soal.txt", "w");
	while (h != NULL){
		fwrite(h,sizeof(soal),1,fp);
		h = h->next;
	}
	fclose(fp);
	printf("\nData tersimpan di file");
}

void read(soal *h){
	soal Soal;
	FILE *fp = fopen("soal.txt", "r");
	while(fread(&Soal, sizeof(soal),1,fp)){
		if(h == NULL){
			h = (soal*)malloc(sizeof(soal));
			strcpy(h->pertanyaan,Soal.pertanyaan);
			strcpy(h->opsiA,Soal.opsiA);
			strcpy(h->opsiB,Soal.opsiB);
			strcpy(h->opsiC,Soal.opsiC);
			strcpy(h->opsiD,Soal.opsiD);
			strcpy(h->jawabanPilgan,Soal.jawabanPilgan);
			h->next = NULL;
			head = h;
		}
		else{
			while(h->next != NULL){
				h = h->next;
			}
			h->next=malloc(sizeof(soal));
			strcpy(h->pertanyaan,Soal.pertanyaan);
			strcpy(h->opsiA,Soal.opsiA);
			strcpy(h->opsiB,Soal.opsiB);
			strcpy(h->opsiC,Soal.opsiC);
			strcpy(h->opsiD,Soal.opsiD);
			strcpy(h->jawabanPilgan,Soal.jawabanPilgan);
			h->next->next = NULL;
		}	
	}
	fclose(fp);
}

void highscore(siswa *data){
	int rank = 1;
	int i;
	char uppercase[6];

	puts("\n\n\n\t=================================================");
	puts("\t| No |         Nama         | Nilai |");
	puts("\t=================================================");

	while (data != NULL){
		printf("\t| %i. | %-20s |   ", rank, data->nama);
		printf("| %5.1lf |\n", data->score);
		data = data->next;
		rank++;
	}
	puts("\t=================================================");
	getch();
}

void menuAdmin(soal *head, siswa *data){
	int ch;
	
	do{
		system("cls");
		printf("\n1. create list\n");
		printf("2. display list\n");
		printf("3. insert list\n");
		printf("4. delete list\n");
		printf("5. write list to file\n");
		printf("6. highscore\n");
		printf("0. exit\n");
		printf("enter your choice: \n");
		scanf("%d", &ch);
		
		switch(ch){
			case 1:
				create(head);
				system("pause");
				system("cls");
				break;
			case 2:
				display(head);
				system("pause");
				system("cls");
				break;
			case 3:
				display(head);
				insert(head);
				system("pause");
				system("cls");
				break;
			case 4:
				display(head);
				deletePos(head);
				display(head);
				system("pause");
				system("cls");
				break;
			case 5:
				write(head);
				system("cls");
				break;
			case 6:
				highscore(data);
				break;
			case 0:
				printf("Bye");
		}
	}while(ch != 0);
}

int signUp(void){
	FILE *log;
	log = fopen("login.txt", "w");
	if (log == NULL){
		fputs("Error", stderr);
		exit(1);
	}
	struct login sign; //membuat akun user
	system("cls");
	printf("============================================\n");
	printf("\t\tBuat Akun\n");
	printf("============================================\n");
	printf("Username: "); scanf("%s",sign.username);
	printf("Password: "); scanf("%s",sign.password);
	
	fwrite(&sign, sizeof(struct login), 1, log);
	fclose(log);
	printf("processing......");
	sleep(5);
	system("cls");
	printf("\nAkun Telah Terdaftar\n");
	system("pause");
	system("CLS");
}

int signIn(soal *head, siswa *data){
	char username[100];
	char password[100];
	FILE *log;
	log = fopen("login.txt", "r");
	if (log == NULL){
		fputs("Error", stderr);
		exit(1);
	}
	struct login sign;
	printf("============================================\n");
	printf("Masukan Kombinasi Username dan Password\n");
	printf("============================================\n");
	printf("Username: "); scanf("%s", username);
	printf("Password: "); scanf("%s", password);
	//login dengan akun user
	while (fread(&sign, sizeof(struct login), 1, log)){
		if (!strcmp(username,sign.username) && !strcmp(password, sign.password)){
			printf("loading....");
			sleep(3);
			system("cls");
			printf("\nLogin Success");
			getch();
			menuAdmin(head, data);
		}
		else {
			printf("Akun Tidak Terdaftar!\n");
			printf("Silahkan daftar terlebih dahulu");
			sleep(2);
			signUp();
			signIn(head, data);
			getch();
		}
	}
	fclose(log);
}

void opening (){  //function Opening
	printf("\t\t\t\t============================================\n");
	printf("\t\t\t\t\t     YukLatsolSimak!\n");
	printf("\t\t\t\t--------------------------------------------\n");
	printf("\t\t\t\t	     This app made by :\n");
	printf("\t\t\t\t     Cecilia Inez Reva	|| 2106636994\n");
	printf("\t\t\t\t     Shabrina Kamiliya	|| 2106733894\n");
	printf("\t\t\t\t============================================\n\n\n");
	system("pause");
	system("cls");
}

int main(){
	opening();  //memanggil function Opening
	int peran, pilihan;
	//login user
	printf("\t\t\t\t============================================\n");
	printf("\t\t\t\t\t SELAMAT DATANG DI APLIKASI\n");
	printf("\t\t\t\t--------------------------------------------\n");
	printf("\t\t\t\tMasuk sebagai Siswa (1)\n\t\t\t\tMasuk sebagai Admin (2)\n");
	printf("\n\t\t\t\tPilih : ");
	scanf("%d", &peran);
	
	switch (peran){
		case 1: 
			read(head);
			game(head, &data);
			break;
		break;
		case 2:
			do{
				system("cls");
				printf("\n\t\t\t\t============================================\n");
				printf("\t\t\t\t\t\tRegister (1)\n\t\t\t\t\t\tSign In  (2)\n");
				printf("\t\t\t\t--------------------------------------------\n");
				printf("\t\t\t\tPilih : ");
				scanf("%d", &pilihan);
				
				switch (pilihan){
				case 1:
					system("CLS");
					signUp();
					signIn(head, data);
					break;
				case 2:
					system("CLS");
					signIn(head, data);
					break;
				default: 
					printf("Input Invalid");
					system("CLS");
					system("pause");
				}	
			}while (pilihan < 1 || pilihan > 2);
		default :
        	system ("cls");
      		printf("Input Error!");
        	break;
	}
	return 0;
}
