#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "game.h"
#include <ncurses.h>

/* 
 * deux modes: en jeu, et hors jeu (dans une salle ou exterieur).
 * initialise l'interface dans le terminal, dont
 * AVANT DE COMMENCER
 * - listes des salles avec leur numero et le nombre de joueurs de la salle.
 * - le joueur doit pouvoir choisir un numero de salle pour s'inscrire
 * - le joueur doit pouvoir raffraichir la liste de salle (un temps d'attente 1s entre raffraichissement)
 * - le joueur doit pouvoir demander la liste de joueurs dans une salle.
 * - le joueur doit pouvoir creer une salle
 */
void init_vue();

void end_vue();

void cur_up();

void cur_down();

void init_salon();

void vue_err(char *mess);

int add_room(int i, int num_salle, int nb_player);
/*
 * DANS UNE SALLE
 * - affiche listes des joueurs
 * - affiche la taille de labyrinthe
 * - le joueur doit pouvoir lancer start (block les entrees)
 * - le joueur doit pouvoir raffraichir la liste de joueur.
 * 
 */


/*
 * - 
 * - 
 * - score des joueurs
 * - listes des joueurs
 * - interface reserve labyrinthe si
 * 
 * 
 */


int getPartie();

void clrline(int i);

int id_interface(char* buff);

void salon_cur();

void clr_err();

void vue_info();

void init_room();

void clr_f2();

void update_nbgames(int nbgames);

void update_game(int gameid, int nbplayer);

void vue_recv();

void add_player(int i, char *id);

void vue_size(int height, int weight);

void vue_mess(char *id, char *mess);

void init_game();

void vue_labyrinthe();

void vue_setFan(int posX, int posY, const char *f);

void vue_setSCOR(char *id, int point, int posX, int posY);

void vue_newSCOR(int point);

int vue_getMess(char *buff);

#endif