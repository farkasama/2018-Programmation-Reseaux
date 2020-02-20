#include "game.h"


struct labyrinthe
{
    int height;
    int weight;
    int posX;
    int posY;
    int** map;
    int nb_fantom;
} labyrinthe = {.height = 0, .weight = 0};

struct game
{
    //0: salon, 1: en jeu 2: salle
    int status;
    int port;
    char *ip;
    int gameID;
    char *player_id;

} game = {.status = SALON, .player_id = NULL, .ip=NULL};

int getPosX()
{
    return labyrinthe.posX;
}

int getPosY()
{
    return labyrinthe.posY;
}

char* getPlayerId()
{
    return game.player_id;
}

int getGameId()
{
    return game.gameID;
}

void setPlayerId(char *id)
{
    game.player_id = id;
}

int setGame_size(int height, int weight)
{
    labyrinthe.height = height;
    labyrinthe.weight = weight;
    labyrinthe.map = malloc(sizeof(char*));
    for (int i = 0; i < height; i++){
        labyrinthe.map[i] = malloc(sizeof(char)*weight);
        for (int j = 0; j < weight ; j++)
        {
            labyrinthe.map[i][j] = 0;
        }
    }
    return 0;
}

void free_game()
{
    for (int i = 0; i < labyrinthe.height; i++){
        free(labyrinthe.map[i]);
    }
}

int change_pos(int posX, int posY)
{
    labyrinthe.posX = posX;
    labyrinthe.posY = posY;
    return 0;
}

int inGame()
{
    if (game.status == STARTED) return 1;
    else return 0;
}

int inRoom()
{
    if (game.status == ROOM) return 1;
    else return 0;
}

int inSalon()
{
    if (game.status == SALON) return 1;
    else return 0;
}

void setStatus(int status)
{
    game.status = status;
}



void setRoom(int id)
{
    game.gameID = id;
    setStatus(ROOM);
}

void setLabyrinthe(int height, int weight, int nb_fantom)
{
    setGame_size(height, weight);    
}

void setFantom(int nb_fantom)
{
    labyrinthe.nb_fantom = nb_fantom;
}

void setGame_port(int port)
{
    game.port = port;
}

void setGame_ip(char *ip)
{
    game.ip = ip;
}

void setGame(int num_game, int height, int weight, int nb_fantom,char *ip, int port)
{
    setRoom(num_game);
    setLabyrinthe(height,weight,nb_fantom);
    setGame_ip(ip);
    setGame_port(port);
    setStatus(STARTED);
}

void setPos(int x, int y)
{
    labyrinthe.posX = x;
    labyrinthe.posY = y;
}

int getFantom()
{
    return labyrinthe.nb_fantom;
}

int getWeight()
{
    return labyrinthe.weight;
}

int getHeight()
{
    return labyrinthe.height;
}

int getBlock(int x, int y)
{
    return labyrinthe.map[y][x];
}

int isPlayerid(char *id)
{
    if (strcmp(id, game.player_id) == 0) 
        return 1;
    else 
        return 0;
}

void setWall(int x, int y)
{
    labyrinthe.map[y][x] = 1;
}