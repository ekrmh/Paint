#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>

void kontrol_et(int,int,int,int);
void buton_ciz(int);
void cizgi_ciz(int);
void kalem_ciz(int);
void sekil_ciz(int,int );
void firca(int);
void doldur(int);

int window1, window2;
DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
DWORD screenHeigth = GetSystemMetrics(SM_CYSCREEN);

int main()                                                        /// MA�N
{
    FreeConsole();
    setlocale(LC_ALL,"Turkish");
    window1 = initwindow(screenWidth-6,screenHeigth-95,"",0,53); /// �izim ekran�
    window2 =initwindow(screenWidth-5,50,"");  /// Ara� �ubu�u ekran�
    setcurrentwindow(window1);
    setbkcolor(WHITE);
    cleardevice();
    buton_ciz(window2);
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,COLOR(0,128,150));
    bar(675,0,725,50);
    setbkcolor(COLOR(0,128,150));
    settextstyle(DEFAULT_FONT,0,1);
    setfillstyle(SOLID_FILL,BLACK);
    bar(680,3,720,33);
    outtextxy(682,34,"Renk");
    rectangle(680,3,720,33);
    setcurrentwindow(window2);
    setbkcolor(COLOR(202,47,47));
    setcolor(COLOR(255,255,255));
    settextstyle(COMPLEX_FONT,0,3);
    outtextxy(3,0,"Kalem");
    setcurrentwindow(window1);
    setcolor(BLACK);
    kalem_ciz(window1);
    return 0;
}

void buton_ciz(int window)                                        /// BUTON
{
    int i,j;
    setcurrentwindow(window);
    rectangle(680,3,720,33);
    setbkcolor(COLOR(0,128,150));
    setcolor(COLOR(255,255,255));
    settextstyle(COMPLEX_FONT,0,3);
    outtextxy(3,0,"Kalem");
    outtextxy(81,0,"�izgi");
    outtextxy(161,0,"��gen");
    outtextxy(240,0,"Daire");
    outtextxy(319,0,"Dikd�rtgen");
    outtextxy(473,0,"F�r�a");
    outtextxy(552,0,"Temizle");
    outtextxy(430,25,"Doldur");
    settextstyle(COMPLEX_FONT,0,6);
    outtextxy(900,0,"A�");
    outtextxy(975,0,"Kaydet");
    setbkcolor(COLOR(202,47,47));
    outtextxy(screenWidth-172,0,"Kapat");
    settextstyle(COMPLEX_FONT,0,3);
    for(i = 0,j=0; i <=15 ; i++,j +=25)
    {
        setcolor(WHITE);
        setfillstyle(SOLID_FILL,i);
        bar(j+10,30,j+25,45);
        rectangle(j+10,30,j+25,45);
    }
    rectangle(680,3,720,33);
}

void kalem_ciz(int window)                                        /// KALEM
{
    int x,y;
    bool ilk = true;
    setcurrentwindow(window);
    POINT mousePos; // Mouse pozisyonu
    while(1)
    {
        GetCursorPos(&mousePos);
        if(mousePos.x < screenWidth-2 && mousePos.y < 50 && GetAsyncKeyState(VK_LBUTTON))
        {
            ilk = true;
            kontrol_et(window,mousePos.x,mousePos.y,0);
        }
        if(GetAsyncKeyState(VK_LBUTTON) && mousePos.y > 50)
        {
          if(ilk == true)
            {
                x = mousePos.x;
                y = mousePos.y;
                ilk = false;
            }
            line(x,y-60,mousePos.x,mousePos.y-60);
            x = mousePos.x;
            y = mousePos.y;
        }
        x = mousePos.x;
        y = mousePos.y;
    }
}

void cizgi_ciz(int window)                                        /// ��ZG�
{
    while(1)
    {
        setcurrentwindow(window);
        int x,y;
        POINT mousePos;
        GetCursorPos(&mousePos);
        if(mousePos.x < screenWidth-2 && mousePos.y <50 && GetAsyncKeyState(VK_LBUTTON))
        {
            kontrol_et(window,mousePos.x,mousePos.y,1);
        }
        if(GetAsyncKeyState(VK_LBUTTON) && mousePos.y > 50)
        {
            x = mousePos.x;
            y = mousePos.y-60;
            writeimagefile("temp",0,0,screenWidth-5,screenHeigth-95);
            while(1)
            {
                GetCursorPos(&mousePos);
                line(x,y,mousePos.x,mousePos.y-60);
                setbkcolor(WHITE);
                line(x,y,mousePos.x,mousePos.y-60);
                readimagefile("temp",0,0,screenWidth-5,screenHeigth-95);
                if(GetAsyncKeyState(VK_RBUTTON) )
                {
                    setbkcolor(WHITE);
                    readimagefile("temp",0,0,screenWidth-5,screenHeigth-95);
                    while(1)if(!GetAsyncKeyState(VK_LBUTTON))kontrol_et(window,mousePos.x,mousePos.y,1);
                }
                if(!GetAsyncKeyState(VK_LBUTTON))
                {
                    line(x,y,mousePos.x,mousePos.y-60);
                    break;
                }
            }

            delay(100);


        }
    }

}

void sekil_ciz(int window,int secim)                              /// �EK�LLER
{
    int ikiKordiArasi,x1,y1,x2,y2,mx,my;
    setcurrentwindow(window);
    int eski_renk;
    POINT mousePos;
    while(1)
    {
        GetCursorPos(&mousePos);
        if(mousePos.x < screenWidth-2 && mousePos.y <50 && GetAsyncKeyState(VK_LBUTTON))
        {
            kontrol_et(window,mousePos.x,mousePos.y,secim);
        }
        if(GetAsyncKeyState(VK_LBUTTON))
        {
            x1 = mousePos.x;
            y1 = mousePos.y;
            writeimagefile("temp",0,0,screenWidth-5,screenHeigth-95);
            while(1)
            {
                GetCursorPos(&mousePos);
                x2 = mousePos.x;
                y2 = mousePos.y;
                ikiKordiArasi = floor(sqrt(pow((abs(y2-y1)),2) + pow((abs(x2-x1)),2)));
                if(secim == 2)
                {
                    setlinestyle(SOLID_LINE,2,1);
                    my=abs(y2+y1)/2;
                    mx=abs(x2+x1)/2;
                    circle(mx,my-60,ikiKordiArasi/2);
                    setbkcolor(WHITE);
                    circle(mx,my-60,ikiKordiArasi/2);
                    readimagefile("temp",0,0,screenWidth-5,screenHeigth-95);
                    if(!GetAsyncKeyState(VK_LBUTTON))break;
                }
                else if(secim == 3)
                {
                    if (x2>x1 && y1<y2) rectangle(x1-4,y1-56,x2-4,y2-56);
                    else if(x1>x2 && y2<y1) rectangle(x2-4,y2-56,x1-4,y1-56);
                    else if(y1<y2) rectangle(x2-4,y1-56,x1-4,y2-56);
                    else if(y2<y1) rectangle(x1-4,y2-56,x2-4,y1-56);
                    setbkcolor(WHITE);
                    if (x2>x1 && y1<y2) rectangle(x1-4,y1-56,x2-4,y2-56);
                    else if(x1>x2 && y2<y1) rectangle(x2-4,y2-56,x1-4,y1-56);
                    else if(y1<y2) rectangle(x2-4,y1-56,x1-4,y2-56);
                    else if(y2<y1) rectangle(x1-4,y2-56,x2-4,y1-56);
                    readimagefile("temp",0,0,screenWidth-5,screenHeigth-95);
                    if(!GetAsyncKeyState(VK_LBUTTON))break;
                }
                else if(secim == 4)
                {
                    line(x1,y1-60,x2,y2-60);
                    line(x1,y1-60,2*x1-x2,y2-60);
                    line(x2,y2-60,2*x1-x2,y2-60);
                    setbkcolor(WHITE);
                    line(x1,y1-60,x2,y2-60);
                    line(x1,y1-60,2*x1-x2,y2-60);
                    line(x2,y2-60,2*x1-x2,y2-60);
                    readimagefile("temp",0,0,screenWidth-5,screenHeigth-95);
                    if(!GetAsyncKeyState(VK_LBUTTON))break;
                }
                if(GetAsyncKeyState(VK_RBUTTON) )
                {
                    setbkcolor(WHITE);
                    readimagefile("temp",0,0,screenWidth-5,screenHeigth-95);
                    while(1)if(!GetAsyncKeyState(VK_LBUTTON))kontrol_et(window,mousePos.x,mousePos.y,secim);
                }
            }
            if(secim == 2)
            {
                eski_renk=getcolor();
                setlinestyle(SOLID_LINE,1,2);
                circle(mx,my-60,ikiKordiArasi/2);
                setcolor(COLOR(254,254,254));
                circle(mx,my-60,(ikiKordiArasi/2)-1);
                setcolor(eski_renk);
                setlinestyle(SOLID_LINE,1,1);
            }
            else if(secim == 3)
            {
                eski_renk = getcolor();
                if (x2>x1 && y1<y2)
                {
                    rectangle(x1-4,y1-56,x2-4,y2-56);
                    setcolor(COLOR(254,254,254));
                    rectangle(x1-3,y1-55,x2-5,y2-57);
                }
                else if(x1>x2 && y2<y1)
                {
                    rectangle(x2-4,y2-56,x1-4,y1-56);
                    setcolor(COLOR(254,254,254));
                    rectangle(x2-3,y2-55,x1-5,y1-57);
                }
                else if(y1<y2)
                {
                    rectangle(x2-4,y1-56,x1-4,y2-56);
                    setcolor(COLOR(254,254,254));
                    rectangle(x2-3,y1-55,x1-5,y2-57);
                }
                else if(y2<y1)
                {
                    rectangle(x1-4,y2-56,x2-4,y1-56);
                    setcolor(COLOR(254,254,254));
                    rectangle(x1-3,y2-55,x2-5,y1-57);
                }
                setcolor(eski_renk);
            }
            else if(secim == 4)
            {
                eski_renk=getcolor();
                line(x1,y1-60,x2,y2-60);
                line(x1,y1-60,2*x1-x2,y2-60);
                line(x2,y2-60,2*x1-x2,y2-60);
                setcolor(COLOR(254,254,254));
                line(x1,y1-59,x2-1,y2-59);
                line(x1,y1-59,2*x1-x2+1,y2-59);
                line(x2-1,y2-61,2*x1-x2+1,y2-61);
                setcolor(eski_renk);
            }
        }
    }
}

void firca(int window)                                            /// FIR�A
{
    setcurrentwindow(window);
    POINT mousePos; // Mouse pozisyonu
    while(1)
    {
        GetCursorPos(&mousePos);
        if(mousePos.x < screenWidth-2 && mousePos.y <50 && GetAsyncKeyState(VK_LBUTTON))
        {
            kontrol_et(window,mousePos.x,mousePos.y,5);
        }
        if(GetAsyncKeyState(VK_LBUTTON) && mousePos.y > 50)
        {
            setfillstyle(SOLID_FILL,getcolor());
            bar(mousePos.x-10,mousePos.y-70,mousePos.x+10,mousePos.y-55);
        }
    }
}

void doldur(int window)                                           /// DOLDUR
{
    setcurrentwindow(window);
    POINT mousePos; // Mouse pozisyonu
    while(1)
    {
        GetCursorPos(&mousePos);
        if(mousePos.x < screenWidth-2 && mousePos.y <50 && GetAsyncKeyState(VK_LBUTTON))
        {
            kontrol_et(window,mousePos.x,mousePos.y,6);
        }
        if(GetAsyncKeyState(VK_LBUTTON) && mousePos.y > 50)
        {
            setfillstyle(SOLID_FILL,getcolor());
            floodfill(mousePos.x,mousePos.y-60,COLOR(254,254,254));
        }
    }
}

void kontrol_et(int window,int x,int y, int r)                    /// MOUSE
{
    setcurrentwindow(window2);
    setbkcolor(COLOR(202,47,47));
    settextstyle(COMPLEX_FONT,0,3);
    int i,j;
    while(1)
    {
        if( x < 82 && x > 5 && y < 27 && y > 3)                /// KALEM
        {
            buton_ciz(window2);
            outtextxy(3,0,"Kalem");
            delay(100);
            kalem_ciz(window);
        }
        else if(x > 84 && x < 161 && y < 27 && y > 3)          /// ��ZG�
        {
            buton_ciz(window2);
            outtextxy(81,0,"�izgi");
            delay(100);
            cizgi_ciz(window);
        }
        else if(x > 240 && x < 319 && y < 27 && y > 3)         /// DA�RE
        {
            buton_ciz(window2);
            outtextxy(240,0,"Daire");
            delay(100);
            sekil_ciz(window,2);
        }
        else if(x > 319 && x< 450 && y < 27 && y > 3 )         /// D�KD�RTGEN
        {
            buton_ciz(window2);
            outtextxy(319,0,"Dikd�rtgen");
            delay(100);
            sekil_ciz(window,3);
        }
        else if(x > 161 && x < 240 && y < 27 && y > 3)         /// ��GEN
        {
            buton_ciz(window2);
            delay(100);
            outtextxy(161,0,"��gen");
            sekil_ciz(window,4);
        }
        else if(x > 475 && x< 550 && y < 27 && y > 3 )         /// FIR�A
        {
            buton_ciz(window2);
            outtextxy(473,0,"F�r�a");
            delay(100);
            firca(window);
        }
        else if(x > 430 && x< 520 && y > 28 && y  <50 )        /// DOLDUR
        {
            buton_ciz(window2);
            outtextxy(430,25,"Doldur");
            delay(100);
            doldur(window);
        }
        else if(x>screenWidth-172&&x<screenWidth-2&&y<52&&y>3) /// KAPAT
        {
            delay(100);
            settextstyle(COMPLEX_FONT,0,6);
            setbkcolor(COLOR(155,47,47));
            outtextxy(screenWidth-172,0,"Kapat");
            delay(300);
            if(GetAsyncKeyState(VK_LBUTTON)==false)
            {
                setbkcolor(COLOR(202,47,47));
                outtextxy(screenWidth-172,0,"Kapat");
                delay(100);
                remove("temp");
                exit(1);
            }
            break;
        }
        else if(x > 901 && x <969 && y < 52 && y > 3)          /// A�
        {
            delay(100);
            settextstyle(COMPLEX_FONT,0,6);
            setbkcolor(COLOR(202,47,47));
            outtextxy(900,0,"A�");
            delay(100);
            if(GetAsyncKeyState(VK_LBUTTON)==false)
            {
                setbkcolor(COLOR(0,128,150));
                outtextxy(900,0,"A�");
                setcurrentwindow(window1);
                char acDosya[50];
                AllocConsole();
                freopen("CONIN$", "r",stdin);
                freopen("CONOUT$", "w",stdout);
                freopen("CONOUT$", "w",stderr);
                printf("Acmak istediginiz dosyanin adini yazin: ");
                gets(acDosya);
                strcat(acDosya,".jpg");
                printf("\nKonsolu kapatiniz.");
                FreeConsole();
                readimagefile(("%s",acDosya),0,0,screenWidth,screenHeigth-95);
            }
            delay(300);
            break;
        }
        else if(x > 977 && x <1174 && y < 52 && y > 3)         /// KAYDET
        {
            delay(100);
            settextstyle(COMPLEX_FONT,0,6);
            setbkcolor(COLOR(202,47,47));
            outtextxy(975,0,"Kaydet");
            delay(100);
            if(GetAsyncKeyState(VK_LBUTTON)==false)
            {
                setbkcolor(COLOR(0,128,150));
                outtextxy(975,0,"Kaydet");
                setcurrentwindow(window1);
                char kayitDosya[50];
                AllocConsole();
                freopen("CONIN$", "r",stdin);
                freopen("CONOUT$", "w",stdout);
                freopen("CONOUT$", "w",stderr);
                printf("Kaydetmek istediginiz resmin adini yazin: ");
                gets(kayitDosya);
                printf("\nKonsolu kapatiniz.");
                strcat(kayitDosya,".jpg");
                FreeConsole();
                delay(100);
                writeimagefile(("%s",kayitDosya),0,0,screenWidth,screenHeigth-95);
            }
            delay(300);
            break;
        }
        else if(x > 552 && x <660 && y < 27 && y > 3)          /// TEM�ZLE
        {
            delay(100);
            setbkcolor(COLOR(202,47,47));
            outtextxy(552,0,"Temizle");
            delay(100);
            if(GetAsyncKeyState(VK_LBUTTON)==false)
            {
                setbkcolor(COLOR(0,128,150));
                outtextxy(552,0,"Temizle");
                setcurrentwindow(window);
                cleardevice();
            }
            delay(300);
            break;
        }
        else
        {
            for(i=0,j=0; i<=15; i++,j+=25)
            {
                if(x<j+27 && x>j+12 && y<48 && y>33)           /// RENK SE��M�
                {
                    delay(20);
                    setcurrentwindow(window);
                    setcolor(i);
                    setcurrentwindow(window2);
                    setfillstyle(SOLID_FILL,COLOR(0,128,150));
                    bar(675,0,725,50);
                    setbkcolor(COLOR(0,128,150));
                    settextstyle(DEFAULT_FONT,0,1);
                    setfillstyle(SOLID_FILL,i);
                    bar(680,3,720,33);
                    setcolor(BLACK);
                    rectangle(681,4,719,32);
                    setcolor(WHITE);
                    outtextxy(682,34,"Renk");
                    rectangle(680,3,720,33);
                }
            }
            buton_ciz(window2);
            switch(r)                                          /// GER� D�N��
            {
            case 0:
                outtextxy(3,0,"Kalem");
                delay(100);
                kalem_ciz(window);
            case 1:
                outtextxy(81,0,"�izgi");
                delay(100);
                cizgi_ciz(window);
            case 2:
                outtextxy(240,0,"Daire");
                delay(100);
                sekil_ciz(window,2);
            case 3:
                outtextxy(319,0,"Dikd�rtgen");
                delay(100);
                sekil_ciz(window,3);
            case 4:
                outtextxy(161,0,"��gen");
                delay(100);
                sekil_ciz(window,4);
            case 5:
                outtextxy(473,0,"F�r�a");
                delay(100);
                firca(window);
            case 6:
                outtextxy(430,25,"Doldur");
                delay(100);
                doldur(window);
            }
        }
    }
    kontrol_et(window,5000,5000,r);
}
