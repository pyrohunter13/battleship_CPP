#include <iomanip>
#include <stdlib.h>
#include <iostream>
#include <time.h>
using namespace std;

void printarr(string[10][10]);
int randnum(int,int);
bool atk(int,int,string[10][10],string[10][10],string[10][10]);
bool botatk(int ,int ,string [10][10],string [10][10]);
int searchBoard(string ,string [10][10]);

int main()
{
    char start;
    do
    {
        cout << "press 1 to start:";
        cin >> start;
    }while (start!='1');
    bool gameend=false;//game on/off
    srand(time(NULL));
    string arp[10][10];//playzone
    string allship[10][10];//all boat a,b,c,d,e,f
    int urhp=9;//hit point
    int len2=4;//BOT ship length
    string enemy[10][10];//undercover array
    for(int i=0;i<10;i++)//reset
    {
        for(int j=0;j<10;j++)
        {
            arp[i][j]='0';//pengenolan
        }
    }

    int  row,col;
    do//P1 destroyer
    {
        row=randnum(4,0);
        col=randnum(9,0);
    }
    while (arp[row][col+1]=="p1"||arp[row][col]=="p1"||col+4>9);//biar gak ke overlay and error
    for (int i=0;i<4;i++)
    {
        arp[row][col+i]="p1";//assign to the first array
        allship[row][col+i]="a";
    }
    do//P1 battleship
    {
        row=randnum(4,0);
        col=randnum(9,0);
    }
    while (arp[row][col+1]=="p1"||arp[row][col]=="p1"||col+3>9);//biar gak ke overlay and error
    for (int i=0;i<3;i++)
    {
        arp[row][col+i]="p1";//assign to the first array
        allship[row][col+i]="b";
    }
    do//P1 boat
    {
        row=randnum(4,0);
        col=randnum(9,0);
    }
    while (arp[row][col+1]=="p1"||arp[row][col]=="p1"||col+2>9);//biar gak ke overlay and error
    for (int i=0;i<2;i++)
    {
        arp[row][col+i]="p1";//assign to the first array
        allship[row][col+i]="c";
    }

    int row2,col2;
    do//BOT destroyer
    {
        row2=randnum(9,5);
        col2=randnum(9,0);
    }
    while (enemy[row2][col2+1]=="x"||enemy[row2][col2]=="x"||col2+4>9);//biar gak ke overlay and error
    for (int i=0;i<4;i++)
    {
        enemy[row2][col2+i]='x';//assign to the second array
        allship[row2][col2+i]='d';
    }
    do//BOT battleship
    {
        row2=randnum(9,5);
        col2=randnum(9,0);
    }
    while (enemy[row2][col2+1]=="x"||enemy[row2][col2]=="x"||col2+3>9);//biar gak ke overlay and error
    for (int i=0;i<3;i++)
    {
        enemy[row2][col2+i]='x';//assign to the second array
        allship[row2][col2+i]='e';
    }
    do//BOT boat
    {
        row2=randnum(9,5);
        col2=randnum(9,0);
    }
    while (enemy[row2][col2+1]=="x"||enemy[row2][col2]=="x"||col2+2>9);//biar gak ke overlay and error
    for (int i=0;i<2;i++)
    {
        enemy[row2][col2+i]='x';//assign to the second array
        allship[row2][col2+i]='f';
    }
    int enemyhp=9;//hit point enemy
    printarr(arp);
    //printarr(enemy); //test
    //printarr(allship);//test
    cout << endl;
    int x,y;//your move
    do//start the game
    {
        do
        {
            cout << "Input number (0-9)x:" << endl;
            cin >> y;
            cout << "Input number (5-9)y:" << endl;
            cin >> x;
        }
    while (y>9||x>9||x<5||arp[x][y] == "H"||arp[x][y] == "X");//biar tidak terulang
    bool g,h,i,j,k,l;//untuk biar gak keulang lagi
    string a="a";//ur ship
    string b="b";
    string c="c";               //utk pengecekkan "destroyed a ship"
    string d="d";//enemy ship
    string e="e";
    string f="f";
    if(atk(x,y,arp,enemy,allship))
    {
        cout << " HIT" << endl;
        enemyhp-=1;
    }
    else
    {
        cout << " U MISS" << endl;
    }
    int z,zz;//bot
    do
    {
        z=randnum(4,0);
        zz=randnum(9,0);
    }
    while (arp[z][zz]=="X"||arp[z][zz]=="H");//biar tidak terulang
    if(botatk(z,zz,arp,allship))//bot move
    {
        cout << " ENEMY HIT" << endl;
        urhp-=1;
    }
    else
    {
        cout << " ENEMY MISSED" << endl;
    }
    //utk yang "destroyed a ship"
    if(g==true)//biar satu kali ke shownnya/untuk biar gak keulang lagi
        {
            if(searchBoard(a,allship)==0)//untuk nge cek di array allship boat yang "a" ada ==0 kalau iya cout destroyed
            {
                cout << "enemy destroyed your destroyer" << endl;
                g=false;
            }
        }
    if(h==true)//biar satu kali ke shownnya/untuk biar gak keulang lagi
        {
            if(searchBoard(b,allship)==0)
            {
                cout << "enemy destroyed your battleship" << endl;
                h=false;
            }
        }
    if(i==true)//biar satu kali ke shownnya/untuk biar gak keulang lagi
        {
            if(searchBoard(c,allship)==0)
            {
                cout << "enemy destroyed your boat" << endl;
                i=false;
            }
        }
    if(j==true)//biar satu kali ke shownnya/untuk biar gak keulang lagi
        {
            if(searchBoard(d,allship)==0)
            {
                cout << "you destroyed a destroyer" << endl;
                j=false;
            }
        }
    if(k==true)//biar satu kali ke shownnya/untuk biar gak keulang lagi
        {
            if(searchBoard(e,allship)==0)
            {
                cout << "you destroyed a battleship" << endl;
                k=false;
            }
        }
    if(l==true)//biar satu kali ke shownnya/untuk biar gak keulang lagi
        {
            if(searchBoard(f,allship)==0)
            {
                cout << "you destroyed a boat" << endl;
                l=false;
            }
        }
    cout << "   ENEMIES HP:" <<enemyhp <<endl;
    cout << "   UR HP:" << urhp <<endl;
    printarr(arp);
    if(urhp==0)//ending the game cond=lose
    {
        cout << "   U LOSE";
        cout <<endl;
        cout <<"ty for pley goblok -Zuqi";
        gameend=true;
    }
    if(enemyhp==0)//ending the do while loop cond=win
    {
        cout << "   U WON";
        cout <<endl;
        cout <<"wp -Zuqi";
        gameend=true;
    }
    }
    while(gameend==false);
    cout <<endl;
    cout <<"GG";
    return 0;
}

void printarr(string arr[10][10])//print array 2d
{
    int atas [10];
    cout <<"     "<< setw(5);
    for (int i=0;i<10;i++)
    {
        atas [i]= i;//index
        cout << setw(5);
        cout << atas [i] << setw(5);
    }
    cout <<endl;
    for(int i=0;i<10;i++)
    {
        cout << i << setw(5);//index
        for(int j=0;j<10;j++)
        {
            cout << arr[i][j] << setw(5);
        }
        cout << endl;
    }

}

int randnum(int max,int min)//random num
{
    return rand() % (max - min - 1) + min + 1;
}

bool atk(int x,int y,string arr[10][10], string enm[10][10],string allship[10][10])//hit or miss
{
    if(enm[x][y]=="x")//check the second array==kordinat from x n y
    {
        arr[x][y] = "H";//untuk interface keluar "H"
        allship[x][y] = "H";//utk yang "destroyed a ship"
        return true;
    }
    else
    arr[x][y] = "X";//untuk interface keluar "X"
    return false;
}

bool botatk(int x,int y,string arr[10][10],string allship[10][10])//hit or miss bot
{
    if(arr[x][y]=="p1")//check the first array=="p1"
    {
        arr[x][y] = "H";//untuk interface keluar "H"
        allship[x][y] = "H";//utk yang "destroyed a ship"
        return true;
    }

    else
    arr[x][y] = "X";//untuk interface keluar "X"
    return false;
}

int searchBoard(string x,string board[10][10])//utk cek di all_array ada berapa "a/b/c..."
{
    for (int r = 0; r < 10; r++)
    {
        for (int c = 0; c < 10; c++)
        {
            if (board[r][c] == x)//pengecekan adakah di board yang sama seperti string "x"
            {
                return r;
            }
        }
    }
}
/*KEKURANGAN:
-TERKADANG GAK JALAN/EROR
-TERKADANG KETUMPUK
-PENOMORAN MSH 0-9 BUKAN 1-10
-TULISAN 0-4/1-5 MASIH ADA
-KURANG MODULAR
KELEBIHAN:
-SUDAH BISA DIMAINKAN
*/
