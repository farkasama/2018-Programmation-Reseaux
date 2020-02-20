import java.io.*;
import java.net.*;

public class ServerUDP {
    private DatagramSocket dso;


    public ServerUDP(int port) {
        try{
            dso = new DatagramSocket();
        } catch(Exception e){
            e.printStackTrace();
        }
    }

    void send(int port, String ip, String mess) {
        byte[] data = mess.getBytes();
        DatagramPacket paquet;

        try {
            paquet = new DatagramPacket(
                    data,data.length, InetAddress.getByName(ip),port);
            dso.send(paquet);
        } catch (Exception ignored) {}
    }

    public DatagramSocket getSocket() {
        return dso;
    }

}
