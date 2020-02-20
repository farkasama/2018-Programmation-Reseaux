import java.net.*;
import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.regex.Pattern;

class Serveur {

    public static void main(String[] args) {
        /*Partie p = new Partie(0);
        p.start(); */

        try {
            ServerSocket serveur = new ServerSocket(8000);
            while (true) {
                ServeurJoueur j = new ServeurJoueur(serveur);
                Thread t = new Thread(j);
                t.start();
            }
        } catch (Exception e) {
            System.out.print(e);
        }

    }
}

class ServeurJoueur implements Runnable {

    private ServerSocket serv;
    private HashMap<Integer,Partie> p;
    private HashMap<String,Integer> mapPartie;
    private HashMap<String,Joueur> mapJoueur;

    public ServeurJoueur (ServerSocket s){
        serv = s;
        p = new ArrayList<Partie>();
    }

    @Override
    public void run() {
        try {
            Socket s = serv.accept();
            BufferedReader bf = new BufferedReader(new InputStreamReader(s.getInputStream()));
            PrintWriter pw = new PrintWriter(new OutputStreamWriter(s.getOutputStream()));
            String str;
            String ip = s.getInetAddress().getHostName();
            pw.print("GAMES "+p.size()+"***");
            pw.flush();
            for(int i = 0; i < p.size(); i++) {
                pw.print("GAME "+i+" "+p.get(i).getPlayers().size()+"***");
            }
            pw.flush();
            while (true) {
                char buff[] = new char[250];
                int r = bf.read(buff);
                str = charsToString(buff);
                String[] tab = splitString(str);
                if (tab == null) ; //FAIRE QQCH
                if (tab[0].equals("QUIT")) {
    	    if(mapJoueur.contains(ip)) {
			p.get(mapPartie.get(ip)).erasePlayer(mapJoueur.get(ip).getId());
			if(p.get(mapPartie.get(ip)).getPlayers().size() == 0) {
			    p.remove(mapPartie.get(ip));
			}
			mapJoueur.remove(ip);
			mapPartie.remove(ip);
		    }
                    pw.print("BYE***");
                    pw.flush();
                    break;
                }
                if (tab[0].equals("NEW")) {
		    int k = 1;
		    while(p.containsKey(k)) {
			k++;
		    }
                    p.put(k,new Partie());
                    p.get(k).addPlayer(tab[1],tab[2]);
                    mapPartie.put(ip,k);
                    mapJoueur.put(ip,p.get(k).getPlayers().get(p.get(k).getPlayers().size()));
                    pw.print("REGOK "+k);
                }
                if (tab[0].equals("REG")) {
		    int k = Integer.parseInt(tab[3]); //à modif avec little endian
                    p.get(k).addPlayer(tab[1],tab[2]); 
		    mapPartie.put(ip,k);
                    mapJoueur.put(ip,p.get(k).getPlayers().get(p.get(k).getPlayers().size()));
                    pw.print("REGOK "+k);
                }
                if (tab[0].equals("START")) {
                    mapJoueur.get(ip).check();
                    boolean start = true;
                    for (int z = 0; z < p.get(k).getPlayers().size(); z++) {
                        if (p.get(k).getPlayers().get(z).getReady() == false) {
                            start = false;
                        }
                    }
                }
                if (tab[0].equals("UNREG")) {
                    p.get(mapPartie.get(ip)).erasePlayer(mapJoueur.get(ip).getId());
                    if(p.get(mapPartie.get(ip)).getPlayers().size() == 0) {
                        p.remove(mapPartie.get(ip));
		    }
		    mapJoueur.remove(ip);
		    mapPartie.remove(ip);
		}
		if (tab[0].equals("SIZE?")) {
		    int k = Integer.parseInt(tab[1]); //à modif avec little endian
		    if(p.size() > k) {
			Labyrinthe l = p.get(k).getLab(); //à modif avec little endian
			pw.print("SIZE! "+k+" "+l.getHeight()+" "+l.getWidth()+"***"); //à modif avec little endian
		    }else{
			pw.print("DUNNO***");
		    }
		}
		if (tab[0].equals("LIST?")) {
		    int k = Integer.parseInt(tab[1]); //à modif avec little endian
		    if(p.size() > k) {
			ArrayList<Joueur> j = p.get(k).getPlayers();
			pw.print("LIST! "+k+" "+j.size());
			pw.flush();
			for(int i = 0; i < j.size(); i++) {
			    pw.print("PLAYER "+j.get(i).getId()+"***");
			}
		    }else{
			pw.print("DUNNO***");
		    }
		}
		if (tab[0].equals("GAMES?")) {
		    pw.print("GAMES "+p.size()+"***");
		    pw.flush();
		    for(int i : p.keySet) {
			pw.print("GAME "+i+" "+p.get(i).getPlayers().size()+"***");
		    }
		}
		//manque encore des fonctions
		pw.flush();
                /*for (int i = 0; i < tab.length; i++) {
		  System.out.println(tab[i]);              debug
		  }*/
	    }
	    bf.close();
	    pw.close();
	    s.close();
	}
    } catch (Exception e) {
	System.out.print(e);
    }


    public static String[] splitString (String s) {
        String key = "";
        String ret[] = null;
        String str = s.substring(0,s.length()-3);

        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == ' ') {
                break;
            } else {
                key += s.charAt(i);
            }
        }
        try{ switch (key) {
            case "REG":
                ret = new String[4];
                ret[0] = key;
                String id = "";
                int i;
                for (i = 4; i < s.length(); i++) {
                    if (s.charAt(i) == ' ') {
                        break;
                    } else {
                        id += s.charAt(i);
                    }
                }
                String port = "";
                for ( i = i+1; i < s.length(); i++) {
                    if (s.charAt(i) == ' ') {
                        break;
                    } else {
                        port += s.charAt(i);
                    }
                }
                if (s.length() < i+2 +1 ||
                        id.equals("") || port.length() != 4) return null;
                String m = "" + s.charAt(i+1) + s.charAt(i+2);
                ret[1] = id;
                ret[2] = port;
                ret[3] = m;
                break;
            case "LIST?":
            case "SIZE?":
                if (s.length() < 8) return null;
                ret = new String[2];
                ret[0] = key;
                ret[1] = s.charAt(6)+""+ s.charAt(7);
                break;
            default:
                Pattern p = Pattern.compile(" ");
                ret = p.split(str);
                break;
        } } catch (Exception e){
            return null;
        }
        return ret;
    }

    static String charsToString(char[] tab) {
        String res = "";
        for (int i = 0; i < tab.length; i++) {
            res += tab[i];
        }
        return res;
    }
}

