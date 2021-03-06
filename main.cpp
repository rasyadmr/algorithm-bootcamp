//Preprocessors
#include <stdio.h>
#include <string.h>


//Global variable
int total = 0; //Untuk total harga nanti
int balance = 0; //Untuk jumlah uang yang dimiliki user
int price; //Untuk harga produk
int kuantitas = 1; //Untuk banyak pembelian produk
bool mainmenubool = false, addbalancebool = false, menupaybool = false, daftardaerahbool = false, paymentbool = false, billbool = false, acehbool = false, riaubool = false, Jawa_Tengahbool = false, Padangbool = false, Jawa_Baratbool = false, Balibool = false, Ambonbool = false;//Booleans untuk masing-masing menu. Tambahkan jika ada menu baru!
bool accepted = false; //Untuk mencegah input yang tidak sesuai (< 1)
bool finished = false; //Untuk dapat menggunakan fungsi closing()
bool billallowed = true; //Untuk akses membuat bill


//Structure
struct Produk {
	char nama[100];
	int harga;
};


//Function list
void animasi(); //Animasi program pertama
void animasi2(); //Animasi program kedua
void gambar(); //Gambar ASCII
void selamat(); //Pembukaan program
void closing(); //Penutupan program
void mainmenu(); //Main menu screen
void fakeloading(); //Mendelay screen dengan alasan loading
void delay(); //Mendelays screen sampai user menekan ENTER
void clear(); //Membersihkan screen
void checking(int kuantitas); //Pengecekan input untuk menghindari input negatif, nol, atau overlimit
void checkingtopup(int kuantitas); //Pengecekan input untuk menghindari input negatif atau nol untuk top up
void purchasing(Produk barang); //Proses pembelian produk dan input kuantitas makanan
void payment(); //Menu metode pembayaran
void addbalance(); //Top up YukPay
void menupay(); //Menu YukPay
int addtotal(int harga, int kuantitas); //Penambahan total harga ke balance
void daftardaerah(); //Menu daerah
void receipt(); //Total akhir pembelian
void createbill(); //Pembuatan file bill
void endbill(int tipe); //Penutupan file bill
void createbalance();


//Functions
void gambar() {
  	printf("\n");
	char string[255][255];
	FILE *fg = fopen("logo.txt", "r");
	int index = 0;
	while (fscanf(fg, "q%[^\n]\n", string[index]) != EOF) {
		index++;
	}
	for (int i = 0;i < index; i++) {
		printf("%s\n", string[i]);
	}
  	fclose(fg);
  	getchar();
	animasi();
}


void animasi(){
	char salam[] = "\t \t \t YUKFOOD!!";
	printf("\n\n\n");
	for (int x = 0; salam[x] != '\0'; x++) {
		printf("%c", salam[x]);
		for(double y = 0; y <= 9999999; y++) {
		}
	}
	getchar();
	animasi2();
}


void animasi2(){
	char slogan[] = "\t \t Masakan Lezat Buatan Nusantara.";
	printf("\n");
	for (int q = 0; slogan[q] != '\0'; q++) {
		printf("%c", slogan[q]);
		for(double z = 0; z <= 9999999; z++){
		}
	}
	getchar();
}


void selamat() {
	puts("Selamat datang di Yukfood!");
	puts("Program ini di buat oleh YukBisaYuk.");
	createbill();
	createbalance();
}


void closing() {
	clear();
	puts("Terima kasih telah menggunakan aplikasi Yukfood!");
	printf("Sampai jumpa lagi!");
	mainmenubool = false;
}


void fakeloading() {
	puts("Processing...");
	for (int i = 0; i < 2e9; i++) {
		;
	}
}


void clear() {
	for (int i = 0; i < 60; i++) {
		puts("");
	}
}


void delay() {
	printf("\nTekan ENTER untuk lanjut.");
	getchar();
}


void menupay() {
	int input;
	menupaybool = true;
	while (menupaybool) {
		puts("********************  YUKPAY  *******************");
		puts("| 1. Cek Balance YukPay\t\t\t\t|");
		puts("| 2. Top Up Balance YukPay\t\t\t|");
		puts("| 0. Kembali ke Main Menu\t\t\t|");
		puts("*************=====================***************");
		printf("Masukan kode menu: ");
		scanf("%d", &input);
		getchar();
		clear();
		switch (input) {
			case 0:
				menupaybool = false;
				break;
			case 1:
				printf("Saldo YukPay anda saat ini: Rp %d", balance);
				delay();
				clear();
				break;
			case 2:
				addbalance();
				break;
			default:
				puts("Kode yang anda masukan tidak dikenal!");
				continue;
		}
	}
}


void addbalance() {
	int balancing;
	FILE *fb = fopen("yukpay.txt", "w+");
	addbalancebool = true;
	while (addbalancebool) {
		printf("Masukan nominal untuk top up: ");
		scanf("%d", &balancing);
		getchar();
		checkingtopup(balancing);
		if (balance + balancing > 1000000000) {
			puts("Anda mencoba melebihi batas maksimal saldo YukPay (Rp 1 Miliar)\nPurchase Canceled!");
			fprintf(fb, "%d", balance);
			fclose(fb);
			accepted = false;
			delay();
			clear();
			return;
		}
		while (accepted) {
			balance += balancing;
			fprintf(fb, "%d", balance);
			printf("Anda telah berhasil top up sebesar Rp %d\n", balancing);
			printf("Total YukPay anda saat ini: Rp %d\n", balance);
			accepted = false;
		}
		fclose(fb);
		fakeloading();
		clear();
		break;
	}
}


int addtotal(int harga, int kuantitas) {
	total += (harga * kuantitas);
}


void checkingtopup(int kuantitas) {
	if (kuantitas < 0) {
		printf("Anda tidak dapat memasukan angka negatif atau overflow!\nInput anda sebelumnya: %d\n", kuantitas);
	} else if (kuantitas == 0) {
		puts("Canceled!");
	} else {
		accepted = true;
	}
}


void checking(int kuantitas) {
	if (kuantitas < 0) {
		printf("Anda tidak dapat memasukan angka negatif atau overflow!\nInput anda sebelumnya: %d\n", kuantitas);
	} else if (kuantitas == 0) {
		puts("Canceled!");
	} else if (kuantitas >= 1000) {
		printf("Anda melebihi limit belanja, anda hanya bisa membeli produk kurang dari 1000 / pembelian\n");
	} else {
		accepted = true;
	}
}


void purchasing(Produk barang) {
	printf("Berapa banyak %s (@%d) yang ingin anda beli: ", barang.nama, barang.harga);
	scanf("%d", &kuantitas);
	getchar();
	clear();
	FILE *atf = fopen("bill.txt", "a");
	int len = strlen(barang.nama);
	checking(kuantitas);
	if (total + (barang.harga * kuantitas) > 1000000000) {
		puts("Total belanja anda melebihi batas maksimal (> Rp 1 Miliar)\nPurchase Canceled!");
		fclose(atf);
		accepted = false;
		delay();
		return;
	}
	if (accepted) {
		addtotal(barang.harga, kuantitas);
		printf("Anda membeli %s dengan harga Rp %d sebanyak %d\n",barang.nama, barang.harga, kuantitas);
		printf("Total belanja sekarang: Rp %d", total);
		if (len < 8) {
			fprintf(atf, "%s\t\t\t\t\t x%d\t\t Rp %d\n", barang.nama, kuantitas, barang.harga * kuantitas);
		} else if (len >= 8 && len < 16) {
			fprintf(atf, "%s\t\t\t\t x%d\t\t Rp %d\n", barang.nama, kuantitas, barang.harga * kuantitas);
		} else if (len >= 16 && len < 24) {
			fprintf(atf, "%s\t\t\t x%d\t\t Rp %d\n", barang.nama, kuantitas, barang.harga * kuantitas);
		} else {
			fprintf(atf, "%s\t\t x%d\t\t Rp %d\n", barang.nama, kuantitas, barang.harga * kuantitas);
		}
		accepted = false;
	}
	fclose(atf);
	delay();
}


void receipt() {
	clear();
	if (total <= 0) {
		char input;
		puts("Anda belum membeli makanan sama sekali!");
		printf("Apakah anda ingin keluar dari program? (Y/N) ");
		scanf("%c", &input);
		getchar();
		if (input == 'Y' || input == 'y') {
			closing();
		} else if (input == 'N' || input == 'n') {
			clear();
			mainmenubool = true;
		} else {
			puts("Input tidak diketahui, kembali ke main menu!");
			mainmenubool = true;
		}
	} else {
		payment();
      	if (finished) {
		closing();
        }
	}
}


void payment() {
	paymentbool = true;
	FILE *fb = fopen("yukpay.txt", "w");
	int input;
	while (paymentbool) {
		puts("***************===========================***********************");
		printf("| Total belanja anda sekarang seharga Rp %d\t\t\t|\n", total);
		puts("| Silakan pilih metode pembayaran:\t\t\t\t|");
		puts("| 1. YukPay\t\t\t\t\t\t\t|");
		puts("| 2. GoPey / UVU/ Shopie Pay (Pajak Rp 2000)\t\t\t|");
		puts("| 3. Transfer Bank (Pajak Rp 6500)\t\t\t\t|");
      	puts("| 0. Kembali ke Main Menu\t\t\t\t\t|");
      	puts("***************===========================***********************");
		printf("Masukan kode metode pembayaran: ");
		scanf("%d", &input);
		getchar();
		clear();
		switch (input) {
			case 1:
				if (total > balance) {
					printf("Saldo anda tidak cukup.\nSaldo anda saat ini: Rp %d", balance);
					delay();
					clear();
					continue;
				} else {
					balance -= total;
					fprintf(fb, "%d", balance);
					printf("Pembayaran berhasil!\nSisa saldo anda: Rp %d", balance);
					endbill(1);
					total = 0;
					finished = true;
					delay();
					paymentbool = false;
				}
				break;
			case 2:
				printf("Silakan melakukan pembayaran ke nomor 081928374655 sebesar Rp %d", total + 2000);
				endbill(2);
				total = 0;
				finished = true;
				delay();
				paymentbool = false;
				break;
			case 3:
				printf("Silakan melakukan pembayaran ke rekening 199209384 (Bank Pertama) sebesar Rp %d", total + 6500);
				endbill(3);
				total = 0;
				finished = true;
				delay();
				paymentbool = false;
				break;
          	case 0:
            	finished = false;
            	paymentbool = false;
				break;
			default:
				puts("Input tidak dikenal!");
				delay();
				clear();
				continue;
		}
	}
	fclose(fb);
}


void createbill() {
	FILE *fb = fopen("bill.txt", "w");
	if (fb == NULL) {
		billallowed = false;
	} else {
		fprintf(fb, "\t\t\t\tYukfood!\n");
		fprintf(fb, "\t\t\t    Receipt Payment\n");
		fprintf(fb, "\t\t\t     By YukBisaYuk\n");
		fprintf(fb, "--------------------------------------------------------------------\n");
		fprintf(fb, "Nama Produk\t\t\t\t QTY\t\t Harga\n");
		fprintf(fb, "--------------------------------------------------------------------\n");
	}
	fclose(fb);
}


void endbill(int tipe) {
	int addition = 0;
	FILE *fb = fopen("bill.txt", "a");
	if (billallowed) {
		fprintf(fb, "--------------------------------------------------------------------\n");
		fprintf(fb, "\t\t\t\t\t     Sub Total = RP %d\n", total);
		if (tipe == 1) {
			fprintf(fb, "\t\t\t\t\t\t Total = Rp %d\n", total + addition);
			fprintf(fb, "\t\t\t\t\t\t\t(YukPay)\n\n");
		} else if (tipe == 2) {
			addition = 2000;
			fprintf(fb, "\t\t\t\t\t\t Pajak = Rp 2000\n");
			fprintf(fb, "\t\t\t\t\t\t Total = Rp %d\n", total + addition);
			fprintf(fb, "\t\t\t\t\t\t\t(E-Wallet)\n\n");
		} else {
          	addition = 6500;
			fprintf(fb, "\t\t\t\t\t\t Pajak = Rp 6500\n");
			fprintf(fb, "\t\t\t\t\t\t Total = Rp %d\n", total + addition);
			fprintf(fb, "\t\t\t\t\t\t\t(Transfer)\n\n");
		}
		fprintf(fb, "\t\t\t      Terima Kasih!");
		fclose(fb);
		printf("\nBill telah dibuat dalam bentuk bill.txt!");
	} else {
		fclose(fb);
		printf("Kami tidak dapat membuat bill karena kami tidak dapat membuat/membuka file.");
	}
}


void createbalance() {
	FILE *fb = fopen("yukpay.txt", "r+");
	int insidefile;
	if (fb == NULL || fscanf(fb, "%d", &insidefile) == EOF) {
		fclose(fb);
		FILE *fb = fopen("yukpay.txt", "w+");
		fprintf(fb, "0");
		fclose(fb);
	} else {
		fscanf(fb, "%d", &insidefile);
		balance = insidefile;
		fclose(fb);
	}
}


void aceh() {
	int input, kuantitas;
	acehbool = true;
	clear();
	while (acehbool) {
      	puts("***************===========================***********************");
		puts("| Dibawah ini daftar menu khas Aceh beserta harga.\t\t|");
		puts("| 1. Mie Aceh\t\t\t\tRp 30.000\t\t|");
		puts("| 2. Sate Matang Aceh\t\t\tRp 35.000\t\t|");
		puts("| 3. Rujak Aceh\t\t\t\tRp 8.000\t\t|");
		puts("| 4. Martabak Aceh Kuah Kari\t\tRp 20.000\t\t|");
		puts("| 5. Kue Adee\t\t\t\tRp 20.000\t\t|");
		puts("| 6. Kopi Aceh\t\t\t\tRp 10.000\t\t|");
		puts("| 0. Kembali ke Daftar Daerah.\t\t\t\t\t|");
      	puts("***************===========================***********************");
    	printf("Masukan Nomor Makanan/Minuman: ");
		scanf("%d", &input);
		getchar();
		clear();
		switch (input) {
			case 0:
				acehbool = false;
				break;
			case 1:
				Produk mieaceh;
				strcpy(mieaceh.nama, "Mie Aceh");
				mieaceh.harga = 30000;
				purchasing(mieaceh);
				break;
			case 2:
				Produk satematang;
				strcpy(satematang.nama, "Sate Matang Aceh");
				satematang.harga = 35000;
				purchasing(satematang);
				break;
			case 3:
				Produk rujakaceh;
				strcpy(rujakaceh.nama, "Rujak Aceh");
				rujakaceh.harga = 8000;
				purchasing(rujakaceh);
				break;
			case 4:
				Produk martabakaceh;
				strcpy(martabakaceh.nama, "Martabak Aceh Kuah Kari");
				martabakaceh.harga = 20000;
				purchasing(martabakaceh);
				break;
			case 5:
				Produk kueadee;
				strcpy(kueadee.nama, "Kue Adee");
				kueadee.harga = 20000;
				purchasing(kueadee);
				break;
			case 6:
				Produk kopiaceh;
				strcpy(kopiaceh.nama, "Kopi Aceh");
				kopiaceh.harga = 10000;
				purchasing(kopiaceh);
				break;
			default:
				puts("Menu tidak diketahui, silakan coba lagi.");
				continue;
		}
		clear();
	}
	daftardaerah();
}


void riau() {
   	int input, kuantitas;
   	riaubool = true;
   	clear();
   	while (riaubool) {
      	puts("***************===========================***********************");
		puts("| Dibawah ini daftar menu khas Riau beserta harga.\t\t|");
	    puts("| 1. Nasi Lemak\t\t\t\tRp 12.000\t\t|");
	    puts("| 2. Sop Tunjang\t\t\tRp 20.000\t\t|");
	    puts("| 3. Roti Jala\t\t\t\tRp 8.000\t\t|");
	    puts("| 4. Mie Sagu\t\t\t\tRp 13.000\t\t|");
	    puts("| 5. Lopek Bugi\t\t\t\tRp 6.000\t\t|");
	    puts("| 6. Air Tebu Nostalgia\t\t\tRp 10.000\t\t|");
	    puts("| 0. Kembali ke Daftar Daerah.\t\t\t\t\t|");
      	puts("***************===========================***********************");
      	printf("Masukan Nomor Makanan/Minuman: ");
	    scanf("%d", &input);
   		getchar();
   		clear();
    	switch (input) {
	   		case 0:
	      		riaubool = false;
	      		break;
	   		case 1:
	      		Produk nasilemak;
				strcpy(nasilemak.nama, "Nasi Lemak");
				nasilemak.harga = 12000;
				purchasing(nasilemak);
				break;
	   		case 2:
			    Produk soptunjang;
				strcpy(soptunjang.nama, "Sop Tunjang");
				soptunjang.harga = 20000;
				purchasing(soptunjang);
				break;
	   		case 3:
	      		Produk rotijala;
				strcpy(rotijala.nama, "Roti Jala");
				rotijala.harga = 8000;
				purchasing(rotijala);
				break;
		   	case 4:
	      		Produk miesagu;
				strcpy(miesagu.nama, "Mie Sagu");
				miesagu.harga = 13000;
				purchasing(miesagu);
				break;
		   	case 5:
	      		Produk lopek;
				strcpy(lopek.nama, "Lopek Bugi");
				lopek.harga = 6000;
				purchasing(lopek);
				break;
	   		case 6:
			    Produk airtebu;
				strcpy(airtebu.nama, "Air Tebu Nostalgia");
				airtebu.harga = 10000;
				purchasing(airtebu);
				break;
	   		default:
	    		puts("Menu tidak diketahui, silakan coba lagi.");
	    		continue;
	  	}
	  	clear();
 	}
 	daftardaerah();
}


void Jawa_Tengah(){
	int input,kuantitas ;
	Jawa_Tengahbool = true;
	clear();
 	while (Jawa_Tengahbool){
      	puts("***************===========================***********************");
		puts("| Dibawah ini daftar menu masakan Jawa Tengah beserta harga.\t|");
		puts("| 1. Soto Kudus\t\t\t\tRp 10.000\t\t|");
		puts("| 2. Gudeg\t\t\t\tRp 10.000\t\t|");
		puts("| 3. Nasi Grombyang\t\t\tRp 25.000\t\t|");
		puts("| 4. Garang asem\t\t\tRp 15.000\t\t|");
		puts("| 5. Nasi Gandul\t\t\tRp 15.000\t\t|");
		puts("| 6. Es Gempol\t\t\t\tRp 10.000\t\t|");
		puts("| 0. Kembali ke Daftar Daerah.\t\t\t\t\t|");
      	puts("***************===========================***********************");
    	printf("Masukan Nomor Makanan/Minuman: ");
    	scanf("%d", &input);
  		getchar();
  		clear();
  		switch (input) {
   			case 0:
    			Jawa_Tengahbool = false;
    			break;
   		case 1:
    		Produk soto;
			strcpy(soto.nama, "Soto Kudus");
			soto.harga = 10000;
			purchasing(soto);
			break;
  		case 2:
    		Produk gudeg;
			strcpy(gudeg.nama, "Gudeg");
			gudeg.harga = 10000;
			purchasing(gudeg);
			break;
   		case 3:
		    Produk nasi;
			strcpy(nasi.nama, "Nasi Grombyang");
			nasi.harga = 25000;
			purchasing(nasi);
			break;
   		case 4:
		    Produk garang;
			strcpy(garang.nama, "Garang Asem");
			garang.harga = 15000;
			purchasing(garang);
			break;
		case 5:
		    Produk gundul;
			strcpy(gundul.nama, "Nasi Gundul");
			gundul.harga = 10000;
			purchasing(gundul);
			break;
   		case 6:
		    Produk gempol;
			strcpy(gempol.nama, "Es Gempol");
			gempol.harga = 10000;
			purchasing(gempol);
			break;
   		default:
		    puts("Menu tidak diketahui, silakan coba lagi.");
		    continue;
  		}
  		clear();
 	}
 	daftardaerah();
}


void Padang(){
	int input, kuantitas;
	Padangbool = true;
	clear();
	while (Padangbool) {
      	puts("***************===========================***********************");
		puts("| Dibawah ini daftar menu khas Padang beserta harga.\t\t|");
		puts("| 1. Nasi Sop Iga\t\t\tRp 35.000\t\t|");
		puts("| 2. Nasi Kikil\t\t\t\tRp 25.000\t\t|");
		puts("| 3. Nasi Soto Padang\t\t\tRp 22.000\t\t|");
		puts("| 4. Nasi Rendang/Dendeng\t\tRp 22.000\t\t|");
		puts("| 5. Teh Talua\t\t\t\tRp 10.000\t\t|");
		puts("| 6. Dadiah\t\t\t\tRp 10.000\t\t|");
		puts("| 0. Kembali ke Daftar Daerah.\t\t\t\t\t|");
      	puts("***************===========================***********************");
    	printf("Masukan Nomor Makanan/Minuman: ");
		scanf("%d", &input);
		getchar();
		clear();
		switch (input) {
			case 0:
				Padangbool = false;
				break;
			case 1:
				Produk iga;
				strcpy(iga.nama, "Nasi Sop Iga");
				iga.harga = 35000;
				purchasing(iga);
				break;
			case 2:
				Produk kikil;
				strcpy(kikil.nama, "Nasi Kikil");
				kikil.harga = 25000;
				purchasing(kikil);
				break;
			case 3:
				Produk soto;
				strcpy(soto.nama, "Nasi Soto Padang");
				soto.harga = 22000;
				purchasing(soto);
				break;
			case 4:
				Produk rendang;
				strcpy(rendang.nama, "Nasi Rendang");
				rendang.harga = 22000;
				purchasing(rendang);
				break;
			case 5:
				Produk teh;
				strcpy(teh.nama, "Teh Talua");
				teh.harga = 10000;
				purchasing(teh);
				break;
			case 6:
				Produk dadiah;
				strcpy(dadiah.nama, "Dadiah");
				dadiah.harga = 10000;
				purchasing(dadiah);
				break;
			default:
				puts("Menu tidak diketahui, silakan coba lagi.");
				continue;
		}
		clear();
	}
	daftardaerah();
}  


void Jawa_Barat() {
	int input, kuantitas;
	Jawa_Baratbool = true;
	clear();
	while (Jawa_Baratbool) {
      	puts("***************===========================***********************");
		puts("| Dibawah ini daftar menu khas Jawa barat beserta harga.\t|");
		puts("| 1. Karedok\t\t\t\tRp 10.000\t\t|");
		puts("| 2. Pepes Tahu\t\t\t\tRp 8.000\t\t|");
		puts("| 3. Pesmol Ikan Nila\t\t\tRp 12.000\t\t|");
		puts("| 4. Sayur Asam Kacang Bereum\t\tRp 13.000\t\t|");
		puts("| 5. Nasi Liwet\t\t\t\tRp 13.000\t\t|");
		puts("| 6. Soto Bandung\t\t\tRp 10.000\t\t|");
		puts("| 0. Kembali ke Daftar Daerah.\t\t\t\t\t|");
      	puts("***************===========================***********************");
    	printf("Masukan Nomor Makanan/Minuman: ");
		scanf("%d", &input);
		getchar();
		clear();
		switch (input) {
			case 0:
				Jawa_Baratbool = false;
				break;
			case 1:
				Produk karedok;
				strcpy(karedok.nama, "Karedok");
				karedok.harga = 10000;
				purchasing(karedok);
				break;
			case 2:
				Produk pepes;
				strcpy(pepes.nama, "Pepes Tahu");
				pepes.harga = 8000;
				purchasing(pepes);
				break;
			case 3:
				Produk pesmol;
				strcpy(pesmol.nama, "Pesmol Ikan Nila");
				pesmol.harga = 12000;
				purchasing(pesmol);
				break;
			case 4:
				Produk sayur;
				strcpy(sayur.nama, "Sayur Asam Kacang Beurem");
				sayur.harga = 13000;
				purchasing(sayur);
				break;
			case 5:
				Produk liwet;
				strcpy(liwet.nama, "Nasi Liwet");
				liwet.harga = 13000;
				purchasing(liwet);
				break;
			case 6:
				Produk soto;
				strcpy(soto.nama, "Soto Bandung");
				soto.harga = 10000;
				purchasing(soto);
				break;
			default:
				puts("Menu tidak diketahui, silakan coba lagi.");
				continue;
		}
		clear();
	}
	daftardaerah();
}


void Bali() {
	int input, kuantitas;
	Balibool = true;
	clear();
	while (Balibool) {
      	puts("***************===========================***********************");
		puts("| Dibawah ini daftar menu khas Bali beserta harga.\t\t|");
		puts("| 1. Bebek Betutu\t\t\tRp 15.000\t\t|");
		puts("| 2. Nasi Jinggo \t\t\tRp 20.000\t\t|");
		puts("| 3. Nasi Campur Bali\t\t\tRp 38.000\t\t|");
		puts("| 4. Es Tambring \t\t\tRp 15.000\t\t|");
		puts("| 5. Sate Plecing\t\t\tRp 20.000\t\t|");
		puts("| 6. Es Loloh Jamu ala Bali\t\tRp 17.000\t\t|");
		puts("| 0. Kembali ke Daftar Daerah.\t\t\t\t\t|");
     	puts("***************===========================***********************");
    	printf("Masukan Nomor Makanan/Minuman: ");
		scanf("%d", &input);
		getchar();
		clear();
		switch (input) {
			case 0:
				Balibool = false;
				break;
			case 1:
				Produk bebek;
				strcpy(bebek.nama, "Bebek Betutu");
				bebek.harga = 15000;
				purchasing(bebek);
				break;
			case 2:
				Produk jinggo;
				strcpy(jinggo.nama, "Nasi Jinggo");
				jinggo.harga = 20000;
				purchasing(jinggo);
				break;
			case 3:
				Produk nasi;
				strcpy(nasi.nama, "Nasi Campur Bali");
				nasi.harga = 38000;
				purchasing(nasi);
				break;
			case 4:
				Produk es;
				strcpy(es.nama, "Es Tambring");
				es.harga = 15000;
				purchasing(es);
				break;
			case 5:
				Produk sate;
				strcpy(sate.nama, "Sate Plecing");
				sate.harga = 20000;
				purchasing(sate);
				break;
			case 6:
				Produk loloh;
				strcpy(loloh.nama, "Es Loloh Jamu");
				loloh.harga = 17000;
				purchasing(loloh);
				break;
			default:
				puts("Menu tidak diketahui, silakan coba lagi.");
				continue;
		}
		clear();
	}
	daftardaerah();
}


void Ambon() {
	int input, kuantitas;
	Ambonbool = true;
	clear();
	while (Ambonbool) {
      	puts("***************===========================***********************");
		puts("| Dibawah ini daftar menu khas Ambon beserta harga.\t\t|");
		puts("| 1. Papeda\t\t\t\tRp 15.000\t\t|");
		puts("| 2. Sambal Colo-Colo\t\t\tRp 20.000\t\t|");
		puts("| 3. Rujak Natsepa\t\t\tRp 38.000\t\t|");
		puts("| 4. Kohu-Kohu\t\t\t\tRp 15.000\t\t|");
		puts("| 5. Pisang Asar\t\t\tRp 20.000\t\t|");
		puts("| 6. Asida\t\t\t\tRp 17.000\t\t|");
		puts("| 0. Kembali ke Daftar Daerah.\t\t\t\t\t|");
      	puts("***************===========================***********************");
    	printf("Masukan Nomor Makanan/Minuman: ");
		scanf("%d", &input);
		getchar();
		clear();
		switch (input) {
			case 0:
				Ambonbool = false;
				break;
			case 1:
				Produk papeda;
				strcpy(papeda.nama, "Papeda");
				papeda.harga = 15000;
				purchasing(papeda);
				break;
			case 2:
				Produk sambal;
				strcpy(sambal.nama, "Sambal Colo-Colo");
				sambal.harga = 20000;
				purchasing(sambal);
				break;
			case 3:
				Produk rujak;
				strcpy(rujak.nama, "Rujak Natsepa");
				rujak.harga = 38000;
				purchasing(rujak);
				break;
			case 4:
				Produk kohu;
				strcpy(kohu.nama, "Kohu-Kohu");
				kohu.harga = 15000;
				purchasing(kohu);
				break;
			case 5:
				Produk pisang;
				strcpy(pisang.nama, "Pisang Asar");
				pisang.harga = 20000;
				purchasing(pisang);
				break;
			case 6:
				Produk asida;
				strcpy(asida.nama, "Asida");
				asida.harga = 17000;
				purchasing(asida);
				break;
			default:
				puts("Menu tidak diketahui, silakan coba lagi.");
				continue;
		}
		clear();
	}
	daftardaerah();
}


void daftardaerah() {
	int input;
	daftardaerahbool = true;
	while (daftardaerahbool) {
      	puts("******************** YUKFOOD! *******************");
		puts("| Masukan kode nomor untuk mengaksesnya.\t|");
		puts("| 1. Aceh\t\t\t\t\t|");
		puts("| 2. Riau\t\t\t\t\t|");
      	puts("| 3. Jawa Tengah\t\t\t\t|");
        puts("| 4. Padang\t\t\t\t\t|");
        puts("| 5. Jawa Barat\t\t\t\t\t|");
        puts("| 6. Bali\t\t\t\t\t|");
        puts("| 7. Ambon\t\t\t\t\t|");
		puts("| 0. Kembali ke Main Menu\t\t\t|");
	    puts("*************=====================***************");
		printf("Masukan kode daerah: ");
		scanf("%d", &input);
		getchar();
		switch (input) {
			case 0:
				daftardaerahbool = false;
				break;
			case 1:
				aceh();
				break;
			case 2:
				riau();
            	break;
          	case 3:
            	Jawa_Tengah();
            	break;
            case 4:
            	Padang();
            	break;
            case 5:
				Jawa_Barat();
				break; 
			case 6:
				Bali();
				break;	
			case 7:
				Ambon();
				break;
          	default:
            	puts("Kode yang anda masukan tidak dikenal!");
				continue;
		}	
	}
	clear();
}


void mainmenu() {
	int input;
	mainmenubool = true;
	while (mainmenubool) {
      	puts("******************** YUKFOOD! *******************");
		puts("| Masukan kode untuk mengakses menu\t\t|");
		puts("| 1. Mulai membeli makanan khas daerah.\t\t|");
		puts("| 2. Cek / Top up balance YukPay\t\t|");
		puts("| 3. Get a Receipt and Close the program.\t|");
      	puts("*************=====================***************");
    	printf("Masukan kode menu: ");
		scanf("%d", &input);
		getchar();
		clear();
		switch (input) {
			case 1:
				daftardaerah();
				break;
			case 2:
				menupay();
				break;
			case 3:
				receipt();
				break;
			default:
				puts("Kode yang anda masukan tidak dikenal!");
				continue;
		}
	}
}


//Main program
int main() {
  	gambar();
	clear();
	selamat();
	fakeloading();
	clear();
	mainmenu();
	return 0;
}
