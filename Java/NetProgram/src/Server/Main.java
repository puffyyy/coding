//package Server;
//
//import java.io.IOException;
//import java.net.InetSocketAddress;
//import java.nio.channels.SelectionKey;
//import java.nio.channels.Selector;
//import java.nio.channels.ServerSocketChannel;
//
//public class Main {
//    public static void main(String[] args) {
//        try {
//            ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();
//            Selector selector = Selector.open();
//            serverSocketChannel.configureBlocking(false);
//            serverSocketChannel.socket().bind(new InetSocketAddress(5500));
//            serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
//}
