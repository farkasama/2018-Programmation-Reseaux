#ifndef __MESS_TREAT_H__
#define __MESS_TREAT_H__

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "clientTCP_service.h"

int get_key(char* buff, char* key, int buff_size);

//[GAMES n]
int get_games(char* buff);

//[GAME n s]
int get_game(char* buff, int* num_salle, int* nb_player);

int stoi(char* buff, int buff_size);

unsigned short etos(char c0, char c1);

int isREGOK(char *buff, int *num_salle);

int treat_unreg(char *buff);

int treat_player(char *buff, char *id);

int treat_list(char *buff);

int treat_size(char *buff, int *num_game, int *height, int *weight);

int treat_welcome(char *buff ,int *num_game, int *height, int *weight, int *nb_fantom,char* ip , int *port);

int treat_pos(char *buff, char *id, int *posX, int *posY);

int treat_mov(char *buff,int *x, int *y, int *point);

int treat_bye(char *buff);

int treat_glist(char *buff, int *nb_player);

int treat_gplayer(char *buff, char *id, int *x, int *y, int *point);

int treat_all(char *buff);

int treat_mesa(char *buff, char *id, char *mess);

int treat_send(char *buff);

int treat_mesp(char *buff, char *id2, char *mess);

int treat_nosend(char *buff);

int treat_fant(char *buff, int *x, int *y);

int treat_scor(char *buff, char *id, int *point, int *x, int *y);

int treat_end(char *buff, char *id, int *point);


#endif