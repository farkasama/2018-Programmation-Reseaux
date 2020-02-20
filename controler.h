#ifndef __CONTROLER_H__
#define __CONTROLER_H__

#include "output.h"
#include "game.h"
#include "vue.h"
#include "clientTCP_service.h"
#include "clientUDP_service.h"
#include "mess_treat.h"

int init_controler();

void* launch_game(void *ptr);

int load_salon();

void load_new();

void load_reg();

void exit_prog(char *mess, int status);

int join_room();

void controler_unreg();

void controler_list();

void controler_size();

void wait_start();

void *multicast_reception(void *ptr);

void controler_left();

void controler_up();

void controler_down();

void controler_right();

void controler_glist();

void controler_all();

void controler_send();

void controler_quit();

#endif