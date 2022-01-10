#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

/* Modul Tampil dan Memilih Menu */
void tampilMenu();
void pilihMenu();
void menu();

/* Modul Inisiasi Awal Permainan (Pemain, Waktu, Saldo Awal) */
int pilihJumlahPemain();
void inputNamaPemain(int *jumlah_pemain);
void pilihWaktu(int *durasi, int *timer, int *salary, int jumlah_pemain, int *timer_sec);

/* Modul Menampilkan Aturan Bermain */
void rules();

/* Modul Keluar Permainan */
void exitGame();
void checkValidity();

/* Modul Tampilan Board dan Info  */
void gotoxy(int x, int y);
void infoAwalPemain(int jumlah_pemain, int timer, int salary, int saldo);
void infoPetak(int indeks_posisi);
void infoPemain(char nama[5], int saldo, char bidak[7]);
void board(int indeks_pemain, int posisi, int dadu);

/* Modul Pengatur Pergerakan Bidak */
int kocokDadu();
int jalan(int indeks_pemain, int dadu, int posisi, int gaji, int *saldo);
void hapusNama(int indeks_pemain);
void tampilDadu(int dadu);

/* Modul Inti Permainan */
void gameStart();
void cekPosisi(int indeks_pemain, int posisi, int jumlah_pemain, int dadu, int gaji);
void doDanaUmum(int *saldo);
void doKesempatan(int *saldo, int *posisi_pemain, char bidak[5], int indeks_pemain, int dadu, int gaji, int jumlah_pemain);
bool cekSaldo(int saldo_pemain, int harga);
void beliTanah(int saldo_pemain, int harga, int indeks_pemain, int posisi);
void beliRumah(int *saldo_pemain, int harga, int posisi, char status[15]);
void beliHotel(int *saldo_pemain, int harga, int posisi);
void bayarSewa(int *saldo, char status_sewa[15], int posisi, int *saldo_pemilik);
int jualRumahKomputer(int batas_jual);
void jualProperti(int *saldo_pemain, int harga, int indeks_posisi, char status[15], int harga_sewa, int jual_semua, char komplek[20], char pemain[10]);
void bayarPajak (int *saldo);

/* Modul Menentukan Menang Kalah */
void ketentuanMenang(int jumlah_pemain);

/* Modul Konfirmasi Untuk Kocok Dadu dan Ganti Giliran */
int konfirmasi(char perintah[15], char pemain[10]);

/* ============================================================================================================================== */

/* === DATA BENTUKAN UNTUK PETAK === */
typedef struct {
	char nama_petak[20];
	char komplek[20];
	char pemilik[20];
	char status_sewa[15];
	bool status_beli;
	int harga_beli;
	int harga_sewa;
	int sewa_tanah;
	int sewa_1rumah;
	int sewa_2rumah;
	int sewa_3rumah;
	int sewa_hotel;
	int harga_rumah;
	int harga_hotel;
} data_petak;

/* === DEKLARASI DATA PADA PETAK === */
data_petak petak[28] = {
	{"P. Listrik", "P. Listrik", " ", "Belum dibeli", false, 15000, 0, 7500, 0, 0, 0, 0, 0, 0},
	{"  Medan   ", "Sumatera", " ", "Belum dibeli", false, 22000, 0, 1800, 9000, 25000, 70000, 105000, 15000, 75000},
	{"  Padang  ", "Sumatera", " ", "Belum dibeli", false, 22000, 0, 1800, 9000, 25000, 70000, 105000, 15000, 75000},
	{" Lampung  ", "Sumatera", " ", "Belum dibeli", false, 24000, 0, 2000, 10000, 30000, 75000, 110000, 15000, 75000},
	{"Dana Umum ", " ", " ", " ", false, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{"Yogyakarta", "DIY", " ", "Belum dibeli", false, 26000, 0, 2200, 11000, 33000, 80000, 115000, 15000, 75000},
	{"  Sleman  ", "DIY", " ", "Belum dibeli", false, 28000, 0, 2400, 14000, 36000, 85000, 120000, 15000, 75000},
	{"  P. air  ", " ", " ", "Belum dibeli", false, 15000, 0, 7500, 0, 0, 0, 0, 0, 0},
	{" Jakarta  ", "Jabodetabek", " ", "Belum dibeli", false, 20000, 0, 1600, 8000, 22000, 60000, 100000, 10000, 50000},
	{" Denpasar ", "Bali", " ", "Belum dibeli", false, 30000, 0, 2600, 13000, 39000, 90000, 127000, 20000, 100000},
	{"  Depok   ", "Jabodetabek", " ", "Belum dibeli", false, 18000, 0, 1400, 7000, 20000, 55000, 95000, 10000, 50000},
	{"   kuta   ", "Bali", " ", "Belum dibeli", false, 32000, 0, 2800, 15000, 45000, 100000, 140000, 20000, 100000},
	{"  Bekasi  ", "Jabodetabek", " ", "Belum dibeli", false, 18000, 0, 1400, 7000, 20000, 55000, 95000, 10000, 50000}, 
	{"Kesempatan", " ", " ", " ", false, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{"Kesempatan", " ", " ", " ", false, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{"Manokwari ", "Papua", " ", "Belum Dibeli", false, 36000, 0, 3500, 17000, 50000, 11000, 150000, 20000, 100000},
	{"  Malang  ", "Jawa Timur", " ", "Belum dibeli", false, 16000, 0, 1200, 6000, 18000, 50000, 90000, 10000, 50000},
	{"  Wamena  ", "Papua", " ", "Belum dibeli", false, 36000, 0, 3500, 17000, 50000, 11000, 150000, 20000, 100000},
	{" Surabaya ", "Jawa Timur", " ", "Belum dibeli", false, 14000, 0, 1000, 5000, 15000, 45000, 75000, 10000, 50000},
	{" Jayapura ", "Papua", " ", "Belum dibeli", false, 40000, 0, 5000, 20000, 60000, 140000, 200000, 20000, 100000},
	{"  Pajak   ", " ", " ", " ", false, 20000, 0, 20000, 0, 0, 0, 0, 0, 0},
	{" Banyumas ", "Jawa Tengah", " ", "Belum dibeli", false, 12000, 0, 800, 3000, 9000, 27000, 55000, 5000, 25000},
	{" Semarang ", "Jawa Tengah", " ", "Belum dibeli", false, 10000, 0, 600, 3000, 9000, 27000, 55000, 5000, 25000},
	{"Dana Umum ", " ", " ", " ", false, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{" Bandung  ", "Jawa Barat", " ", "Belum dibeli", false, 7000, 0, 500, 2000, 6000, 18000, 45000, 5000, 25000},
	{"  Bogor   ", "Jawa Barat", " ", "Belum dibeli", false, 6000, 0, 400, 1000, 3000, 9000, 25000, 5000, 25000},
	{"  Cimahi  ", "Jawa Barat", " ", "Belum dibeli", false, 6000, 0, 400, 1000, 3000, 9000, 25000, 5000, 25000},
	{"   Start  ", " ", " ", " ", false, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

/* === DATA BENTUKAN UNTUK TEMPAT BIDAK === */
typedef struct{
	char bidak[20];
} tempat_bidak;

/* === DEKLARASI DATA UNTUK TEMPAT BIDAK === */
tempat_bidak tempat[28] = {"     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     "};

/* === DATA URUTAN LANGKAH === */
int urutan_langkah[28] = {27, 26, 25, 24, 23, 22, 21, 20, 18, 16, 14, 12, 10, 8, 0, 1, 2, 3, 4, 5, 6, 7, 9, 11, 13, 15, 17, 19};

/* === DATA BENTUKAN UNTUK DATA PEMAIN === */
typedef struct {
	char nama[20];
	char bidak[7];
	int saldo;
	int posisi;
} data_pemain;

/* === DEKLARASI DATA PEMAIN === */
data_pemain pemain[3] = {{"player1","  \002  ", 200000, 0},{"player2", "  \003  ", 200000, 0},{"player3", "  \005  ", 10000, 0}};

/* === DATA BENTUKAN UNTUK DATA DANA UMUM dan KESEMPATAN === */
typedef struct{
	char ketentuan[50];
} damum;

/* === DEKLARASI DATA DANA UMUM DAN KESEMPATAN === */
damum dana_umum[4] = {"Melanggar lalu lintas denda Rp.15.000,00", 
					  "Buang sampah sembarangan, denda Rp. 5000,00", 
					  "Terima bunga dari Bank 7%, Rp 25.000,00", 
					  "Dapat Komisi Rp 50.000,00"};
damum kesempatan[6] = {"Maju tiga petak", "Mundur satu petak", "Maju sampai Jakarta Pusat", 
					   "Maju sampai Start", "Maju sampai Jayapura", "Mendapat hadiah Rp.10.000,00"};

/* Deklarasi variabel */
int timer ;
int durasi;
int salary;
int start_balance;
int timer_sec;

/* ============================================================================================================== */

/* Procedure Go to X Y untuk mengatur posisi pada tampilan */
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;  
	COORD dwCursorPosition;  
	dwCursorPosition.X = x;  
	dwCursorPosition.Y = y;  
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);  
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);   
}

/* === TAMPILAN AWAL DAN MENU AWAL === */
void tampilMenu(){
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),11);
	system("color e"); 	//mengubah warna text pada console
	
	system("cls");
	printf("\n");
	printf("\n");
	printf("\n"); 
	printf("\t\t $$$$     $$$$     $$$     $$$$      $$  $$$$$$$$  $$      $$  $$$$$$$$       $$$    $$        $$      $$ \n");
	printf("\t\t $$  $$$$$  $$   $$   $$   $$ $$     $$  $$         $$    $$   $$      $$   $$   $$  $$         $$    $$  \n");
	printf("\t\t $$   $$$   $$  $$     $$  $$  $$    $$  $$          $$  $$    $$      $$  $$     $$ $$          $$  $$   \n");
	printf("\t\t $$    $    $$  $$     $$  $$   $$   $$  $$$$$        $$$$     $$$$$$$$    $$     $$ $$           $$$$    \n");
	printf("\t\t $$         $$  $$     $$  $$    $$  $$  $$            $$      $$          $$     $$ $$            $$	   \n");
	printf("\t\t $$         $$   $$   $$   $$     $$ $$  $$            $$      $$           $$   $$  $$            $$     \n");
	printf("\t\t $$         $$     $$$     $$      $$$$  $$$$$$$       $$      $$             $$$    $$$$$$$$      $$     \n");
	printf("\n");
	printf("\t\t+==========================================================================================================+\n");
}

/* === PILIH JUMLAH PEMAIN === */
int pilihJumlahPemain(){
	int jumlah_pemain;
	
	tampilMenu();
	printf("\t\t\n");
	printf("\t\t                                              M O N E Y P O L Y\n");
	printf("\t\t\n");
	printf("\t\t                                                  Pilih Pemain  \n");
	printf("\t\t\n");
	printf("\t\t                                             1. Manusia vs Manusia\n");
	printf("\t\t                                             2. Manusia vs Komputer\n");
	printf("\t\t                                        3. Manusia vs Manusia vs Komputer\n");
	printf("\t\t\n");
	printf("\t\t\n");
	
  	printf("\t\t Pilih Pemain (1-3)");	
  	scanf("%d", &jumlah_pemain);
  	
  	/* perulangan untuk validasi jika user menginput selain angka 1, 2, 3 */
  	while(jumlah_pemain != 1 && jumlah_pemain != 2 && jumlah_pemain != 3){
  		printf("\t\t Input a valid number!");
  		printf("\t\t Select Player (1-3)");
  		scanf("%d", &jumlah_pemain);
	  }
	  
  	return jumlah_pemain;
}

/* === INPUT NAMA PEMAIN === */
void inputNamaPemain(int *jumlah_pemain){
	int i=0;
	char nama[5];
	
	printf("\t\tMasukkan nama, Tidak boleh ada spasi!\n");
	
	/*kondisi untuk input nama dengan atau tidak ada komputer*/
	if(*jumlah_pemain == 1){ //manusia vs manusia
		*jumlah_pemain = 2;
		while(i < *jumlah_pemain){
			printf("\t\tMasukkan nama untuk pemain ke - %d = ", i+1);
			scanf("%s", &nama);
			
			if(strlen(nama) >= 10){			//validasi nama tidak boleh lebih 10 huruf
				printf("\t\tnama tidak boleh lebih dari 10 huruf !\n");
			} else if(strlen(nama) < 10){
				strcpy(pemain[i].nama , nama);
				i++ ; 
			}
		}
	} else{  //manusia vs komputer
		while(i < *jumlah_pemain - 1){
			printf("\t\tMasukkan nama untuk player ke - %d = ", i+1);
			scanf("%s", &nama);
			
			if(strlen(nama) >= 10){
				printf("\t\tnama tidak boleh lebih dari 10 huruf !\n");
			} else if(strlen(nama) < 10){
				strcpy(pemain[i].nama , nama);
				i++ ; 
			}
		}
		
		strcpy(pemain[*jumlah_pemain-1].nama, "komputer");		//input nama default untuk komputer (nama tidak dapat diubah)
		printf("\t\tMasukkan nama(default) untuk Komputer adalah komputer");
		sleep(1);
	}
}

/* === INFO AWAL PEMAIN === */
void infoAwalPemain(int jumlah_pemain, int timer, int salary, int saldo){
	tampilMenu();
	int i;
	char konfirm = 'n';
	
	printf("\n");
	printf("                                                         M O N E Y P O L Y\n");
	printf("\n");
	printf("\n");
	printf("                                                         INFO AWAL PEMAIN\n");
	printf("\n");
	printf("                                                   Waktu Lama Bermain = %d Menit\n", timer);
	printf("\n");
	if(jumlah_pemain == 1){
		jumlah_pemain = jumlah_pemain+1;
	}
		printf("                                             +===================================+\n");
	for(i=0; i<jumlah_pemain;i++){
		printf("\n");
    	printf("                                                    Nama Pemain   = %s\n", pemain[i].nama);
    	printf("                                                    Gaji          = Rp. %d\n", salary);
		printf("                                                    Saldo Awal    = Rp. %d\n",saldo);
		printf("\n");
		printf("\n");
	}
		printf("                                             +==================================+\n");
	printf("\t\t\n");
	while(konfirm != 'y'){
		printf("\t\t Press 'y' to continue to the game ");
		scanf("%s", &konfirm);	
	}
}

/* === PILIH WAKTU untuk lamanya bermain pada permainan */
void pilihWaktu(int *durasi, int *timer, int *salary, int jumlah_pemain, int *timer_sec){
	tampilMenu();
	int terima, i;
	
	printf("\n");
	printf("                                                         M O N E Y P O L Y\n");
	printf("\n");
	printf("\n");
	printf("                                                        Pilih Waktu Bermain\n");
	printf("\n");
	printf("                          +========== 15 Menit =========+          +========= 25 Menit ==========+\n");
    printf("                          |                             |          |                             |\n");
    printf("                          | Gaji        = Rp. 20.000    |          | Gaji        = Rp. 15.000    |\n");
	printf("                          | Saldo Awal  = Rp. 200.000   |          | Saldo Awal  = Rp. 150.000   |\n");
	printf("                          |                             |          |                             |\n");
	printf("                          +=========== no 1 ============+          +============ no 2 ===========+\n");
	printf("\n");
	printf("\t\t\n");
	printf("\t\tPilih waktu bermain (1/2) ");
	
	scanf("%d", &terima);
	*durasi = terima;
	while(terima > 2 || terima < 1){
		printf("Input the valid number!\n");
		scanf("%d", &terima);
		*durasi = terima;
	}

	int saldo;
	if(terima == 1){
		saldo = 200000;
		*timer = 15;
		*timer_sec = 900;
		*salary = 20000;
	}else if(terima == 2){
		saldo = 150000;
		*timer = 25;
		*timer_sec = 1250;
		*salary = 15000;
	}
	
	for(i=0; i<jumlah_pemain; i++){
		pemain[i].saldo = saldo;
	}
	
	 infoAwalPemain(jumlah_pemain, *timer, *salary, saldo);
}

/* Ketentuan Menang Kalah */
void ketentuanMenang(int jumlah_pemain){
	int i, max = 0;
	char pemainWin[20];
	
	for(i = 0; i < jumlah_pemain; i++){
		if(pemain[i].saldo > max){
				strcpy(pemainWin, pemain[i].nama);
				max = pemain[i].saldo;
		}
		printf("%d\n", pemain[i].saldo);
	}
	
	for(i=1;i<=15;i++)
	{
		system("cls");
		printf("CONGRATS TO %s\n", pemainWin);
		gotoxy(3,21-i); printf("\t\t $$    $$     $$$      $$    $$     $$         $$  $$  $$$$    $$ \n");
		gotoxy(3,-8+i); printf("\t\t  $$  $$    $$   $$    $$    $$     $$         $$  $$  $$ $$   $$ \n");
		gotoxy(3,23-i); printf("\t\t   $$$$    $$     $$   $$    $$     $$    $    $$  $$  $$  $$  $$ \n");
		gotoxy(3,-6+i); printf("\t\t    $$      $$   $$    $$    $$     $$  $$ $$  $$  $$  $$   $$ $$ \n");
		gotoxy(3,25-i); printf("\t\t    $$        $$$       $$$$$$      $$$$     $$$$  $$  $$    $$$$ \n");
	}
	printf("\n");
	printf("===========================================================================================\n");

}

/* === Menentukan angka dadu yang keluar === */
int kocokDadu(){
	int dadu = rand() % (12 + 1 - 2) + 2;
	return dadu;
}

/* === Bidak berpindah === */
int jalan(int indeks_pemain, int dadu, int posisi, int gaji, int *saldo){
	int berhenti;
	while(dadu > 0){
		if(posisi < 27){
			posisi++ ;
		} else {
			*saldo = *saldo + gaji;
			gotoxy(105,32); printf("Dapat gaji %d, saldo anda %d", gaji, *saldo);
			sleep(3);
			posisi = 0;
		}
		dadu-- ;
	}
	berhenti = posisi;
	return berhenti;
}

/* === Menghapus simbol bidak pada petak sebelumnya === */ 
void hapusNama(int indeks_pemain){
	int x = 0;
	while(x < 28){
		if(strcmp(tempat[x].bidak, pemain[indeks_pemain].bidak) == 0){
			strcpy(tempat[x].bidak, "     ");
		}	
		x++ ;
	}
}

/* === Menampilkan dadu didalam board ===*/
void tampilDadu(int dadu){
	gotoxy(35,19);printf("Dadu = %d", dadu);
	gotoxy(35,20);printf("+-------+	+-------+");
	switch(dadu){
		case 2 : gotoxy(35,21);printf("|       |	|       |");gotoxy(35,22);printf("|   @   |	|   @   |");gotoxy(35,23);printf("|       |	|       |");break;
		case 3 : gotoxy(35,21);printf("| @     |	|       |");gotoxy(35,22);printf("|       |	|   @   |");gotoxy(35,23);printf("|     @ |	|       |"); break;
		case 4 : gotoxy(35,21);printf("| @     |	| @     |");gotoxy(35,22);printf("|       |	|       |");gotoxy(35,23);printf("|     @ |	|     @ |"); break;
		case 5 : gotoxy(35,21);printf("| @     |	| @     |");gotoxy(35,22);printf("|   @   |	|       |");gotoxy(35,23);printf("|     @ |	|     @ |"); break;
		case 6 : gotoxy(35,21);printf("| @   @ |	|       |");gotoxy(35,22);printf("|   @   |	|   @   |");gotoxy(35,23);printf("| @   @ |	|       |"); break;
		case 7 : gotoxy(35,21);printf("| @   @ |	| @     |");gotoxy(35,22);printf("|       |	|   @   |");gotoxy(35,23);printf("| @   @ |	|     @ |"); break;
		case 8 : gotoxy(35,21);printf("| @   @ |	| @   @ |");gotoxy(35,22);printf("|       |	|       |");gotoxy(35,23);printf("| @   @ |	| @   @ |"); break;
		case 9 : gotoxy(35,21);printf("| @   @ |	| @   @ |");gotoxy(35,22);printf("|   @   |	|       |");gotoxy(35,23);printf("| @   @ |	| @   @ |"); break;
		case 10 : gotoxy(35,21);printf("| @   @ |	| @   @ |");gotoxy(35,22);printf("|   @   |	|   @   |");gotoxy(35,23);printf("| @   @ |	| @   @ |"); break;
		case 11 : gotoxy(35,21);printf("| @   @ |	| @ @ @ |");gotoxy(35,22);printf("|   @   |	|       |");gotoxy(35,23);printf("| @   @ |	| @ @ @ |"); break;
		case 12 : gotoxy(35,21);printf("| @ @ @ |	| @ @ @ |");gotoxy(35,22);printf("|       |	|       |");gotoxy(35,23);printf("| @ @ @ |	| @ @ @ |"); break;
	}	
	gotoxy(35,24);printf("+-------+	+-------+");	
}

/* === Info Petak yang diinjak oleh bidak === */
void infoPetak(int indeks_posisi){
	gotoxy(100,3);printf("\t+========= Info Petak =========+");
	gotoxy(100,4);printf("\t|                              |");
	gotoxy(100,5);printf("\t|  Kota         : %s", petak[indeks_posisi].nama_petak);gotoxy(135,5);printf("|");
	gotoxy(100,6);printf("\t|  Komplek      : %s", petak[indeks_posisi].komplek);gotoxy(135,6);printf("|");
	gotoxy(100,7);printf("\t|  Harga Beli   : %d", petak[indeks_posisi].harga_beli);gotoxy(135,7);printf("|");
	gotoxy(100,8);printf("\t|  Harga Rumah  : %d", petak[indeks_posisi].harga_rumah);gotoxy(135,8);printf("|");
	gotoxy(100,9);printf("\t|  Harga Hotel  : %d", petak[indeks_posisi].harga_hotel);gotoxy(135,9);printf("|");
	gotoxy(100,10);printf("\t|  Sewa Tanah   : %d", petak[indeks_posisi].sewa_tanah);gotoxy(135,10);printf("|");
	gotoxy(100,11);printf("\t|  Sewa 1 Rumah : %d", petak[indeks_posisi].sewa_1rumah);gotoxy(135,11);printf("|");
	gotoxy(100,12);printf("\t|  Sewa 2 Rumah : %d", petak[indeks_posisi].sewa_2rumah);gotoxy(135,12);printf("|");
	gotoxy(100,13);printf("\t|  Sewa 3 Rumah : %d", petak[indeks_posisi].sewa_3rumah);gotoxy(135,13);printf("|");
	gotoxy(100,14);printf("\t|  Sewa Hotel   : %d", petak[indeks_posisi].sewa_hotel);gotoxy(135,14);printf("|");
	gotoxy(100,15);printf("\t|                              |");
	gotoxy(100,16);printf("\t+==============================+");
	gotoxy(100,19);printf("\t+=========== Status ===========+");
	gotoxy(100,20);printf("\t|                              |");
	gotoxy(100,21);printf("\t|  Hak Milik   : %s", petak[indeks_posisi].pemilik);gotoxy(135,21);printf("|");
	gotoxy(100,22);printf("\t|  Status Sewa : %s", petak[indeks_posisi].status_sewa);gotoxy(135,22);printf("|");
	gotoxy(100,23);printf("\t|  Harga Sewa  : %d", petak[indeks_posisi].harga_sewa);gotoxy(135,23);printf("|");
	gotoxy(100,24);printf("\t|                              |");
	gotoxy(100,25);printf("\t+==============================+");
}

/* === Info Pemain pada saat didalam permainan === */
void infoPemain(char nama[5], int saldo, char bidak[7]){
	gotoxy(105,28);printf("Giliran : %s", nama);
	gotoxy(105,29);printf("Saldo   : %d", saldo);
	gotoxy(105,30);printf("Bidak   : %s", bidak);
}

/* BOARD atau PAPAN */
void board(int indeks_pemain, int posisi, int dadu) {
  system("cls");
  int i;
  int indeks_posisi = urutan_langkah[posisi];
  hapusNama(indeks_pemain);
  strcpy(tempat[indeks_posisi].bidak, pemain[indeks_pemain].bidak);
  printf("\n+================================================================================================+\n| ");
  for(i = 0; i < 8; i++){
    printf("%s |", petak[i].nama_petak);
  }
  printf("\n| ");
  for(i = 0; i < 8; i++){
    printf("  %s    |", tempat[i].bidak);
  }
  printf("\n| ");
  for(i = 0; i < 8; i++){
    if(petak[i].harga_beli != 0){
      printf("  %d    |", petak[i].harga_beli);
    } else {
      printf("           |");
    }
  }
  printf("\n|================================================================================================|");
  printf("\n| ");
  for(i = 8; i < 20; i++){
    printf("%s |", petak[i].nama_petak);
    if(i == 10){
    	printf("      |    |  \\___/  |   \\| |____   |   |      \\___/  |____  | 	     ");
	} else {
		if(i == 8){
			printf("   	     ___	   ____	       ___    ___		     ");
		} else {
			printf("\t\t\t\t\t\t\t\t\t     ");
		}
	}
    i++ ;
    printf("|%s |", petak[i].nama_petak);
    printf("\n| ");
    i-- ;
    printf("  %s    |", tempat[i].bidak);
    if(i == 8){
    	printf("      |\\  /|  /   \\  |\\   | |     \\   / |   |  /   \\  |    \\   / 	     ");
	} else {
		printf("\t\t\t\t\t\t\t\t\t     ");	
	}
    i++ ;
    printf("|  %s    |", tempat[i].bidak);
    printf("\n| ");
    i-- ;
     if(petak[i].harga_beli != 0){
      printf("  %d    |", petak[i].harga_beli);
    } else {
      printf("           |");
    }
   if(i == 8){
    	printf("      | \\/ | |     | | \\  | |____  \\ /  |___| |     | |     \\ / 	     ");
	} else {
		printf("\t\t\t\t\t\t\t\t\t     ");	
	}
    i++ ;
    if(petak[i].harga_beli != 0){
      printf("|  %d    |", petak[i].harga_beli);
    } else {
      printf("|           |");
    }

    if(i != 19){
    	if(i == 9){
    		printf("\n|============|      |	 | |     | |  \\ | |	  |   |     |     | |	   |         |===========|");
		} else {
			printf("\n|============|                                                                       |===========|");
		}
    	printf("\n| ");
	} else {
		printf("\n|================================================================================================|\n| ");
	}

  }
  for(i = 20; i < 28; i++){
    printf("%s |", petak[i].nama_petak);
  }
  printf("\n| ");
  for(i = 20; i < 28; i++){
    printf("  %s    |", tempat[i].bidak);
  }
  printf("\n| ");
  for(i = 20; i < 28; i++){
    if(petak[i].harga_beli != 0 && i < 24 && i != 27){
      printf("  %d    |", petak[i].harga_beli);
    } else {
      if(i >= 24 && i != 27){
        printf("   %d    |", petak[i].harga_beli);
      } else {
        printf("           |");
      }
    }
  }
  printf("\n+================================================================================================+");
  tampilDadu(dadu);
  if((strcmp(petak[indeks_posisi].nama_petak, "Dana Umum ") == 1 || strcmp(petak[indeks_posisi].nama_petak, "Dana Umum ") == -1) && (strcmp(petak[indeks_posisi].nama_petak, "Kesempatan") == 1 || strcmp(petak[indeks_posisi].nama_petak, "Kesempatan") == -1) && (strcmp(petak[indeks_posisi].nama_petak, "  Pajak   ") == 1 || strcmp(petak[indeks_posisi].nama_petak, "  Pajak   ") == -1) && (strcmp(petak[indeks_posisi].nama_petak, "   Start  ") == 1 || strcmp(petak[indeks_posisi].nama_petak, "   Start  ") == -1)){
  	infoPetak(indeks_posisi);
  }
  infoPemain(pemain[indeks_pemain].nama, pemain[indeks_pemain].saldo, pemain[indeks_pemain].bidak);
}

/* === DANA UMUM === */
void doDanaUmum(int *saldo){
	int i = rand() % 3;
	switch(i){
		case 0 : 
			gotoxy(100,10);printf("Melanggar lalu lintas denda Rp.15.000,00");
			*saldo = *saldo - 15000;
			gotoxy(100,11);printf("Sisa saldo %d", *saldo);
			break;
		case 1 : 
			gotoxy(100,10);printf("Buang sampah sembarangan, denda Rp. 5000,00");
			*saldo = *saldo - 5000;
			gotoxy(100,11);printf("Sisa saldo %d", *saldo); 
			break;
		case 2 : 
			gotoxy(100,10);printf("Terima bunga dari Bank 7%, Rp 25.000,00");
			*saldo = *saldo + 25000;
			gotoxy(100,11);printf("Sisa saldo %d", *saldo);
			break;
		case 3 : 
			gotoxy(100,10);printf("Dapat Komisi Rp 50.000,00");
			*saldo = *saldo + 50000;
			gotoxy(100,11);printf("Sisa saldo %d", *saldo); 
			break;
	}
}

/* === KESEMPATAN === */
void doKesempatan(int *saldo, int *posisi_pemain, char bidak[5], int indeks_pemain, int dadu, int gaji, int jumlah_pemain){
	int i = rand() % 5;
	int posisi_awal, saldo_awal;
	switch(i){
		case 0 : posisi_awal = *posisi_pemain;
				 *posisi_pemain = *posisi_pemain + 3;
				 gotoxy(100,10);printf(" Maju Tiga Petak ");
				 strcpy(tempat[posisi_awal].bidak, "     ");
				 strcpy(tempat[*posisi_pemain].bidak, bidak);	
				 sleep(3);
				 board(indeks_pemain, pemain[indeks_pemain].posisi, dadu);
				 cekPosisi(indeks_pemain, pemain[indeks_pemain].posisi, jumlah_pemain, dadu, gaji);	 
		break;
		case 1 : posisi_awal = *posisi_pemain;
				 *posisi_pemain = *posisi_pemain - 1;
				 gotoxy(100,10);printf("\tMundur Satu Petak ");
				 strcpy(tempat[posisi_awal].bidak, "     ");
				 strcpy(tempat[*posisi_pemain].bidak, bidak);
				 sleep(3);
				 board(indeks_pemain, pemain[indeks_pemain].posisi, dadu);
				 cekPosisi(indeks_pemain, pemain[indeks_pemain].posisi, jumlah_pemain, dadu, gaji);
		break;
		case 2 : posisi_awal = *posisi_pemain;
				 *posisi_pemain = *posisi_pemain * 0 + 13;
				 gotoxy(100,10);printf("\tMaju Sampai Jakarta");
				 strcpy(tempat[posisi_awal].bidak, "     ");
				 strcpy(tempat[*posisi_pemain].bidak, bidak);
				 sleep(3);
				 board(indeks_pemain, pemain[indeks_pemain].posisi, dadu);
				 cekPosisi(indeks_pemain, pemain[indeks_pemain].posisi, jumlah_pemain, dadu, gaji);
		break;
		case 3 : posisi_awal = *posisi_pemain;
				 *posisi_pemain = *posisi_pemain * 0;
				 *saldo = *saldo + gaji;
				 gotoxy(100,10);printf("\tMaju Sampai Start ");
				 strcpy(tempat[posisi_awal].bidak, "     ");
				 strcpy(tempat[*posisi_pemain].bidak, bidak);
				 sleep(3);
				 board(indeks_pemain, pemain[indeks_pemain].posisi, dadu);
				 cekPosisi(indeks_pemain, pemain[indeks_pemain].posisi, jumlah_pemain, dadu, gaji);
		break;
		case 4 : posisi_awal = *posisi_pemain;
				 *posisi_pemain = *posisi_pemain * 0 + 27;
				 gotoxy(100,10);printf("\tMaju Sampai Jayapura ");
				 strcpy(tempat[posisi_awal].bidak, "     ");
				 strcpy(tempat[*posisi_pemain].bidak, bidak);
				 sleep(3);
				 board(indeks_pemain, pemain[indeks_pemain].posisi, dadu);
				 cekPosisi(indeks_pemain, pemain[indeks_pemain].posisi, jumlah_pemain, dadu, gaji);
		break;
		case 5 : gotoxy(100,10);printf("\tMendapat Hadiah 10 Rebu Yeay ");
				 saldo_awal = *saldo;
				 *saldo = *saldo + 10000;
				 gotoxy(100,11);printf("\t Saldo anda %d", *saldo); 
		break;
	}
}

/* Mengecek saldo untuk pengecekan boleh membeli atau tidak */
bool cekSaldo(int saldo_pemain, int harga){
	bool boleh_beli;
	if(saldo_pemain >= harga){
		boleh_beli = true;
	} else {
		boleh_beli = false;
	}
	return boleh_beli;
}

/* === Membeli tanah === */
void beliTanah(int saldo_pemain, int harga, int indeks_pemain, int posisi){
	int indeks_posisi = urutan_langkah[posisi];
	int i;
	petak[indeks_posisi].harga_sewa = petak[indeks_posisi].sewa_tanah;
	pemain[indeks_pemain].saldo = pemain[indeks_pemain].saldo - petak[indeks_posisi].harga_beli;
	petak[indeks_posisi].status_beli = true;
	strcpy(petak[indeks_posisi].status_sewa, "Hanya Tanah");
	for(i = 0; i < 28; i++){
		if(strcmp(petak[i].komplek, petak[indeks_posisi].komplek) == 0){
			strcpy(petak[i].pemilik, pemain[indeks_pemain].nama);
		}
	}
}

/* Membeli Rumah */
void beliRumah(int *saldo_pemain, int harga, int posisi, char status[15]){
	int indeks_posisi = urutan_langkah[posisi];
	int banyak_rumah = 0;
	int batas_beli;
	bool saldo_cukup;
	if(strcmp(status, "Hanya Tanah") == 0){
		batas_beli = 3;
	} else {
		if(strcmp(status, "1 Rumah") == 0){
			batas_beli = 2;
		} else {
			if(strcmp(status, "2 Rumah") == 0){
				batas_beli = 1;
			}
		}
	}
	
	saldo_cukup = cekSaldo(*saldo_pemain, harga);
	if(saldo_cukup == true){
		*saldo_pemain = *saldo_pemain - harga;
		switch(batas_beli){
			case 1 : strcpy(petak[indeks_posisi].status_sewa, "3 Rumah") ; 
				 	petak[indeks_posisi].harga_sewa = petak[indeks_posisi].sewa_3rumah;
			break;
			case 2 : strcpy(petak[indeks_posisi].status_sewa, "2 Rumah") ; 
					 petak[indeks_posisi].harga_sewa = petak[indeks_posisi].sewa_2rumah;
			break;
			case 3 : strcpy(petak[indeks_posisi].status_sewa, "1 Rumah") ; 
					 petak[indeks_posisi].harga_sewa = petak[indeks_posisi].sewa_1rumah;
			break;
		} 		
	} else {
		gotoxy(105,32);printf("Saldo tidak cukup");
	}
}

/* membeli Hotel */
void beliHotel(int *saldo_pemain, int harga, int posisi){
	int indeks_posisi = urutan_langkah[posisi];
	*saldo_pemain = *saldo_pemain - harga;
	petak[indeks_posisi].harga_sewa = petak[indeks_posisi].sewa_hotel;
	strcpy(petak[indeks_posisi].status_sewa, "Hotel");
}

void bayarSewa(int *saldo, char status_sewa[15], int posisi, int *saldo_pemilik){
	if(strcmp(status_sewa, "Hanya Tanah") == 0){
		*saldo = *saldo - petak[posisi].sewa_tanah;
		*saldo_pemilik = *saldo_pemilik + petak[posisi].sewa_tanah;
	} else {
		if(strcmp(status_sewa, "1 Rumah") == 0){
			*saldo = *saldo - petak[posisi].sewa_1rumah;
			*saldo_pemilik = *saldo_pemilik + petak[posisi].sewa_1rumah;
		} else {
			if(strcmp(status_sewa, "2 Rumah") == 0){
				*saldo = *saldo - petak[posisi].sewa_2rumah;
				*saldo_pemilik = *saldo_pemilik + petak[posisi].sewa_2rumah;
			} else {
				if(strcmp(status_sewa, "3 Rumah") == 0){
					*saldo = *saldo - petak[posisi].sewa_3rumah;
					*saldo_pemilik = *saldo_pemilik + petak[posisi].sewa_3rumah;
				} else {
					if(strcmp(status_sewa, "Hotel") == 0){
						*saldo = *saldo - petak[posisi].sewa_hotel;
						*saldo_pemilik = *saldo_pemilik + petak[posisi].sewa_hotel;
					}	
				}
			}
		}
	}
}

/*Jual rumah jika pemain komputer*/
int jualRumahKomputer(int batas_jual){
	int jual_rumah;
	jual_rumah = rand() % (batas_jual + 1 - 1) + 1;
	gotoxy(105,38);printf("Komputer menjual %d rumah", jual_rumah);
	return jual_rumah;
	sleep(3);
}

/*Jual Properti*/
void jualProperti(int *saldo_pemain, int harga, int indeks_posisi, char status[15], int harga_sewa, int jual_semua, char komplek[20], char pemain[10]){
	int batas_jual, banyak_rumah, jual_rumah, i;
	if(jual_semua == 2 ){
		if(strcmp(status, "2 Rumah") == 0){
			banyak_rumah = 2;
			batas_jual = 2;		
		} else {
			if(strcmp(status, "3 Rumah") == 0){
				batas_jual = 3;
				banyak_rumah = 3;
			} else {
				if(strcmp(status, "Hotel") == 0){
					gotoxy(105,37);printf("Anda menjual hotel");
				} else {
					gotoxy(105,37);printf("Anda menjual 1 rumah");
				}
			}
		}
		if(strcmp(status, "2 Rumah") == 0 || strcmp(status, "3 Rumah") == 0){
			if(strcmp(pemain, "komputer") == 1 || strcmp(pemain, "komputer") == -1){
				gotoxy(105,37);printf("Banyak rumah yang ingin dijual (Batas %d rumah) ", batas_jual);
				scanf("%d", &jual_rumah);				
			} else {
				if(strcmp(status, "2 Rumah") == 0){	
					jual_rumah = jualRumahKomputer(batas_jual);
					
				} else {
					jual_rumah = jualRumahKomputer(batas_jual);
				}
			}
		}		
		banyak_rumah = banyak_rumah - jual_rumah;
		switch(banyak_rumah){
			case 2 : 
				strcpy(petak[indeks_posisi].status_sewa, "2 Rumah");
				petak[indeks_posisi].harga_sewa = petak[indeks_posisi].sewa_2rumah;
				break;
			case 1 : 
				strcpy(petak[indeks_posisi].status_sewa, "1 Rumah");
				petak[indeks_posisi].harga_sewa = petak[indeks_posisi].sewa_1rumah;
				break;
			case 0 :
				strcpy(petak[indeks_posisi].status_sewa, "Hanya Tanah");
				petak[indeks_posisi].harga_sewa = petak[indeks_posisi].sewa_tanah;
				break;
			default :
				petak[indeks_posisi].harga_sewa = harga_sewa;	
				strcpy(petak[indeks_posisi].status_sewa, "Hanya Tanah");
				break;				
		}
		harga = jual_rumah * petak[indeks_posisi].harga_rumah;
	} else {
		if(jual_semua == 1){
			int hitung = 0;
			for(i = 0; i < 28; i++){ 		// cek jika ini adalah kota terakhir dalam satu komplek yang dijual
				if(strcmp(petak[i].komplek, komplek) == 0 && petak[i].status_beli == true){
					hitung++ ;
				}
			}
			if(hitung == 1){				// Jika 
				for(i = 0; i < 28; i++){
					if(strcmp(petak[i].komplek, komplek) == 0){
						strcpy(petak[i].pemilik, " ");
					}	
				}
			}
			petak[indeks_posisi].status_beli = false;
			petak[indeks_posisi].harga_sewa = harga_sewa;	
			strcpy(petak[indeks_posisi].status_sewa, status);
		}		
	}

	*saldo_pemain = *saldo_pemain + harga;	
}

/*Membayar Pajak*/
void bayarPajak (int *saldo){
	*saldo = *saldo - 20000;
	gotoxy(105,11);printf("Saldo anda Rp. %d\n", *saldo);
}

/*Mengecek posisi*/
void cekPosisi(int indeks_pemain, int posisi, int jumlah_pemain, int dadu, int gaji){	
	int indeks_posisi = urutan_langkah[posisi];
	int i, indeks_pemilik;
	bool boleh_beli = true;
	bool saldo_cukup;
	char konfirm;
	
	/*Periksa Jika Petak Kesempatan*/
	if(strcmp(petak[indeks_posisi].nama_petak, "Kesempatan") == 0){
		gotoxy(100,8);printf("\t\tKESEMPATAN");
		doKesempatan(&pemain[indeks_pemain].saldo, &pemain[indeks_pemain].posisi, pemain[indeks_pemain].bidak, indeks_pemain, dadu, gaji, jumlah_pemain);
	} else {
		
	/*Periksa Jika Petak Dana Umum*/
		if(strcmp(petak[indeks_posisi].nama_petak, "Dana Umum ") == 0){
			gotoxy(100,8);printf("\t\tDANA UMUM");
			doDanaUmum(&pemain[indeks_pemain].saldo);			
		} else {
			
	/*Periksa Jika Petak Pajak*/
			if(strcmp(petak[indeks_posisi].nama_petak, "  Pajak   ") == 0){
				gotoxy(100,8);printf("\t\tPAJAK");
				gotoxy(105,10);printf("Bayar pajak Rp. 20.000");
				bayarPajak(&pemain[indeks_pemain].saldo);
			} else { 
			
	/*Periksa Jika Petak Merupakan Kota dan Perusahaan*/		
			if(strcmp(petak[indeks_posisi].nama_petak, "   Start  ") == 1 || strcmp(petak[indeks_posisi].nama_petak, "   Start  ") == 1){  // Jika bukan Start
			
	/*Periksa Jika Petak Sudah Dibeli dan Pemilik Bukan Pemain Yang Sedang Bermain
	  Maka Pemain Harus Membayar Sewa Ke Pemilik Petak*/	
				if(petak[indeks_posisi].status_beli == true && (strcmp(petak[indeks_posisi].pemilik, pemain[indeks_pemain].nama) == 1 || strcmp(petak[indeks_posisi].pemilik, pemain[indeks_pemain].nama) == -1)){
					gotoxy(105,32);printf("Bayar sewa ke %s", petak[indeks_posisi].pemilik);
					for(i = 0; i < jumlah_pemain; i++){
						if(strcmp(pemain[i].nama, petak[indeks_posisi].pemilik) == 0){		// Mencari Pemilik Petak 
							indeks_pemilik = i;
							i = 3;
						}
					}
					bayarSewa(&pemain[indeks_pemain].saldo, petak[indeks_posisi].status_sewa, indeks_posisi, &pemain[indeks_pemilik].saldo);
					gotoxy(105,33);printf("Sisa saldo anda %d", pemain[indeks_pemain].saldo);
					gotoxy(105,34);printf("Saldo %s %d", pemain[indeks_pemilik].nama, pemain[indeks_pemilik].saldo);
				} else {
					
	/*Periksa Jika Ada Kota Dalam Satu Komplek Milik Pemain Yang Belum Dibeli
	  Maka Pemain Tidak Boleh Membeli Petak Yang Diinjak*/
					for(i = 0; i < 28; i++){ // cek jika ada komplek yang belum dibeli
						if(strcmp(petak[i].pemilik, pemain[indeks_pemain].nama) == 0 && petak[i].status_beli == false){
							boleh_beli = false;
							gotoxy(105,33);printf("Selesaikan Dulu Pembelian Kota di Komplek %s", petak[i].komplek);
							i = 28;
						}
					}
					
	/*Periksa Jika Petak Belum Ada Pemilik Atau Pemiliknya Adalah Pemain Yang Sedang Bermain*/				
					if((boleh_beli == true && strcmp(petak[indeks_posisi].pemilik, " ") == 0) || (strcmp(petak[indeks_posisi].pemilik, pemain[indeks_pemain].nama) == 0)){
						boleh_beli = true;
					} else {
						
	/*Periksa Jika Petak Belum Dibeli Dan Pemainnya Sudah Ada Tapi Bukan Pemain Yang Sedang bermain*/
						if(petak[indeks_posisi].status_beli == false && (strcmp(petak[indeks_posisi].pemilik, pemain[indeks_pemain].nama) == 1 || strcmp(petak[indeks_posisi].pemilik, pemain[indeks_pemain].nama) == -1) && strcmp(petak[indeks_posisi].pemilik, " ") == 1 ){
							boleh_beli = false;
						}						
					}
					
	/*Jika Status Boleh Beli Adalah True dan Petak Belum Dibeli Maka Boleh Membeli Petak*/
			if(boleh_beli == true){
				if(petak[indeks_posisi].status_beli == false){
					saldo_cukup = cekSaldo(pemain[indeks_pemain].saldo, petak[indeks_posisi].harga_beli);
					if(saldo_cukup == true){
		/*Periksa Apakah Pemain Komputer Atau Bukan*/				
						if(strcmp(pemain[indeks_pemain].nama, "komputer") == 1 || strcmp(pemain[indeks_pemain].nama, "komputer") == -1){
							gotoxy(105,32);printf("Bisa beli %s, Mau beli (y/n) ? ", petak[indeks_posisi].nama_petak);
							scanf("%s", &konfirm);							
						} else {
							konfirm = 'y';
							gotoxy(105,32);printf("Komputer membeli kota %s", petak[indeks_posisi].nama_petak);
						}
						if(konfirm == 'y' || konfirm == 'y'){
							beliTanah(pemain[indeks_pemain].saldo, petak[indeks_posisi].harga_beli, indeks_pemain, posisi);
							gotoxy(105,33);printf("Sisa saldo anda %d\t\t\t\t\t\t", pemain[indeks_pemain].saldo);
						}			
					} else {
						gotoxy(105,33);printf("Saldo tidak cukup");
					}	 				
				} else {
					
	/*Jika Petak Sudah Dibeli dan Petak Merupakan Kota (Bukan Perusahaan)*/				
					if((strcmp(petak[indeks_posisi].nama_petak, "P. Listrik") == 1 || strcmp(petak[indeks_posisi].nama_petak, "P. Listrik") == -1) && (strcmp(petak[indeks_posisi].nama_petak, "  P. air  ") == 1 || strcmp(petak[indeks_posisi].nama_petak, "  P. air  ") == -1)){
						int beli_jual;
						gotoxy(105,32);printf("Tanah milik anda,");
						gotoxy(105,33);printf("1. Beli properti\t\t\t\t\t\t\t\t\t");
						gotoxy(105,34);printf("2. Jual properti");
						gotoxy(105,35);printf("3. Lewat");
						gotoxy(105,36);printf("Pilih nomor  :  ");						
		/*Periksa Apakah Pemain Komputer Atau Bukan*/
						if(strcmp(pemain[indeks_pemain].nama, "komputer") == 1 || strcmp(pemain[indeks_pemain].nama, "komputer") == -1){	// Jika Bukan Pemain Komputer Maka Meminta Konfirmasi
							scanf("%d", &beli_jual);
						} else {
							if(pemain[indeks_pemain].saldo > 20000){				// Jika Merupakan Pemain Komputer Maka :
								beli_jual = 1;										// Komputer Memiliki Limit Saldo 20000
							} else {												// Jika Saldo Lebih dari 20000 Maka Dia Akan Membeli Properti
								if(pemain[indeks_pemain].saldo < 0){				// Jika Kurang dari 20000 Tetapi Tidak Minus Maka Akan Lewat Saja
									beli_jual = 2;									// Jika Saldo Minus Maka Akan Menjual Properti
								}
								else {
									beli_jual = 3;
								}
							}
						}
						
	/*Jika Memilih 1, Membeli Properti*/					
						if(beli_jual == 1){
							
	/*Jika Status Sewa = 3 Rumah Maka Diperbolehkan Membeli Hotel*/						
							if(strcmp(petak[indeks_posisi].status_sewa, "3 Rumah") == 0){
								saldo_cukup = cekSaldo(pemain[indeks_pemain].saldo, petak[indeks_posisi].harga_hotel);
								if(saldo_cukup == true){		// Jika Saldo Mencukupi							
		/*Periksa Apakah Pemain Komputer Atau Bukan*/							
									if(strcmp(pemain[indeks_pemain].nama, "komputer") == 1 || strcmp(pemain[indeks_pemain].nama, "komputer") == -1){
										gotoxy(105,32);printf("Bisa beli hotel, mau beli (y/n)?   ");		// Jika Bukan Komputer
										scanf("%s", &konfirm);									
									} else {																// Jika Komputer
										konfirm = 'y';
										gotoxy(105,32);printf("Komputer membeli hotel");									
									}
									if(konfirm == 'y' || konfirm == 'y'){
										beliHotel(&pemain[indeks_pemain].saldo, petak[indeks_posisi].harga_hotel, posisi);	// Panggil Modul Beli Hotel
										gotoxy(105,33);printf("Sisa saldo anda %d\t\t\t\t\t\t\t\t\t\t\t\t\t\t", pemain[indeks_pemain].saldo);
									}							
								} else {
									gotoxy(105,33);printf("Saldo tidak cukup\t\t\t\t\t\t\t\t\t\t\t\t\t\t");								// Jika Saldo Tidak Cukup
								}
							} else {
								
	/*Jika Status Sewa = Hotel Artinya Sudah Tidak Bisa Membeli Properti*/							
								if(strcmp(petak[indeks_posisi].status_sewa, "Hotel") == 0){
									gotoxy(105,37);printf("Sudah tidak bisa membeli properti");							
								} else {
									
	/*Jika Status Bukan Hotel dan 3 Rumah, Maka Boleh Membeli Rumah*/
		/*Periksa Apakah Pemain Komputer Atau Bukan*/	
									if(strcmp(pemain[indeks_pemain].nama, "komputer") == 1 || strcmp(pemain[indeks_pemain].nama, "komputer") == -1){
										gotoxy(105,32);printf("Bisa beli rumah, mau beli (y/n)?   ");
										scanf("%s", &konfirm);
									} else {
										konfirm = 'y';
										gotoxy(105,32);printf("Komputer membeli 1 rumah");										
									}
									if(konfirm == 'y' || konfirm == 'y'){
										beliRumah(&pemain[indeks_pemain].saldo, petak[indeks_posisi].harga_rumah, posisi, petak[indeks_posisi].status_sewa);		// Panggil Modul Beli Rumah
										gotoxy(105,34);printf("Sisa saldo anda %d", pemain[indeks_pemain].saldo);
									} 								
								}
							}
						
	/*Jika Memilih 2, Menjual Properti*/					
					} else if(beli_jual == 2){
						int harga_jual;
						gotoxy(105,32);printf("Pilih opsi jual   ");
						gotoxy(105,33);printf("1. Jual Properti, Tanah\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
						gotoxy(105,34);printf("2. Jual Properti");
						gotoxy(105,35);printf("3. Lewat");
						gotoxy(105,36);printf("Pilih nomor  :   ");
		/*Periksa Apakah Pemain Komputer Atau Bukan*/				
						if(strcmp(pemain[indeks_pemain].nama, "komputer") == 1 || strcmp(pemain[indeks_pemain].nama, "komputer") == -1){	// Jika Bukan Komputer
							scanf("%d", &beli_jual);
						} else {
							if(strcmp(petak[indeks_posisi].status_sewa, "Hanya Tanah") == 0){		// Jika Komputer
								beli_jual = 1;														// Jika Status Sewa Hanya Tanah Maka Pilih No 1 Karena
							} else {																// Tidak Ada Properti
								beli_jual = 2;														// Pilih 2 Karena Memiliki Properti
							}
						}
						
	/*Jika Memilih 1 Atau Menjual Properti atau Tanah atau Properti dan Tanah*/				
						if(beli_jual == 1){
							// Jika Status Hanya Tanah
							if(strcmp(petak[indeks_posisi].status_sewa, "Hanya Tanah") == 0){
								jualProperti(&pemain[indeks_pemain].saldo, petak[indeks_posisi].harga_beli, indeks_posisi, "Belum dibeli", 0, beli_jual, petak[indeks_posisi].komplek, pemain[indeks_pemain].nama);
								gotoxy(105,38);printf("Saldo anda bertambah %d, sisa saldo %d", petak[indeks_posisi].harga_beli, pemain[indeks_pemain].saldo);
							} else {
							// Jika Status 1 Rumah	
								if(strcmp(petak[indeks_posisi].status_sewa, "1 Rumah") == 0){
									harga_jual = petak[indeks_posisi].harga_beli + petak[indeks_posisi].harga_rumah;
									jualProperti(&pemain[indeks_pemain].saldo, harga_jual, indeks_posisi, "Belum dibeli", 0,  beli_jual, petak[indeks_posisi].komplek, pemain[indeks_pemain].nama);
									gotoxy(105,38);printf("Saldo anda bertambah %d, sisa saldo %d", harga_jual, pemain[indeks_pemain].saldo);
								} else {
							// Jika Status 2 Rumah		
									if(strcmp(petak[indeks_posisi].status_sewa, "2 Rumah") == 0){
										harga_jual = petak[indeks_posisi].harga_beli + (2 * petak[indeks_posisi].harga_rumah);
										jualProperti(&pemain[indeks_pemain].saldo, harga_jual, indeks_posisi, "Belum dibeli", 0, beli_jual, petak[indeks_posisi].komplek, pemain[indeks_pemain].nama);
										gotoxy(105,38);printf("Saldo anda bertambah %d, sisa saldo %d", harga_jual, pemain[indeks_pemain].saldo);
									} else {
							// Jika Status 3 Rumah			
										if(strcmp(petak[indeks_posisi].status_sewa, "3 Rumah") == 0){
											harga_jual = petak[indeks_posisi].harga_beli + (3 * petak[indeks_posisi].harga_rumah);
											jualProperti(&pemain[indeks_pemain].saldo, harga_jual, indeks_posisi, "Belum dibeli", 0, beli_jual, petak[indeks_posisi].komplek, pemain[indeks_pemain].nama);
											gotoxy(105,38);printf("Saldo anda bertambah %d, sisa saldo %d", harga_jual, pemain[indeks_pemain].saldo);
										} else {
							// Jika Status Hotel				
											harga_jual = petak[indeks_posisi].harga_beli + petak[indeks_posisi].harga_hotel;
											jualProperti(&pemain[indeks_pemain].saldo, harga_jual, indeks_posisi, "Belum dibeli", 0, beli_jual, petak[indeks_posisi].komplek, pemain[indeks_pemain].nama);
											gotoxy(105,38);printf("Saldo anda bertambah %d, sisa saldo %d", harga_jual, pemain[indeks_pemain].saldo);											
										}
									}
								}								
							}
						} else {
							
	/*Jika Memilih 2 Atau Menjual Properti*/									
							if(beli_jual ==2){
								// Jika Status Hotel
								if (strcmp(petak[indeks_posisi].status_sewa, "Hotel") == 0){
									jualProperti(&pemain[indeks_pemain].saldo, petak[indeks_posisi].harga_hotel, indeks_posisi, petak[indeks_posisi].status_sewa, petak[indeks_posisi].sewa_tanah, beli_jual, petak[indeks_posisi].komplek, pemain[indeks_pemain].nama);
									gotoxy(105,38);printf("Saldo anda bertambah %d, sisa saldo %d", petak[indeks_posisi].harga_hotel, pemain[indeks_pemain].saldo);
								} else {
								// Jika Status 1 Rumah	
									if(strcmp(petak[indeks_posisi].status_sewa, "1 Rumah") == 0){
										jualProperti(&pemain[indeks_pemain].saldo, petak[indeks_posisi].harga_rumah, indeks_posisi, petak[indeks_posisi].status_sewa, petak[indeks_posisi].sewa_tanah, beli_jual, petak[indeks_posisi].komplek, pemain[indeks_pemain].nama);
										gotoxy(105,38);printf("Saldo anda bertambah %d, sisa saldo %d", petak[indeks_posisi].harga_beli, pemain[indeks_pemain].saldo);
									} else {
								// Jika Status 2 Rumah atau 3 Rumah		
										if(strcmp(petak[indeks_posisi].status_sewa, "2 Rumah") == 0 || strcmp(petak[indeks_posisi].status_sewa, "3 Rumah") == 0){
											jualProperti(&pemain[indeks_pemain].saldo, harga_jual, indeks_posisi, petak[indeks_posisi].status_sewa, 0, beli_jual, petak[indeks_posisi].komplek, pemain[indeks_pemain].nama);									
											gotoxy(105,38);printf("Saldo anda bertambah %d, sisa saldo %d", harga_jual, pemain[indeks_pemain].saldo);
										} else {
								// Jika Status Hanya Tanah			
											gotoxy(105,38);printf("Anda tidak punya properti");
										}
									}
								}								
							}							
						}
					}						
					}
				} 
			} else {
				gotoxy(105,32);printf("Tidak boleh beli");				// Jika Status Beli False
			}			
		}				
			} else {
				gotoxy(100,8);printf("\t\tS T A R T");
				gotoxy(100,10);printf("\tDapat gaji Rp. %d", gaji);		// Jika Menginjak Petak Start Maka Mendapat Gaji
			}
			
		}
		}
	}
}

/* === KONFIRMASI INPUTAN PEMAIN === */
int konfirmasi(char perintah[15], char pemain[10]){
	int konfirm = 0;
	if(strcmp(pemain, "komputer") == 1 || strcmp(pemain, "komputer") == -1){
    	gotoxy(30,37);printf("Ketik 1 untuk %s", perintah);
    	gotoxy(30,38);printf("(Masukkan angka 1, bukan yang lain!)");
		scanf("%d", &konfirm);		
	} else {
		konfirm = 1;
		gotoxy(30,37);printf("Komputer meng%s", perintah);
		sleep(3);
	}
	return konfirm; 	
}

/* === Waktu Pertama === */
int startTime(){
	clock_t startInput;     //Tipe data dari variabel startInput adalah clock_t
	startInput = clock();   //startInput diisi dengan nilai dari modul clock()
	return startInput;
}

/* === Waktu Terakhir === */
int endTime(){
	clock_t endInput;
	endInput = clock();
	return endInput;
}

/* === Memulai Permainan === */
void gameStart(){
  //Kamus Data
  int i = 0, dadu = 0, t;
  double waktuInput;
  int jumlah_pemain = pilihJumlahPemain();
  int konfirm;
  inputNamaPemain(&jumlah_pemain);
  pilihWaktu(&durasi, &timer, &salary, jumlah_pemain, &timer_sec);
  //Algoritma
  t = startTime();
  while(i < jumlah_pemain && waktuInput < timer_sec){   //Perulangan Giliran Pemain
    konfirm = 0;
    board(i, pemain[i].posisi, dadu);   //Memanggil modul board 
    while(konfirm != 1){    //Jika inputan konfirm tidak sama dengan 1 maka perintah kocok dadu akan ditampilkan kembali
    	konfirm = konfirmasi("kocok dadu", pemain[i].nama);  
    }
    konfirm = 0;
    dadu = kocokDadu();
    pemain[i].posisi = jalan(i, dadu, pemain[i].posisi, salary, &pemain[i].saldo);
    board(i, pemain[i].posisi, dadu);
    cekPosisi(i, pemain[i].posisi, jumlah_pemain, dadu, salary);
    while(konfirm != 1){    //Jika inputan konfirm tidak sama dengan 1 maka perintah untuk ganti giliran ditampilkan kembali
    	konfirm = konfirmasi("ganti giliran", pemain[i].nama);
    }
    i++ ;
    if(i >= jumlah_pemain){   //Jika i melebihi jumlah_pemain maka nilai i akan diisi menjadi 0
    	i = 0;
    }
    t = endTime() - t;
    waktuInput = ((double)t) / CLOCKS_PER_SEC;  //Mengonversi t menjadi detik
  }
  if(waktuInput > timer_sec){   //Jika waktuInput melenihi timer_sec (15mnt atau 25mnt)
  		system("cls");
    	ketentuanMenang(jumlah_pemain);   //Tampil modul pemenang
	}
}

/* === PROCEDURE UNTUK MENAMPILKAN RULES === */
void rules(){
  system("cls");
	FILE *FF;
	char CC[100000], pilih_rules, konfirm;
	
	if((FF = fopen("rules.txt","r")) == NULL){
		printf("File Aturan Bermain tidak ditermukan !");
    exit(1);
	}

  while(fgets(CC, sizeof(CC) ,FF)){
    printf("%s", CC);
  }
  
  fclose(FF);
	fflush(stdin);

  printf("\t\tKetik 'y' untuk kembali ke menu ");
  scanf("%s", &pilih_rules);  //memilih apakah ingin kembali ke menu

  while(pilih_rules != 'y'){ //melakukan perulangan untuk mengecek apakah inputan yang dimasukkan berhuruf y
    printf("(Masukkan huruf 'y' bukan yang lain)\n");
    printf("Kembali ke menu ? ");
    scanf("%s", &pilih_rules);
  }
  menu();
}

/* === KELUAR DARI GAME === */
void exitGame(){
  char pilih_exit;

  tampilMenu();
	printf("\t\t\n");
	printf("\t\t                                              M O N E Y P O L Y\n");
	printf("\t\t\n");
	printf("\t\t                                        Apakah Anda Yakin akan Keluar ?\n");
	printf("\t\t\n");
	printf("\t\t                                                Ya(y)   Tidak(n)\n");
	printf("\t\t\n");
	printf("\t\t\n");
	printf("\t\t\n");
    printf("\t\t Yakin akan keluar? (y/n)");
    scanf(" %c", &pilih_exit);
void checkValidity(){
    
  switch(pilih_exit){
      case 'y':
      printf("\n");
      printf("\t\t $$$$$$$$  $$   $$   $$$$$   $$$$    $$  $$  $$     $$    $$    $$    $$   $$\n");
      printf("\t\t    $$     $$   $$  $$   $$  $$ $$   $$  $$ $$       $$  $$   $$  $$  $$   $$\n");
      printf("\t\t    $$     $$$$$$$  $$$$$$$  $$  $$  $$  $$$$         $$$$   $$    $$ $$   $$\n");
      printf("\t\t    $$     $$   $$  $$   $$  $$   $$ $$  $$ $$         $$     $$  $$  $$   $$\n");
      printf("\t\t    $$     $$   $$  $$   $$  $$    $$$$  $$   $$       $$       $$     $$$$$ \n");
      exit(1);
      break;
      case 'n':
      menu();
      break;
      default:
      printf("\t\t Command Not Found\n");
      
      printf("\t\t Are you sure want to exit? (y/n)");
      scanf(" %c", &pilih_exit);
      checkValidity();
      break;
  }
}
    checkValidity(); 
  
}

void pilihMenu(){
	int no_menu;

	printf("\t\t\n");
	printf("\t\t                                              M O N E Y P O L Y\n");
	printf("\t\t\n");
	printf("\t\t                                                1. Mulai\n");   //jika mengetik 1 akan melanjutkan ke permainan
	printf("\t\t                                                2. Aturan Bermain\n");   //jika mengetik 2 akan melanjutkan untuk melihat rules
	printf("\t\t                                                3. Keluar\n");    //jika mengetik 3 akan menutup permainan
	printf("\t\t\n");
	printf("\t\t\n");
	printf("\t\t\n");
	
	printf("\t\tPilih menu (1-3) ");
	scanf("%d", &no_menu);
	
	switch(no_menu){
		case 1 : gameStart(); break;
		case 2 : rules(); break;
		case 3 : exitGame(); break;
    default: printf("Masukkan angka antara 1 sampai 3"); break;
	}
}

void menu(){
  tampilMenu();
  pilihMenu();
}

int main() {
	menu();
  return 0;
}

