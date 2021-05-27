package Server;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class Server {
    public static void main(String[] args) throws IOException {
        ServerSocket ss = new ServerSocket(5500); // 监听指定端口
        System.out.println("server is running...");
        while (true) {
            Socket sock = ss.accept();
            System.out.println("connected from " + sock.getRemoteSocketAddress());
            Thread t = new Handler(sock);
            Thread r = new HandlerOut(sock);
            t.start();
            r.start();
        }
    }
}

class Handler extends Thread {
    Socket sock;
    
    public Handler(Socket sock) {
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
            System.out.println("client disconnected.");
        }
    }
    
    private void handle(InputStream input, OutputStream output) throws IOException {
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(output, StandardCharsets.UTF_8));
        BufferedReader reader = new BufferedReader(new InputStreamReader(input, StandardCharsets.UTF_8));
        writer.write("hello\n");
        writer.flush();
        for (; ; ) {
            String s = reader.readLine();
            if (s.equals("bye")) {
                writer.write("bye");
                writer.newLine();
                writeS("Connection interruption", writer);
                break;
            }
            writeS(s, writer);
        }
    }
    
    private void writeS(String s, BufferedWriter writer) throws IOException {
        writer.write("received " + s);
        writer.newLine();
        writer.flush();
        System.out.println("received from server:" + s);
    }
}

class HandlerOut extends Thread {
    Socket sock;
    
    public HandlerOut(Socket sock) {
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
            System.out.println("client disconnected.");
        }
    }
    
    private void handle(OutputStream output) throws IOException {
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(output, StandardCharsets.UTF_8));
        Scanner scanner = new Scanner(System.in);
        for (; ; ) {
            String terminalRead = scanner.nextLine();
            writeS( terminalRead, writer);
        }
    }
    
    private void writeS(String s, BufferedWriter writer) throws IOException {
        writer.write(s);
        writer.newLine();
        writer.flush();
        System.out.println(">>> send to server:" + s);
    }
}