package Server.Controller;

import Common.entity.*;
import Common.util.SocketIO;
import Server.ServerCache;
import Server.Service.FriendService;
import Server.Service.GroupService;
import Server.Service.OfflineMessageService;
import Server.Service.UserService;

import javax.imageio.ImageIO;
import java.io.File;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;

import static Common.entity.RequestType.LOGIN;
import static Common.entity.ResponseType.OK;
import static Common.entity.ResponseType.WRONG;

public class RequestProcessor implements Runnable {
    private final Socket clientSocket;
    
    public RequestProcessor(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }
    
    @Override
    public void run() {
        try {
            ObjectOutputStream oos = new ObjectOutputStream(clientSocket.getOutputStream());
            ObjectInputStream ois = new ObjectInputStream(clientSocket.getInputStream());
            SocketIO socketIO = new SocketIO(ois, oos);
            label:
            while (true) {
                //从请求输入流中读取到客户端提交的请求对象
                Request request = (Request) socketIO.getOis().readObject();
                
                RequestType requestType = request.getRequestType();   //获取请求中的动作
                System.out.println("Request from Client:" + request.getRequestType());
                switch (requestType) {
                    case REGISTER:       //用户注册
                        register(socketIO, request);
                        break;
                    case LOGIN:   //用户登录
                        login(socketIO, request);
                        break;
                    case LOGOUT:        //请求断开连接
                        logout(socketIO, request);
                        break label;
                    case SEND_MESSAGE:        //聊天
                        sendMessage(request);
                        break;
                    case ADD_FRIEND:
                        addFriend();
                        break;
                    case JOIN_GROUP:
                        joinGroup();
                        break;
                    case CHANGE_AVATAR:
                        changeAvatar(request);
                        break;
                    case CHANGE_PASSWORD:
                        changePassword(request);
                        break ;
                }
                
            }
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println(clientSocket.getLocalAddress() + " exit");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
            System.out.println("request class not found");
        }
        
    }
    
    private void changePassword(Request request) {
        User user = (User)request.getAttribute("user");
        ServerCache.onlineUsersMap.put(user.getUid(), user);
//        UserService.
    
    }
    
    private void changeAvatar(Request request) {
        User user = (User)request.getAttribute("user");
        ServerCache.onlineUsersMap.put(user.getUid(), user);
        java.io.File file = new File("./cache/" + user.getUid() + ".png");
        try {
            ImageIO.write(user.getAvatar(), "png", file);
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("change user "+user.getUid()+" failed");
        }
    }
    
    private void joinGroup() {
    
    }
    
    private void addFriend() {
    
    }
    
    /**
     * 想指定用户发送消息，发送方无需等待
     *
     */
    private void sendMessage(Request request) throws IOException {
        Message msg = (Message) request.getAttribute("message");
        
        Long to_id = msg.getToUserId();
        if (ServerCache.onlineUsersMap.containsKey(to_id)) {
            
            SocketIO toSocket = ServerCache.onlineUserIOCacheMap.get(to_id);
            sendRequest(toSocket, request);//向接收方发送Message
//            request.setRequestNeedRespond(true);
//            Request requestToSendUser = new Request(STATE, false);//发送方
//            request.setAttribute("response_state","ok");
//            sendRequest(socketIO, request);//向发送方回传已发送信息
            
        } else {
            OfflineMessageService offlineMessageService = new OfflineMessageService();
            offlineMessageService.setOfflineMessage(msg);
        }
        
    }
    
    private void logout(SocketIO socketIO, Request request) {
        User user = (User) request.getAttribute("user");
        SocketIO.close(socketIO.getOis(), socketIO.getOos());
        SocketIO.close(clientSocket);
        ServerCache.onlineUserIOCacheMap.remove(user.getUid());
        ServerCache.onlineUsersMap.remove(user.getUid());
        //update online user
        //notice other online user if they are friend
        //change states
    }
    
    /**
     * 登录请求
     * 向客户端回传request
     * 客户端需要等待读取返回信息
     * map 包含 state friend_list previous_message
     *
     * @param socketIO 输入输出流
     * @param request  请求对象
     * @throws IOException when send req failed
     */
    private void login(SocketIO socketIO, Request request) throws IOException {
        User logUser = (User) request.getAttribute("user");
        User getUser = UserService.selectUserById(logUser.getUid());
        Request retReq = new Request(LOGIN);
        retReq.setAttribute("user", getUser);
        if (getUser != null && getUser.getPassword().equals(logUser.getPassword())) {
            retReq.setAttribute("state", OK);
            ArrayList<User> friendIdList = new FriendService().getFriendListByUid(logUser.getUid());//send friend list
            retReq.setAttribute("friend_list", friendIdList);
            
            ArrayList<Message> messageNotReceiveList = new OfflineMessageService().selectOfflineMessageById(logUser.getUid());
            // not used     retReq.setAttribute("previous_message", messageNotReceiveList); //send message not received
            ArrayList<Group> groupList = GroupService.selectGroupByUid(getUser.getUid());
            retReq.setAttribute("group_list", groupList);
            ServerCache.onlineUsersMap.put(logUser.getUid(), logUser);//update online user    logUser: uid pwd
            ServerCache.onlineUserIOCacheMap.put(logUser.getUid(), socketIO);
        } else {
            retReq.setAttribute("state", WRONG);
        }
        sendRequest(socketIO, retReq);
    }
    
    /**
     * 注册函数
     * 向客户端回传request
     * 客户端需要等待读取返回信息
     * map 包含 user
     *
     * @param socketIO 输入输出流
     * @param request  请求对象
     * @throws IOException catch
     */
    private void register(SocketIO socketIO, Request request) throws IOException {
        User regUser = (User) request.getAttribute("user");
        Long uid = UserService.registerNewUser(regUser.getUsername(), regUser.getPassword(), regUser.getSex(), regUser.getAvatarPath(), regUser.getPhoneNum());
        regUser.setUid(uid);
//        Request retRequest = new Request(REGISTER);
        request.setAttribute("user", regUser);
        request.setAttribute("state", OK);
        sendRequest(socketIO, request);
    }
    
    /**
     * 向该输出流输出 request 对象
     *
     * @param socketIO 输入输出流
     * @param request  请求对象
     */
    private void sendRequest(SocketIO socketIO, Request request) throws IOException {
        ObjectOutputStream oos = socketIO.getOos();
        oos.writeObject(request);
        oos.flush();
    }
}