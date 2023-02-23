#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct siteiliski {
  int bul_siteler[50];
  int bul_siteNum;
  int key;
  int find_seq;
  char *key_char;
};

int hornersmethod(char *kelime,int m){
	
	int i,length,hash,R=31,x;
	hash=0;
	length=0;
	length=strlen(kelime);
	for(i=0;i<length;i++){
		//hash=hash+R*(kelime[i]-'A'+1);
		hash=(R*hash+(kelime[i]-'A'+1));		
		hash=hash % m;
	}	
	return hash;
}

void insert(int key, int m,struct siteiliski *hash_table,int site_num,char *kelime)
{
 	int i,adr,num,x,flag=0;
 	adr=key%m;
 	i=0;
 while((i<m)&&(hash_table[adr].key!=-1)&&hash_table[adr].key!=key){
 	i++;
 	adr=(adr+1)%m;
 }
 if(i==m){
 	printf("Tablo Dolu \n");
 }else{
 	if(hash_table[adr].key==-1){
 		hash_table[adr].key=key;
 		hash_table[adr].key_char = malloc(sizeof(char) * 254);
 		strcpy(hash_table[adr].key_char,kelime)	;	
 		hash_table[adr].bul_siteler[hash_table[adr].bul_siteNum]=site_num;
 		hash_table[adr].bul_siteNum++;
 		hash_table[adr].find_seq=i+1;
 		x=(hash_table[adr].bul_siteNum)-1;
 		printf("-------------------------------------------------------------------------------- \n");
 		printf("%s Isimli Kelime %d Keyi Ile Hash Tablosunun %d. Indisine %d. Deneme Sonrasi Ilk Kez Eklendi \n",hash_table[adr].key_char,key,adr,i);
 		
	 }else{
	 	while( i < hash_table[adr].bul_siteNum && flag==0){
				if(site_num == hash_table[adr].bul_siteler[i]){
					flag=1;			
					}
					i++;
		}
		if(flag==0){
		hash_table[adr].bul_siteler[hash_table[adr].bul_siteNum]=site_num;
	 	hash_table[adr].bul_siteNum++;				
		}
		printf("-------------------------------------------------------------------------------- \n");
	 	printf("%s Isimli Kelime %d Keyi Ile Hash Tablosunun %d. Indisine Onceden Eklenmis \n",kelime,key,adr,i);
	 }
 }

}

int find(int key,int m,struct siteiliski *hash_table,char *kelime)
{
 
    int hashIndex = (key % m);
    int counter = 0;
    while (hash_table[hashIndex].key != -1) {
 
        int counter = 0;
        if (counter++ > m)
            break;
        if (hash_table[hashIndex].key == key &&(strcmp(hash_table[hashIndex].key_char,kelime)==0) ){
        	return hashIndex;
		}           
 		key++;
        hashIndex = (key % m);
    }
    return -1;
}
	
int isPrime(int m){
	
	int i,n=0,flag=0;    
	n=m/2;    
	for(i=2;i<=n;i++)    
	{    
		if(m%i==0)    
		{    
			flag=1;    
		return flag;    
		}    
	}    
	if(flag==0)    
	 
	return flag; 	
	
} 

int main(int argc, char *argv[]) {
	
	FILE *dosya = fopen("Sample.txt", "r");
	int max_uzunluk = 255,kelime_sayi=0,site_sayisi=0,i,satir_sayi= -1,m,m_tmp,y=0,n=0,keys_num=0;;
	int key,flag,site_num,site_num2,site_num3,adr,tmp,site_bul,sayi,iliski,j,secim;
	float load_factor;
	int site_tmp[10],site_tmp2[10],site_pr[10];
	char satir[max_uzunluk],kelimeler[max_uzunluk][20],siteler[max_uzunluk][2000],birsatir[100],search[3][20];
	char *site,*kelime,* birkelime=NULL;
	const char *bosluk=" ";   
	char aranan[20],aranan2[20];
	struct siteiliski *hash_table;
	
	
	//Kelime ve sitelerin sayýlarýnýn belirlendiði ve Site indislerini tutmak amacý ile sitelerin diziye alýndýðý kýsým.
	while(fgets(satir, max_uzunluk, dosya)) {
		satir_sayi++;
	  	if (satir_sayi %2 ==0){	
	  	//printf("-------------------------------------------------------------------------------- \n");
		  	kelime = strtok (satir," ");	  		  		  		
	  		if (strcmp("\n",kelime) != 0){
				if(site_sayisi==0){
					strcpy(siteler[site_sayisi], kelime);							
					site_sayisi++;
					
					//printf("Site: %s\n", siteler[site_sayisi-1]);
				}else{
					flag=0;
					i=0;
					while( i < site_sayisi && flag==0){
						if(strcmp(siteler[i],kelime) == 0 ){
						flag=1;			
						}
						i++;
					}
					if(flag==0){
						strcpy(siteler[site_sayisi], kelime);		
						site_sayisi++;	
						//printf("Site: %s\n", siteler[site_sayisi-1]);	
					}
				}												
			}  		
	  		kelime = strtok(NULL, " ");	
		  }  
		else{		
	    	kelime = strtok (satir," ");					
			while (kelime != NULL)
			{	
			if (strcmp("\n",kelime) != 0){
				if(kelime_sayi==0){
					strcpy(kelimeler[kelime_sayi], kelime);							
					kelime_sayi++;
					//printf("Kelime: %s\n", kelimeler[kelime_sayi-1]);
				}else{
					flag=0;
					i=0;
					while( i < kelime_sayi && flag==0){
						if(strcmp(kelimeler[i],kelime) == 0 ){
						flag=1;			
						}
						i++;
					}
					if(flag==0){
						strcpy(kelimeler[kelime_sayi], kelime);		
						kelime_sayi++;	
						//printf("Kelime: %s\n", kelimeler[kelime_sayi-1]);	
					}
				}									
				
			}
			kelime = strtok(NULL, " ");						
			}  
		}	
	}	
	fclose(dosya);
	
	flag=1;
	printf("Load factoru giriniz : ");
	scanf("%f",&load_factor);
	printf("\n");
	m=1/(load_factor);
	m=m*kelime_sayi;	
	while(flag==1){
		flag=isPrime(m); //Asal sayý olan tabko boyutu belirleniyor.
		if(flag==1){
			m++;
		}
			
	}
	hash_table = (struct siteiliski *)malloc(m * sizeof(struct siteiliski));
	
	for(i=0;i<m;i++){
		hash_table[i].key=-1;
		hash_table[i].key_char="NULL";
		hash_table[i].bul_siteNum=0;
		
	}
	dosya = fopen("Sample.txt", "r");
	satir_sayi=-1;
	
	//Kelimelerin hash tablosuna eklendiði ve geçtiði sitelerin eklendiði kýsým
	while(fgets(satir, max_uzunluk, dosya)) {
		satir_sayi++;
	  	if (satir_sayi %2 ==0){	 		  		
			kelime = strtok (satir," ");
			if (strcmp("\n",kelime) != 0){
				for(i=0;i<site_sayisi;i++){
					if(strcmp(siteler[i],kelime) == 0 ){
					site_num=i;
					}				
				}
			}	
		  }  
		else{	
	    	kelime = strtok (satir," ");					
			while (kelime != NULL)
			{	
			if (strcmp("\n",kelime) != 0){
				flag=0;	
				i=0;
				key=hornersmethod(kelime,m);
				while(i<m){
					if(key==hash_table[i].key){
						if(strcmp(kelime,hash_table[i].key_char) !=0){
							key++;
							//i=0;
						}
						else{
							i=m;
						}
					}
					i++;
				}
				keys_num++;
				insert(key,m,hash_table,site_num,kelime);			
			}	
			kelime = strtok(NULL, " ");						
			}  
		}	
	}		
	printf("1-- NORMAL MODDA CALISTIR \n");
	printf("2-- DETAY MODDA CALISTIR \n");
	printf("SECIMINIZI YAPINIZ [1-2] \n");
	scanf("%d",&secim);		
				
	printf("Arama yapmak istediginiz kelime(ler)i giriniz: \n");
	fflush(stdin);
	gets(birsatir);
	
	birkelime=strtok(birsatir,bosluk);
	while(birkelime!=NULL)
	{
	     strcpy(search[n],birkelime);
	     n++;
	     birkelime=strtok(NULL,bosluk);                 
	}	
		
		if(n==1)	{  //Aranan kelime sayýsý 1 ise
			flag=0;
			key=hornersmethod(search[0],m);	
			adr=find(key,m,hash_table,search[0]);
	
			
			if (adr!= -1){
				site_num2=hash_table[adr].bul_siteNum;
				if(site_num2 > 1){
					for(i=0; i< site_num2 ;i++){
					site_bul=hash_table[adr].bul_siteler[i];
					printf(" %s \n",siteler[site_bul]);
					}
				}else{
					site_bul=hash_table[adr].bul_siteler[0];
					printf(" %s \n",siteler[site_bul]);
					}
				}
			else{//Aranan kelime sayýsý 1 ise ve tabloda yok ise
				printf("Liste bos");
			}
		}	
		//Aranan kelime sayýsý 2 ise		
		else{		
		if(strcmp(search[1],"ve")==0){
			iliski=0; // Ve ile aramam
		}else{
			iliski=1; //Veya ile arama
		}
		

		flag=0;
		//Aranan ilk kelimenin keyi ve adresi
		key=hornersmethod(search[0],m);	
		adr=find(key,m,hash_table,search[0]); 
		
		if (adr!= -1){
		site_num2=hash_table[adr].bul_siteNum;
		if(site_num2 > 1){ //birinci kelime bir sitede geçiyorsa
			for(i=0; i< site_num2 ;i++){
			site_bul=hash_table[adr].bul_siteler[i];
			site_tmp[i]=site_bul;
			}
		}else{//birinci kelime birden fazla sitede geçiyorsa
			site_bul=hash_table[adr].bul_siteler[0];
			site_tmp[i]=site_bul;
			}
		}
		else{//birinci kelime hash tablosunda yoksa
			site_num2=0;
		}


		flag=0;
		//Aranan ikinci kelimenin keyi ve adresi.
		key=hornersmethod(search[2],m);	
		adr=find(key,m,hash_table,search[2]);

		if (adr!= -1){
		site_num3=hash_table[adr].bul_siteNum;
		if(site_num3 > 1){ //ikinci kelime birden fazla sitede geçiyorsa
			for(i=0; i< site_num3 ;i++){
				flag=0;
				site_bul=hash_table[adr].bul_siteler[i];
				for(j=0;j<site_num2;j++){
					if(site_bul==site_tmp[j]){
						flag=1;
					}
				}
				if(iliski==0 && flag==1){
					site_tmp2[y]=site_bul;
					y++;
				}
				if(iliski==1 && flag==0){
					site_tmp[site_num2]=site_bul;
					site_num2++;
				}		
			}
		}else{  //ikinci kelime bir sitede geçiyorsa
			flag=0;
			site_bul=hash_table[adr].bul_siteler[0];
			for(j=0;j<site_num2;j++){
					if(site_bul==site_tmp[j]){
						flag=1;
					}
				}
				if(iliski==0 && flag==1){
					site_tmp2[y]=site_bul;
					y++;
				}
				if(iliski==1 && flag==0){
					site_tmp[site_num2]=site_bul;
					site_num2++;
				}
			}
		}else{
			y=0; //ikinci kelime hash tablosunda yoksa
		}
		if(iliski == 0){
			if(site_num2==0 || y==0){
				printf("Liste Bos"); // birinci veya ikinci kelime hash tablosunda yoksa ve iliþki olarak 've' seçildi ise
			}
			else{
			printf("Kelime(ler)in Bulunduðu siteler : \n");
			for(i=0;i<y;i++){
			printf("%s \n",siteler[site_tmp2[i]]); // birinci ve ikinci kelime hash tablosunda varsa ve iliþki olarak 've' seçildi ise
			}
			
		}
	}
		else if(iliski == 1){
		for(i=0;i<site_num2;i++){
			printf("%s \n",siteler[site_tmp[i]]);// birinci veya ikinci kelime hash tablosunda varsa ve iliþki olarak 'veya' seçildi ise
		}
	}
}
	if(secim==2){
		printf("HASH TABLO UZUNLUGU(m) : %d \n",m);
		for(i=0;i<m;i++){
		printf("-------------------------------------------------------------------------------- \n");
		printf("%d KEY'li %s KELIMESI TABLOYA %d. DENEMEDE YERLESMISTIR -",hash_table[i].key,hash_table[i].key_char,hash_table[i].find_seq);	
		printf("%d Adet Sitede Bu Kelime Yer Almaktadýr \n",hash_table[i].bul_siteNum);
	}
	}

	return 0;
}
