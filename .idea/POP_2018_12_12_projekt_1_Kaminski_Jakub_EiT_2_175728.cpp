// POP 2018-12-12 projekt 1 Kamiñski Jakub EIT 2 175528 Dev-C++ 5.11
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
struct MI           //Podstawa
{
    int x;
    int y;
    bool slash;
};
 
int clamp(int value, int min, int max)
{
    return value>max?max:value<min?min:value;   //wyciagniecie posredniej wartosci
}
 
string getFormattedString(int n,int length){
    stringstream s;
    s<<n;
    string str=s.str();
    s.str("");
    for(int i=0;i<length-str.length();i++){         //Dodawanie 0 jesli jest 1 a powinno byc 01
        s<<"0";
    }
    for(int i=0;i<str.length();i++){
        s<<str[i];
    }
    return s.str();
}
 
 
void begin()
{
 
    cout<<"     A   B   C   D   E   F   G   H   I   J  "<< endl;            //Góra tabeli
    cout<<"   ----------------------------------------"<< endl;
}
 
int StB(int c)
{
    return (c<65 || c>90)?c-32:c;
}
 
void inst()
{
    cout << "               *INSTRUKCJA*                " << endl;      //Instrukcja
    cout << "Celem zadania jest zbadanie zdolnosci koncentracji, spostrzegawczosci i logicznego myslenia. Test polega na analizie planszy z rozstawionymi zwierciadlami i przewidzenie, w ktorym miejscu planszy promien swiatla ja opusci oraz wpisaniu odpowiedzi PRZYKLAD: B (moze byc mala lub wielka litera) 1. Zwierciadla sa rozstawione w sposob losowy i sa ustawione pod skosem z lewej na prawa lub z prawej na lewa. Przez 3 sekundy uk³ad luster jest prezentowany na standardowym wyjsciu. Nastepnie lustra znikaj a pojawia sie miejsce gdzie swiatlo jest wprowadzane. Zadanie polega na okresleniu gdzie swiatlo opusci plansze.Test jest przeprowadzany na planszy o rozmiarze 10 x 10. W grze wystepuje 6 poziomow. Na pierwszym poziomie na planszy znajduje sie tylko jedno zwierciadlo, na drugim 2, odpowiednio na kolejnych o jedno wiecej. Test jest ograniczony w czasie, calosc testu trwa nie wiecej ni¿ 180 sekund" <<endl<<endl;
}
 
void create_mir(int am_mirr, MI mirror[])
{
    for(int i=0; i < am_mirr; i++)                  //losowe lustra w losowych miejscach
    {
        mirror[i].x = rand()%8+1;
        mirror[i].y = rand()%8+1;
        mirror[i].slash = rand()%2;
    }
}
 
int getID (int x, int y, MI mirror[], int am_mirr)
{
    int id=-1;
    for(int i = 0; i < am_mirr; i++){
        if(mirror[i].x==x and mirror[i].y==y){				//zwraca id zwierciadla a jak nie to -1
            id=i;
        }
        return id;
 
    }
}
 
void scr(MI mirror[], int am_mirr)
{
    begin();
    for(int y = 0;y < 10; y++) {
 
        cout<<getFormattedString(y+0,2)<<" ";				//wypelnienie tabeli
 
        for (int x = 0; x < 10; x++) {
 
            int id=getID(x,y,mirror,am_mirr);
            char thg=(id==-1)?' ': mirror[id].slash?'/':'\\';
            cout<<"| "<<thg<<" ";
        }
 
        cout<<"| ";
        cout<<endl;
        cout<<"   ";
        for (int x = 0; x <10; x++) {
            cout<<"----";
        }
        cout<<endl;
 
    }
 
 
}
 
void scr_las(int x_las, int y_las)              //tworzenie tabeli ale z laserem nie zwierciadlami
{
    begin();
    for(int y = 0; y < 10 ; y++) {
        cout<<getFormattedString(y+1,2)<<" ";
        for (int x = 0; x < 10; x++) {
            char thg=((x_las==x && y_las==y))?'*':' ';
            cout<<"| "<<thg<<" ";
        } cout<<"|";
        cout<<endl;
        cout<<"   ";
        for (int x = 0; x < 10; x++) {
            cout<<"----";
        }
        cout<<endl;
 
    }
 
 
}
 
void las_path (int& x_las, int& y_las, int am_mirr, MI mirror[] ){
 
    int dx, dy;
    if(y_las == 0){
        dx=0; dy=1;                         //takim sposobem laser ma sie przemieszczac
    }
    else if(y_las == 9){
        dx=0; dy=-1;
    }
    else if(x_las == 0){
        dx=1; dy=0;
    }
    else if(x_las == 9){
        dx=-1; dy=0;
    }
 
    while(1){
 
        if(x_las > 9 or x_las < 0 or y_las > 9 or y_las <0){
            y_las=clamp(y_las,0,9);
            x_las=clamp(x_las,0,9);
            break;
        }
        for(int i = 0; i < am_mirr; i++) {
            if (mirror[i].x == x_las && mirror[i].y == y_las) {
                int tx = dx;
                int ty = dy;
                dy = tx*(mirror[i].slash*-2+1);
                dx = ty*(mirror[i].slash*-2+1);
            }
        }
        x_las += dx;
        y_las += dy;
 
 
    }
 
}
 
void clears(){
    system("pause");            //pauza i czyszczenie
    system("CLS");
 
}
 
void waiting (int secs)
{
    int retTime = time(0) + secs;       //m¹dry sposob na ominiecie sleep ;(
    while (time(0) < retTime);
}
 
 
int play(int am_mirr, int &score, int&unscore, int lvl, double sum_s, int maps, int map1, int map2, int map3, int map4, int map5, int map6, int all, int s_max, int s_min){
 
    cout<<"         POZIOM NUMER:  "<<lvl<<".  "<<"PLANSZA "<<all+1<<endl<<endl;
    MI mirror[am_mirr];
    create_mir(am_mirr, mirror);
    scr(mirror, am_mirr);
    cout<<endl;
 
 
    int losoweID=rand()%am_mirr;
    MI losowe_mirror=mirror[losoweID];                    //wyszukanie losowego lasera pod ktory przystosuje sie laser
    int x_las, y_las;
    if(rand()%2?true:false)
    {
        x_las = (rand()%2?true:false)?0:9;
        y_las = losowe_mirror.y;                                 //losowanie kierunku lasera
    } else {
        x_las = losowe_mirror.x;
        y_las = (rand()%2?true:false)?0:9;
    }
    waiting(3);
    system("CLS");
    cout<<"         POZIOM NUMER:  "<<lvl<<".  "<<"PLANSZA "<<all+1<<endl<<endl;
    scr_las(x_las, y_las);
    cout<<endl;
    las_path(x_las, y_las, am_mirr, mirror);
    double time=clock();
    cout<<"Punkty: "<<score<<endl;
    // cout<<"ODPOWIEDZ [Kolumna: " << (char)((x_las+'A')) << " Wiersz: " << ((y_las+1))<<" ]"<<endl;  // <--Przydatne do sprawdzania czy gra poprawnie dzia³a :)
    int a;
    char b;
    cin>>b>>a;
    cout<<endl;
    time = clock() - time;
    double s= time/ CLOCKS_PER_SEC*1000.0;
 
    b=StB(b);
    all=all+1;
    if((y_las+1)==a && (char)((x_las+'A'))==b){
        cout<<"Dobrze"<<endl;
        score++;
        maps++;
        unscore=0;
        switch(lvl){
            case 1: map1++;break;
            case 2: map2++;break;
            case 3: map3++;break;			//punkty za poziomy
            case 4: map4++;break;
            case 5: map5++;break;
            case 6: map6++;break;
        }
 
    }else{
        cout<<"Zle"<<endl;
        unscore++;
        score=0;
    }
    cout<<"ODPOWIEDZ [Kolumna: " << (char)((x_las+'A')) << " Wiersz: " << ((y_las+1))<<" ]"<<endl;
    clears();
    sum_s=sum_s+s;
    if (lvl==1)
    {
        int s_max=sum_s;
        int s_min=sum_s;
    }
    if (s_max<s)
        s_max=s;
    if (s_min>s)
        s_min=s;
    if(sum_s<=180000)cout<<"CZAS KTORY POZOSTAL: "<<(180000-sum_s)/1000.0<<" SEKUND";
    if(sum_s>=180000)
    {
        cout<<"ILOSC ROZWIAZANYCH MAP: "<<maps<<endl;
        cout<<"ILOSC ROZWIAZANYCH MAP NA POZIOMIE 1. : "<<map1<<"  ILOSC ROZWIAZANYCH MAP NA POZIOMIE 2. : "<<map2<<endl;
        cout<<"ILOSC ROZWIAZANYCH MAP NA POZIOMIE 3. : "<<map3<<"  ILOSC ROZWIAZANYCH MAP NA POZIOMIE 4. : "<<map4<<endl;
        cout<<"ILOSC ROZWIAZANYCH MAP NA POZIOMIE 5. : "<<map5<<"  ILOSC ROZWIAZANYCH MAP NA POZIOMIE 6. : "<<map3<<endl;
        cout<<"SREDNI CZAS SPEDZONY NA MAPIE: "<<(float)((sum_s/1000.0)/all)<<endl;
        cout<<"NAJKROTSZY CZAS: "<<(float)(s_min/1000.0)<<endl<<"NAJDLOZSZY CZAS: "<<(float)(s_max/1000.0)<<endl;
        system("pause");
        return 0;
    }
 
    if (score==3)
    {
        lvl=lvl+1;
        score=0;
        unscore=0;
    }
    if (unscore==2)
    {
        if(lvl==1){
        }
        else{
            lvl=lvl-1;
        }
        score=0;
        unscore=0;
    }
    play(lvl, score, unscore, lvl, sum_s, maps, map1, map2, map3, map4, map5, map6, all, s_max, s_min);
}
 
void endlines(){
    cout<<endl<<endl<<endl<<endl<<endl;
}
 
 
int main()
{
    inst();
    system("pause");
    endlines();
    srand(time(NULL));
    int score=0;
    int unscore=0;
    play(1, score, unscore, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
 
    return 0;
}
