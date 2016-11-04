//ZADNJA VERZIJA
#include <stdio.h>
#include <conio.h>
#include <string.h> //Zaglavna datoteka potrebna za strlen, strcpy i strcmp
#include <windows.h> //Zaglavna datoteka potrebna za system("CLS")
#define MAX 50 //Maksimalan broj zaposlenika u listi


//struktura podataka o zaposleniku
typedef struct 
{
	char imeZaposlenika[20+1];
	char prezimeZaposlenika[30+1];
	char spolZaposlenika[1+1];
	int godinaRodjenjaZaposlenika;
	char oibZaposlenika[11+1];
	char strucnaSpremaZaposlenika[3+1];
	float mjesecnaPlacaZaposlenika;
	char pozicijaUTvrtki[30+1];
} Zaposlenik;

//deklaracija liste
typedef struct
{
	int zadnji; 
	Zaposlenik elementi[MAX];
	
} LISTA;


//funkcija UBACI u LISTU
void UBACI (Zaposlenik x, int pozicija_ubacivanja, LISTA *pokLista)
{
  	int pozicija;
  	if (pokLista->zadnji >= MAX-1)
  	{
  		printf("LISTA JE PUNA!\n\n");
	  }
  			
  	else if ((pozicija_ubacivanja>pokLista->zadnji+1) || (pozicija_ubacivanja<0))
	   {
  		printf("POZICIJA NE POSTOJI!\n\n");
  		}
  	else
	  {
        	for (pozicija=pokLista->zadnji; pozicija >= pozicija_ubacivanja; pozicija--) 
			{
        		pokLista->elementi[pozicija+1]= pokLista->elementi[pozicija];
			}
            pokLista->zadnji++;
            pokLista->elementi[pozicija_ubacivanja] = x;
	  }
}

//Ispis liste
void ISPIS(LISTA *pokLista)
{
	int pozicija=-1;
	
	printf("\tISPIS ZAPOSLENIKA! \n\n");
	
	if(pozicija==pokLista->zadnji)
	{
		printf("LISTA JE PRAZNA!! \n");
	}
	else
	{
		
	
	  	for (pozicija=0; pozicija <= pokLista->zadnji; pozicija++)
		  {
		  	printf("ZAPOSLENIK %d ",pozicija+1);
	    	printf("\n\nIME:%s \nPREZIME:%s \nSPOL:%s \nGODINA RODJENJA:%d \nOIB:%s \nSTRUCNA SPREMA:%s \nMJESECNA PLACA:%.2f KN \nMJESTO RADA:%s \n",
				   pokLista->elementi[pozicija].imeZaposlenika, 
				   pokLista->elementi[pozicija].prezimeZaposlenika,
				   pokLista->elementi[pozicija].spolZaposlenika,
				   pokLista->elementi[pozicija].godinaRodjenjaZaposlenika,
				   pokLista->elementi[pozicija].oibZaposlenika,
				   pokLista->elementi[pozicija].strucnaSpremaZaposlenika,
				   pokLista->elementi[pozicija].mjesecnaPlacaZaposlenika,
				   pokLista->elementi[pozicija].pozicijaUTvrtki);
			printf("\n");
	  	}
	}
}

//Spremanje u datoteku
void SPREMI_U_DATOTEKU(char *nazivDatoteke, LISTA *pokLista) {
	FILE *datoteka;
    datoteka = fopen(nazivDatoteke, "wb");
    if (datoteka == NULL) {
      	printf("PROBLEM U OTVARANJU DATOTEKE!!\n\n");
    }
    else{
        fwrite(pokLista, sizeof(*pokLista), 1, datoteka);
    }  
    fclose( datoteka );    
}

//Citanje podataka iz datoteke
void PROCITAJ_IZ_DATOTEKE(char *nazivDatoteke, LISTA *pokLista) {
	FILE *datoteka;
  	datoteka = fopen(nazivDatoteke, "rb");
  	if( datoteka == NULL ) {
    	printf("PROBLEM U OTVARANJU DATOTEKE!!\n\n");
  	}
  	else {
    	fread(pokLista, sizeof(*pokLista), 1, datoteka);
  }    
  fclose(datoteka );   
}


//Izbornik za odabir brisanja iz liste
int izbornikBRISANJE()
{
	int odlukaBrisanja=-1;
	
	printf("\n\n\tIZBORNIK BRISANJA\n");
	printf("OBRSI JEDNOG ZAPOSLENIKA (1)\n");
	printf("OBRISI CIJELU LISTU (2)\n");
	printf("ODUSTANI (0)\n");
	printf("\n\nIZBOR: ");
	scanf("%d",&odlukaBrisanja);
	
	return odlukaBrisanja;
}

//BRISANJE
void OBRISI (LISTA *pokLista) {
  int pozicija, odlukaBrisanja=-1,  korakFor=0, pozicija_brisanja=0;
  
  
  
do
{
	odlukaBrisanja=izbornikBRISANJE();
	
  switch(odlukaBrisanja)
  {
  	case 1:
  		{
  			do{
  				
			  
				printf("KOJEG ZAPOSLENIKA ZELITE OBRISATI?: ");
				scanf("%d",&pozicija_brisanja);
				
			}while(pozicija_brisanja<0);
				
				if(pozicija_brisanja==0)
				{
					printf("\n\n");
					break;
				}
				
				pozicija_brisanja--;
				
				if ( (pozicija_brisanja>pokLista->zadnji ) || (pozicija_brisanja<0) )
					{
						printf("\n\n\tPOZICIJA NE POSTOJI! \n\n");
					} 
				else 
				{
					pokLista->zadnji--;    
					for (pozicija=pozicija_brisanja; pozicija<=pokLista->zadnji; pozicija++)
					{
						pokLista->elementi[pozicija] = pokLista->elementi[pozicija+1];
					}
					
					printf("\nZAPOSLENIK IZBRISAN!! \n\n");
					
				}
				
				break;
		}
	case 2:
		{
			pokLista->zadnji=-1;    
			
			printf("\nLISTA IZBRISANA!! \n\n");
			
			break;
		}
		
		
	case 0: 
		{
			printf("\n\n");
			break;
			
		}
	
	default:
		{
			printf("\nPOGRESAN UNOS!! \n\n"); 
			break;
		}
	
  }  
  
}while(odlukaBrisanja!=0 && odlukaBrisanja!=1 && odlukaBrisanja!=2);


  	 SPREMI_U_DATOTEKU("ListaZaposlenika.bin",pokLista);
  	 
  	 
}

//UNOS ZAPOSLENIKA u listu
void UNOS_ZAPOSLENIKA(LISTA *pok_listaZaposlenika, Zaposlenik *pok_podatciZaposlenik, int a_rbrUnosa)
{
	int duljinaOIB=0, provjeraStrcmpM=-1, provjeraStrcmpZ=-1,rBrUnosa=a_rbrUnosa;
	char spolM[1+1]="M", spolZ[1+1]="Z", provjeraStrcmpSpol[1+1];
	char spSSS[3+1]= "SSS",spVSS[3+1]="VSS",spNKV[3+1]="NKV", provjeraStrcmpSP[3+1];
	int provjeraStrcmpSSS=-1, provjeraStrcmpVSS=-1, provjeraStrcmpNKV=-1; // -1 zato sto strcmp vraca -1 kada nije isto


	printf("UNESITE IME %d. ZAPOSLENIKA: ",rBrUnosa+1);
	scanf("%s",&pok_podatciZaposlenik->imeZaposlenika);
	printf("UNESITE PREZIME %d. ZAPOSLENIKA: ",rBrUnosa+1);
	scanf("%s",&pok_podatciZaposlenik->prezimeZaposlenika);

	//Unos spola zaposlenika i provjera dali je ono M ili Z	
	do{
		printf("UNESITE SPOL %d. ZAPOSLENIKA (M/Z): ",rBrUnosa+1);
		scanf("%s",&provjeraStrcmpSpol);	

		provjeraStrcmpM=strcmp(provjeraStrcmpSpol,spolM);
		provjeraStrcmpZ=strcmp(provjeraStrcmpSpol,spolZ);

		if(provjeraStrcmpM !=0 && provjeraStrcmpZ !=0)
		{
			printf("\tDOPUSTENI UNOS JE M ILI Z! \n\n");
		}
		
	}while(provjeraStrcmpM !=0 && provjeraStrcmpZ !=0);	
	strcpy(pok_podatciZaposlenik->spolZaposlenika,provjeraStrcmpSpol);

	do{
		printf("UNESITE GODINU RODJENJA %d. ZAPOSLENIKA: ",rBrUnosa+1);
		scanf("%d",&pok_podatciZaposlenik->godinaRodjenjaZaposlenika);

		if(pok_podatciZaposlenik->godinaRodjenjaZaposlenika >1997)
		{
			printf("\tZAPOSLENIK MORA BITI PUNOLJETAN! \n\n");
		}
		else if(pok_podatciZaposlenik->godinaRodjenjaZaposlenika <1900)
		{
			printf("\tZAPOSLENIK JE PRESTAR! \n\n");
		}

	}while(pok_podatciZaposlenik->godinaRodjenjaZaposlenika >1997 || pok_podatciZaposlenik->godinaRodjenjaZaposlenika <1900 );

	do {
		printf("UNESITE OIB %d. ZAPOSLENIKA: ",rBrUnosa+1);
		scanf("%s",&pok_podatciZaposlenik->oibZaposlenika);
		duljinaOIB=strlen(pok_podatciZaposlenik->oibZaposlenika);
		
		if(duljinaOIB!=11)
		{
			printf("\tDULJINA OIB-A MORA BITI 11 ZNAMENKI! \n\n");
		}
		
	}while(duljinaOIB!=11);

	do
	{
		printf("UNESITE STRUCNU SPREMU %d. ZAPOSLENIKA: ",rBrUnosa+1);
		scanf("%s",&provjeraStrcmpSP);

		provjeraStrcmpNKV=strcmp(provjeraStrcmpSP,spNKV);
		provjeraStrcmpSSS=strcmp(provjeraStrcmpSP,spSSS);
		provjeraStrcmpVSS=strcmp(provjeraStrcmpSP,spVSS);

		if(provjeraStrcmpNKV!=0 && provjeraStrcmpSSS!=0 && provjeraStrcmpVSS!=0)
		{
			printf("\tDOPUSTENI UNOSI SU NKV, SSS, VSS! \n\n");
		}

	}while(provjeraStrcmpNKV!=0 && provjeraStrcmpSSS!=0 && provjeraStrcmpVSS!=0); 
	strcpy(pok_podatciZaposlenik->strucnaSpremaZaposlenika,provjeraStrcmpSP);

	printf("UNESITE MJESECNU PLACU %d. ZAPOSLENIKA: ",rBrUnosa+1);
	scanf("%f",&pok_podatciZaposlenik->mjesecnaPlacaZaposlenika);
	printf("UNESITE MJESTO RADA %d. ZAPOSLENIKA: ",rBrUnosa+1);
	scanf("%s",&pok_podatciZaposlenik->pozicijaUTvrtki);
	
	printf("\n\nZAPOSLENIK UNESEN!!\n\n");

}


//pocetni izbornik
int izbornik()
{
	int odluka=0;
	
	printf("\tPOCETNI IZBORNIK \n\n");
	printf("UNOS NOVOG ZAPOSLENIKA (1) \n");
	printf("ISPIS SVIH ZAPOSLENIKA (2) \n");
	printf("BRISANJE ZAPOSLENIKA (3) \n");
	printf("ZAMJENA PODATAKA ZAPOSLENIKA (4)\n");
	printf("TRAZI ZAPOSLENIKA (5) \n");
	printf("OCISTI KONZOLU (9) \n");
	printf("IZLAZ IZ PROGRAMA (0) \n\n");
	printf("\n\nIZBOR: ");
	scanf("%d",&odluka);
	printf("\n");
	return odluka;
}

//izbornik zamjene
int zamjena_izbornik()
{
	int odluka_zamjene=0;
	
	printf("\tIZBORNIK ZAMJENE!!\n\n");
	printf("ZAMJENA IMENA (1) \n");
	printf("ZAMJENA PREZIMENA (2) \n");
	printf("ZAMJENA SPOLA (3) \n");
	printf("ZAMJENA GODINE RODJENJA (4) \n");
	printf("ZAMJENA OIB-a (5) \n");
	printf("ZAMJENA STRUCNE SPREME (6) \n");
	printf("ZAMJENA MJESECNE PLACE (7) \n");
	printf("ZAMJENA MJESTA RADA (8) \n");
	printf("ZAMJENI SVE (9) \n");
	printf("ODUSTANI (0) \n");
	printf("\n\nIZBOR: ");
	scanf("%d",&odluka_zamjene);
	printf("\n");
	
	switch(odluka_zamjene)
	{
		do
		{
			
		case 1: return odluka_zamjene; break;
		case 2: return odluka_zamjene; break;
		case 3: return odluka_zamjene; break;
		case 4: return odluka_zamjene; break;
		case 5: return odluka_zamjene; break;
		case 6: return odluka_zamjene; break;
		case 7: return odluka_zamjene; break;
		case 8: return odluka_zamjene; break;
		case 9: return odluka_zamjene; break;
		case 0: break;
		default: printf("\tKRIVI UNOS!!\n"); break;
		
		}while(odluka_zamjene!=1 && odluka_zamjene!=2 && odluka_zamjene!=3 && odluka_zamjene!=4 && odluka_zamjene!=5 && odluka_zamjene!=6 &&
				odluka_zamjene!=7 && odluka_zamjene!=8 && odluka_zamjene!=9 && odluka_zamjene!=0);
	} 
	
}


//Zamjena zaposlenika
void ZAMJENI(int pozicija_zamjene, LISTA *pokLista, Zaposlenik *pok_podatciZaposlenik)
{
	int pozicija;
	int odabir=0;
	
	char spolM[1+1]="M", spolZ[1+1]="Z", provjeraStrcmpSpol[1+1];
	int provjeraStrcmpM=-1, provjeraStrcmpZ=-1;
	
	int duljinaOIB=0;
	
	char spSSS[3+1]= "SSS",spVSS[3+1]="VSS",spNKV[3+1]="NKV", provjeraStrcmpSP[3+1];
	int provjeraStrcmpSSS=-1, provjeraStrcmpVSS=-1, provjeraStrcmpNKV=-1;
	
	odabir=zamjena_izbornik();
	
	switch(odabir)
	{
		case 1:
			{
				printf("UNESITE NOVO IME %d. ZAPOSLENIKA: ",pozicija_zamjene+1);
				scanf("%s",&pokLista->elementi[pozicija_zamjene].imeZaposlenika);
				printf("\nPODATCI O ZAPOSLENIKU ZAMIJENJENI!! \n\n"); 
				break;
			}
		case 2:
			{
				printf("UNESITE NOVO PREZIME %d. ZAPOSLENIKA: ",pozicija_zamjene+1);
				scanf("%s",&pokLista->elementi[pozicija_zamjene].prezimeZaposlenika);
				printf("\nPODATCI O ZAPOSLENIKU ZAMIJENJENI!! \n\n");
				break;
			}
		case 3:
			{
				do
				{
					printf("UNESITE NOVI SPOL(M/Z) %d. ZAPOSLENIKA: ",pozicija_zamjene+1);
					scanf("%s",&provjeraStrcmpSpol);
					
					provjeraStrcmpM=strcmp(provjeraStrcmpSpol,spolM);
					provjeraStrcmpZ=strcmp(provjeraStrcmpSpol,spolZ);
			
					if(provjeraStrcmpM !=0 && provjeraStrcmpZ !=0)
					{
						printf("\tDOPUSTENI UNOS JE M ILI Z! \n\n");
					}
				
				}while(provjeraStrcmpM !=0 && provjeraStrcmpZ !=0);	
				strcpy(pokLista->elementi[pozicija_zamjene].spolZaposlenika,provjeraStrcmpSpol);
				printf("\nPODATCI O ZAPOSLENIKU ZAMIJENJENI!! \n\n");
				break;
			}
		case 4:
			{
				do
				{
					printf("UNESITE NOVU GODINU RODJENJA %d. ZAPOSLENIKA: ",pozicija_zamjene+1);
					scanf("%d",&pokLista->elementi[pozicija_zamjene].godinaRodjenjaZaposlenika);
					
					if(pokLista->elementi[pozicija_zamjene].godinaRodjenjaZaposlenika<1900)
					{
						printf("\n\n\tZAPOSLENIK JE PRESTAR!!\n\n");
					}
					else if (pokLista->elementi[pozicija_zamjene].godinaRodjenjaZaposlenika>1997)
					{
						printf("\n\n\tZAPOSLENIK MORA BITI PUNOLJETAN\n\n");
					}
				}while(pokLista->elementi[pozicija_zamjene].godinaRodjenjaZaposlenika<1900 || 
					pokLista->elementi[pozicija_zamjene].godinaRodjenjaZaposlenika>1997);
				printf("\nPODATCI O ZAPOSLENIKU ZAMIJENJENI!! \n\n");
				break;
			}
		case 5:
			{
				do
				{
					printf("UNESITE NOVI OIB %d. ZAPOSLENIKA: ",pozicija_zamjene+1);
					scanf("%s",&pokLista->elementi[pozicija_zamjene].oibZaposlenika);
					
					duljinaOIB=strlen(pokLista->elementi[pozicija_zamjene].oibZaposlenika);
	
					if(duljinaOIB!=11)
					{
						printf("\tDULJINA OIB-A MORA BITI 11 ZNAMENKI! \n\n");
					}
	
				}while(duljinaOIB!=11);
				printf("\nPODATCI O ZAPOSLENIKU ZAMIJENJENI!! \n\n");
				break;
			}
		case 6:
			{
				do
				{
					
					printf("UNESITE NOVU STRUCNU SPREMU %d. ZAPOSLENIKA: ",pozicija_zamjene+1);
					scanf("%s",&provjeraStrcmpSP);
					
					provjeraStrcmpNKV=strcmp(provjeraStrcmpSP,spNKV);
					provjeraStrcmpSSS=strcmp(provjeraStrcmpSP,spSSS);
					provjeraStrcmpVSS=strcmp(provjeraStrcmpSP,spVSS);

					if(provjeraStrcmpNKV!=0 && provjeraStrcmpSSS!=0 && provjeraStrcmpVSS!=0)
					{
						printf("\tDOPUSTENI UNOSI SU NKV, SSS, VSS! \n\n");
					}

				}while(provjeraStrcmpNKV!=0 && provjeraStrcmpSSS!=0 && provjeraStrcmpVSS!=0); 
				strcpy(pokLista->elementi[pozicija_zamjene].strucnaSpremaZaposlenika,provjeraStrcmpSP);
				printf("\nPODATCI O ZAPOSLENIKU ZAMIJENJENI!! \n\n");
				break;
			}
		case 7:
			{
				printf("UNESITE NOVU MJESECU PLACU %d. ZAPOSLENIKA: ",pozicija_zamjene+1);
				scanf("%f",&pokLista->elementi[pozicija_zamjene].mjesecnaPlacaZaposlenika);
				printf("\nPODATCI O ZAPOSLENIKU ZAMIJENJENI!! \n\n");
				break;
			}
		case 8:
			{
				printf("UNESITE NOVO RADNO MJESTO %d. ZAPOSLENIKA: ",pozicija_zamjene+1);
				scanf("%s",&pokLista->elementi[pozicija_zamjene].pozicijaUTvrtki);
				printf("\nPODATCI O ZAPOSLENIKU ZAMIJENJENI!! \n\n");
				break;
			}
		case 9:
			{
				pokLista->zadnji--;    
			    for (pozicija=pozicija_zamjene; pozicija<=pokLista->zadnji; pozicija++)
			    {
			    	pokLista->elementi[pozicija] = pokLista->elementi[pozicija+1];
				}
				
			  	UNOS_ZAPOSLENIKA(pokLista,pok_podatciZaposlenik,pozicija_zamjene);
			  	UBACI(*pok_podatciZaposlenik,pozicija_zamjene,pokLista);
			  	break;
			}
	}
  	
	SPREMI_U_DATOTEKU ("ListaZaposlenika.bin",pokLista); 



}


//Izbornik za funkciju trazi
int izbornikTRAZI()
{
	int odlukaTrazi=-1;
	
	do
	{
		printf("TRAZI PREMA IMENU (1) \n");
		printf("TRAZI PREMA PREZIMENU (2) \n");
		printf("ODUSTANI (0) \n\n");
		printf("\n\nIZBOR: ");
		scanf("%d",&odlukaTrazi);
		printf("\n");
		
		switch(odlukaTrazi)
		{
			case 1:
				{
					return odlukaTrazi;
					break;
				}
			case 2: 
				{
					return odlukaTrazi;
					break;
				}
			case 0:
				{
					break;
				}
			default:
				{
					printf("\tKRIVI UNOS!! \n\n");
					break;
				}
				
	
			
		}
	}while(odlukaTrazi!=0 && odlukaTrazi!=1 && odlukaTrazi!=2);
}


//Funkcija za trazenje zaposlenika u listi preko imena ili prezimna
void TRAZI(LISTA *pok_listaZaposlenika, int *pok_lista_zadnji, int a_odlukaTrazi)
{
	int odlukaTrazi=a_odlukaTrazi, korakPretrage=0, rezultatStrcmp=-1, brojPronadjenihZaposlenika=0;
	char a_imeZaposlenika[20+1], a_prezimeZaposlenika[30+1];
	
	switch(a_odlukaTrazi)
	{
		case 1:
			{
				printf("\tPRETRAGA ZAPOSLENIKA PREMA IMENU! \n\n");
				printf("UNESITE IME ZAPOSLENIKA: ");
				scanf("%s",&a_imeZaposlenika);
				
				for(korakPretrage=0; korakPretrage<=*pok_lista_zadnji; korakPretrage++)
				{
					
					rezultatStrcmp=strcmp(a_imeZaposlenika,pok_listaZaposlenika->elementi[korakPretrage].imeZaposlenika);

					if(rezultatStrcmp==0)
					{
						printf("\nZAPOSLENIK PRONADJEN! \n");
						printf("\n\nIME:%s \nPREZIME:%s \nSPOL:%s \nGODINA RODJENJA:%d \nOIB:%s \nSTRUCNA SPREMA:%s \nMJESECNA PLACA:%.2f KN \nMJESTO RADA:%s \n",
						   pok_listaZaposlenika->elementi[korakPretrage].imeZaposlenika, 
						   pok_listaZaposlenika->elementi[korakPretrage].prezimeZaposlenika,
						   pok_listaZaposlenika->elementi[korakPretrage].spolZaposlenika,
						   pok_listaZaposlenika->elementi[korakPretrage].godinaRodjenjaZaposlenika,
						   pok_listaZaposlenika->elementi[korakPretrage].oibZaposlenika,
						   pok_listaZaposlenika->elementi[korakPretrage].strucnaSpremaZaposlenika,
						   pok_listaZaposlenika->elementi[korakPretrage].mjesecnaPlacaZaposlenika,
						   pok_listaZaposlenika->elementi[korakPretrage].pozicijaUTvrtki);
						   
						   brojPronadjenihZaposlenika++;
						   printf("\nPRITISNI ENTER ZA NASTAVAK...\n");
						   getch();
						   
					}
					
					if(korakPretrage==*pok_lista_zadnji)
					{
						if(brojPronadjenihZaposlenika>0)
						{
							
						printf("\nSVI ZAPOSLENICI POD IMENOM: %s PRONADJENI! \n",a_imeZaposlenika);
						printf("PRONADJENO %d ZAPOSLENIKA POD IMENOM: %s \n",brojPronadjenihZaposlenika,a_imeZaposlenika);
						printf("\nPRITISNI ENTER ZA NASTAVAK...\n");
						
						getch();
						
						}
						
						else if(brojPronadjenihZaposlenika==0)
						{
							printf("NITI JEDAN ZAPOSLENIK POD IMENOM: %s NIJE PRONADJEN! \n",a_imeZaposlenika);
							printf("\nPRITISNI ENTER ZA NASTAVAK...\n");
						
							getch();
							
						}
						
						
					}

					
				}
				
				break;
			}
		case 2:
			{
				printf("\tPRETRAGA ZAPOSLENIKA PREMA PREZIMENU! \n\n");
				printf("UNESITE PREZIME ZAPOSLENIKA: ");
				scanf("%s",&a_prezimeZaposlenika);
				
				for(korakPretrage=0; korakPretrage<=*pok_lista_zadnji; korakPretrage++)
				{
					
					rezultatStrcmp=strcmp(a_prezimeZaposlenika,pok_listaZaposlenika->elementi[korakPretrage].prezimeZaposlenika);

					if(rezultatStrcmp==0)
					{
						printf("\nZAPOSLENIK PRONADJEN! \n");
						printf("\n\nIME:%s \nPREZIME:%s \nSPOL:%s \nGODINA RODJENJA:%d \nOIB:%s \nSTRUCNA SPREMA:%s \nMJESECNA PLACA:%.2f KN \nMJESTO RADA:%s \n",
						   pok_listaZaposlenika->elementi[korakPretrage].imeZaposlenika, 
						   pok_listaZaposlenika->elementi[korakPretrage].prezimeZaposlenika,
						   pok_listaZaposlenika->elementi[korakPretrage].spolZaposlenika,
						   pok_listaZaposlenika->elementi[korakPretrage].godinaRodjenjaZaposlenika,
						   pok_listaZaposlenika->elementi[korakPretrage].oibZaposlenika,
						   pok_listaZaposlenika->elementi[korakPretrage].strucnaSpremaZaposlenika,
						   pok_listaZaposlenika->elementi[korakPretrage].mjesecnaPlacaZaposlenika,
						   pok_listaZaposlenika->elementi[korakPretrage].pozicijaUTvrtki);
						   
						   printf("\nPRITISNI ENTER ZA NASTAVAK...\n");
						   brojPronadjenihZaposlenika++;
						   getch();
					}
					
					if(korakPretrage==*pok_lista_zadnji)
					{
						if(brojPronadjenihZaposlenika>0)
						{
							
							printf("\nSVI ZAPOSLENICI POD PREZIMENOM: %s PRONADJENI! \n",a_prezimeZaposlenika);
							printf("PRONADJENO %d ZAPOSLENIKA POD PREZIMENOM: %s \n",brojPronadjenihZaposlenika,a_prezimeZaposlenika);
							printf("\nPRITISNI ENTER ZA NASTAVAK...\n");
							
							getch();
						
						}
						
						else if(brojPronadjenihZaposlenika==0)
						{
							
							printf("NITI JEDAN ZAPOSLENIK POD PREZIMENOM: %s NIJE PRONADJEN! \n",a_prezimeZaposlenika);
							printf("\nPRITISNI ENTER ZA NASTAVAK...\n");
						
							getch();
						}
					
						
						
					}

					
				}
				
				break;
			}
			
	}
}


main()
{	
	Zaposlenik podatciZaposlenik;
	LISTA listaZaposlenika;
	int odluka=-1;
	int odlukaBrisanja=-1;
	int odlukaZamjene=-1;
	int brojUnosa=0, rbrUnosa=0;
	int odlukaTrazi=-1;
	int uvjetZamjena=1;
	
	listaZaposlenika.zadnji=-1; //Nepotrebno kada postoji èitanje iz datoteke, ali potrebno prilikom prvog pokretanja programa na raèunalu
	
	PROCITAJ_IZ_DATOTEKE("ListaZaposlenika.bin",&listaZaposlenika);
	
	printf("\t\t\tTVRTKA d.o.o. \n\n");
	printf("\t\t[EVIDENCIJA ZAPOSLENIKA] \n\n");

	do{
		
		odluka=izbornik();
		
		switch(odluka)
		{
			case 1:
				{
					do	
					{
						printf("KOLIKO ZAPOSLENIKA ZELITE UNIJETI? ");
						scanf("%d",&brojUnosa);
						
						if(brojUnosa==0)
						{
							printf("\n\n");
							break;
						}
	
					}while(brojUnosa<0);
					
					for(rbrUnosa=0; rbrUnosa<brojUnosa; rbrUnosa++)
					{
						UNOS_ZAPOSLENIKA(&listaZaposlenika,&podatciZaposlenik,rbrUnosa);
						UBACI(podatciZaposlenik,listaZaposlenika.zadnji+1,&listaZaposlenika);
						
					}
					
					SPREMI_U_DATOTEKU ("ListaZaposlenika.bin",&listaZaposlenika);
					break;
						
				}
			case 2:
				{
					PROCITAJ_IZ_DATOTEKE("ListaZaposlenika.bin",&listaZaposlenika);
					ISPIS(&listaZaposlenika);
					printf("\n");
					break;
				}
			case 3:
				{
					OBRISI(&listaZaposlenika);
					break;
				}
			case 4:
				{
					do
					{
						printf("KOJEM ZAPOSLENIKU ZELITE ZAMIJENITI PODATKE?: ");
						scanf("%d",&odlukaZamjene);
						odlukaZamjene--;
						uvjetZamjena=1;
						if ( (odlukaZamjene>listaZaposlenika.zadnji ) || (odlukaZamjene<0) )
						{
							printf("\tPOZICIJA NE POSTOJI! \n\n");
							uvjetZamjena=0;
						}
						
						
					}while(uvjetZamjena==0);
					
					ZAMJENI(odlukaZamjene,&listaZaposlenika,&podatciZaposlenik);
					
					break;
				}
			case 5:
				{
					odlukaTrazi=izbornikTRAZI();
					TRAZI(&listaZaposlenika,&listaZaposlenika.zadnji,odlukaTrazi);
					
				}
			case 9:
				{
					system("CLS");
					break;
				}
			case 0:
				{
					printf("PRITISNI ENTER ZA KRAJ!");
					break;
				}
			default: printf("KRIVI UNOS!! \n\n"); break;
		}
		 
	}while(odluka!=0);

}
	
