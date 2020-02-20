#include "controler.h"

#define BUFF_SIZE 100

int init_controler()
{
    init_vue();
	load_salon();
    return 1;
}

void* launch_game(void * ptr)
{
	pthread_t multicast_recep;	
	do
	{
		int ch = getch();
		if (strcmp(keyname(ch), "^C")==0) {
			end_vue();
			return NULL;
		}
		if (inSalon()){
			clr_err();
			if (ch == 258) { // KEY_DOWN
				cur_down();
			} else if (ch == 259) { // KEY_UP
				cur_up();
			} else if (ch == 110 || ch == 78) {	//[nN]: new
				load_new();
			} else if (ch == 10) {	// enter : REG
				load_reg();
			} else if (ch == 114 || ch == 82) { //[rR]: refresh -> GAMES?
				out_games();
				load_salon();
			} else if (ch == 113 || ch == 81){ //[qQ] -> quit
				return NULL;
			} else if (ch == 108 || ch == 76){//[lL] -> LIST?
				controler_list();
			} else if (ch == 115 || ch == 83) {//[sS] -> SIZE?
				controler_size();
			}
		} else if (inRoom()){
			if (ch == 113 || ch == 81){ //[qQ] -> unreg
				controler_unreg();
			} else if (ch == 114 || ch == 82) { //[rR]: refresh -> LIST?
				controler_list();
			} else if (ch == 115 || ch == 83) {//[sS] -> SIZE?
				controler_size();
			} else if (ch == 10) {	// enter : REG
				out_start();
				wait_start();
				pthread_create(&multicast_recep,NULL, multicast_reception, NULL);
			}
		} else if (inGame()){
			if (ch == 113 || ch == 81){ //[qQ] -> QUIT
				controler_quit();
			} else if (ch == 114 || ch == 82) { //[rR]: refresh -> GLIST?
				controler_glist();
			} else if (ch == 258) { // KEY_DOWN
				controler_down();
			} else if (ch == 259) { // KEY_UP
				controler_up();
			} else if (ch == 260) { // KEY_LEFT
				controler_left();
			} else if (ch == 261) { // KEY_RIGHT
				controler_right();
			} else if (ch == 10) {	// enter : all mess
				controler_all();
			} else if (ch == 115 || ch == 83) { // [sS]
				controler_send();
			}
			vue_labyrinthe();
			refresh();
		} else {
			end_vue();
			return NULL;
		}

		//258 = KEY_DOWN 259 = KEY_UP
		//if (ch == 258) scrl(-1);
		//else if (ch == 259) scrl(1);

		
		refresh();
	} while (1);
}

int load_salon()
{
	setStatus(SALON);
	init_salon();
	char buff[BUFF_SIZE];
    int nb_games;
    int r;
	while (1)
    {   
		r = get_message(buff,BUFF_SIZE);
		if (r == 0) {
			vue_err("No sig of server. Plz press r to refresh");
			return 0;
		} else if (r == -1) {
			exit_prog("Le server a fermer la co.\n", 0);			
			return -1;
		}
		nb_games = get_games(buff);
        if (nb_games > 0) {
			break;
		} else if (nb_games == 0) vue_info("No game, plz press r to refresh");
	}
	int count = 0;
	for (int i = 0; i < nb_games ;i++){
		int num_game;
		int nb_player;
		r = get_message(buff, BUFF_SIZE);
		if (r == 0) {
			if (i>0) vue_info("You can select");
			else if (i==0) vue_info("No game, plz press r to refresh");
			salon_cur();
			return 0;
		} else if (r == -1) 
		{
			exit_prog("Le server a fermer la co.\n", 0);
			return -1;
		}
		r = get_game(buff, &num_game, &nb_player);
		if (r == 1) {
			add_room(count, num_game, nb_player);
			count++;
		}
		else if (r == 0)
		{
			if (i>0) {
				vue_info("You can select");
				break;
			}
		}
	}
	salon_cur();
	return 1;
}

void load_new()
{
	char id[9];
	int r =id_interface(id);
	vue_info(id);
	if (r>0) out_new(id, MYUDP_PORTSTR);
	else return;
	if (join_room()){
		setPlayerId(id);
	}
}

void load_reg()
{
	char id[9];
	int r =id_interface(id);
	vue_info(id);
	if (r>0) out_reg(id, MYUDP_PORTSTR, getPartie());
	else return;
	if (join_room()>0){
		setPlayerId(id);
	}
}

int join_room()
{
	char buff[BUFF_SIZE];
	vue_info("En attente reponse du server.");
	int r = get_message(buff,BUFF_SIZE);
	if ( r >= 3 )
	{
		int num_game;
		if (isREGOK(buff, &num_game) > 0)
		{
			setRoom(num_game);
			init_room();
			return 1;
		} else {
			vue_info("Le server vous refuse.");
		}
	}
	else if ( r == 0 ) vue_err("No sig of server. plz refresh");
	else {
		exit_prog("Le server a fermer la co.\n",0);
	}
	return -1;
}

void exit_prog(char *mess, int status)
{
	end_vue();
	printf("%s", mess);
	exit(status);
}

void controler_unreg()
{
	char buff[BUFF_SIZE];	
	int r;
	vue_info("En attente reponse du server.");
	for (int i = 0; i < 2; i++)
	{
		out_unreg();
		while (1)
		{
			r = get_message(buff,BUFF_SIZE);
			if ( r >= 3 )
			{
				r = treat_unreg(buff);
				if (r>0) {
					out_games();
					load_salon();
					return;
				}
			} else if (r == -1) return exit_prog("Le server a fermer la co.\n",0);
			else if (r == 0) break;
		}
		vue_info("Retry send request.");
	}
	exit_prog("Time out.\n",0);
}

void controler_list()
{
	clr_f2();
	out_list(getPartie());
	int nb_player;
	char buff[BUFF_SIZE];
	int r;
	while (1)
    {   
		r = get_message(buff,BUFF_SIZE);
		if (r == 0) {
			vue_err("No sig of server.");
			return;
		} else if (r == -1) {
			return exit_prog("Le server a fermer la co.\n", 0);			
		}
		nb_player = treat_list(buff);
        if (nb_player > 0) {
			break;
		} else if (nb_player == 0) vue_info("No player");
	}

	int i = 0;
	while (1)
	{
		r = get_message(buff,BUFF_SIZE);
		if ( r >= 3 )
		{
			char id[9];
			r = treat_player(buff, id);
			if (r>0) {
				add_player(i, id);
				i++;
			}
		} else if (r == -1) return exit_prog("Le server a fermer la co.\n",0);
		else if (r == 0) break;
	}
}

void controler_size()
{
	char buff[BUFF_SIZE];	
	int r;
	int num_game, height, weight;
	vue_info("En attente reponse du server.");
	clr_f2();
	for (int i = 0; i < 2; i++)
	{
		out_size(getPartie());
		while (1)
		{
			r = get_message(buff,BUFF_SIZE);
			if ( r >= 3 )
			{
				r = treat_size(buff, &num_game, &height, &weight);
				if (r>0) {
					vue_size(height, weight);
					clr_err();
					return;
				}
			} else if (r == -1) return exit_prog("Le server a fermer la co.\n",0);
			else if (r == 0) break;
		}
		vue_info("Retry send request.");
	}
	vue_err("Time out.");
}


void wait_start()
{
	char buff[BUFF_SIZE];
	int r;
	int num_game, height, weight, nb_fantom, port, posX, posY;
	char ip[16], id[9];
	do
	{
		r = get_message(buff, BUFF_SIZE);
		if (r == 1 || r == 0) continue;
		else if (r == -1) exit_prog("Le server a fermer la co.\n", 0);
		r = treat_welcome(buff, &num_game, &height, &weight, &nb_fantom, ip ,&port);
		if (r <= 0) return exit_prog("Error from server.\n", 1);
		
		r = treat_pos(buff, id, &posX, &posY);
		setPos(posX, posY);
		break;
	} while (1);
	setGame(num_game, height, weight, nb_fantom, ip, port);
	init_game();
	int sock_muticast = init_multicast_reception(port, ip);
	if (sock_muticast == -1) return exit_prog("Impossible connection au multicast.\n", 1);
}

void *multicast_reception(void *ptr)
{
	int sock = getMultSock();
	char buff[250];
    while(1){
        int rec=recv(sock,buff,250,0);
        buff[rec]='\0';
		char out[250];
		if (strncmp(buff, "MESA", 4) == 0){
			char id[9];
			char mess[201];
			treat_mesa(buff, id, mess);
			vue_mess(id, mess);
		} else if (strncmp(buff, "FANT", 4) == 0){
			int posX, posY;
			treat_fant(buff, &posX, &posY);
			vue_setFan(posX, posY, "F");
		} else if (strncmp(buff, "SCOR", 4) == 0){
			char id[9];
			int point, posX, posY;
			treat_scor(buff, id, &point, &posX, &posY);
			vue_setFan(posX, posY, "X");
			vue_setSCOR(id, point, posX, posY);
		} else if (strncmp(buff, "END", 3) == 0){
			char id[9];
			int point;
			treat_end(buff, id, &point);
			snprintf(out, 50, "Le Joueur %s a remporté la victoire avec %d point(s)", id, point);
			exit_prog(out, 0);
		}

    }
	return NULL;
}

void controler_up()
{
	out_up(1);
	char buff[BUFF_SIZE];
	int r;
	int posX, posY, point;
	int x, y;
	r = get_message(buff, BUFF_SIZE);
	if (r == -1) exit_prog("Le server a fermer la co.\n", 0);
	else if (r == 0) return;

	switch (treat_mov(buff, &posX, &posY, &point))
	{
		case -1:
			return;
		case 0:
			x = getPosX();
			y = getPosY();
			if (x == posX && posY == y) setWall(x, y-1);
			setPos(posX,posY);
			return;
		case 1:
			x = getPosX();
			y = getPosY();
			if (x == posX && posY == y) setWall(x, y-1);
			setPos(posX,posY);
			vue_newSCOR(point);
			return;
		default: return;
	}
}

void controler_down()
{
	out_down(1);
	char buff[BUFF_SIZE];
	int r;
	int posX, posY, point;
	int x, y;
	r = get_message(buff, BUFF_SIZE);
	if (r == -1) exit_prog("Le server a fermer la co.\n", 0);
	else if (r == 0) return;

	switch (treat_mov(buff, &posX, &posY, &point))
	{
		case -1:
			return;
		case 0:
			x = getPosX();
			y = getPosY();
			if (x == posX && posY == y) setWall(x, y+1);
			setPos(posX,posY);
			return;
		case 1:
			x = getPosX();
			y = getPosY();
			if (x == posX && posY == y) setWall(x, y+1);
			setPos(posX,posY);
			vue_newSCOR(point);
			return;
		default: return;
	}
}

void controler_left()
{
	out_left(1);
	char buff[BUFF_SIZE];
	int r;
	int posX, posY, point;
	int x, y;
	r = get_message(buff, BUFF_SIZE);
	if (r == -1) exit_prog("Le server a fermer la co.\n", 0);
	else if (r == 0) return;

	switch (treat_mov(buff, &posX, &posY, &point))
	{
		case -1:
			return;
		case 0:
			x = getPosX();
			y = getPosY();
			if (x == posX && posY == y) setWall(x-1, y);
			setPos(posX,posY);
			return;
		case 1:
			x = getPosX();
			y = getPosY();
			if (x == posX && posY == y) setWall(x-1, y);
			setPos(posX,posY);
			vue_newSCOR(point);
			return;
		default: return;
	}
}

void controler_right()
{
	out_right(1);
	char buff[BUFF_SIZE];
	int r;
	int posX, posY, point;
	int x, y;
	r = get_message(buff, BUFF_SIZE);
	if (r == -1) exit_prog("Le server a fermer la co.\n", 0);
	else if (r == 0) return;

	switch (treat_mov(buff, &posX, &posY, &point))
	{
		case -1:
			return;
		case 0:
			x = getPosX();
			y = getPosY();
			if (x == posX && posY == y) setWall(x+1, y);
			setPos(posX,posY);
			return;
		case 1:
			x = getPosX();
			y = getPosY();
			if (x == posX && posY == y) setWall(x+1, y);
			setPos(posX,posY);
			vue_newSCOR(point);
			return;
		default: return;
	}
}


void controler_glist()
{
	out_glist();
	int r, nb_player;
	int posX, posY, point;	
	char buff[BUFF_SIZE];
	char id[9];
	while (1) {
		r = get_message(buff, BUFF_SIZE);
		if (r == -1) exit_prog("Le server a fermer la co.\n", 0);
		else if (r == 0) return;
		r = treat_glist(buff, &nb_player);
		if (r == 1);
	}
	
	int i = 0;
	while (1) {
		r = get_message(buff, BUFF_SIZE);
		if (r == -1) exit_prog("Le server a fermer la co.\n", 0);
		else if (r == 0) return;
		r = treat_gplayer(buff, id, &posX, &posY, &point);
		if (r == 1) {
			add_player(i, id);
			i++;
		}
	}
}


void controler_quit()
{
	out_quit();
	int r;
	char buff[1];
	while (1) {
		r = get_message(buff, 1);
		if (r == -1) exit_prog("Le server a fermer la co.\n", 0);
		else if (r == 0) break;
	}
	exit_prog("Vous avez quitter", 0);
}


void controler_all()
{
	char mess[201];
	int r;
	if (!vue_getMess(mess)) return;
	out_all(mess);
	while (1) {
		r = get_message(mess, 200);
		if (r == -1) exit_prog("Le server a fermer la co.\n", 0);
		else if (r == 0) break;
	}
}

void controler_send()
{
	int r;
	char mess[201];
	char id[9];
	if (!id_interface(id)) return;
	if (!vue_getMess(mess)) return;
	out_send(id, mess);
	while (1) {
		r = get_message(mess, 200);
		if (r == -1) exit_prog("Le server a fermer la co.\n", 0);
		else if (r == 0) break;
	}
}