import java.io.*;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) throws IOException {
        
        Socket sock = new Socket("10.128.76.32", 5500); // 连接指定服务器和端口10.128.76.32
        try (InputStream input = sock.getInputStream()) {
            try (OutputStream output = sock.getOutputStream()) {
                Thread t = new ServerHandler(sock);
                Thread s = new ServerTerminalHandler(sock);
                t.start();
                s.start();
                s.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        sock.close();
        System.out.println("disconnected.");
    }
}
class ServerHandler extends Thread {
    Socket sock;
    
    public ServerHandler(Socket sock) {
        this.sock = sock;
    }
    
    @Override
    public void run() {
        try (InputStream input = this.sock.getInputStream()) {
            try (OutputStream output = this.sock.getOutputStream()) {
                handle(input, output);
            }
        } catch (Exception e) {
            try {
                this.sock.close();
            } catch (IOException ioe) {
                ioe.printStackTrace();
            }
            System.out.println("client disconnected.ServerHandler Thread end.");
        }
    }
    
    private void handle(InputStream input, OutputStream output) throws IOException {
        var writer = new BufferedWriter(new OutputStreamWriter(output, StandardCharsets.UTF_8));
        var reader = new BufferedReader(new InputStreamReader(input, StandardCharsets.UTF_8));
        writer.write("hello\n");
        writer.flush();
        for (; ; ) {
            String s = reader.readLine();
            System.out.println("<<< " + s);
            if (s.equals("bye")) {
                break;
            }
        }
    }
    
}
class ServerTerminalHandler extends Thread {
    Socket sock;
    
    public ServerTerminalHandler(Socket sock) {
        this.sock = sock;
    }
    
    @Override
    public void run() {
        try (OutputStream output = this.sock.getOutputStream()) {
            handle(output);
            
        } catch (Exception e) {
            try {
                this.sock.close();
            } catch (IOException ioe) {
                ioe.printStackTrace();
            }
            System.out.println("client disconnected.Terminal Thread end.");
        }
    }
    
    private void handle(OutputStream output) throws IOException {
        var writer = new BufferedWriter(new OutputStreamWriter(output, StandardCharsets.UTF_8));
        Scanner scanner = new Scanner(System.in);
        for (; ; ) {
            String s = scanner.nextLine(); // 读取一行输入
            writeS(s, writer);
        }
        
    }
    
    private void writeS(String s, BufferedWriter writer) throws IOException {
        writer.write(s);
        writer.newLine();
        writer.flush();
    }
}
