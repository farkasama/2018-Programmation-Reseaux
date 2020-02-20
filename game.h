#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SALON   0
#define STARTED 1
#define ROOM    2

struct labyrinthe;

int setGame_size(int height, int weight);

int getPosX();

int getPosY();

char *getPlayerId();

void setPlayerId(char *id);

int getGameId();

int change_pos(int posX, int posY);

int inGame();

int inRoom();

int inSalon();

void free_game();

void setRoom(int id);

void setStatus(int status);

void setLabyrinthe(int height, int weight, int nb_fantom);

void setFantom(int nb_fantom);

void setGame_port(int port);

void setGame_ip(char *ip);

void setGame(int num_game, int height, int weight, int nb_fantom,char *ip, int port);

void setPos(int x, int y);

int getFantom();

int getWeight();

int getHeight();

int getBlock(int x, int y);

int isPlayerid(char *id);

void setWall(int x, int y);

#endif