#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include "clientTCP_service.h"

int out_games();

int out_new(char *id, char* port);

int out_reg(char *id, char* port, unsigned short num_partie);

int out_start();

int out_unreg();

int out_list(unsigned short num_partie);

int out_size(unsigned short num_partie);

int out_up(unsigned int distance);
int out_down(unsigned int distance);
int out_left(unsigned int distance);
int out_right(unsigned int distance);

int out_quit();

int out_glist();

int out_all(char *mess);

int out_send(char *id, char *mess);


#endif