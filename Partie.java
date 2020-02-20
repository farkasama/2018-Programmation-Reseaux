import java.lang.Math;
import java.net.*;
import java.io.*;
import java.util.*;

class Partie {
    
    private Labyrinthe l;
    private ArrayList<Joueur> j;

    public Partie () {
        l = new Labyrinthe();
        System.out.println(l.toString());
        j = new ArrayList<Joueur>();
    }

    public void addPlayer(String id, String port) {
	Joueur j = this.l.initialiserJoueur(id,port);
	this.j.add(j);
    }

    public ArrayList<Joueur> getPlayers() {
	return j;
    }

    public Labyrinthe getLab() {
	return l;
    }

    public void erasePlayer(String id) {
	for(Joueur j : this.j) {
	    if(j.getId().equals(id)) {
		l.wipe(j.getX(),j.getY());
		this.j.remove(j);
	    }
	}
    }
    
}

class Labyrinthe {

    private int maxX;
    private int maxY;
    private int[][] l;
    private int nbFantome = 3;
    private Fantome[] f;

    public Labyrinthe () {
        maxX = 6;
        maxY = 7;
        l = new int[maxX][maxY];
        for (int i = 0; i < maxX; i++) {
            for (int j = 0; j < maxY; j++) {
                l[i][j] = 1;
            }
        }
        l[0][1] = 0;
        l[1][1] = 0;
        l[2][1] = 0;
        l[3][0] = 0;
        l[3][1] = 0;
        l[4][1] = 0;
        l[4][2] = 0;
        l[4][3] = 0;
        l[4][4] = 0;
        l[4][5] = 0;
        l[5][5] = 0;
        l[3][3] = 0;
        l[3][4] = 0;
        l[2][4] = 0;
        l[1][3] = 0;
        l[1][4] = 0;
        l[1][5] = 0;
        l[1][6] = 0;


        f = new Fantome[nbFantome];

        initialiserFantome();
    }

    public boolean estDisponible(int x, int y) {
        if (l[x][y] != 1)
            return true;
        return false;
    }

    public int getType(int x, int y) {
        return l[x][y];
    }

    public void initialiserFantome() {
        for (int i = 0; i < nbFantome; i++) {
            int x = (int)(Math.random()*maxX);
            int y = (int)(Math.random()*maxY);
            while (!estDisponible(x, y)) {
                x = (int)(Math.random()*maxX);
                y = (int)(Math.random()*maxY);
            }
            l[x][y] = 2;
            f[i] = new Fantome(x, y);
        }
    }

    public Joueur initialiserJoueur(String id, String port) {
	int x = (int)(Math.random()*maxX);
	int y = (int)(Math.random()*maxY);
	while (!estDisponible(x, y)) {
	    x = (int)(Math.random()*maxX);
	    y = (int)(Math.random()*maxY);
	}
	l[x][y] = 3;
	return new Joueur(x,y,id,Integer.parseInt(port));
    }
    
    public String toString() {
        String str = "";
        for (int i = 0; i < maxX; i++) {
            for (int j = 0; j < maxY; j++) {
                str += l[i][j] + " ";
            }
            str += "\n";
        }
        return str;
    }

    public int getWidth() {
	return maxX;
    }

    public int getHeight() {
	return maxY;
    }

    public void wipe(int x, int y) {
	l[x][y] = 0;
    }

    public void movePlayer(Joueur j, int x, int y) {
	l[x][y] = 3;
	wipe(j.getX(),j.getY());
	j.move(x,y);
    }

    public boolean moveRight(Joueur j, int i) {
	int c = 1;
	boolean score = false;
	while(c < i && estDisponible(j.getX()+c,j.getY())) {
	    if(l[j.getX()+c][j.getY()] == 2) {
		score = true;
		j.score();
	    }
	    c++;
	}
	movePlayer(j,j.getX()+c-1,j.getY());
	return score;
    }

    public boolean moveLeft(Joueur j, int i) {
	int c = 1;
	boolean score = false;
	while(c < i && estDisponible(j.getX()-c,j.getY())) {
	    if(l[j.getX()-c][j.getY()] == 2) {
		score = true;
		j.score();
	    }
	    c++;
	}
	movePlayer(j,j.getX()-c-1,j.getY());
	return score;
    }

    public boolean moveUp(Joueur j, int i) {
	int c = 1;
	boolean score = false;
	while(c < i && estDisponible(j.getX(),j.getY()+c)) {
	    if(l[j.getX()][j.getY()+c] == 2) {
		score = true;
		j.score();
	    }
	    c++;
	}
	movePlayer(j,j.getX(),j.getY()+c-1);
	return score;
    }

    public boolean moveDown(Joueur j, int i) {
	int c = 1;
	boolean score = false;
	while(c < i && estDisponible(j.getX(),j.getY()-c)) {
	    if(l[j.getX()][j.getY()-c] == 2) {
		score = true;
		j.score();
	    }
	    c++;
	}
	movePlayer(j,j.getX(),j.getY()-c-1);
	return score;
    }

    public boolean moveGhost(Fantome f, int x, int y) {
	if(estDisponible(x,y)){
	    l[x][y] = 2;
	    wipe(f.getX(),f.getY());
	    f.move(x,y);
	    return true;
	}
	return false;
    }
    
}

class Entite {

    private int x,y;

    public Entite(int x, int y) {
	this.x = x;
	this.y = y;
    }

    public void move(int x, int y) {
	this.x = x;
	this.y = y;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

}

class Joueur extends Entite {

    private String id;
    private int p,port;
    private boolean ready;

    public Joueur(int x, int y, String id,int port) {
	super(x,y);
	this.id = id;
	this.p = 0;
    this.port = port;
    ready = false;
    }

    public String getId() {
	return id;
    }

    public int getPoint() {
	return p;
    }

    public void score() {
	p++;
    }

    public void check() {
        ready = true;
    }

    public boolean getReady() {
        return ready;
    }

}

class Fantome extends Entite {

    public Fantome (int x, int y) {
	super(x,y);
    }

}
