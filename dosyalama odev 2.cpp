#include <iomanip> 
#include <cstring> 
#include <stdlib.h>
#include <conio.h>
#include <stdio.h> 
#include <fstream>                   
#include <iostream>

using namespace std;

struct Mobilya
{
	char urun_ad[80];
	char kategori[80];
	char urun_no[10];
	char stok[10];	
};

void UrunEkle();
void UrunListeleme();
void UrunArama();
void UrunSil();
void UrunDuzenle();

int main(){
	char secim;
	char anamenu;
	do{
	system("cls");
	
		cout << "| === MOBILYA OTOMASYON SISTEMI === |" << endl;
        cout << "|      1- Yeni Urun (Stok) Ekle     |" << endl;
        cout << "|      2- Stok Listesini Gor        |" << endl;
        cout << "|      3- Urun Arama                |" << endl;
        cout << "|      4- Urun Sil                  |" << endl;
        cout << "|      5- Urun Duzenle              |" << endl;
        cout << "|      0- Cikis                     |" << endl;
        cout << "| --------------------------------- |" << endl;
	cout << "Seciminiz: ";
    
	secim=getche();
	cout<<endl;
	
	switch(secim) 
	{
		case '1' : { 
		UrunEkle(); 
		break; }
		case '2' : { 
		UrunListeleme(); 
		break; }
		case '3' : { 
		UrunArama(); 
		break; }
		case '4' : { 
		UrunSil(); 
		break; }
		case '5' : { 
		UrunDuzenle(); 
		break; }
		case '0': 
		return 0;
		
		default:{
		
		
                cout << "\n!!! Yanlis Secim Yaptiniz. Lutfen Tekrar Deneyin !!!" << endl;
                break;}
		}	
	cout << "Anamenuye Donmek icin: a basin cikmak icin: c" <<endl ; 
	anamenu=getche();
	
    }while(anamenu=='a');
     
return 0;
}

Mobilya mob;

void UrunEkle()
{
	ofstream yaz("mobilya.dat",ios::binary |ios::app);
	char secim;
	int adet=0;
	
	do{
	cout << "Urun Adini Giriniz" << endl;
	cin>> mob.urun_ad;
	cout << "Kategori Giriniz" << endl;
	cin>> mob.kategori;
	cout << "Urun No Giriniz" << endl;
	cin>> mob.urun_no;
	cout << "Stok Miktarini Giriniz" << endl;
	cin>> mob.stok;
	cout << endl;
	yaz.write((char*)&mob, sizeof(mob));	
	adet++;	
	cout << "Baska Kayit Eklemek Istermisin (E/H)" << endl;
	secim=getche();
	cout << endl;
	}while(secim=='e' || secim=='E');
	
	cout << adet << " adet Urun Eklendi.." << endl;
	yaz.close();
}

void UrunListeleme()
{
	ifstream oku("mobilya.dat",ios::binary |ios::app);
	oku.seekg(0,ios::end);
	int kayits=oku.tellg()/sizeof(mob);
	cout << "Toplam Kayitli Urun Sayisi:"<< kayits << endl;
	
	if(kayits>0)
	{
		for(int i=0; i<kayits;i++)
		{
			oku.seekg(i*sizeof(mob));
			oku.read((char*)&mob, sizeof(mob));	
		
			cout << i+1 << ". Urunun Bilgileri"<< endl;
			cout << "Urun Adi: "<< mob.urun_ad <<endl ;
			cout << "Kategori: "<< mob.kategori <<endl ;
			cout << "Urun No: "<< mob.urun_no <<endl ;
			cout << "Stok: "<< mob.stok <<endl ;
			cout << "--------------------------" << endl;
		}
	}
	else
	cout << "Kayit Bulunamadi..." << endl;
	oku.close();
}

void UrunArama()
{
	ifstream oku("mobilya.dat",ios::binary |ios::app);
	oku.seekg(0,ios::end);
	int kayits=oku.tellg()/sizeof(mob);

	cout <<"Aranan Urun Numarasini Giriniz"<< endl;
	char no[80];
	cin>> no;
		
	if(kayits>0)
	{
		for(int i=0; i<kayits;i++)
		{
			oku.seekg(i*sizeof(mob));
			oku.read((char*)&mob, sizeof(mob));
			
			if(strcmp(mob.urun_no,no)==0)
			{
				cout <<  "Bulunan Urunun Bilgileri"<< endl;
				cout << "Urun Adi: "<< mob.urun_ad <<endl ;
				cout << "Urun No: "<< mob.urun_no <<endl ;
				cout << "Stok: "<< mob.stok <<endl ;
		    }
		}
	}
	else
	cout << "Kayit Bulunamadi..." << endl;
	oku.close();
}

void UrunSil()
{
	 char uno[80];
     char secim= ' ';
     bool var=false;
     
    ifstream oku("mobilya.dat",ios::binary |ios::app);
	oku.seekg(0,ios::end);
	int kayitsayisi=oku.tellg()/sizeof(mob);
	
     cout<<"Sileceginiz Urun No Giriniz : ";
     cin>>uno;

     for(int i=0;i<kayitsayisi;i++)
     {
            oku.seekg(i*sizeof(mob));
			oku.read((char*)&mob, sizeof(mob));
			
     if(strcmp(mob.urun_no,uno)==0)
       {
                 cout<<"\nUrun Adi : "<<mob.urun_ad;
                 cout<<"\nUrun No : "<<mob.urun_no;
                 cout<<"\n\nSilmek Istediginiz Kayit Bu Mu? [E/H] : ";
                 secim=getche();
            if(secim == 'H' || secim == 'h')
              {      
                ofstream y_dosya("Yedek.dat",ios::app|ios::binary);
                y_dosya.write((char*)&mob, sizeof(mob));
                y_dosya.close();
              }
            if(secim=='e'||secim=='E') var=true;
       }
       else
       {
             ofstream y_dosya("Yedek.dat",ios::app|ios::binary);
             y_dosya.write((char*)&mob, sizeof(mob));
             y_dosya.close();
       }
     }
    oku.close();
    if(var)
    {
               remove("mobilya.dat");
               rename("Yedek.dat","mobilya.dat");
               cout<<"\n Kayit Silindi"<<endl;
    }
    else
    {
               remove("Yedek.dat");
               cout<<"\n Kayit Bulunamadi"<<endl;                  
    }
}

void UrunDuzenle()
{
	 char uno[80];
     char secim= ' ';
     bool var=false;
     
    ifstream oku("mobilya.dat",ios::binary |ios::app);
	oku.seekg(0,ios::end);
	int kayitsayisi=oku.tellg()/sizeof(mob);
		
     cout<<"Duzelteceginiz Urun No Giriniz : ";
     cin>>uno;

     for(int i=0;i<kayitsayisi;i++)
     {
            oku.seekg(i*sizeof(mob));
			oku.read((char*)&mob, sizeof(mob));
			
     		if(strcmp(mob.urun_no,uno)==0)
     		  {
                 cout << endl;
            cout << "Urunun Bilgileri;";
            cout << "\nUrun No   : " << mob.urun_no;
            cout << "\nUrun Adi  : " << mob.urun_ad;
            cout << "\nKategori  : " << mob.kategori;
            cout << "\nStok Adedi: " << mob.stok;
                 cout<<"\n\nDuzeltmek Istediginiz Kayit Bu Mu? [E/H] : ";
                 secim=getche();
                 if(secim == 'E' || secim == 'e')
                  {cout<<endl;
                  	cout<<"Lutfen Arada Bosluk Birakmayiniz"<<endl;
                       	var=true;
                        ofstream dosya("Yedek.dat",ios::app|ios::binary);
                        cout << "\nYeni Urun Adini Giriniz" << endl;
						cin>> mob.urun_ad;
						cout << "Yeni Stok Miktarini Giriniz" << endl;
						cin>> mob.stok;
                        dosya.write((char*)&mob, sizeof(mob));
                        dosya.close();
            	  }
            	 else
                  {
                         ofstream y_dosya("Yedek.dat",ios::app|ios::binary);
                         y_dosya.write((char*)&mob, sizeof(mob));
                         y_dosya.close();
                  }
     }
 }
    oku.close();
    if(var)
    {
               remove("mobilya.dat");
               rename("Yedek.dat","mobilya.dat");
               cout<<"\nKayit Duzeltildi."<<endl;
    }
    else
    {
               remove("Yedek.dat");
               cout<<"\nKayit Bulunamadi"<<endl;                  
    }
}
