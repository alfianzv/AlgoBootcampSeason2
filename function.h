//global struct
struct user{
    char username[15];
    char nomorhp[15];
    char password[129];
    char pin[9];
    long long int balance;
};

//global variable
int jmlhuser = 0;
struct user akun[100];
int currentuser;

// prototype alur GoVoNa //
void scanfile();
void editfile();
void regis();
void login();
void screen();
void mainMenu();
void topupSaldo();
void isiPulsa();
void beliTiket();
void topupGame();
void settings();
void validpin();

// prototype settings //
void userProfile();
void editProfile();

// prototype topup saldo online //
void topUpOnline();
void topUpAtm();
void bcaAtm();
void mandiriAtm();
void briAtm();
void topUpMBanking();
void bcaMobile();
void mandiriMobile();
void briMobile();
// prototype topup saldo offline //
void topupOffline();
void topupAlfamart();
void topupIndomaret();

// prototype top up game //
void gameEPEP();
void gamePUBGM();
void gameCODM();
void epepTOPUP();
void pubgmTOPUP();
void codmTOPUP();

// prototype function helper //
void clrscr();
//                          //
void scanfile(){
    FILE *fp = fopen("accounts.txt", "r");
    
    while(fscanf(fp, "%s\n", &akun[jmlhuser].username) != EOF){
        fscanf(fp, "%s\n", &akun[jmlhuser].nomorhp);
        fscanf(fp, "%s\n", &akun[jmlhuser].password);
        fscanf(fp, "%s\n", &akun[jmlhuser].pin);
        fscanf(fp, "%lld\n", &akun[jmlhuser].balance);
        jmlhuser++;
    }
    fclose(fp);
}

void editfile(){
	FILE *fp = fopen("accounts.txt", "w");
    int i = 0;
    while(i<jmlhuser){
		fprintf(fp, "%s\n", akun[i].username);
        fprintf(fp, "%s\n", akun[i].nomorhp);
        fprintf(fp, "%s\n", akun[i].password);
        fprintf(fp, "%s\n", akun[i].pin);
        fprintf(fp, "%lld\n", akun[i].balance);
        i++;
    }
    fclose(fp);
}

void regis(){
    clrscr();
    puts("===========================================================\n");
    puts("      <> <> <>     == R E G I S T E R ==     <> <> <>      \n");
    puts("===========================================================\n");
    
    while(1){
        int flag = 1;
        printf("Username: ");
        scanf("%s", &akun[jmlhuser].username);
        for(int i = 0; i < jmlhuser; i++){
            if(strcasecmp(akun[jmlhuser].username, akun[i].username) == 0){
                printf("That username already exists.\n");
                printf("Try another one.\n\n");
                flag = 0;
                break;
            }
        }
        
        if(flag){
        	printf("\n");
            break;
        }
    }
    
    while(1){
        int flag = 1;
        int len = 0;
        printf("Phone Number: 08xxxxxxxx\b\b\b\b\b\b\b\b\b\b");
        scanf("%s", akun[jmlhuser].nomorhp);
        if(akun[jmlhuser].nomorhp[0] != '0' || akun[jmlhuser].nomorhp[1] != '8'){
        	printf("Number is invalid.\n\n");
        	flag = 0;
		}
        for(int i = 0; akun[jmlhuser].nomorhp[i] != '\0'; i++){
            if(akun[jmlhuser].nomorhp[i] < '0' || akun[jmlhuser].nomorhp[i] > '9'){
                printf("Input can only consist of numbers.\n\n");
                flag = 0;
                break;
            }
            len++;
        }
        for(int i = 0; i<jmlhuser; i++){
            if(strcmp(akun[jmlhuser].nomorhp, akun[i].nomorhp) == 0){
                printf("Phone number has been used.\n\n");
                flag = 0;
                break;
            }
        }
        if(len <10 || len>12){
            printf("Number is invalid.\n\n");
            flag = 0; 
            continue;
        }
        if(flag){
        	printf("\n");
            break;
        }
    }
    
    while(1){
        int flag = 1;
        int up = 0, low = 0, num = 0;
        int len = 0;
        printf("Password (8 characters, has A-Z, a-z, 0-9, no spaces): ");
        scanf("%s", &akun[jmlhuser].password);
        for(int i = 0; akun[jmlhuser].password[i] != '\0'; i++){
            if(akun[jmlhuser].password[i] >= 'A' && akun[jmlhuser].password[i] <= 'Z'){
                up++;
            }
            else if(akun[jmlhuser].password[i] >= 'a' && akun[jmlhuser].password[i] <= 'z'){
                low++;
            }
            else if(akun[jmlhuser].password[i] >= '0' && akun[jmlhuser].password[i] <= '9'){
                num++;
            }
            len++;
        }
        if(up == 0 || low == 0 || num == 0 || len != up + low + num){
            printf("Password must not have spaces and include A-Z, a-z, and 0-9.\n\n");
            flag = 0;
        }
        if(len<8){
        	puts("Password is too short.\n");
        	flag = 0;
		}
        if(flag){
        	printf("\n");
            break;
        }
    }
    
    while(1){
        int flag = 1;
        int len = 0;
        printf("PIN (8 digits, 0-9, permanent): ");
        scanf("%s", &akun[jmlhuser].pin);
        for(int i = 0; akun[jmlhuser].pin[i] != '\0'; i++){
				if(akun[jmlhuser].pin[i] < '0' || akun[jmlhuser].pin[i] > '9'){
					printf("PIN Invalid.\n");
					flag = 0;
					break;
				}
				len++;
            }
        if(len > 8){
            printf("PIN is too long.\n\n");
            flag = 0;
            continue;
        }
        if(len < 8){
        	printf("PIN isn't long enough.\n\n");
        	flag = 0;
        	continue;
		}
        if(flag){
        	printf("\nRegistration Succesfull!");
        	getchar();
            break;
        }
    }    
    currentuser = jmlhuser;
    jmlhuser++;
	editfile();
	mainMenu();
}

void login(){
	clrscr();
	puts("===========================================================\n");
    puts("      <> <> <>      ==  L O G  I N  ==      <> <> <>      \n");
    puts("===========================================================\n");
	int index;
	while(1){
		int flag;
		char uname[255];
		printf("Username: ");
		scanf("%s", uname);
		for(int i = 0; i<jmlhuser; i++){
  			if(strcasecmp(uname, akun[i].username) == 0){
  				flag = 1;
                index = i;
				break;
            }
            else{
            	flag = 0;
			}
		}
		if(flag){
			break;
		}
		else{
			puts("Username does not exsist, please register first.\n");
		}
	}
	
	while(1){
		char pw[101];
		printf("\nPassword: ");
		scanf("%s", pw);
		if(strcmp(pw, akun[index].password) == 0){
			puts("\nLogged in successfully.\n");
			getchar();
			break;
		}
		else{
			puts("Incorrect Password, please try again\n");
		}
	}
	currentuser = index;
	mainMenu();
}

void screen(){
	clrscr();
    printf("\n\n\n");
    puts("              ¦¦¦¦¦¦¦¦¦¦¦¦¦¦            ¦            ¦            ¦¯_         ¦                                  ");
    puts("              ¦¦¦                       ¦            ¦            ¦  ¯_       ¦                                  ");
    puts("              ¦¦¦                        ¦          ¦             ¦    ¯_     ¦                                  ");
    puts("              ¦¦¦                         ¦        ¦              ¦      ¯_   ¦                                  ");
    puts("              ¦¦¦     ¦¦¦¦¦¦¦  ¦¦¦¦¦¦¦¦¦¦ ¦        ¦  ¦¦¦¦¦¦¦¦¦¦  ¦        ¯_ ¦   _______                        ");
    puts("              ¦¦¦          ¦¦  ¦¦      ¦¦  ¦      ¦   ¦¦      ¦¦  ¦          ¯¦  ¦       ¯_                      ");
    puts("              ¦¦¦          ¦¦  ¦¦      ¦¦   ¦    ¦    ¦¦      ¦¦  ¦           ¦  ¦        ¦                      ");
    puts("              ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦  ¦¦¦¦¦¦¦¦¦¦    ¦¦¦¦     ¦¦¦¦¦¦¦¦¦¦  ¦           ¦   ¯______¯¯_                     \n");
    puts("                         1. Register                                    2. Login                                 \n");

	char option;
	do{
		printf(">>");
		scanf("%c", &option);
		getchar();
		if(option != '1' &&option!= '2'){
			printf("Input is not recognized.\n\n");
		}
	}
	while(option!= '1' && option!='2');
	switch(option){
		case '1':
			regis();
			break;
		case '2':
			login();
			break;
	}
}


void mainMenu()
{
	clrscr();
	char inputNum;
	puts("===========================================================");
    puts("      <> <> <>      ==   GOVONA App  ==      <> <> <>      ");
    puts("      <> <> <>       ==  MAIN MENU  ==       <> <> <>      ");
    puts("===========================================================");
	printf("Hello, ");
	printf("%s!\n", akun[currentuser].username);
	printf("You have Rp");
	printf("%lld,- credit left.\n", akun[currentuser].balance);
	puts("===========================================================");
	puts("[1] Top Up Saldo"); 
	puts("[2] Beli Pulsa"); 
	puts("[3] Beli Tiket"); 
	puts("[4] Top Up Game"); 
	puts("[5] Settings"); 
	puts("[0] Exit Program");
	puts("===========================================================");
	do 
	{
		printf("Input a number: "); scanf("%c", &inputNum);
		getchar();
		if(inputNum < '0' || inputNum > '5'){
			printf("Input is not recognized.\n");
		}
	}
	while (inputNum < '0' || inputNum > '5');
	switch (inputNum)
	{
		case '1':
			topupSaldo();
			break;
		case '2':
			isiPulsa();
			break;
		case '3':
			beliTiket();
			break;
		case '4':
			topupGame();
			break;
		case '5':
			settings();
			break;
		case '0':
			puts("\nThank you for using Govona!");
			getchar();
			exit(0);
			break;
	}
}

void settings() {
	clrscr();
	char input;
	puts("===========================================================");
    puts("        <> <> <>       == SETTINGS ==       <> <> <>       ");
    puts("===========================================================");
    puts("[1] Profile");
    puts("[0] Back to Main Menu");
    puts("===========================================================");
    do
	{
		printf("\nInput a Number: ");
		scanf("%c", &input);
		getchar();
		if(input != '0' && input != '1'){
			printf("Input is not recognized.\n");
		}
	} 
	while (input != '0' && input != '1');
	switch (input)
	{
		case '1':
			userProfile();
			break;
		case '0':
			mainMenu();
			break;
	}
	
}

void userProfile()
{
	clrscr();
	char input;
	puts("===========================================================");
    puts("        <> <> <>       == PROFILE ==       <> <> <>        ");
    puts("===========================================================");
    printf("Username	: ");
    printf("%s\n", akun[currentuser].username);
    printf("Credit		: Rp");
	printf("%lld,-\n", akun[currentuser].balance);
    printf("Phone Number	: ");
	printf("%s\n", akun[currentuser].nomorhp);
    puts("===========================================================");
    puts("[1] Edit Profile");
    puts("[2] Log Out");
    puts("[0] Back to Main Menu");
    puts("===========================================================");
    do 
	{
		printf("\nInput a number: "); scanf("%c",&input);
		getchar();
		if(input< '0' || input > '2'){
			printf("Input is not recognized.\n");
		}
	} while (input < '0' || input > '2');
	switch (input) 
	{
		case '1':
			clrscr();
			editProfile();
			break;
		case '2':
			clrscr();
			screen();
			break;
		case '0':
			clrscr();
			mainMenu();
			break;
	}
	
}

void editProfile(){
	char pw[255];
	char uname[255];
	char nohp[13];
	printf("Input password to edit your profile.\n");
	while(1){
		printf("Password: ");
		scanf("%s", pw);
		if(strcmp(pw, akun[currentuser].password) != 0){
			puts("Password incorrect.");
		}
		else{
			puts("");
			break;
		}
	}

	while(1){
		int flag = 1;
		printf("New username: ");
		scanf("%s", uname);
		for(int i = 0; i < jmlhuser; i++){
			if(strcasecmp(uname, akun[i].username) == 0){
				if(i != currentuser){
					printf("That username already exists.\n");
                	printf("Try another one.\n\n");
                	flag = 0;
                	break;
				}                
            }
        }        
        if(flag){
        	strcpy(akun[currentuser].username, uname);
        	printf("\n");
            break;
        }   
    }
    
    while(1){
        int flag = 1;
        int up = 0, low = 0, num = 0;
        int len = 0;
        printf("New password: ");
        scanf("%s", pw);
        for(int i = 0; pw[i] != '\0'; i++){
            if(pw[i] >= 'A' && pw[i] <= 'Z'){
                up++;
            }
            else if(pw[i] >= 'a' && pw[i] <= 'z'){
                low++;
            }
            else if(pw[i] >= '0' && pw[i] <= '9'){
                num++;
            }
            len++;
        }
        if(up == 0 || low == 0 || num == 0 || len != up + low + num){
            printf("Password must not have spaces and include A-Z, a-z, and 0-9.\n\n");
            flag = 0;
        }
        if(len<8){
        	puts("Password is too short.\n");
        	flag = 0;
		}
        if(flag){
        	strcpy(akun[currentuser].password, pw);
        	printf("\n");
            break;
        }
    }
    
    while(1){
        int flag = 1;
        int len = 0;
        printf("Phone Number: 08xxxxxxxx\b\b\b\b\b\b\b\b\b\b");
        scanf("%s", nohp);
        if(nohp[0] != '0' || nohp[1] != '8'){
        	printf("Number is invalid.\n\n");
        	flag = 0;
		}
        for(int i = 0; nohp[i] != '\0'; i++){
            if(nohp[i] < '0' || nohp[i] > '9'){
                printf("Input can only consist of numbers.\n\n");
                flag = 0;
                break;
            }
            len++;
        }
        for(int i = 0; i<jmlhuser; i++){
            if(strcmp(nohp, akun[i].nomorhp) == 0){
            	if(i!=currentuser){
            		printf("Phone number has been used.\n\n");
                	flag = 0;
                	break;
				}                
            }
        }
        if(len <10 || len>12){
            printf("Number is invalid.\n\n");
            flag = 0; 
        }
        if(flag){
        	strcpy(akun[currentuser].nomorhp, nohp);
        	printf("\n\n");
            break;
        }
    }
    editfile();
    userProfile();
}

void topupSaldo() 
{
	clrscr();
    char inputmenu;
    puts("===========================================================");
    puts("       <> <> <>      == TOP UP MENU ==      <> <> <>       ");
    puts("===========================================================");
    puts("[1] Top Up melalui M-Banking atau ATM");
    puts("[2] Top Up melalui Minimart");
    puts("[0] Back to Main Menu");
    puts("===========================================================");
    do 
    {
        printf("\nInput a number: "); scanf("%c",&inputmenu);
        getchar();
        if(inputmenu < '0' || inputmenu > '2'){
        	printf("Input is not recognized.\n");
		}
	} while (inputmenu < '0' || inputmenu > '2');
       switch (inputmenu) 
       {
            case '1': 
               topUpOnline();
               break;
            case '2':
               topupOffline();
               break;
            case '0':
    	       	clrscr();
                mainMenu();
                break;
       }
    
}

void topUpOnline(){
	char input = 0;
	puts("========================================");
    puts(" <> <> <> == TOP UP ONLINE == <> <> <>  ");
    puts("========================================\n");
    printf("Pilih Salah Satu Menu! \n");
    printf("[1] Top Up Via M-Banking\n");
    printf("[2] Top Up Via ATM\n");
    printf("[9] Back to Top Up Saldo Menu\n");
    printf("[0] Back to Main Menu\n\n");
	do
	{
		printf(">> "); scanf("%c",&input);
		getchar();
		if(input < '0' || ('2' < input && input < '9') || input > '9'){
			printf("Input is not recognized.\n");
		}
	} while (input < '0' || ('2' < input && input < '9') || input > '9');		
	switch(input)
	{
		case '1':
			clrscr();
			topUpMBanking();
		case '2':
			clrscr();
			topUpAtm();
		case '9':
			topupSaldo();
		case '0':
			clrscr();
			mainMenu();
	}
	
}

void topUpMBanking(){
	char input = 0;
	puts("===================================================");
    puts(" <> <> <> == TOP UP Melalui M-Banking == <> <> <>  ");
    puts("===================================================\n");
    printf("Pilih Salah Satu Menu! \n");
    printf("1. Top Up Via BCA\n");
    printf("2. Top Up Via Mandiri\n");
    printf("3. Top Up Via BRI\n");
    printf("4. Back to Top Up Online Menu\n\n");
	do{
		printf(">> "); scanf("%c",&input);
		getchar();
		if(input<'1' || input > '4'){
			printf("Input is not recognized.\n");
		}
	} while (input< '1' || input > '4');
	switch(input)
	{		
	case '1':
		clrscr();
		bcaMobile();
	case '2':
		clrscr();
		mandiriMobile();
	case '3':
		clrscr();
		briMobile();
	case '4':
		clrscr();
		topUpOnline();
	}
}

void topUpAtm(){
	char input = 0;
	puts("=============================================");
    puts(" <> <> <> == TOP UP Melalui ATM == <> <> <>  ");
    puts("=============================================\n");
    printf("Pilih Salah Satu Menu! \n");
    printf("1. Top Up Via BCA\n");
    printf("2. Top Up Via Mandiri\n");
    printf("3. Top Up Via BRI\n");
    printf("4. Back to Top Up Online Menu\n\n");
	do{
		printf(">> "); scanf("%c",&input);
	}while (input<'1' || input > '4');
	switch(input){
		case '1':
			clrscr();
			bcaAtm();
		case '2':
			clrscr();
			mandiriAtm();
		case '3':
			clrscr();
			briAtm();
		case '4':
			clrscr();
			topUpOnline();
	}		
		
}

void bcaMobile() {
    puts("===================================================================");
    puts(" <> <> <> == HOW TO TOP UP THROUGH BCA MOBILE BANKING == <> <> <>  ");
    puts("===================================================================\n");
    printf ("\n");
    printf ("1. Buka Aplikasi BCA Mobile, Lalu pilih M-BCA\n");
    printf ("2. Masukkan kode akses untuk login\n");
    printf ("3. Pilih menu m-transfer\n");
    printf ("4. Pilih BCA Virtual Account \n");
    printf ("5. Masukkan nomor virtual account BCA GoVoNa, yaitu 12345 + no HP yang terdaftar di GoVoNa, lalu pilih 'OK'\n");
    printf ("6. Setelah itu, pilih tombol Send, jika nomor benar maka akan muncul nama pemilik akun GoVoNa, lanjut memilik 'OK'\n");
    printf ("7. Masukkan nominal saldo yang hendak di-top up\n");
    printf ("8. Masukkan pin M-BCA, lalu pilih OK\n");
    printf ("9. Jika transfer berhasil, makan akan muncul pemberitahuan dan saldo pada akun yang di-top up sehingga saldo akan \n");
	printf ("   langsung bertambah.\n");
    
    getchar ();
    clrscr();
    topUpMBanking();
    
}

void mandiriMobile(){
	puts("=======================================================================");
    puts(" <> <> <> == HOW TO TOP UP THROUGH MANDIRI MOBILE BANKING == <> <> <>  ");
    puts("=======================================================================\n");
    printf ("\n");
    printf ("1. Buka aplikasi Mandiri Online\n");
    printf ("2. Login ke akun Mandiri Online Anda\n");
    printf ("3. Pilih menu Pembayaran\n");
    printf ("4. Pilih menu Buat Pembayaran Baru \n");
    printf ("5. Pilih menu Multipayment\n");
    printf ("6. Pilih GoVoNa dan masukkan nomor ponsel Anda: 0812-xxxx-xxxx\n");
    printf ("7. Masukkan nominal top-up GoVoNa yang anda inginkan\n");
    printf ("8. Ikuti instruksi untuk menyelesaikan transaksi\n");
    
    getchar ();
    clrscr();
    topUpMBanking();
}

void briMobile(){
	puts("===================================================================");
    puts(" <> <> <> == HOW TO TOP UP THROUGH BRI MOBILE BANKING == <> <> <>  ");
    puts("===================================================================\n");
    printf ("\n");
    printf ("1. Masuk ke dalam akun BRI Mobile Anda dengan memasukkan informasi yang diminta.\n");
    printf ("2. Begitu Anda berhasil masuk ke dalam mobile banking BRI, layar akan menampilkan sederet menu. Pilih menu BRIVIA\n");
    printf ("3. Masukkan kode nomor virtual account GoVona BRI yang diawali angka 12345 + nomor HP Anda yang terdaftar di akun GoVoNa\n");
    printf ("4. nominal saldo yang ingin Anda tambahkan ke dalam akun GoVona Anda. \n");
    printf ("5. Ikuti petunjuk dan langkah-langkah berikut yang diinstruksikan untuk melanjutkan dan menyelesaikan transaksi Anda.\n");
    
    getchar();
    clrscr();
    topUpMBanking();
}

void bcaAtm(){
	puts("========================================================");
    puts(" <> <> <> == HOW TO TOP UP THROUGH BCA ATM == <> <> <>  ");
    puts("========================================================\n");
    printf ("\n");
    printf ("1. Masukkan kartu ATM BCA ke mesin ATM, lalu masukkan pin\n");
    printf ("2. Pilih menu 'transaksi lainnya'\n");
    printf ("3. Lalu, klik 'transfer'\n");
    printf ("4. Pilih 'Ke Rek BCA Virtual Account' \n");
    printf ("5. Masukkan nomor virtual account GoVoNa yang akan diisi saldo, yakni kode perusahaan GoVoNa 12345+no HP terdaftar\n");
	printf ("   lalu pilih  'Benar'\n");
    printf ("6. Ketika muncul nomor virtual GoVoNa, nama akun, dan nama produk, silakan isi jumlah top up (minimal Rp20.000)\n");
	printf ("   lalu klik 'Benar'\n");
    printf ("7. Pada layar konfirmasi akan muncul pertanyaan mengenai apakah data yang dimasukkan sudah tepat, jika tepat\n");
	printf ("   pilih 'Iya'\n");
    printf ("8. Tunggu hingga transaksi selesai dan struk pengisian saldo GoVoNa dicetak keluar dari mesin ATM sebagai bukti\n");
	printf ("   pengisian ulang\n");
    
    getchar ();
    clrscr();
    topUpAtm();
	
}

void mandiriAtm(){
	puts("============================================================");
    puts(" <> <> <> == HOW TO TOP UP THROUGH MANDIRI ATM == <> <> <>  ");
    puts("============================================================\n");
    printf ("\n");
    printf ("1. Masukkan kartu ATM dan PIN Mandiri Anda\n");
    printf ("2. Pilih menu Bayar/Beli\n");
    printf ("3. Pilih menu Lainnya, pilih lagi menu Lainnya\n");
    printf ("4. Pilih menu E-Commerce \n");
    printf ("5. Masukkan kode GoVoNa 12345, Khusus bank Mandiri\n");
	printf ("   Nomor Khususnya yakni 12345 + Nomor Ponsel Anda. Misal 0812-XXXX-XXXX\n");
    printf ("6. Masukkan nominal top-up yang anda inginkan\n");
    printf ("7. Ikuti instruksi untuk menyelesaikan transaksi\n");
    
    getchar ();	
    clrscr();
    topUpAtm();
}

void briAtm(){
	puts("========================================================");
    puts(" <> <> <> == HOW TO TOP UP THROUGH BRI ATM == <> <> <>  ");
    puts("========================================================\n");
    printf ("\n");
    printf ("1. Masukkan kartu ATM dan PIN BRI Anda\n");
    printf ("2. Pilih menu Transaksi Lain lalu pilih Bank Lain\n");
    printf ("3. Pilih menu Pembayaran lalu pilih Bank Lain\n");
    printf ("4. Pilih menu Lainnya lalu pilih Bank Lain\n");
    printf ("5. Pilih BRIVA\n");
    printf ("6. Masukkan 12345 + nomor ponsel Anda 12345+ 08xx-xxxx-xxxx\n");
    printf ("7. Masukkan nominal transfer\n");
    printf ("8. Ikuti instruksi untuk menyelesaikan transaksi\n");
    
    getchar();
    clrscr();
    topUpAtm();
	
}

void topupOffline() 
{
	clrscr();
    char inputmenu;
    puts("===========================================================");
    puts("       <> <> <>      == TOP UP OFFLINE ==      <> <> <>    ");
    puts("===========================================================");
    printf("[1] ALFAMART\n");
    printf("[2] INDOMARET\n");
    printf("[9] Back to Top-Up Saldo Page\n");
    printf("[0] Back to Main Menu\n");
    puts("===========================================================");
    do 
    {
        printf("\nInput a number: "); scanf("%c",&inputmenu);
        getchar();
        if(inputmenu < '0' || ('2' < inputmenu && inputmenu < '9')|| inputmenu > '9'){
        	printf("Input is not recognized.\n");
		}
    } while (inputmenu < '0' || ('2' < inputmenu && inputmenu < '9')|| inputmenu > '9');
        switch (inputmenu) 
        {
            case '1': 
                topupAlfamart();
                break;
            case '2':
                topupIndomaret();
                break;
            case '9':
            	topupSaldo();
            	break;
            case '0':
            	clrscr();
                mainMenu();
                break;
        }
}

void topupAlfamart() 
{
	clrscr();
	char input;
	puts("===========================================================");
    puts("   <> <> <> == HOW TO TOP UP THROUGH ALFAMART == <> <> <>  ");
    puts("===========================================================");
	printf ("1. Come to the nearest Alfamart\n");
	printf ("2. Tell the cashier that you want to Top Up for GoVoNa\n");
	printf ("3. Tell them GoVoNa's product code 696 + your number\n");
	printf ("4. Example : 6960818207839\n");
	printf ("5. The cashier will confirm your code by asking you your name\n");
	printf ("6. If it match the data from our server then you can move on to the next step\n");
	printf ("7. Tell the cashier how much you wanted to Top Up\n");
	printf ("8. Pay the cashier with Top Up + Rp.2000 for administration fee\n");
	printf ("9. Lastly the cashier will confirm your payment and will give you the Top Up receipt\n");
	printf ("10. Save your receipt and confirm your Top Up have been accepted by checking GoVoNa app\n");
	puts("");
	printf ("[9] Back to Top Up Menu\n");
	printf ("[0] Main Menu\n");
    do 
    {
        printf("\nInput a number: "); scanf("%c",&input);
        getchar();
        if(input != '9' || input != '0'){
        	printf("Input is not recognized.\n");
		}
    } while (input != '9' || input != '0');
    switch (input) 
    {
        case '9': 
            topupSaldo();
            break;
        case '0':
         	clrscr();
            mainMenu();
            break;
    }
}

void topupIndomaret() 
{
	clrscr();
	char input;
	puts("===========================================================");
    puts("   <> <> <> == HOW TO TOP UP THROUGH INDOMARET == <> <> <> ");
    puts("===========================================================");
	printf ("1. Come to the nearest Indomaret\n");
	printf ("2. Tell the cashier that you want to Top Up for GoVoNa\n");
	printf ("3. Tell them GoVoNa's product code 696 + your number\n");
	printf ("4. Example : 6960818207839\n");
	printf ("5. The cashier will confirm your code by asking you your name\n");
	printf ("6. If it match the data from our server then you can move on to the next step\n");
	printf ("7. Tell the cashier how much you wanted to Top Up\n");
	printf ("8. Pay the cashier with Top Up + Rp.2000 for administration fee\n");
	printf ("9. Lastly the cashier will confirm your payment and will give you the Top Up receipt\n");
	printf ("10. Save your receipt and confirm your Top Up have been accepted by checking GoVoNa app\n");
	puts ("");
	printf ("[9] Back to Top Up Menu\n");
	printf ("[0] Main Menu\n");
    do 
    {
        printf("\nInput a number: "); scanf("%c",&input);
        getchar();
        if(input != '9' && input != '0'){
        	printf("Input is not recognized.\n");
		}
    } while (input != '9' && input != '0');
    switch (input) 
    {
        case '9': 
            topupSaldo();
            break;
        case '0':
          	clrscr();
            mainMenu();
            break;
    }
}

void beliTiket() {
	clrscr();
    puts("===========================================================");
	puts("       <> <> <>      == BELI  TIKET ==      <> <> <>       ");
	puts("===========================================================");
	printf("         Mohon maaf, fitur sementara tidak dapat         \n");
	printf("  digunakan untuk mematuhi anjuran PSBB dari pemerintah. \n");
	puts("===========================================================");
	printf("          (Press \"Enter\" to go back to Main Menu)");
	getchar();
	getchar();
	clrscr();
	mainMenu();
}

void topupGame() {
	char inputGame;
	clrscr();
	puts("===========================================================");
	puts("       <> <> <>      == TOP UP GAME ==      <> <> <>       ");
	puts("===========================================================");
	printf("[1] Garena Free Fire\n");
	printf("[2] PUBG MOBILE\n");
	printf("[3] Call of Duty: Mobile\n");
	printf("[0] Back to Main Menu\n");
	puts("===========================================================");
	do 
	{
		printf("\nInput a number: "); scanf("%c",&inputGame);
		getchar();
		if(inputGame < '0' || inputGame > '3'){
			printf("Input is not recognized.\n");
		}
	} while (inputGame < '0' || inputGame > '3');
	switch (inputGame) 
	{
		case '1':
			gameEPEP();
			break;
		case '2':
			gamePUBGM();
			break;
		case '3':
			gameCODM();
			break;
		case '0':
			clrscr();
			mainMenu();
			break;
	}
}

void gameEPEP() {
	char playerID[100];
	int ctr, j = 0, temp = 1;
	clrscr();
	puts("===========================================================");
	puts("     <> <> <>     == GARENA : Free Fire ==     <> <> <>    ");
	puts("===========================================================");
	printf("To find your PlayerID, click on your profile on the top-left corner\n");
	printf("of your screen. ");
	printf("Your Free Fire PlayerID will be displayed there.\n");
	puts("===========================================================");

	do
	{
		printf("Insert your PlayerID: "); scanf("%s",&playerID);
		int flag = 1, ctr = 0;
		for (int i = 0; playerID[i] != '\0'; i++)
		{
			ctr++;
		}
		if (ctr < 8 || ctr > 9)
		{
			puts("PlayerID is not recognized.\n");
			temp = 0;
			continue;
		}
		for (int j = 0; playerID[j] != '\0'; j++)
		{
			if (playerID[j] < 48 || playerID[j] > 57)
			{
				flag = 0;
				temp = 0;
				break;
			}
			temp = 1;
		}
		flag ? printf("PlayerID detected.\n") : printf("PlayerID format is illegal.\n");
	} while (temp == 0);
	printf("\n");
	epepTOPUP();
}

void gamePUBGM() {
	char playerID[100];
	int ctr, j = 0, temp = 1;
	clrscr();
	puts("===========================================================");
	puts("      <> <> <>       == PUBG MOBILE ==       <> <> <>      ");
	puts("===========================================================");
	printf("To find your PlayerID, click on your avatar on the top-right corner\n");
	printf("of your screen. ");
	printf("Your PUBG MOBILE PlayerID will be displayed there.\n");
	puts("===========================================================");

	do
	{
		printf("Insert your PlayerID: "); scanf("%s",&playerID);
		int flag = 1, ctr = 0;
		for (int i = 0; playerID[i] != '\0'; i++)
		{
			ctr++;
		}
		if (ctr < 10 || ctr > 10)
		{
			puts("PlayerID is not recognized.\n");
			temp = 0;
			continue;
		}
		for (int j = 0; playerID[j] != '\0'; j++)
		{
			if (playerID[j] < 48 || playerID[j] > 57)
			{
				flag = 0;
				temp = 0;
				break;
			}
			temp = 1;
		}
		flag ? printf("PlayerID detected.\n") : printf("PlayerID format is illegal.\n");
	} while (temp == 0);
	printf("\n");
	pubgmTOPUP();
}

void gameCODM() {
	char openID[100];
	int ctr, j = 0, temp = 1;
	clrscr();
	puts("===========================================================");
	puts("    <> <> <>    == CALL OF DUTY:  MOBILE ==    <> <> <>    ");
	puts("===========================================================");
	printf("To find your OpenID, press on \"Setting\" that is located on\n");
	printf("the top right corner of your screen then press on \"Legal and\n");
	printf("Privacy\". Your OpenID will be available there.\n");
	puts("===========================================================");

	do
	{
		printf("Insert your OpenID: "); scanf("%s",&openID);
		int flag = 1, ctr = 0;
		for (int i = 0; openID[i] != '\0'; i++)
		{
			ctr++;
		}
		if (ctr < 20 || ctr > 20)
		{
			puts("OpenID is not recognized.\n");
			temp = 0;
			continue;
		}
		for (int j = 0; openID[j] != '\0'; j++)
		{
			if (openID[j] < 48 || openID[j] > 57)
			{
				flag = 0;
				temp = 0;
				break;
			}
			temp = 1;
		}
		flag ? printf("OpenID detected.\n") : printf("OpenID format is illegal.\n");
	} while (temp == 0);
	printf("\n");
	codmTOPUP();
}

void epepTOPUP() {
	for (long long int i = 0; i <= 180000000; i++) {
		;
	}
	int inputUC;
	puts("===========================================================");
	puts("Please choose the amount of Free Fire Diamonds you wish to buy?");
	puts("===========================================================");
	printf("[1] 5 Diamonds\n"); // Rp 1rb
	printf("[2] 12 Diamonds\n"); // Rp 2rb
	printf("[3] 50 Diamonds\n"); // Rp 8rb
	printf("[4] 70 Diamonds\n"); // Rp 10rb
	printf("[5] 140 Diamonds UC\n"); // Rp 20rb
	printf("[9] Back to Top-Up Game Page\n");
	printf("[0] Back to Main Menu\n");
	puts("===========================================================");
	do 
	{
		printf("\nInput a number: "); scanf("%d",&inputUC);
		getchar();
		if((inputUC < 0) || (5 < inputUC && inputUC < 9) || (inputUC > 9)){
			printf("Input is not recognized.\n");
		}
	} while ((inputUC < 0) || (5 < inputUC && inputUC < 9) || (inputUC > 9));
		switch (inputUC)
		{
			case 1:
				printf("It will cost Rp 1,000,-\n");
				if(akun[currentuser].balance < 1000){
					printf("Can't do transaction. Balance is insufficient.\n");
				}
				else{
					validpin();
					akun[currentuser].balance -= 1000;
					editfile();
					printf("Your balance is now Rp%lld,-\n", akun[currentuser].balance);
					getchar();
					getchar();
					mainMenu();
				}
				break;
			case 2:
				printf("It will cost Rp 2,000,-\n");
				if(akun[currentuser].balance < 2000){
					printf("Can't do transaction. Balance is insufficient.\n");
				}
				else{
					validpin();
					akun[currentuser].balance -= 2000;
					editfile();
					printf("Your balance is now Rp%lld,-\n", akun[currentuser].balance);
					getchar();
					getchar();
					mainMenu();
				}
				break;
			case 3:
				printf("It will cost Rp 8,000,-\n");
				if(akun[currentuser].balance < 8000){
					printf("Can't do transaction. Balance is insufficient.\n");
				}
				else{
					validpin();
					akun[currentuser].balance -= 8000;
					editfile();
					printf("Your balance is now Rp%lld,-\n", akun[currentuser].balance);
					getchar();
					getchar();
					mainMenu();
				}
				break;
			case 4:
				printf("It will cost Rp 10,000,-\n");
				if(akun[currentuser].balance < 10000){
					printf("Can't do transaction. Balance is insufficient.\n");
				}
				else{
					validpin();
					akun[currentuser].balance -= 10000;
					editfile();
					printf("Your balance is now Rp%lld,-\n", akun[currentuser].balance);
					getchar();
					getchar();
					mainMenu();
				}
				break;
			case 5:
				printf("It will cost Rp 20,000,-\n");
				if(akun[currentuser].balance < 20000){
					printf("Can't do transaction. Balance is insufficient.\n");
				}
				else{
					validpin();
					akun[currentuser].balance -= 20000;
					editfile();
					printf("Your balance is now Rp%lld,-\n", akun[currentuser].balance);
					getchar();
					getchar();
					mainMenu();
				}
				break;
			case 9:
				topupGame();
				break;
			case 0:
				clrscr();
				mainMenu();
				break;
		}
}

void pubgmTOPUP() {
	for (long long int i = 0; i <= 180000000; i++) {
		;
	}
	int inputUC;
	puts("===========================================================");
	puts("Please choose the amount of PUBG Mobile UC you wish to buy?");
	puts("===========================================================");
	printf("[1] 250+13 UC\n"); // Rp 50rb
	printf("[2] 500+25 UC\n"); // Rp 100rb
	printf("[3] 1250+125 UC\n"); // Rp 250rb
	printf("[4] 2500+375 UC\n"); // Rp 500rb
	printf("[5] 5000+1000 UC\n"); // Rp 1 000rb
	printf("[9] Back to Top-Up Game Page\n");
	printf("[0] Back to Main Menu\n");
	puts("===========================================================");
	do 
	{
		printf("\nInput a number: "); scanf("%d",&inputUC);
		getchar();
		if((inputUC < 0) || (5 < inputUC && inputUC < 9) || (inputUC > 9)){
			printf("Input is not recognized.\n");
		}
	} while ((inputUC < 0) || (5 < inputUC && inputUC < 9) || (inputUC > 9));
	switch (inputUC) 
	{
		case 1:
			printf("It will cost Rp 50,000,-\n");
			if(akun[currentuser].balance < 50000){
					printf("Can't do transaction. Balance is insufficient.\n");
				}
				else{
					validpin();
					akun[currentuser].balance -= 50000;
					editfile();
					printf("Your balance is now Rp%lld,-\n", akun[currentuser].balance);
					getchar();
					getchar();
					mainMenu();
				}
			break;
		case 2:
			printf("It will cost Rp 100,000,-\n");
			if(akun[currentuser].balance < 100000){
					printf("Can't do transaction. Balance is insufficient.\n");
				}
				else{
					validpin();
					akun[currentuser].balance -= 100000;
					editfile();
					printf("Your balance is now Rp%lld,-\n", akun[currentuser].balance);
					getchar();
					getchar();
					mainMenu();
				}
			break;
		case 3:
			printf("It will cost Rp 250,000,-\n");
			if(akun[currentuser].balance < 250000){
					printf("Can't do transaction. Balance is insufficient.\n");
				}
				else{
					validpin();
					akun[currentuser].balance -= 250000;
					editfile();
					printf("Your balance is now Rp%lld,-\n", akun[currentuser].balance);
					getchar();
					getchar();
					mainMenu();
				}
			break;
		case 4:
			printf("It will cost Rp 500,000,-\n");
			if(akun[currentuser].balance < 500000){
					printf("Can't do transaction. Balance is insufficient.\n");
				}
				else{
					validpin();
					akun[currentuser].balance -= 500000;
					printf("Your balance is now Rp%lld,-\n", akun[currentuser].balance);
					editfile();
					getchar();
					getchar();
					mainMenu();
				}
			break;
		case 5:
			printf("It will cost Rp 1,000,000,-\n");
			if(akun[currentuser].balance < 1000000){
					printf("Can't do transaction. Balance is insufficient.\n");
				}
				else{
					validpin();
					akun[currentuser].balance -= 1000000;
					printf("Your balance is now Rp%lld,-\n", akun[currentuser].balance);
					editfile();
					getchar();
					getchar();
					mainMenu();
				}
			break;
		case 9:
			topupGame();
			break;
		case 0:
			clrscr();
			mainMenu();
			break;
	}
}

void codmTOPUP() {
	for (long long int i = 0; i <= 180000000; i++) {
		;
	}
	int inputCP;
	puts("===========================================================");
	puts("Please choose the amount of COD Points you wish to buy?");
	puts("===========================================================");
	printf("[1] 317 CP\n"); // Rp 50rb
	printf("[2] 634 CP\n"); // Rp 100rb
	printf("[3] 1373 CP\n"); // Rp 200rb
	printf("[4] 3564 CP\n"); // Rp 500rb
	printf("[5] 7656 CP\n"); // Rp 1 000rb
	printf("[9] Back to Top-Up Game Page\n");
	printf("[0] Back to Main Menu\n");
	puts("===========================================================");
	do 
	{
		printf("\nInput a number: "); scanf("%d",&inputCP);
		getchar();
		if((inputCP < 0) || (5 < inputCP && inputCP < 9) || (inputCP > 9)){
			printf("Input is not recognized.\n");
		}
	} while ((inputCP < 0) || (5 < inputCP && inputCP < 9) || (inputCP > 9));
	switch (inputCP) 
	{
		case 1:
			printf("It will cost Rp 50,000,-\n");
			if(akun[currentuser].balance < 50000){
					printf("Can't do transaction. Balance is insufficient.\n");
				}
				else{
					validpin();
					akun[currentuser].balance -= 50000;
					editfile();
					printf("Your balance is now Rp%lld,-\n", akun[currentuser].balance);
					getchar();
					getchar();
					mainMenu();
				}
			break;
		case 2:
			printf("It will cost Rp 100,000,-\n");
			if(akun[currentuser].balance < 100000){
					printf("Can't do transaction. Balance is insufficient.\n");
				}
				else{
					validpin();
					akun[currentuser].balance -= 100000;
					printf("Your balance is now Rp%lld,-\n", akun[currentuser].balance);
					editfile();
					getchar();
					getchar();
					mainMenu();
				}
			break;
		case 3:
			printf("It will cost Rp 200,000,-\n");
			if(akun[currentuser].balance < 200000){
					printf("Can't do transaction. Balance is insufficient.\n");
				}
				else{
					validpin();
					akun[currentuser].balance -= 200000;
					printf("Your balance is now Rp%lld,-\n", akun[currentuser].balance);
					editfile();
					getchar();
					getchar();
					mainMenu();
				}
			break;
		case 4:
			printf("It will cost Rp 500,000,-\n");
			if(akun[currentuser].balance < 500000){
					printf("Can't do transaction. Balance is insufficient.\n");
				}
				else{
					validpin();
					akun[currentuser].balance -= 500000;
					printf("Your balance is now Rp%lld,-\n", akun[currentuser].balance);
					editfile();
					getchar();
					getchar();
					mainMenu();
				}
			break;
		case 5:
			printf("It will cost Rp 1,000,000,-\n");
			if(akun[currentuser].balance < 1000000){
					printf("Can't do transaction. Balance is insufficient.\n");
				}
				else{
					validpin();
					akun[currentuser].balance -= 1000000;
					printf("Your balance is now Rp%lld,-\n", akun[currentuser].balance);
					editfile();
					getchar();
					getchar();
					mainMenu();
				}
			break;
		case 9:
			topupGame();
			break;
		case 0:
			clrscr();
			mainMenu();
			break;
	}
}

void validpin(){
	int flag = 1;
	char p[9];
	while(1){
		printf("Enter PIN to confirm transaction: ");
		scanf("%s", p);
		if(strcmp(akun[currentuser].pin, p) != 0){
			flag = 0;
			printf("PIN is incorrect.\n");
		}
		if(flag){
			printf("Transaction successfully done!\n");
			break;
		}
	}
}

void isiPulsa(){
	
	clrscr();
    puts("===========================================================");
	puts("       <> <> <>      == BELI  PULSA ==      <> <> <>       ");
	puts("===========================================================");
	printf("   Mohon maaf, fitur sementara tidak dapat digunakan   \n");
	puts("===========================================================");
	printf("          (Press \"Enter\" to go back to Main Menu)");
	
	while (1) 
	{
		getchar();
		clrscr();
		mainMenu();
	}
	
	
}


void clrscr()
{
	for (int i = 0; i <= 100; i++)
	{
   		printf("\n");
	}
}
