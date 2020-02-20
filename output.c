#include "output.h"

int out_games()
{
    char *mess = "GAMES?***";
    return send_message(mess);
}

int out_new(char *id, char *port)
{
    char buff[30];
    snprintf(buff, sizeof(buff),"NEW %s %s***", id, port);
    return send_message(buff);
}

int out_reg(char *id, char *port, unsigned short num_partie)
{
    char buff[30];
    unsigned char d0 = (uint)num_partie;
    unsigned char d1 = (((uint)num_partie >> 8) & 0xFF);
    snprintf(buff, sizeof(buff),"REG %s %s %c%c***", id, port, d0, d1);
    return send_message(buff);
}

int out_unreg()
{
    return send_message("UNREG***");
}

int out_start()
{
    return send_message("START***");
}

int out_list(unsigned short num_partie)
{
    char buff[30];
    unsigned char d0 = (uint)num_partie;
    unsigned char d1 = (((uint)num_partie >> 8) & 0xFF);
    snprintf(buff, sizeof(buff),"LIST? %c%c***", d0, d1);
    return send_message(buff);
}

int out_size(unsigned short num_partie)
{
    char buff[30];
    unsigned char d0 = (uint)num_partie;
    unsigned char d1 = (((uint)num_partie >> 8) & 0xFF);
    snprintf(buff, sizeof(buff),"SIZE? %c%c***", d0, d1);
    return send_message(buff);
}

int out_up(unsigned int distance)
{
    char dist[30];
    int len = snprintf(NULL, 0, "%d", distance);
    if (len == 1) {
        snprintf(dist, 30, "UP 00%d***", distance);
    } else if (len ==2){
        snprintf(dist, 30, "UP 0%d***", distance);
    } else {
        snprintf(dist, 30, "UP %d***", distance);        
    }
    return send_message(dist);
}


int out_down(unsigned int distance)
{
    char dist[30];
    int len = snprintf(NULL, 0, "%d", distance);
    if (len == 1) {
        snprintf(dist, sizeof(dist), "DOWN 00%d***", distance);
    } else if (len ==2){
        snprintf(dist, sizeof(dist), "DOWN 0%d***", distance);
    } else {
        snprintf(dist, sizeof(dist), "DOWN %d***", distance);        
    }
    return send_message(dist);
}

int out_left(unsigned int distance)
{
    char dist[30];
    int len = snprintf(NULL, 0, "%d", distance);
    if (len == 1) {
        snprintf(dist, sizeof(dist), "LEFT 00%d***", distance);
    } else if (len ==2){
        snprintf(dist, sizeof(dist), "LEFT 0%d***", distance);
    } else {
        snprintf(dist, sizeof(dist), "LEFT %d***", distance);        
    }
    return send_message(dist);
}

int out_right(unsigned int distance)
{
    char dist[30];
    int len = snprintf(NULL, 0, "%d", distance);
    if (len == 1) {
        snprintf(dist, sizeof(dist), "RIGHT 00%d***", distance);
    } else if (len ==2){
        snprintf(dist, sizeof(dist), "RIGHT 0%d***", distance);
    } else {
        snprintf(dist, sizeof(dist), "RIGHT %d***", distance);        
    }
    return send_message(dist);
}

int out_quit()
{
    return send_message("QUIT***");
}

int out_glist()
{
    return send_message("GLIST?***");
}

int out_all(char *mess)
{
    char buff[250];
    snprintf(buff, sizeof(buff),"ALL? %s***", mess);
    return send_message(buff);
}

int out_send(char *id, char *mess)
{
    char buff[250];
    snprintf(buff, sizeof(buff),"SEND? %s %s***",id, mess);
    return send_message(buff);
}