#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <ctype.h>

#define BOYUT 8
#define BOMB 7
#define KAZAN 1
#define KAYBET -1
#define DEVAM 0

int alt_mayin[BOYUT][BOYUT];
char kapali_mayin[BOYUT][BOYUT];
int bayraksayisi;
int Dsayisi;

void giris();
void altmayin_olustur();
void kapalimayin_olustur();
void mayin_bas();
int kutuyu_ac(int,int);
void kesfet(int,int);
void bayrak_koy(int,int);
void bayragi_cek(int,int);
int kazan_kaybet(int);
void tekrar();


int main()
{
    giris();
}

void giris()
{
    int x=0,satir,sutun;
    char harf;
    bayraksayisi=0;
    Dsayisi=0;
    printf("----------MAYİN TARLASİ OYUNUNA HOSGELDİNİZ!!!----------\n\n");
    altmayin_olustur();
    kapalimayin_olustur();
    mayin_bas();

    do
    {
        printf("\nBir kutu acmak icin --> a,satir,sutun\nBayrak koymak icin --> b,satir,sutun\nBayragi geri cekmek icin --> c,satir,sutun\nLutfen seciminizi giriniz:");
        scanf("%c%d%d",&harf,&satir,&sutun);

        if(harf == 'a')
        {
            x=kutuyu_ac(satir-1,sutun-1);
        }
        else if(harf == 'b')
        {
            bayrak_koy(satir-1,sutun-1);
        }
        else if(harf == 'c')
        {
            bayragi_cek(satir-1,sutun-1);
        }
        else
        {
            printf("\n!!!Gecersiz Giris lutfen tekrar deneyiniz!!!\n");
            x = DEVAM;
        }

        mayin_bas();
        x=kazan_kaybet(x);

        if(x == KAYBET)
        {
            printf("\n\n----------KAYBETTİNİZ :( ----------\n\n");
            tekrar();
        }
        if(x == KAZAN)
        {
            printf("\n\n----------TEBRİKLER KAZANDİNİZ!!!---------\n\n");
            tekrar();
        }
    }while(x == DEVAM);
}

void altmayin_olustur()
{
    srand(time(NULL));
    int i,j,k,randomsatir,randomsutun;

    for(i=0;i<BOYUT;i++)
    {
        for(j=0;j<BOYUT;j++)
        {
            alt_mayin[i][j] = 0;
        }
    }

    for(i=0;i<BOMB;i++)
    {
        randomsatir = rand() % BOYUT;
        randomsutun = rand() % BOYUT;
        if(alt_mayin[randomsatir][randomsutun] != -1)
        {
            alt_mayin[randomsatir][randomsutun] = -1;
            for(j=-1;j<=1;j++)
            {
                for(k=-1;k<=1;k++)
                {
                    if(alt_mayin[randomsatir+j][randomsutun+k] != -1 && randomsatir+j >= 0 && randomsatir+j < BOYUT && randomsutun+k >= 0 && randomsutun+k < BOYUT)
                    {
                        alt_mayin[randomsatir+j][randomsutun+k]++;
                    }
                }
            }
        }
        else
        {
            i--;
        }
    }
}

void kapalimayin_olustur()
{
    int i,j;

    for(i=0;i<BOYUT;i++)
    {
        for(j=0;j<BOYUT;j++)
        {
            kapali_mayin[i][j] = '#';
        }
    }
}

void mayin_bas()
{
    int i,j;

    printf("\n ");

    for(i=1;i<=BOYUT;i++)
    {
        printf("%3d",i);
    }

    printf("\n  ");

    for(i=1;i<=BOYUT;i++)
    {
        printf("---");
    }

    printf("\n");

    for(i=0;i<BOYUT;i++)
    {
        printf("|");
        for(j=0;j<BOYUT;j++)
        {
            printf("%3c",kapali_mayin[i][j]);
        }
        printf("  |%d",i+1);
        printf("\n");
    }

    printf("  ");

    for(i=1;i<=BOYUT;i++)
    {
        printf("---");
    }
}

int kutuyu_ac(int satir,int sutun)
{
    kapali_mayin[satir][sutun] = '0' + alt_mayin[satir][sutun];
    if(alt_mayin[satir][sutun] > 0)
    {
        return DEVAM;
    }
    
    else if(alt_mayin[satir][sutun] == -1)
    {
        return KAYBET;
    }

    else
    {
        kesfet(satir,sutun);
        return DEVAM;
    }
}

void kesfet(int satir,int sutun)
{
    int i,j;
    
    kapali_mayin[satir][sutun] = '0' + alt_mayin[satir][sutun];

    for(i=-1;i<=1;i++)
    {
        for(j=-1;j<=1;j++)
        {
            if(alt_mayin[satir+i][sutun+j] == 0 && satir+i >= 0 && satir+i < BOYUT && sutun+j >= 0 && sutun+j < BOYUT && kapali_mayin[satir+i][sutun+j] == '#')
            {
                kapali_mayin[satir+i][sutun+j] = '0' + alt_mayin[satir+i][sutun+j];
                kesfet(satir+i,sutun+j);
            }
            else if(alt_mayin[satir+i][sutun+j] > 0 && satir+i >= 0 && satir+i < BOYUT && sutun+j >= 0 && sutun+j < BOYUT && kapali_mayin[satir+i][sutun+j] == '#')
            {
                kapali_mayin[satir+i][sutun+j] = '0' + alt_mayin[satir+i][sutun+j];
            }
        }
    }
}

void bayrak_koy(int satir,int sutun)
{
    if(alt_mayin[satir][sutun] == -1 && kapali_mayin[satir][sutun] == '#')
    {
        bayraksayisi++;
    }
    kapali_mayin[satir][sutun] = 'D';
    Dsayisi++;
}

void bayragi_cek(int satir,int sutun)
{
    if(alt_mayin[satir][sutun] == -1 && kapali_mayin[satir][sutun] == 'D')
    {
        bayraksayisi--;  
    }
    else if(kapali_mayin[satir][sutun] == 'D')
    {
        Dsayisi--;
    }
    kapali_mayin[satir][sutun] = '#';
}

int kazan_kaybet(int x)
{
    if(bayraksayisi == BOMB)
    {
        x = KAZAN;
    }
    if(Dsayisi > BOMB)
    {
        x = KAYBET;
    }
    return x;
}

void tekrar()
{
    char cevap[10];
    int i;

    printf("\nTekrar Oynamak Ister Misiniz?: ");
    scanf("%s",cevap);

    for(i=0;i<strlen(cevap);i++)
    {
        cevap[i] = tolower(cevap[i]);
    }

    if(strcmp(cevap,"evet") == 0)
    {
        giris();
    }
    else
    {
        exit(0);
    }
}
