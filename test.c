#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ncurses.h>

#define PARTIE_LINE 3
int port = 8000;
//⁰¹²³⁴⁵⁶⁷⁸⁹⁻

void init_salon()
{
	clear();
	char *msg = "liste de salon: ";
	mvprintw(0,4,"%s",msg);
	mvprintw(1,0,"salle id");
	mvprintw(1,15,"nombre player");
}

int add_room(int i, int num_salle, int nb_player)
{
	if (i >= 20) return 0;
	mvprintw(i+1,0 ,"%d",num_salle);
	mvprintw(i+1,15,"%d",nb_player);
	return 1;
}

void ncurses()
{
	initscr();              
	keypad(stdscr, TRUE);
	raw();
	noecho();
	scrollok(stdscr, TRUE);
	clearok(stdscr, TRUE);
	int row, col;
	getmaxyx(stdscr,row,col);
	int x, y;
	getyx(stdscr, y, x);
	init_salon();
	for (int i = 1; i < 50; ++i)
	{
		add_room(i, i*10, 10);
	}
	do
	{
		int ch = getch();
		getyx(stdscr, y, x);
		if (strcmp(keyname(ch), "^C")==0) {
			printw("%d", ch);
			break;
		}
		//258 = KEY_DOWN 259 = KEY_UP
		else if (ch == 260) move(y,x-1);
		else if (ch == 263) mvdelch(y,x-1);
		else if (ch == 258) scrl(-1);
		else if (ch == 259) scrl(1);
		else {
			printw("%d,%d, %d, %s",y,x, ch, keyname(ch));
		}
		refresh();
	} while (1);
	endwin();
}

void *thread_1(void *arg)
{
	printf("Nous sommes dans le thread.\n");
	printf("Nous sommes dans le thread.\n");
	printf("Nous sommes dans le thread.\n");

    /* Pour enlever le warning */
	(void) arg;
	pthread_exit(NULL);
}

void * launch_UDP_reception(void *descr)
{
	printf("Dans la fonction: %d", *(int*)descr);
}

int stoi(char* buff, int buff_size) {
    if (buff_size > 5) return -1;
    int res = 0, i;
	for(i=0; i<buff_size; i++){
		if (buff[i] > 47 && buff[i]<58) {
			res = res * 10 + ( buff[i] - '0' );
		} else {
			printf("contain: %c\n", buff[i]);
			return -1;
		}
	}
	return res;
}

int getWeight()
{
    return 10;
}

int getHeight()
{
    return 15;
}

int getBlock(int x, int y)
{
    return 0;
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
}

int main(void)
{
	/*
    struct sockaddr_in adress_sock;
    adress_sock.sin_family = AF_INET;
    adress_sock.sin_port = htons(port);
    inet_aton("127.0.0.1",&adress_sock.sin_addr);
    int descr=socket(PF_INET,SOCK_STREAM,0);
    int r=connect(descr,(struct sockaddr *)&adress_sock,sizeof(struct sockaddr_in));
    if(r!=-1){
        printf("You are connected!\n");
    } else{
        printf("Probleme de connexion!\n");
        return -1;
    }

    char buff[2] = {}
    htons(100);
    int16_t result;
	memcpy(&result, buff, sizeof(int16_t));
	result = (int16_t)ntohs((uint16_t)result);
    */
	/*    
    unsigned short num_partie = 12849;
    unsigned char litt[2];
 	unsigned char d0 = (uint)num_partie;
 	litt[0] = (uint)num_partie;
 	litt[1] = (((uint)num_partie >> 8) & 0xFF);
    unsigned char d1 = (((uint)num_partie >> 8) & 0xFF);
    printf("d0:%d, d1:%d, d0|d1:%d, litt[0]:%c, litt[1]:%c",d0, d1, d0|(d1<<8), litt[0], litt[1]);
	*/


	ncurses();

	return 0;
	

} 