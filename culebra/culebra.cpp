#include<windows.h>
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define ABAJO 80
#define DERECHA 77
#define ESC 27
#define ENTER 13

int cuerpo[200][2];
int n = 1;
int tan = 7;
int x = 10, y = 12;
int dir = 3;
int xc = 30, yc = 15;
int score = 0;
int velocidad = 100, h=1;
int pos = 1;

char tecla;

void gotoxy(int x, int y){

	HANDLE brayan;
	brayan = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD gomez;
	gomez.X = x;
	gomez.Y = y;

	SetConsoleCursorPosition(brayan, gomez);
}

void OcultarCursor(){
	HANDLE brayan;
	brayan = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO manco;
	manco.dwSize = 50;
	manco.bVisible = FALSE;

	SetConsoleCursorInfo(brayan,&manco);
}

class MENU{

public:
    void pintar_menu(int &a);
};

void MENU::pintar_menu(int &a){

char inicio[50][100] =
{
"                                                                  ",
"         A A           AAAAA  AA   A  AAAA  A A    AAAA           ",
"          A            A      A A  A  A  A  AAA    A              ",
"        AAAAA          A      A  A A  AAAA  A  A   AAAA           ",
"       A AAA A         A      A   AA  A  A  A   A  A              ",
"      AAAAAAAAA    AAAAA      A   AA  A  A  A   A  AAAA           ",
"      AAAAAAAAA                                                   ",
"       AAAAAAA           AAAAAAAAAA            AAAAAAAAAAAA       ",
"       AAAAAAA          AAAAAAAAAAAA          AAAAAAAAAAAAAAA     ",
"        AAAAAAA        AAAAAAAAAAAAAA        AAAAAAAAAAAAAA       ",
"         AAAAAAA      AAAAAA    AAAAAA      AAAAAA                ",
"          AAAAAAA    AAAAAA      AAAAAA    AAAAAA                 ",
"           AAAAAAAAAAAAAAA        AAAAAAAAAAAAAA                  ",
"            AAAAAAAAAAAAA          AAAAAAAAAAAA                   ",
"             AAAAAAAAAAA            AAAAAAAAAA                    ",
};

for(int i = 0; i < 15; i++ ){
    for(int j = 0; j < 66; j++ ){
        gotoxy(j + 5 ,i + 5); printf("%c",inicio[i][j]);
    }
}

a = getch();

for(int i = 0; i < 15; i++ ){
    for(int j = 0; j < 66; j++ ){
        gotoxy(j + 5 ,i + 5); printf(" ");
    }
}

}

void pintar(){

	// lineas horizontales

	for(int i=2; i<78;i++){
		gotoxy(i,3); printf("%c",205);
		gotoxy(i,23); printf("%c",205);
	}

	// lineas verticales

	for(int i=4;i<23;i++){
		gotoxy(2,i); printf("%c", 186);
		gotoxy(77,i); printf("%c", 186);
	}

	gotoxy(2,3); printf("%c", 201);
	gotoxy(2,23); printf("%c", 200);
	gotoxy(77,3); printf("%c", 187);
	gotoxy(77,23); printf("%c", 188);
}

void guardar_posicion(){
    cuerpo[n][0] = x;
    cuerpo[n][1] = y;
    n++;
    if(n == tan ) n = 1;
}

void pintar_cuerpo(){
    for(int i = 1; i < tan; i++){
        gotoxy(cuerpo[i][0], cuerpo[i][1]); printf("*");
    }
}

void borrar_cuerpo(){
    gotoxy(cuerpo[n][0], cuerpo[n][1]); printf(" ");
}

void teclear(){
 if(kbhit()){
        	tecla = getch();
        	switch(tecla){
        		case ARRIBA :

        			if (dir != 2)
        			 dir = 1;
        			 break;

        	    case ABAJO :
        	    	if (dir != 1)
        			 dir = 2;
        			 break;

        	    case DERECHA :
        	    	if (dir != 4)
        			 dir = 3;
        			 break;

        	    case IZQUIERDA :
        	    	if (dir != 3)
        			 dir = 4;
        			 break;
			}
		}
}

void cambiar_velocidad(){
	if(score == h*20) {
		velocidad -= 10;
		h++;
	}
}

void comida(){
	if(x == xc && y == yc){
		xc = (rand()%73) +4;
		yc = (rand()%19) +4;

		tan++;
		score += 10;
		gotoxy(xc,yc); printf("%c",111);

		cambiar_velocidad();
	}
}

bool game_over(){
	if( y == 3  ||  y == 23  ||  x == 2  || x == 77) return false;

	for(int j = tan-1; j > 0; j-- ){
		if(cuerpo[j][0] == x && cuerpo[j][1] == y)
		return false;
	}

	return true;
}


void puntos(){
	gotoxy(3,1); printf("PUNTOS %d", score);
}


int main(){

	OcultarCursor();
	pintar();
	 gotoxy(xc,yc); printf("%c",4);
	 
	int op_juego; 
	MENU M;
	M.pintar_menu(op_juego);
		 
    while(tecla != ESC && game_over()){
        borrar_cuerpo();
        guardar_posicion();
        pintar_cuerpo();
        comida();
        puntos();

        teclear();
        teclear();

        if(dir == 1) y--;
        if(dir == 2) y++;
        if(dir == 3) x++;
        if(dir == 4) x--;

        Sleep(velocidad);
    }

	pintar();
	system("pause>null");
	return 0;
}

