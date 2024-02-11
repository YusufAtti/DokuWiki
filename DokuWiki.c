#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <locale.h>


char dosyaIsimleri[50][50];
char yetimEtiketler[50][50];
char etiketler[50][50];
int numarator = 200;


void etiketleriCek(){
	int sayac = 0;
	FILE *fp = fopen("etiketler.txt" , "r");
	char* etiket = malloc(50);
	while(fgets(etiket,50,fp) != NULL){
		int len = strlen(etiket);
		etiket[len - 1] = '\0';
		strcpy(etiketler[sayac], etiket);
		sayac++;
	}
	fclose(fp);
}

void dosyaIsimleriBul(){
	char foldernames[3][40] = {"Bölümler" , "Dersler" , "Öðretim Elemanlarý"};
	int j=0,i=0,a;
	for(a=0; a<3; a++){
    	DIR *d;
    	struct dirent *dir;
		char yol[80];
		strcpy(yol,"./Üniversite/");
		strcat(yol,foldernames[a]);
   		d = opendir(yol);
    	if (d)
    	{
        	while ((dir = readdir(d)) != NULL)
        	{
        		if(j<2)
        			j++;
            	else {
            		if(strstr(dir->d_name,".txt")){
						strcpy(dosyaIsimleri[i],dir->d_name);
						i++;
					}		
				}		
        	}
        	closedir(d);
		}
		memset(yol,0,sizeof(yol)); 
	}
}

void istenenEtiketYaz(){
	int max_size = 300;
	int i,kontrol = 0;
	
	//--------------------------------------------------	
	FILE *fp = fopen("etiketler.txt", "r");
	FILE *fp1 = fopen("istenenetiketler.txt" , "w");
	//--------------------------------------------------
	
	if(fp == NULL || fp1 == NULL)
		printf("Dosya acilamadi...");
	else {
		for(i = 0; i < 50; i++){
			if(strlen(dosyaIsimleri[i]) < 4)
				break;
			char* etiket = malloc(max_size);
			while (fgets(etiket, max_size, fp) != NULL) {
				int len = strlen(etiket);
				etiket[len - 1] = '\0';
				strcat(etiket,".txt");
    			//printf("%s--------%s----------%d\n" , dosyaIsimleri[i] , etiket , strcmp(dosyaIsimleri[i], etiket));
    			if(strcmp(dosyaIsimleri[i], etiket) == 0){
					kontrol = 1;
    				break;
				}
			}		
			if(kontrol == 0){
				char* istenenetiket = malloc(100);
				strcpy(istenenetiket, dosyaIsimleri[i]);
				int uzunluk = strlen(istenenetiket);
				int sayac = 0;
				while( sayac < uzunluk){
					if(istenenetiket[sayac] == ' '){
						istenenetiket[sayac] = '_';
						break;
					}
					sayac++;
				}	
				istenenetiket[uzunluk - 4] = '\0';
				fprintf(fp1, "%s\n" , istenenetiket);
				free(istenenetiket);
			}
			kontrol = 0;
			free(etiket);
			fseek(fp , 0 , SEEK_SET);
		}	
	}
	fclose(fp);
	fclose(fp1);
}

struct etiket {
	char ad[50];
	int adet;
};

void arraytofile(char *metin , char *_dir){
	FILE *fp = fopen(_dir, "w");
	if( fp == NULL)
		printf("Dosyaya ulasilamadi...");
	else {
		int len = strlen(metin);
		int i;
		for(i = 0 ; i < len; i++){
			fprintf(fp, "%c" , metin[i]);
		}
	}
	fclose(fp);
}

char *filetoarray(char *filename){
	//printf("%s\n", filename);
	FILE *fp;
	fp = fopen(filename, "r");
	if(fp == NULL){	
		printf("Dosya acilamadi... filetoarray");		
	} else {
		fseek(fp, 0 , SEEK_END);
		int len = ftell(fp);
		fseek(fp , 0 , SEEK_SET);
		char *arr = malloc( sizeof(char) * (len + 1));
		char c;
		int i =0;
		while( (c = fgetc(fp)) != EOF){
			arr[i] = c;
			i++;
		}
		arr[i] = '\0';
		fclose(fp);
		return arr;
	}
	return 0;	
}

void filename(char *foldername , char files[][50]){
	int j=0,i=0;
    DIR *d;
    struct dirent *dir;
	char yol[80];
	strcpy(yol,"./Üniversite/");
	strcat(yol,foldername);
    d = opendir(yol);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
        	if(j<2)
        		j++;
            else {
            	if(strstr(dir->d_name,".txt")){
					strcpy(files[i],dir->d_name);
					i++;
				}		
			}		
        }
        closedir(d);
	} 
}

void outputYazdir(){
		struct etiket etiketler[50];
		struct etiket yetimetiketler[50];
		int i,j=0,k,a=0,b=0;
		for(i=0; i<50; i++){
			etiketler[i].adet = 0;
			yetimetiketler[i].adet = 0;
		}
		char etiket[50];
		FILE *fp = fopen("etiketler.txt" , "r");
		if(fp == NULL){
			printf("Dosya Acilamadi...");
		} 
		else {	
			while(!feof(fp)){
				fgets(etiket,50,fp);
				//printf("%s\n",etiket);
				if(a == 0){
					strcpy(etiketler[0].ad,etiket);
					etiketler[0].adet++;
					a++;
				}
				else {
					for(i=0; i<50; i++){
						if(strcmp(etiketler[i].ad , etiket) == 0){
							etiketler[i].adet++;
							break;
						}	
						else if(etiketler[i].adet == 0 && i > 0){
							strcpy(etiketler[i].ad,etiket);
							etiketler[i].adet++;
							break;
						}
					}
				}	
			}
			etiketler[i].adet--;
		}
		char yetimetiket[50];
		FILE *fp2 = fopen("yetimetiketler.txt" , "r");
		if(fp2 == NULL){
			printf("Dosya Acilamadi...");
		} else {
			while(!feof(fp2)){
				fgets(yetimetiket,50,fp2);
				//printf("yetim etiket : %s\n",yetimetiket);
				if(b == 0){
					strcpy(yetimetiketler[0].ad,yetimetiket);
					yetimetiketler[0].adet++;
					b++;
				}
				else {
					for(i=0; i<50; i++){
						if(strcmp(yetimetiketler[i].ad , yetimetiket) == 0){
							yetimetiketler[i].adet++;
							break;
						}	
						else if(yetimetiketler[i].adet == 0 && i > 0){
							strcpy(yetimetiketler[i].ad,yetimetiket);
							yetimetiketler[i].adet++;
							break;
						}
					}
				}
			}
		}
				
		fclose(fp2);
		FILE *fp1 = fopen("output.txt", "w+");
		if(fp1 == NULL){
			printf("Dosya Acilamadi...");
		}
		else {
			fprintf(fp1 ,"\n%s\n-----------\n" , "Etiketler");
			for(i=0; i<50; i++){
				if(etiketler[i].adet == 0)
					break;
				fprintf(fp1 , "Etiket Adý : %sGeçtiði Sayi : %d\n", etiketler[i].ad , etiketler[i].adet);
			}	
			fprintf(fp1 ,"\n%s\n-----------\n" , "Yetim Etiketler");
			for(i=0; i<50; i++){
				if(yetimetiketler[i].adet == 0)
					break;
				fprintf(fp1 , "%s", yetimetiketler[i].ad);
			}	
		}
		fclose(fp);
		fclose(fp1);		
}

void etiketYazdir(char *_dir){
		FILE *fp1 = fopen("yetimetiketler.txt", "a+");
		FILE *fp = fopen("etiketler.txt" , "a+");
		if(fp == NULL || fp1 == NULL){
			printf("Dosya Acilamadi");
		} else {
			char metin[2048];
			strcpy(metin,filetoarray(_dir));
			int boyut = strlen(metin);	
			char kelime[50];	
			int i,j,k,a=0,c=0;
			int kelimeSayisi=0;
			int index=0,index2=0,etiketMi = 0;
			for(i=0; i<boyut; i++){
				if(metin[i] == '[' && metin[i+1] == '[') {
					for(j=i+1; j<boyut; j++){
						if(metin[j] == ' ')
							kelimeSayisi++;
						if(metin[j] == ']' && metin[j+1] == ']' && kelimeSayisi < 2){
							int len = j - i - 2;					
							for(k=i+2; k <= i + len + 1; k++){
								kelime[a] = metin[k];
								a++;
							}
							kelime[a] = '\0';
							//printf("Kelime : %s\n", kelime);
							char kelime2[50];
							strcpy(kelime2,kelime);
							strcat(kelime2,".txt");
							for(index=0; index<50; index++){
								if(strlen(dosyaIsimleri[index]) < 2)
									break;
								if(strcmp(dosyaIsimleri[index],kelime2) == 0){
									fprintf(fp ,"%s\n", kelime);
									etiketMi++;
									break;		
								}
							}
							if(etiketMi == 0){
								fprintf(fp1,"%s\n", kelime);
								strcpy(yetimEtiketler[index2],kelime);
								index2++;
							}
											
							memset(kelime2,0,sizeof(kelime2));
							memset(kelime,0,sizeof(kelime));
							a = 0;
							etiketMi = 0;
							break;
						}	
						else if(metin[j] == ']' && metin[j+1] != ']'){
							i = j + 1;
							break;
						}	
							
						else if(metin[j + 1] == '['){
							i = j - 1;
							break;
						}
					}
					kelimeSayisi = 0;
				}			
			}
			//memset(metin,0,sizeof(metin));
		}
	
	fclose(fp1);
	fclose(fp);
}

void yetimEtiketYazdir(){
	char yetimEtiket[50];
	char etiket[50];
	FILE *fp = fopen("yetimetiketler.txt" , "r");
	FILE *fp1 = fopen("istenenetiketler.txt" , "r");
	if(fp == NULL){
		printf("Dosya acilamadi...");
	} else {
		puts("\nYetim Etiketler");
		puts("------------------");
		while(fgets(yetimEtiket , 50 , fp)){
			printf("%s", yetimEtiket);
		}	
		puts("\nIstenen Etiketler");
		puts("------------------");
		while(fgets(etiket , 50 , fp1)){
			printf("%s", etiket);
		}
	}
	fclose(fp);
	fclose(fp1);
}

void output(){
	FILE *fp = fopen("etiketler.txt","w");
	FILE *fp1 = fopen("yetimetiketler.txt","w");
	fclose(fp);
	fclose(fp1);
	char foldernames[3][40] = {"Dersler" , "Bölümler" , "Öðretim Elemanlarý"};	
	char filenames[50][50];
	char _dir[80];
	int i,j;
	for(i=0; i<3; i++){	
		filename(foldernames[i],filenames);		
		for(j= 0; j < 10; j++){
			//printf("%s\n", filenames[j]);
			if(strstr(filenames[j] , ".txt") == NULL)
				break;
			strcpy(_dir,"./Üniversite/");
			strcat(_dir,foldernames[i]);
			strcat(_dir,"/");
			strcat(_dir,filenames[j]);
			//printf("%s\n", _dir);
			etiketYazdir(_dir);	
			memset(_dir,0,sizeof(_dir));	
		}
		memset(filenames,0,sizeof(filenames));
	}
	outputYazdir();
	istenenEtiketYaz();
	//printf("sdada");
}

void outputuEkranaBas(){
	char metin[2048];
	strcpy(metin , filetoarray("output.txt"));
	printf("\n\nOutput.txt\n");
	printf("--------------\n");
	printf("%s", metin);
}

void arama(char *kelime){
	yetimEtiketYazdir();
	printf("\n\n");
	char folders[3][50] = {"Dersler" , "Bölümler" , "Öðretim Elemanlarý"};	
	char metin[2048];
	char etiketMi[30];
	char filenames[20][50];
	int i,j,k=0,a,satir=0,index,index2;	
	for(i=0; i<3; i++){	
		filename(folders[i],filenames);	
		for(a= 0; a < 20; a++){
			if(strstr(filenames[a] , ".txt") == NULL)
				break;	
			//Dosya Yolunu Ayarlýyoruz
			char _dir[80] = "./Üniversite/";
			strcat(_dir,folders[i]);
			strcat(_dir,"/");
			strcat(_dir,filenames[a]);
			//----------------------
			//Dosyadan verileri diziye Alýyorum
			strcpy(metin,filetoarray(_dir));
			//-------------------------------
			//Arama fonksiyonunu cagiriyoruz
			int metinUzunlugu = strlen(metin);
			int kelimeUzunlugu = strlen(kelime);
			int index, index2, found;
			int satir=1;	
			for(index=0; index<metinUzunlugu - kelimeUzunlugu; index++){
				found = 1;
				for(index2=0; index2<kelimeUzunlugu; index2++){
					if(metin[index + index2] != kelime[index2]){
						found = 0;
						break;
					}
				}
				if(metin[index] == '\n')
					satir++;
				
				char* etiket = malloc(50);
				int indis;
				int sayac = 0;
				//Dosyasý var mý yok mu kontrol edilecek...
				if(metin[index-1] == '[' && metin[index-2] == '[' && metin[index2 + index] == ']' && metin[index2 + index + 1] == ']'){
					for(indis=0; indis<50; indis++){
						if(strlen(etiketler[indis]) < 3)
							break;
						if(strcmp(etiketler[indis], kelime) == 0){
							strcpy(etiketMi,"Etiket");
							break;
						}
					}
				} else {
					strcpy(etiketMi,"Kelime");
				}
					
				if(found == 1){
					//printf("%d----%d\n", index , index2);
					printf("%s Klasorunde %s Dosyasinda %d.Satirda %s Bulundu.\n", folders[i], filenames[a] , satir , etiketMi);
				}
			}
			//--------------------------------
			memset(_dir,0,sizeof(_dir));
			memset(metin,0,sizeof(metin));
		}
		memset(filenames,0,sizeof(filenames));
	}	
	
}

void replaceWordInText(char *text, char *oldWord, char *newWord , char *_dir) {
   int i = 0, cnt = 0;
   int len1 = strlen(newWord);
   int len2 = strlen(oldWord);
   for (i = 0; text[i] != '\0'; i++) {
      if (strstr(&text[i], oldWord) == &text[i]) {
         cnt++;
         i += len2 - 1;
      }
   }
   char *newString = (char *)malloc(i + cnt * (len1 - len2) + 1);
   i = 0;
   while (*text) {
      if (strstr(text, oldWord) == text) {
         strcpy(&newString[i], newWord);
         i += len1;
         text += len2;
      }
      else
      newString[i++] = *text++;
   }
   newString[i] = '\0';
   //printf("New String: %s\n", newString);
   arraytofile(newString, _dir);
}

void guncelle(char *arananKelime){
	char metin[2048];
	FILE *fp = fopen("etiketler.txt" , "r");
	FILE *fp1 = fopen("yetimetiketler.txt" , "r");
	int kontrol = - 1;
	
	if(fp == NULL || fp1 == NULL)
		printf("Dosyalarin birine ulasilamadi...");
	else {
		char* kelime = malloc(50);
		while(fgets(kelime, 50 , fp) != NULL){
			int len = strlen(kelime);
			kelime[len - 1] = '\0';
			if(strcmp(kelime,arananKelime) == 0){
				kontrol = 1;
				break;
			}
		}
		free(kelime);
		char* kelime1 = malloc(50);
		while(fgets(kelime1, 50 , fp1) != NULL){
			int len = strlen(kelime);
			kelime1[len - 1] = '\0';
			if(strcmp(kelime1,arananKelime) == 0){
				kontrol = 0;
				break;
			}
		}
		free(kelime1);
		fclose(fp);
		fclose(fp1);
		
		if(kontrol == 1){
			printf("Bu kelime bir etikettir. Etiketi degistirmek istediginiz yeni kelimeyi girin : \n");
			char* yeniEtiket = malloc(50);	
			gets(yeniEtiket);
			int j=0,i=0,a;
			//Dosyada güncelleme için tutuluyorlar
			char* eskiKelime = malloc(strlen(arananKelime) + 4);
			strcat(eskiKelime, "[[");
			strcat(eskiKelime,arananKelime);
			strcat(eskiKelime , "]]");
		
			char* yeniKelime = malloc(strlen(yeniEtiket) + 4);
			strcat(yeniKelime,"[[");
			strcat(yeniKelime,yeniEtiket);
			strcat(yeniKelime, "]]");
			//-------------------------
			
			strcat(yeniEtiket, ".txt");
			char* _dir = malloc(255);
			char* _dosyaadi = malloc(50);
			
			//Ismini degistireceðimiz dosyanýn adresinin basi
			strcpy(_dir,"C:\\\\Users\\\\yusufa\\\\Desktop\\\\Üniversite\\\\");
			
			//Path için aranan dosya düzenleniyor...
			strcpy(_dosyaadi,arananKelime);
			strcat(_dosyaadi , ".txt");
			//------------------------------
			
			//Dosyanýn Nerede oldugu bulunuyor.
			char foldernames[3][40] = {"Bölümler" , "Dersler" , "Öðretim Elemanlarý"};
			for(a=0; a<3; a++){
    			DIR *d;
    			struct dirent *dir;
				char yol[80];
				strcpy(yol,"./Üniversite/");
				strcat(yol,foldernames[a]);
   				d = opendir(yol);
    			if (d)
    			{
        		while ((dir = readdir(d)) != NULL)
        		{
        			if(j<2)
        			j++;
            	else {
            		if(strstr(dir->d_name,".txt")){
            			char* _dir2 = malloc(255);
            			if(strcmp(dir->d_name ,  _dosyaadi) == 0){
            				strcat(_dir,foldernames[a]);
						}
						strcpy(_dir2 , ".\\Üniversite\\");
						strcat(_dir2 , foldernames[a]);
						strcat(_dir2 , "\\");
						strcat(_dir2 , dir->d_name);
						strcpy(metin,filetoarray(_dir2));
						replaceWordInText(metin , eskiKelime , yeniKelime,_dir2);
					}		
				}		
        		}
        		closedir(d);
			}
				memset(yol,0,sizeof(yol)); 
			}
			
			//Path e klasör adi eklendi
			strcat(_dir , "\\\\");
			
			
			//Yeni dosya ismi için path olusturuluyor
			char* _newdir = malloc(255);
			strcpy(_newdir,_dir);
			
			//Eski path tamamlandý
			strcat(_dir , _dosyaadi);
			//------------------------------------
				
			strcat(_newdir, yeniEtiket);
			
			//printf("%s\n%s\n", _dir , _newdir);	
			rename(_dir, _newdir);				
		}
			
		else if(kontrol == 0){
			int secim;
			printf("Bu bir yetim etikettir. Dosyasini olusturmak istiyorsaniz 1 , ismini degistirmek istiyorsaniz 2 týklayýn.");
			scanf("%d", &secim);
			//printf("Secilen secim : %d\n" , secim);
			if(secim == 1){
				char dersinkodu[80] =  "Dersin Kodu : BLM";
				char dersinadi[80] = "Dersin Adi : [[";
				char dersinicerigi[80] = "Ders Icerigi : ";
				strcat(dersinadi , arananKelime);
				strcat(dersinadi,"]]");
				char numara[3];
				itoa(numarator, numara, 10);
				strcat(dersinkodu,numara);
				numarator++;
				char yol[80] = ".\\\\Üniversite\\\\Dersler\\\\";
				strcat(yol,arananKelime);
				strcat(yol,".txt");
				//printf("yol : %s" , yol);
				FILE *fp2 = fopen(yol,"w");
				if(fp2 == NULL)
					printf("Dosya olusturulamadi...");
				else {
					fprintf(fp2 , "%s\n" , dersinkodu);
					fprintf(fp2 , "%s\n" , dersinadi);
					fprintf(fp2 , "%s\n" , dersinicerigi);
					printf("Dosya olusturuldu. Outputu yazdýrýp kontrol edebilirsiniz...\n");
				}		
				fclose(fp2);
			}	
			
			//------------------------------------------------------------------------------------------------
			if(secim == 2){
				getchar() != '\n';
				printf("Yetim etiketi degistirmek istediginiz yeni kelimeyi girin : \n");
				char* yeniEtiket = malloc(50);	
				gets(yeniEtiket);
				
				int j=0,i=0,a;
				//Dosyada güncelleme için tutuluyorlar
				char* eskiKelime = malloc(strlen(arananKelime) + 4);
				strcat(eskiKelime, "[[");
				strcat(eskiKelime,arananKelime);
				strcat(eskiKelime , "]]");
		
				char* yeniKelime = malloc(strlen(yeniEtiket) + 4);
				strcat(yeniKelime,"[[");
				strcat(yeniKelime,yeniEtiket);
				strcat(yeniKelime, "]]");
				//-------------------------
			
				strcat(yeniEtiket, ".txt");
				char* _dir = malloc(255);
				char* _dosyaadi = malloc(50);
			
				//Ismini degistireceðimiz dosyanýn adresinin basi
				strcpy(_dir,"C:\\\\Users\\\\yusufa\\\\Desktop\\\\Üniversite\\\\");
			
				//Path için aranan dosya düzenleniyor...
				strcpy(_dosyaadi,arananKelime);
				strcat(_dosyaadi , ".txt");
				//------------------------------
			
				//Dosyanýn Nerede oldugu bulunuyor.
				char foldernames[3][40] = {"Dersler" , "Bölümler" , "Öðretim Elemanlarý"};
		
				for(a=0; a<3; a++){
    				DIR *d;
    				struct dirent *dir;
					char yol[80];
					strcpy(yol,"./Üniversite/");
					strcat(yol,foldernames[a]);
   					d = opendir(yol);
    				if (d)
    				{
        				while ((dir = readdir(d)) != NULL)
        			{
        				if(j<2)
        				j++;
            		else {
            			if(strstr(dir->d_name,".txt")){
            				char* _dir2 = malloc(255);
            				if(strcmp(dir->d_name ,  _dosyaadi) == 0){
            					strcat(_dir,foldernames[a]);
							}
							strcpy(_dir2 , ".\\Üniversite\\");
							strcat(_dir2 , foldernames[a]);
							strcat(_dir2 , "\\");
							strcat(_dir2 , dir->d_name);
							strcpy(metin,filetoarray(_dir2));
							replaceWordInText(metin , eskiKelime , yeniKelime,_dir2);
						}		
					}		
        			}
        			closedir(d);
				}
					memset(yol,0,sizeof(yol)); 
				}
				printf("Yetim etiket ismi degistirildi...\n\n");				
			}
			
			//----------------------------------------------------------
			else {
				printf("Yanlis bir secim yaptiniz....");
			}
			
			
		}
		
		else if(kontrol == -1)
			printf("Girilen kelime etiket veya yetim etiket degil degisim yapamazsýnýz...\n");
			
	
			
	}		
}

void main(){
	setlocale(LC_ALL, "Turkish");
	etiketleriCek();
	dosyaIsimleriBul();
	output();
			
	int secim;
	while(1){
		printf("Yapmak istediginiz islemi seciniz...\n1-Outputu Bas\n2-Arama\n3-Güncelleme\nCikis icin 0\nSeciminiz : ");
		scanf("%d", &secim);
		if(secim == 0)
			break;
		switch(secim){ 
		case 1: {		
			dosyaIsimleriBul();
			output();
			etiketleriCek();
			outputuEkranaBas();
			printf("\n");	
			break;
		}
		case 2: {
			char* arananKelime = malloc(100);
			getchar() != '\n';
			printf("Aramak istediginiz kelimeyi giriniz : ");
			gets(arananKelime);
			arama(arananKelime);
			free(arananKelime);
			break;
		}
		case 3: {	
			char* arananKelime = malloc(100);
			getchar() != '\n';
			printf("Guncellemek istediginiz etiketi veya yetimetiketi giriniz : ");
			gets(arananKelime);
			guncelle(arananKelime);
			free(arananKelime);
			dosyaIsimleriBul();
			output();
			etiketleriCek();
			break;
		}
		default: {
			printf("Gecersiz secim yapildi...");
			break;
			}		
		}
	}	
}
