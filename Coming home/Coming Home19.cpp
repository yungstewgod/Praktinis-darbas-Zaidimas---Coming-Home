#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <list>
#include <iostream>
#include <fstream>

using namespace std;

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
string failas;
string Slapyvardis;
int a, b;
string line;
int pasirinkimas;
int shop;
int hp=2;
int shields=2;
int score=0;
bool Lygiai[3] = {false,false,false};
bool Atrakintas[2] = {false, false};

void gotoxy(int x, int y)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hCon, dwPos);
}

void HideCursor()
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = false;
	SetConsoleCursorInfo(hCon,&cci);
}
void FailoSpausdinimas()
{
    string linija;
    ifstream myfile (failas);
  if (myfile.is_open())
  {
    while ( getline (myfile,linija) )
    {
      cout << linija << endl;
    }
    myfile.close();
  }
}

void RibaLinija(int a_x, int a_y, int b_x, int b_y)
{
	for(int i = a_x; i < b_x; i++)
	{
		for(int j = a_y; j < b_y; j++)
		{
			gotoxy(i,j); printf(" ");
		}
	}
}

void RibaPiesimas(int a_x, int a_y, int b_x, int b_y)
{
	RibaLinija(a_x, a_y, b_x, b_y);
	for(int i = a_x; i < b_x; i++)
	{
		gotoxy(i, a_y); printf("%c",205);
		gotoxy(i, b_y); printf("%c",205);
	}
	for(int i = a_y; i < b_y; i++)
	{
		gotoxy(a_x, i); printf("%c",186);
		gotoxy(b_x, i); printf("%c",186);
	}
	gotoxy(a_x, a_y); printf("%c", 201);
	gotoxy(b_x, a_y); printf("%c", 187);
	gotoxy(a_x, b_y); printf("%c", 200);
	gotoxy(b_x, b_y); printf("%c", 188);
}

void ZaidimoRiba()
{
	gotoxy(30,1); printf("Gyvybiu:");
	gotoxy(50,1); printf("Apsaugos sistema:");
	gotoxy(80,1); printf("Taskai:");
}
void KosmosoHudas()
{
    gotoxy(10,1); printf("Vardas:");
    gotoxy(30,1); printf("Gyvybiu:");
	gotoxy(50,1); printf("Apsaugos sistema:");
	gotoxy(80,1); printf("Taskai:");
}


void Intro()
{
failas =  "Logo1.txt";
FailoSpausdinimas();
gotoxy(35,22); printf("[ Noredami testi spauskite bet kuri mygtuka ]");

}
void Istorija(string Slapyvardis)
{
    failas = "Logo1.txt";
    FailoSpausdinimas();

	system("cls");
	failas="istorija1.txt";
    FailoSpausdinimas();
	Sleep(500);
}

void Pralaimejimas()
{
    system("CLS");
	RibaPiesimas(36,10,75,15);
	gotoxy(45,11); printf("*Erdvelaivis sprogo*");
    gotoxy(38,13); printf("Nenusiminkite ir bandykite is naujo");
}

class SpaceShip
{
private:
	int x, y;
	bool DroneDead;
public:
	int X() {return x;}
	int Y() {return y;}
	int HP() {return hp;}

SpaceShip(int _x, int _y)
{
	x = _x;
	y = _y;
	DroneDead = false;

}
bool isDead()
{
	DrawSpaceShipInfo();
    return DroneDead;


}




void DrawSpaceShipInfo()
{
	gotoxy(35, 1); printf(" ");
	gotoxy(38, 1); cout << hp << endl;
	gotoxy(55,1); printf(" ");
	gotoxy(70,1); cout << shields << endl;
}


void Draw()
{
	if(a == 1)
	{
    gotoxy(x,y);		printf( "  %c  ", 94);
	gotoxy(x,y + 1);	printf( " %c%c%c", 124, 223, 124);
	gotoxy(x,y + 2);	printf( "%c%c %c%c", 47, 124, 124, 92);
	gotoxy(x,y + 3);    printf("%c%c%c%c%c",223, 223, 223, 223, 223);
	gotoxy(x,y + 4);	printf( "%c   %c", 94, 94);
	}
	else if(a==2)
	{
	gotoxy(x,y);		printf( "  %c  ", 94);
	gotoxy(x,y + 1);	printf( " %c%c%c", 124, 223, 124);
	gotoxy(x,y + 2);	printf( "%c%c %c%c", 47, 124, 124, 92);
	gotoxy(x,y + 3);    printf("%c%c%c%c%c",223, 223, 223, 223, 223);
	gotoxy(x,y + 4);	printf( "%c   %c", 94, 94);
	}
	else
	{
	gotoxy(x,y);		printf( "  %c  ", 94);
	gotoxy(x,y + 1);	printf( " %c%c%c", 124, 223, 124);
	gotoxy(x,y + 2);	printf( "%c%c %c%c", 47, 124, 124, 92);
	gotoxy(x,y + 3);    printf("%c%c%c%c%c",223, 223, 223, 223, 223);
	gotoxy(x,y + 4);	printf( "%c   %c", 94, 94);
	}
}

void Erase()
{
	gotoxy(x,y); 		printf("     ");
	gotoxy(x,y + 1);	printf("     ");
	gotoxy(x,y + 2); 	printf("     ");
}

void Damage()
{
    shields--;
	if(shields == 0)
	{
		Explosion();
	}
	else
	{
		Erase();
		gotoxy(x,y); 		printf("  *  ");
		gotoxy(x,y + 1);	printf("*   *");
		gotoxy(x,y + 2);	printf("*   *");
		gotoxy(x,y + 3);	printf("******");
		Sleep(100);
	}
}
void Explosion()
{
	hp--;
	Erase();
	gotoxy(x,y); 			printf("  *  ");
	gotoxy(x,y + 1); 		printf(" * * ");
	gotoxy(x,y + 2); 		printf(" * * ");
	gotoxy(x,y + 3);		printf("*****");
	Sleep(80);
	Erase();
	gotoxy(x,y);			printf(" * * ");
	gotoxy(x,y + 1);		printf("* * *");
	gotoxy(x,y + 2); 		printf(" * * ");
	Sleep(80);
	Erase();
	gotoxy(x,y);			printf("*   *");
	gotoxy(x,y + 1);		printf(" * * ");
	gotoxy(x,y + 2);		printf("* * *");
	Sleep(80);
	if(hp > 0)
	{
		shields = 1;
	}
	else
	{
		DroneDead = true;
	}
}
void Move()
{
	if(kbhit())
	{
		Erase();
		char key = getch();
		switch(key)
		{
			case LEFT: 	if(x > 2)	   	x -= 1; break;
			case RIGHT: if(x + 4 < 77) 	x += 1; break;
			case UP: 	if(y > 3)		y -= 1; break;
			case DOWN: 	if(y + 2 < 22)	y += 1; break;
			default:
				break;
		}
	}
	Draw();
}
};

class Asteroid
{
private:
	int x;
	int y;
public:
	int X()
	 {
        return x;
     }
	int Y()
	 {
    return y;
     }


Asteroid(int _x, int _y)
{
	x = _x;
	y = _y;
}

void Draw()
{
	gotoxy(x,y); printf("%c", 254);
}

void Collision(SpaceShip &ss)
{
	if(((x >= ss.X()) && (x <= ss.X() + 5)) && ((y >= ss.Y()) && (y <= ss.Y() + 4)))
	{
		ss.Damage();
		gotoxy(x,y); printf(" ");
		x = rand()%74 + 3;
		y = 4;
	}
	else
	{
		gotoxy(x,y); printf(" ");
		y++;
		if(y > 22)
		{
			x = rand()%74 + 3;
			y = 4;
		}
		Draw();
	}
}
};


class Bullet
{
private:
	int x;
	int y;
public:
	int X() {return x;}
	int Y() {return y;}
Bullet(int _x, int _y)
{
	x = _x;
	y = _y;
}
bool isOut()
{
	if(y <= 3)
	{
		gotoxy(x,y); printf(" ");
		return true;
	}
	else
	{
		return false;
	}
}
void Move()
{

    y--;
	gotoxy(x,y); printf("|");
}
};

void menu()
{
    failas = "Meniu.txt";
    FailoSpausdinimas();
	cin >> pasirinkimas;
}
void LygiuPasirinkimas()
{
    failas = "Lygiai.txt";
    FailoSpausdinimas();

}
void GameLevel3(bool Lygiai[])
{
	Lygiai[3] = true;
    RibaPiesimas(25,11,92,15);
    gotoxy(26,12);  printf(" Nuejote ilga kelia ir sugebejote padaryti neimanoma");
    gotoxy(26,13); printf(" Isgyvenote Saturno ir Jupiterio asteroidu audras");
    gotoxy(26,14); printf(" Erdvelaivis yra stipriai apgadintas ir daugiau smugiu neatlaikys");
    Sleep(5000);
    system("CLS");
     RibaPiesimas(25,11,94,15);
    gotoxy(26,12); printf (" Jusu bukle darosi kritine, nuo skausmo sunku mastyti ir judeti");
    gotoxy(26,13); printf(" Suprantate, jog jums liko praskristi paskutine planeta Marsa");
    gotoxy(26,14); printf(" Ir toliau jusu lauks rami kelione namo, AR SUGEBESITE TAI PADARYTI?");

    Sleep(5000);
    system("CLS");


	list<Bullet*> Bullets;
	list<Bullet*>::iterator bullet;

	list<Asteroid*> Asteroids;
	list<Asteroid*>::iterator asteroid;

	for(int i = 0; i < 9; i++)
	{
		Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
	}

	SpaceShip ss = SpaceShip(40,20);


	while(!ss.isDead() && score != 4)
	{
        ZaidimoRiba();
		if(kbhit())
		{
			char key = getch();
			if(key == ' ')
			{
				Bullets.push_back(new Bullet(ss.X() + 2, ss.Y() - 1));
			}
		}
		for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
		{
			(*bullet)->Move();
			if((*bullet)->isOut())
			{
				delete (*bullet);
				bullet = Bullets.erase(bullet);
			}
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			(*asteroid)->Collision(ss);
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
			{
				int astX = (*asteroid)->X();
				int astY = (*asteroid)->Y();
				int bulX = (*bullet)->X();
				int bulY = (*bullet)->Y();
				if((astX == bulX) && ((astY == bulY) || (astY + 1 == bulY)))
				{
					gotoxy(bulX,bulY); printf(" ");
					gotoxy(astX,astY); printf("X"); printf(" ");
					delete (*bullet);
					bullet = Bullets.erase(bullet);
					delete (*asteroid);
					asteroid = Asteroids.erase(asteroid);
					Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
					score++;
				}
			}
		}
		ss.Move();
		gotoxy(90,1); printf("%d", score);
		Sleep(80);
		system("CLS");
	}
	if(!ss.isDead())
	{
system("CLS");
    RibaPiesimas(25,11,90,14);
    gotoxy(26,12); printf(" Jums pavyko isgyventi pavojingiausiu planetu asteroidu audras");
    gotoxy(26,13); printf(" Pagaliau jusu laukia rami kelione namo...");
    Sleep(5000);
		system("CLS");
    RibaPiesimas(25,11,90,15);
    gotoxy(26,12); printf(" Taciau esate per silpnas testi kelione namo..");
    gotoxy(26,13); printf(" Is paskutiniu jegu irasote atsisveikinimo irasa savo seimai");
    gotoxy(26,14); printf(" Ir uzmerke akis, uzmiegate amziams..");
    Sleep(7000);
		system("CLS");
		RibaPiesimas(20,11,92,17);
		gotoxy(46,12); printf(" Pabaiga");
		gotoxy(35,13); cout << "Uzbaigete zaidima" << " 'Coming Home' "<< endl;
		gotoxy(21,14); cout << "---------------------------------------------------------------------"<< endl;
        gotoxy(21,15); cout << "Jei zaidimas jus sudomino tada isbandykite - Kosmoso karaliaus rezima"<< endl;
        gotoxy(21,16); cout << "Jame jusu tikslas surinkti kuo daugiau tasku naikinant asteroidus "<< endl;
        Sleep(8000);
		system("CLS");
		menu();
	}
	else
	{
		Pralaimejimas();
		Sleep(5000);
		system("CLS");
		menu();
	}
}
void GameLevel2(bool Lygiai[])
{
	Lygiai[2] = true;

 	RibaPiesimas(29,11,85,15);
    gotoxy(30,12); printf(" Isgyvenote Saturno keliama pavoju");
    gotoxy(30,13); printf(" Taciau supratote, jog dar nereiketu dziaugtis");
    gotoxy(30,14); printf(" Kelias namo tapo trumpesnis, bet dar pavojingesnis");
    Sleep(5000);
    system("CLS");

	list<Bullet*> Bullets;
	list<Bullet*>::iterator bullet;

	list<Asteroid*> Asteroids;
	list<Asteroid*>::iterator asteroid;

	for(int i = 0; i < 7; i++)
	{
		Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
	}

	SpaceShip ss = SpaceShip(40,20);


	while(!ss.isDead() && score != 3)
	{
        ZaidimoRiba();
		if(kbhit())
		{
			char key = getch();
			if(key == ' ')
			{
				Bullets.push_back(new Bullet(ss.X() + 2, ss.Y() - 1));
			}
		}
		for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
		{
			(*bullet)->Move();
			if((*bullet)->isOut())
			{
				delete (*bullet);
				bullet = Bullets.erase(bullet);
			}
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			(*asteroid)->Collision(ss);
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
			{
				int astX = (*asteroid)->X();
				int astY = (*asteroid)->Y();
				int bulX = (*bullet)->X();
				int bulY = (*bullet)->Y();
				if((astX == bulX) && ((astY == bulY) || (astY + 1 == bulY)))
				{
					gotoxy(bulX,bulY); printf(" ");
					gotoxy(astX,astY); printf("X"); printf(" ");
					delete (*bullet);
					bullet = Bullets.erase(bullet);
					delete (*asteroid);
					asteroid = Asteroids.erase(asteroid);
					Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
					score++;
				}
			}
		}
		ss.Move();
		gotoxy(90,1); printf("%d", score);
		Sleep(80);
		system("CLS");
	}
	if(!ss.isDead())
	{
		GameLevel3(Lygiai);
	}
	else
	{
		Pralaimejimas();
		Sleep(5000);
		system("CLS");
		menu();
	}
}

void GameLevel1(bool Lygiai[])
{
	Lygiai[1] = true;
	failas = "LVL1.txt";
    FailoSpausdinimas();
    Sleep(5000);
 	system("CLS");

    RibaPiesimas(29,11,85,15);
    gotoxy(30,12); printf(" Nuo sprogimo ir jo sukeltos audros praradote samone");
    gotoxy(30,13); printf(" Atsipeikeje supratote, jog esate salia Saturno");
    gotoxy(30,14); printf(" Ir kelias namo laukia ilgas ir pavojingas");
    Sleep(5000);
    system("CLS");


	list<Bullet*> Bullets;
	list<Bullet*>::iterator bullet;

	list<Asteroid*> Asteroids;
	list<Asteroid*>::iterator asteroid;

	for(int i = 0; i < 5; i++)
	{
		Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
	}

	SpaceShip ss = SpaceShip(40,20);



	while(!ss.isDead() && score != 2)
	{
        ZaidimoRiba();
		if(kbhit())
		{
			char key = getch();
			if(key == ' ')
			{
			 Bullets.push_back(new Bullet( ss.X() + 2, ss.Y() - 1));


			}
		}
		for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
		{
			(*bullet)->Move();
			if((*bullet)->isOut())
			{
				delete (*bullet);
				bullet = Bullets.erase(bullet);
			}
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			(*asteroid)->Collision(ss);
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
			{
				int astX = (*asteroid)->X();
				int astY = (*asteroid)->Y();
				int bulX = (*bullet)->X();
				int bulY = (*bullet)->Y();

				if((astX == bulX) && ((astY == bulY) || (astY + 1 == bulY)))
				{
					gotoxy(bulX,bulY); printf(" ");
					gotoxy(astX,astY); printf("X"); printf(" ");
					delete (*bullet);
					bullet = Bullets.erase(bullet);
					delete (*asteroid);
					asteroid = Asteroids.erase(asteroid);
					Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
					score++;
				}
			}
		}
		ss.Move();
		gotoxy(90,1); printf("%d", score);
		Sleep(100);
		system("CLS");
	}
	if(!ss.isDead())
	{
		system("CLS");
		GameLevel2(Lygiai);
	}
	else
	{
		Pralaimejimas();
		Sleep(3000);
		system("CLS");
		menu();
	}
}


void KosmosoKaralius2(bool Atrakintas[])
{

    int lygis;
       system("CLS");
       LygiuPasirinkimas();
       cout << endl;
       cout << "Pasirinkite viena is galimu lygiu" << endl;
       cin>>lygis;

                 if(lygis == 2)
       {
           Atrakintas[1]=true;
            system("CLS");
    RibaPiesimas(29,11,80,15);
    gotoxy(30,12); printf(" Noredami pradeti irasykite savo vartojo varda:");
    gotoxy(31,14); 	cin >> Slapyvardis;
    system("CLS");
    Lygiai[2] = true;

	list<Bullet*> Bullets;
	list<Bullet*>::iterator bullet;

	list<Asteroid*> Asteroids;
	list<Asteroid*>::iterator asteroid;

	for(int i = 0; i < 7; i++)
	{
		Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
	}

	SpaceShip ss = SpaceShip(40,20);


	while(!ss.isDead())
	{
        KosmosoHudas();
		if(kbhit())
		{
			char key = getch();
			if(key == ' ')
			{
				Bullets.push_back(new Bullet(ss.X() + 2, ss.Y() - 1));
			}
		}
		for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
		{
			(*bullet)->Move();
			if((*bullet)->isOut())
			{
				delete (*bullet);
				bullet = Bullets.erase(bullet);
			}
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			(*asteroid)->Collision(ss);
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
			{
				int astX = (*asteroid)->X();
				int astY = (*asteroid)->Y();
				int bulX = (*bullet)->X();
				int bulY = (*bullet)->Y();
				if((astX == bulX) && ((astY == bulY) || (astY + 1 == bulY)))
				{
					gotoxy(bulX,bulY); printf(" ");
					gotoxy(astX,astY); printf("X"); printf(" ");
					delete (*bullet);
					bullet = Bullets.erase(bullet);
					delete (*asteroid);
					asteroid = Asteroids.erase(asteroid);
					Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
					score++;
				}
			}
		}
		ss.Move();
		gotoxy(18,1); cout << Slapyvardis;
		gotoxy(90,1); cout << score;
		Sleep(80);
		system("CLS");
		}
	if (ss.isDead())
	{
		Pralaimejimas();
		Sleep(1000);
		system("CLS");
		if(hp==0 && shields == 0)
        {
            hp=hp+2;
            shields=shields+2;

        }
        menu();

	}



}

}
void KosmosoKaralius3(bool Atrakintas[])
{
     int lygis;
       system("CLS");
       LygiuPasirinkimas();
       cout << endl;
       cout << "Pasirinkite viena is galimu lygiu" << endl;
       cin>>lygis;

                 if(lygis == 3)
                Atrakintas[2]=true;
       {

    system("CLS");
    RibaPiesimas(29,11,80,15);
    gotoxy(30,12); printf(" Noredami pradeti irasykite savo vartojo varda:");
    gotoxy(31,14); 	cin >> Slapyvardis;
    system("CLS");
	Lygiai[3] = true;

	list<Bullet*> Bullets;
	list<Bullet*>::iterator bullet;

	list<Asteroid*> Asteroids;
	list<Asteroid*>::iterator asteroid;

	for(int i = 0; i < 9; i++)
	{
		Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
	}

	SpaceShip ss = SpaceShip(40,20);


	while(!ss.isDead() && score <=3)
	{
        KosmosoHudas();
		if(kbhit())
		{
			char key = getch();
			if(key == ' ')
			{
				Bullets.push_back(new Bullet(ss.X() + 2, ss.Y() - 1));
			}
		}
		for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
		{
			(*bullet)->Move();
			if((*bullet)->isOut())
			{
				delete (*bullet);
				bullet = Bullets.erase(bullet);
			}
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			(*asteroid)->Collision(ss);
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
			{
				int astX = (*asteroid)->X();
				int astY = (*asteroid)->Y();
				int bulX = (*bullet)->X();
				int bulY = (*bullet)->Y();
				if((astX == bulX) && ((astY == bulY) || (astY + 1 == bulY)))
				{
					gotoxy(bulX,bulY); printf(" ");
					gotoxy(astX,astY); printf("X"); printf(" ");
					delete (*bullet);
					bullet = Bullets.erase(bullet);
					delete (*asteroid);
					asteroid = Asteroids.erase(asteroid);
					Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
					score++;
				}
			}
		}
		ss.Move();
		gotoxy(18,1); cout << Slapyvardis;
		gotoxy(90,1); cout << score;
		Sleep(80);
		system("CLS");
	}
	system("CLS");
	gotoxy(40,15); cout << "Taskai dvigubinasi !!";
	{
	    Sleep(500);
	}
	while(!ss.isDead() && score >=2)
	{


        KosmosoHudas();
		if(kbhit())
		{
			char key = getch();
			if(key == ' ')
			{
				Bullets.push_back(new Bullet(ss.X() + 2, ss.Y() - 1));
			}
		}
		for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
		{
			(*bullet)->Move();
			if((*bullet)->isOut())
			{
				delete (*bullet);
				bullet = Bullets.erase(bullet);
			}
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			(*asteroid)->Collision(ss);
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
			{
				int astX = (*asteroid)->X();
				int astY = (*asteroid)->Y();
				int bulX = (*bullet)->X();
				int bulY = (*bullet)->Y();
				if((astX == bulX) && ((astY == bulY) || (astY + 1 == bulY)))
				{
					gotoxy(bulX,bulY); printf(" ");
					gotoxy(astX,astY); printf("X"); printf(" ");
					delete (*bullet);
					bullet = Bullets.erase(bullet);
					delete (*asteroid);
					asteroid = Asteroids.erase(asteroid);
					Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
					score=score+2;
				}
			}
		}
		ss.Move();
		gotoxy(18,1); cout << Slapyvardis;
		gotoxy(90,1); cout << score;
		Sleep(80);
		system("CLS");
	}
	if(ss.isDead())
	{
		Pralaimejimas();
		Sleep(1000);
		system("CLS");
		if(hp==0 && shields == 0)
        {
            hp=hp+2;
            shields=shields+2;

        }
		menu();

	}

}
}

void Parduotuve()
{
    system("CLS");
    failas = "Parduotuve.txt";
    FailoSpausdinimas(); cout << endl;
}


void Start()
{
   	HideCursor();
	Intro();
	getch();
	system("CLS");

	Istorija(Slapyvardis);
    Sleep (500);
	system("CLS");

	menu();

	system("CLS");

while(0<=1)
{
	if(pasirinkimas == 1 )
	{
		system("CLS");

			if(!Lygiai[1])
			{
				GameLevel1(Lygiai);
			}
			else if(!Lygiai[2])
			{
                RibaPiesimas(30,11,55,16);
                gotoxy(31,12); printf(" Nori pagerinti drona?");
                gotoxy(31,13); printf(" Pirma karta nemokamai.");
                gotoxy(31,14); printf("    1. Taip 2. Ne");
				gotoxy(41,15);cin >> b;
				if(b == 1)
				{
					a=1;
					GameLevel2(Lygiai);
				}
				else
				{
					GameLevel2(Lygiai);
				}
			}
			else if(!Lygiai[3])
			{
				GameLevel3(Lygiai);
			}

	}
	else if(pasirinkimas == 2)
	{

	    int lygis;
       system("CLS");
       LygiuPasirinkimas();
       cout << endl;
       cout << "Pasirinkite viena is galimu lygiu" << endl;
       cin>>lygis;

       if(lygis == 1)
       {

    system("CLS");
    RibaPiesimas(29,11,80,15);
    gotoxy(30,12); printf(" Noredami pradeti irasykite savo vartojo varda:");
    gotoxy(31,14); 	cin >> Slapyvardis;
    system("CLS");
	list<Bullet*> Bullets;
	list<Bullet*>::iterator bullet;

	list<Asteroid*> Asteroids;
	list<Asteroid*>::iterator asteroid;

	for(int i = 0; i < 5; i++)
	{
		Asteroids.push_back(new Asteroid(rand()%80, rand()%10));
	}

	SpaceShip ss = SpaceShip(40,20);


	while(!ss.isDead())
	{

        KosmosoHudas();
		if(kbhit())
		{
			char key = getch();
			if(key == ' ')
			{
				Bullets.push_back(new Bullet(ss.X() + 2, ss.Y() - 1));
			}
		}
		for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
		{
			(*bullet)->Move();
			if((*bullet)->isOut())
			{
				delete (*bullet);
				bullet = Bullets.erase(bullet);
			}
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			(*asteroid)->Collision(ss);
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
			{
				int astX = (*asteroid)->X();
				int astY = (*asteroid)->Y();
				int bulX = (*bullet)->X();
				int bulY = (*bullet)->Y();

				if((astX == bulX) && ((astY == bulY) || (astY + 1 == bulY)))
				{
					gotoxy(bulX,bulY); printf(" ");
					gotoxy(astX,astY); printf("X"); printf(" ");
					delete (*bullet);
					bullet = Bullets.erase(bullet);
					delete (*asteroid);
					asteroid = Asteroids.erase(asteroid);
					Asteroids.push_back(new Asteroid(rand()%80,rand()%10));
					score++;
				}
			}
		}
		ss.Move();
		gotoxy(18,1); cout << Slapyvardis;
		gotoxy(38,1); cout << hp;
		gotoxy(70,1); cout << shields;
		gotoxy(90,1); cout << score;
		Sleep(100);
		system("CLS");
	}
	if(ss.isDead())
	{
		Pralaimejimas();
		Sleep(1000);
		system("CLS");
		if(hp==0 && shields == 0)
        {
            hp=hp+2;
            shields=shields+2;

        }
        menu();
	}
       }

     else if(lygis == 2)
     {


                system("CLS");
                RibaPiesimas(30,12,82,16);
                gotoxy(31,14); printf(" Noredami zaisti Jupiteryje turite ji atrakinti !");
                Sleep(2000);
                system("CLS");
                menu();

     }
      else if(lygis == 3)

      {
          system("CLS");
          RibaPiesimas(30,12,82,16);
          gotoxy(31,14); printf("Noredami zaisti Marse turite ji atrakinti !");
          Sleep(2000);
          system("CLS");
          menu();
      }
	}


	else if(pasirinkimas == 3)
	{
	    system("CLS");
        Parduotuve();
        cout << "Jusu (Gyvybes: " << hp << ") (Taskai: " << score << ") (Skydai: " << shields << ")" << endl;
		cin >> shop;


		if(shop == 1)
		{
			if(score == 0)
			{
			    RibaPiesimas(30,11,65,13);
                gotoxy(31,12); printf(" Deja, pirkiniui neuztenka tasku. ");
				Sleep(1000);
				system("CLS");
				menu();
			}
			else
			{
				hp++;
				score--;
				system("CLS");
				menu();
			}
		}
		else if(shop == 2)
		{
			if(score == 0)
			{
			    RibaPiesimas(30,11,65,13);
                gotoxy(31,12); printf(" Deja, pirkiniui neuztenka tasku. ");
				Sleep(1000);
				system("CLS");
				menu();
			}
			else
			{
				shields++;
				score--;
				system("CLS");
				menu();
			}
		}
		else if(shop == 3)
        {
            if(score >= 2)
            {
                system("CLS");
                RibaPiesimas(38,12,73,14);
                gotoxy(43,13); printf(" Atrakinote Jupiteri !");
                score=score-2;
                Atrakintas[1] = true;
				Sleep(1000);
				system("CLS");
				menu();
				if(pasirinkimas == 2)
                {
	    int lygis;
       system("CLS");
       LygiuPasirinkimas();
       cout << endl;
       cout << "Pasirinkite viena is galimu lygiu" << endl;
       cin>>lygis;

                 if(lygis == 2)
             {

                while(pasirinkimas == 2 && lygis == 2)
                {
                    KosmosoKaralius2(Atrakintas);
                }
            }
                }

            }
            else
            {
                 system("CLS");
                RibaPiesimas(38,12,73,14);
                gotoxy(39,13); printf(" Deja, neuztenka tasku atrakinti Jupiteri. ");
				Sleep(1000);
				system("CLS");
				menu();

            }

            }
            else if(shop == 4)
            {

                if(score >= 4)
            {
                system("CLS");
                RibaPiesimas(38,12,73,14);
                gotoxy(43,13); printf(" Atrakinote Marsa !");
                score=score-4;
                Atrakintas[2] = true;
				Sleep(1000);
				system("CLS");
				menu();
				if(pasirinkimas == 2)
                {
	    int lygis;
       system("CLS");
       LygiuPasirinkimas();
       cout << endl;
       cout << "Pasirinkite viena is galimu lygiu" << endl;
       cin>>lygis;

                 if(lygis == 3)
             {

                while(pasirinkimas == 2 && lygis == 3)
                {
                    KosmosoKaralius3(Atrakintas);
                }

            }

                }

            }
            else
            {
                 system("CLS");
                RibaPiesimas(38,12,73,14);
                gotoxy(39,13); printf(" Deja, neuztenka tasku atrakinti Marsui ");
				Sleep(1000);
				system("CLS");
				menu();

            }



            }

		else if (shop == 0)
		{
			system("CLS");
			menu();
		}
	}

	else if(pasirinkimas == 5)
	{
		break;
	}
	else if(pasirinkimas < 1 || pasirinkimas > 4)
    {
        cout << "Blogai ivedete pasirinkima!!!"<< endl;
    }

}
}
int main()
{
Start();
return 0;
}
