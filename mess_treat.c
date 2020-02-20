#include "mess_treat.h"

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

unsigned short etos(char c0, char c1)
{
    return (uint)c0 <<  0 | (uint)c1 <<  8;
}

int get_key(char* buff, char* key, int buff_size)
{
    char *ch;
    ch = strtok(buff, " ");
    strncpy(key, ch, buff_size);
    return 1;
}

int get_games(char* buff)
{
    if (strlen(buff)<8) return -1;
    char *ch;
    ch = strtok(buff, " ");
    if (strcmp(ch, "GAMES")==0) {
        /*
        int nb_game = stoi(&buff[6], 2);
        if (nb_game <= 0) return -1;
        return nb_game;
        */
        return etos(buff[0], buff[1]);
    } else return -1;
}

int get_game(char* buff, int* num_salle, int* nb_player)
{
    if (strlen(buff) < 10) return -1;
    char* ch;
    ch = strtok(buff, " ");
    if(strcmp(ch, "GAME")==0)
    {
        /*
        int r = stoi(&buff[5], 2);
        if (r >= 0) *num_salle = r;
        else return r;

        r = stoi(&buff[8], 2);
        if (r >= 0) *nb_player = r;
        else return r;
        */
       *num_salle = etos(buff[5], buff[6]);
       *nb_player = etos(buff[8], buff[9]);
        return 1;
    } else return -1;
}


int isREGOK(char *buff, int *num_salle)
{
    char *REGOK = "REGOK";
    if (strlen(buff) < 8) return -1;
    if (strncmp(buff, REGOK, strlen(REGOK)) == 0)
    {
        *num_salle = etos(buff[6], buff[7]);
        return 1;
    }
    return -1;
}

int treat_unreg(char *buff)
{
    if (strlen(buff) < 7) return -1;
	char *UNREGOK = "UNREGOK" ;
    if (strncmp(buff, UNREGOK, strlen(UNREGOK)) == 0)
    {
        return 1;
    }
    return 0;
}

int treat_list(char *buff)
{
    if (strlen(buff) < 11) return -1;
    char *ch;
    ch = strtok(buff, " ");
    if (ch != NULL) {
        if (strcmp(ch, "LIST!") == 0)
        {
            return etos(buff[9], buff[10]);
        }
    }
    return -1;
}

int treat_player(char *buff, char *id)
{
    if (strlen(buff) < 8) return -1;
    char *ch;
    ch = strtok(buff, " ");
    if (ch != NULL) {
        if (strcmp(ch, "PLAYER") != 0) return -1;
        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        strncpy(id, ch, 8);
        id[8] = '\0';
        return 1;
    }
    return 0;
}

int treat_size(char *buff, int *num_game, int *height, int *weight)
{
    if (strlen(buff) < 14) return -1;
    char *ch;
    ch = strtok(buff, " ");
    if (ch != NULL) {
        if (strcmp(ch, "SIZE!") != 0) return -1;
        *num_game = etos(buff[6], buff[7]);
        *height = etos(buff[9], buff[10]);
        *weight = etos(buff[12], buff[13]);
        return 1;
    }
    return 0;
}


int treat_welcome(char *buff, int *num_game, int *height, int *weight, int *nb_fantom,char* ip, int *port)
{
    if (strlen(buff) < 41) return -1;
    char *ch;
    ch = strtok(buff, " ");
    if (ch != NULL) {
        if (strcmp(ch, "WELCOME") != 0) return -1;
        *num_game = etos(buff[7], buff[8]);
        *height = etos(buff[10], buff[11]);
        *weight = etos(buff[13], buff[14]);
        *nb_fantom = etos(buff[16], buff[17]);
        strncpy(ip, &buff[19], 15);
        ip[15] = '\0';
        int r = stoi(&buff[36], 4);
        if ( r == -1) return -1;
        *port = r;
        return 1;   
    }
    return -1;
}

int treat_pos(char *buff, char *id, int *posX, int *posY)
{
    if (strlen(buff) < 41) return -1;
    char *ch;
    int r;
    ch = strtok(buff, " ");
    if (ch != NULL) {
        if (strcmp(ch, "POS") != 0) return -1;
        //get id
        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        strncpy(id, ch, 8);
        id[8] = '\0';

        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        r = stoi(ch, strlen(ch));
        if (r == -1) return -1;
        *posX = r;

        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        r = stoi(ch, strlen(ch));
        if (r == -1) return -1;
        *posY = r;
        return 1;
    }

    return -1;
}

int treat_mesp(char *buff, char *id2, char *mess)
{
    char *ch;
    ch = strtok(buff, " ");
    if (ch != NULL) {
        ch = strtok(NULL, " ");
        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        strncpy(id2, ch, 8);
        id2[8] = '\0';

        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        strncpy(mess, ch, 200);
        mess[200] = '\0';
        return 1;
    }
    return -1;
}


int treat_mesa(char *buff, char *id, char *mess)
{
    return treat_mesp(buff, id, mess);
}

int treat_fant(char *buff, int *x, int *y)
{
    char *ch;
    int r;
    ch = strtok(buff, " ");
    if (ch != NULL) {
        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        r = stoi(ch, strlen(ch));
        if (r == -1) return -1;
        *x = r;

        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        r = stoi(ch, strlen(ch));
        if (r == -1) return -1;
        *y = r;
        return 1;
    }
    return -1;
}


int treat_scor(char *buff, char *id, int *point, int *x, int *y)
{
    char *ch;
    int r;
    ch = strtok(buff, " ");
    if (ch != NULL) {
        //get id
        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        strncpy(id, ch, 8);
        id[8] = '\0';

        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        r = stoi(ch, strlen(ch));
        if (r == -1) return -1;
        *point = r;


        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        r = stoi(ch, strlen(ch));
        if (r == -1) return -1;
        *x = r;

        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        r = stoi(ch, strlen(ch));
        if (r == -1) return -1;
        *y = r;
        return 1;
    }

    return -1;
}



int treat_end(char *buff, char *id, int *point)
{
    char *ch;
    int r;
    ch = strtok(buff, " ");
    if (ch != NULL) {
        //get id
        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        strncpy(id, ch, 8);
        id[8] = '\0';

        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        r = stoi(ch, strlen(ch));
        if (r == -1) return -1;
        *point = r;

        return 1;
    }

    return -1;
}

int treat_mov(char *buff,int *x, int *y, int *point)
{
    char *ch;
    int r;
    int ret = 1;
    ch = strtok(buff, " ");
    if (ch != NULL) {
        if (strcmp(ch, "MOV") == 0) ret = 0;
        else if (strcmp(ch, "MOF") == 0) ret = 1;
        
        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        r = stoi(ch, strlen(ch));
        if (r == -1) return -1;
        *x = r;

        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        r = stoi(ch, strlen(ch));
        if (r == -1) return -1;
        *y = r;

        if ( ret ) {
            ch = strtok(NULL, " ");
            if (ch == NULL) return -1;
            r = stoi(ch, strlen(ch));
            if (r == -1) return -1;
            *point = r;
        }
        return ret;
    }

    return -1;
}

int treat_glist(char *buff, int *nb_player)
{
    char *ch;
    ch = strtok(buff, " ");
    int r;
    if (ch != NULL) {
        if (strcmp(ch, "GLIST!") != 0) return -1;

        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        r = stoi(ch, strlen(ch));
        if (r == -1) return -1;
        *nb_player = r;
        
        return 1;
    }
    return 0;
}

int treat_gplayer(char *buff, char *id, int *x, int *y, int *point)
{
    char *ch;
    ch = strtok(buff, " ");
    int r;
    if (ch != NULL) {
        if (strcmp(ch, "GPLAYER") != 0) return -1;
        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        strncpy(id, ch, 8);
        id[8] = '\0';
        
        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        r = stoi(ch, strlen(ch));
        if (r == -1) return -1;
        *x = r;

        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        r = stoi(ch, strlen(ch));
        if (r == -1) return -1;
        *y = r;

        ch = strtok(NULL, " ");
        if (ch == NULL) return -1;
        r = stoi(ch, strlen(ch));
        if (r == -1) return -1;
        *point = r;
        
        return 1;
    }
    return 0;
}