import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class ServerMulticast {
    private String ip;
    private int port;
    private DatagramSocket dso;

    public ServerMulticast(String ip, int port) {
        this.ip = ip;
        this.port = port;
        try {
            dso = new DatagramSocket();
        } catch (SocketException e) {
            e.printStackTrace();
        }
    }

    void send(String mess) {
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
