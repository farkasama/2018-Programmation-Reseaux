#include "vue.h"

#define ESPACEMENT 15
#define PARTIE_LINE 3
#define ERR_LINE 25
#define INFO_LINE 25
#define ESP_FENETRE2 30
#define RECV_LINE 26
#define MESS_LINE 27

int row, col;
int curPos;
int cur_lim;
int list_partie[20] = {0};

void init_vue()
{
    initscr();              
	keypad(stdscr, TRUE);
	//raw();
	noecho();
	scrollok(stdscr, TRUE);
	clearok(stdscr, TRUE);
	getmaxyx(stdscr,row,col);
}

void end_vue()
{
	endwin();
	printf("BYE!\n");
}

void init_salon()
{
	clear();
	char *msg = "Partie non commence: ";
	mvprintw(1,0,"%s",msg);
	mvprintw(2,0,"salle id");
	mvprintw(2,ESPACEMENT,"nb joueur");
	mvprintw(INFO_LINE,0,"loading...");
	mvprintw(0,0,"Vous etes dans salon");
	curPos = PARTIE_LINE;
	cur_lim = 0;
	curs_set(0);
	refresh();
}

int add_room(int i, int num_salle, int nb_player)
{
    if (!inSalon()) return -1;
	else if (i >= PARTIE_LINE+20) return 0;
    mvprintw(i+PARTIE_LINE,2 ,"%d",num_salle);
    mvprintw(i+PARTIE_LINE,2+ESPACEMENT,"%d",nb_player);
	cur_lim = i+PARTIE_LINE;
	list_partie[i] = num_salle;
	refresh();
    return 1;
}

void cur_up()
{
	if (curPos>PARTIE_LINE) {
		mvprintw(curPos, 0, " ");
		curPos--;
		mvprintw(curPos, 0, ">");
	}
}

void cur_down()
{
	if (curPos<cur_lim) {
		mvprintw(curPos, 0, " ");
		curPos++;
		mvprintw(curPos, 0, ">");
	}
}

void vue_err(char *mess)
{
	clrline(ERR_LINE);
	mvprintw(ERR_LINE, 2, "error: %s", mess);
	refresh();
}

int getPartie()
{
    return list_partie[curPos-PARTIE_LINE];
}

int id_interface(char* buff)
{
	int ch;
	int x,y;
	mvprintw(24, 2, "id(max 8 alpha num):");
	getyx(stdscr, y, x);
	int exit = 0;
	int size = 0;
	int pos = 0;
	int ret = 1;
	curs_set(1);
	while(!exit)
	{
		getyx(stdscr, y, x);			
		ch = getch();
		if (ch == 10){ //ENTER
			if (size == 0) {
				ret = 0;
				exit = 1;
			}
			else {
				exit = 1;
			}
		} else if (ch == 3) return -1;
		else if ( 
			size<8 && ((ch >= 48 && ch <= 57) ||
			(ch >= 65 && ch <= 90) ||
			(ch >= 97 && ch <= 122))
		) {
			buff[pos] = *keyname(ch);
			addch(ch);
			pos ++;
			size++;
		} else if (ch == 263 && pos>0) {
			pos--;
			size--;
			mvdelch(y, x-1);
		} else if (ch == 260 && pos>0) {
			pos--;
			move(y,x-1);
		} else if (ch == 261 && pos<size) {
			pos ++;
			move(y,x+1);
		}
	}
	buff[size] = '\0';
	curs_set(0);
	clrline(24);
	return ret;
}

void clrline(int i)
{
	move(i, 0);
	clrtoeol();
	refresh();
}

void salon_cur()
{
	mvprintw(PARTIE_LINE, 0, ">");
	refresh();
}

void clr_err()
{
	clrline(ERR_LINE);
}

void vue_info(char *mess)
{
	clrline(INFO_LINE);
	mvprintw(INFO_LINE, 2, "%s", mess);
	refresh();
}

void init_room()
{
	clear();
	//mvprintw(2,ESP_FENETRE2,"liste de joueur:");
	//mvprintw(INFO_LINE,0,"loading...");
	mvprintw(0,0,"Inscrit partie id: %d", getGameId());
	curPos = PARTIE_LINE;
	cur_lim = 0;
	curs_set(0);
	refresh();
}

void clr_f2()
{
	for(int i = 0; i<23; i++)
	{
		move(i, ESP_FENETRE2);
		clrtoeol();
	}
	refresh();
}

void vue_recv(char *mess)
{
	clrline(RECV_LINE);
	mvprintw(RECV_LINE, 2, "%s", mess);
	refresh();
}

void add_player(int i, char *id)
{
	mvprintw(i+PARTIE_LINE, ESP_FENETRE2+2,"%s", id);
	refresh();
}

void vue_size(int height, int weight)
{
	mvprintw(2, ESP_FENETRE2, "height: %d, weight: %d", height, weight);
	refresh();
}

void vue_mess(char *id, char *mess)
{
	mvprintw(MESS_LINE, 0, "%s: %s", id, mess);
	refresh();
}

void init_game()
{
	clear();
	mvprintw(0,0,"En game id: %d", getGameId());
	mvprintw(1,0,"Nombre Fantom: %d", getFantom());
	mvprintw(2,0,"Votre socre: %d", 0);
	//mvprintw(2,ESP_FENETRE2,"liste de joueur:");
	curPos = PARTIE_LINE;
	cur_lim = 0;
	vue_labyrinthe();
	curs_set(0);
	refresh();
}

void vue_labyrinthe()
{
	move(PARTIE_LINE, 2);	
	for(int j=0; j<getWeight()+2; j++)
	{
		printw("+");
	}


	for(int i = 0; i<getHeight(); i++)
	{
		move(PARTIE_LINE+1+i, 2);
		printw("+");
		for(int j=0; j<getWeight(); j++)
		{
			if (getBlock(j,i) == 1) printw("+");
			else printw(" ");
		}
		printw("+");
	}

	move(PARTIE_LINE+getHeight(), 2);	
	for(int j=0; j<getWeight()+2; j++)
	{
		printw("+");
	}

	mvprintw(getPosY()+PARTIE_LINE+1,getPosX()+2+1, "Y");
}

void vue_setFan(int posX, int posY, const char *f)
{
	mvprintw(posY + PARTIE_LINE+1, posX+2+1, "%s", f);
}

void vue_setSCOR(char *id, int point, int posX, int posY)
{
	move(2, ESP_FENETRE2);
	clrtoeol();
	mvprintw(2, ESP_FENETRE2, "%s catch f at %d,%d;p: %d", id, posX, posY, point);
}

void vue_newSCOR(int point)
{
	mvprintw(2,0,"Votre socre: %d", point);
	refresh();
}

int vue_getMess(char *buff)
{
	int ch;
	int x,y;
	mvprintw(28, 2, "votre message(max 200 alpha|num|espace):");
	getyx(stdscr, y, x);
	int exit = 0;
	int size = 0;
	int pos = 0;
	int ret = 1;
	curs_set(1);
	while(!exit)
	{
		getyx(stdscr, y, x);			
		ch = getch();
		if (ch == 10){ //ENTER
			if (size == 0) {
				ret = 0;
				exit = 1;
			}
			else {
				exit = 1;
			}
		} else if (ch == 3) return -1;
		else if ( 
			size<200 && ((ch >= 48 && ch <= 57) ||
			(ch >= 65 && ch <= 90) ||
			(ch >= 97 && ch <= 122))
		) {
			buff[pos] = *keyname(ch);
			addch(ch);
			pos ++;
			size++;
		} else if (ch == 263 && pos>0) {
			pos--;
			size--;
			mvdelch(y, x-1);
		} else if (ch == 260 && pos>0) {
			pos--;
			move(y,x-1);
		} else if (ch == 261 && pos<size) {
			pos ++;
			move(y,x+1);
		}
	}
	buff[size] = '\0';
	curs_set(0);
	clrline(28);
	clrline(29);
	clrline(30);
	return ret;
}