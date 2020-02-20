public class Utils {


    public static int letoi(String s) {
        if (s.length() < 2) return 0;
        char c0 = s.charAt(0);
        char c1 = s.charAt(1);
        return (byte) c0 | (byte)c1 <<  8;
    }

    public static String itole(int i) {
        char c0 = (char) (i % 256);
        char c1 = (char) (i >> 8);
        return ""+c0 + c1;
    }

    // retourne -1 si presence de non numerique
    public static int strtoi(String buff) {
        if (buff.length() > 5) return -1;
        int res = 0, i;
        for(i=0; i<buff.length(); i++){
            if (buff.charAt(i) > 47 && buff.charAt(i)<58) {
                res = res * 10 + ( buff.charAt(i) - '0' );
            } else {
                return -1;
            }
        }
        return res;
    }

    public static String itostr(int i) {
        String res = "" + i;
        for (int j = 0; j < 3-res.length()+1; j++) {
            res = "0" + res;
        }
        return res;
    }
}
