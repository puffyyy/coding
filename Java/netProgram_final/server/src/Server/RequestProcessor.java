package Server;

import Common.entity.*;
import Common.util.SocketIO;
import Server.Service.*;

import javax.imageio.ImageIO;
import java.io.File;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Map;
import java.util.stream.Collectors;

import static Common.entity.RequestType.*;
import static Common.entity.ResponseType.OK;
import static Common.entity.ResponseType.WRONG;

/**
 * 这是一个请求处理方法的综合类
 *
 * @author Java_Team
 * @version 1.5
 */

public class RequestProcessor implements Runnable {
    private final Socket clientSocket;
    private User curUser;
    
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
                        addFriend(socketIO, request);
                        break;
                    case JOIN_GROUP:
                        joinGroup(request);
                        break;
                    case CHANGE_AVATAR:
                        changeAvatar(request);
                        break;
                    case CHANGE_PASSWORD:
                        changePassword(request);
                        break;
                }
                
            }
        } catch (IOException e) {
            e.printStackTrace();
            ServerCache.onlineUsersMap.remove(curUser.getUid());
            ServerCache.onlineUserIOCacheMap.remove(curUser.getUid());
            System.out.println(clientSocket.getInetAddress() + ":" + clientSocket.getPort() + " exit");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
            System.out.println("request class not found");
        }
        
    }
    
    /**
     * 修改密码请求
     *
     * @param request 请求对象
     */
    private void changePassword(Request request) {
        User user = (User) request.getAttribute("user");
        ServerCache.onlineUsersMap.put(user.getUid(), user);
        UserService.modifyPersonalInformation(user.getUid(), user.getPassword(), "password");
    }
    
    /**
     * 修改头像请求
     *
     * @param request 请求对象
     */
    private void changeAvatar(Request request) {
        User user = (User) request.getAttribute("user");
        ServerCache.onlineUsersMap.put(user.getUid(), user);
        java.io.File file = new File(user.getAvatarPath());
        try {
            ImageIO.write(user.getAvatar(), "png", file);
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("change user " + user.getUid() + " failed");
        }
    }
    
    /**
     * 加入群聊
     *
     * @param request 请求对象
     * @throws IOException when failed
     */
    private void joinGroup(Request request) throws IOException {
        Group group = (Group) request.getAttribute("group");
        ArrayList<User> users = group.getUsers();
        ArrayList<Long> usersId = users.stream().map(User::getUid).collect(Collectors.toCollection(ArrayList::new));
        Long gid = GroupService.createGroup(group.name, usersId);
        group.setGid(gid);
        group.messages = new ArrayList<>();
        Group retGroup = new Group(group);
        Request retReq = new Request(JOIN_GROUP);
        retReq.setAttribute("group", group);
        retReq.setAttribute("from", curUser);
        
        if (gid != null)
            for (Long u : usersId) {
                if (ServerCache.onlineUsersMap.containsKey(u)) {
                    SocketIO socketIO = ServerCache.onlineUserIOCacheMap.get(u);
                    sendRequest(socketIO, retReq);
                }
            }
    }
    
    /**
     * 添加好友请求
     *
     * @param socketIO 输入输出流
     * @param request  请求对象
     * @throws IOException when failed
     */
    private void addFriend(SocketIO socketIO, Request request) throws IOException {
        String method = (String) request.getAttribute("method");
        Request retReq = new Request(ADD_FRIEND);
        if (method.equals("user_list")) {
            retReq.setAttribute("method", "user_list");
            String findKey = (String) request.getAttribute("search");
            retReq.setAttribute("user_list", UserService.searchUserByKeywords(findKey));
            sendRequest(socketIO, retReq);
        } else if (method.equals("add_friend_from")) {//接到发送方发来的添加好友请求
            Notice noc = (Notice) request.getAttribute("notice");
            retReq.setAttribute("method", "add_friend_from");
            retReq.setAttribute("notice", noc);
            retReq.setAttribute("from", request.getAttribute("from"));
            Long to_id = noc.getGetId();
            if (ServerCache.onlineUsersMap.containsKey(to_id)) {
                SocketIO toSocket = ServerCache.onlineUserIOCacheMap.get(to_id);
                sendRequest(toSocket, retReq);
            } else {
                NoticeService.sendNotice((Notice) request.getAttribute("notice"));
            }
        } else if (method.equals("add_friend_to")) {//接到被加好友那一方的回复请求
            String str = (String) request.getAttribute("pass");
            if (str.equals("yes")) {
                Notice noc = (Notice) request.getAttribute("notice");
                Long gid = FriendService.addFriend(noc.getSendId(), noc.getGetId());//向数据库中加入好友关系
                Long from_id = noc.getSendId();
                retReq.setAttribute("notice", noc);
                retReq.setAttribute("method", "add_friend_to");
                retReq.setAttribute("pass", "yes");
                User from = UserService.selectUserById(from_id);
                retReq.setAttribute("user", from);
                retReq.setAttribute("group_id", gid);
                sendRequest(socketIO, retReq);
                
                if (ServerCache.onlineUsersMap.containsKey(from_id)) {
                    retReq.setAttribute("user", request.getAttribute("from"));
                    SocketIO toSocket = ServerCache.onlineUserIOCacheMap.get(from_id);
                    sendRequest(toSocket, retReq);
                }
            }
        }
    }
    
    /**
     * 向指定用户发送消息，发送方无需等待
     *
     * @param request 请求对象
     * @throws IOException when failed
     */
    private void sendMessage(Request request) throws IOException {
        Message msg = (Message) request.getAttribute("message");
        Long from_uid = msg.getFromUserId();
        Long to_gid = msg.getGroupId();
        //lazy load
        ArrayList<User> groupMember;
        if (ServerCache.groupMapCache.get(to_gid) == null)
            groupMember = GroupService.selectGroupMemberByGid(to_gid);
        else
            groupMember = ServerCache.groupMapCache.get(to_gid).getUsers();
        if (groupMember == null) return;
        
        for (User u : groupMember) {
            if (u.getUid() == from_uid) continue;
            Request retReq = new Request(RequestType.SEND_MESSAGE);
            msg.setToUserId(u.getUid());
            if (ServerCache.onlineUsersMap.containsKey(u.getUid())) {
                SocketIO toSocket = ServerCache.onlineUserIOCacheMap.get(u.getUid());
                msg.setRead(true);
                retReq.setAttribute("message", msg);
                sendRequest(toSocket, request);
            } else {
                msg.setRead(false);
            }
            MessageService.insertMessageRecords(msg);
        }
        
    }
    
    /**
     * 登出请求 关闭客户端 将用户设置为不在线
     *
     * @param socketIO 输入输出流
     * @param request  请求对象
     */
    private void logout(SocketIO socketIO, Request request) {
        User user = (User) request.getAttribute("user");
        SocketIO.close(socketIO.getOis(), socketIO.getOos());
        SocketIO.close(clientSocket);
        ServerCache.onlineUserIOCacheMap.remove(user.getUid());
        ServerCache.onlineUsersMap.remove(user.getUid());
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
            if (ServerCache.onlineUsersMap.containsKey(getUser.getUid())) {
                Request request1 = new Request(LOGOUT);
                request1.setAttribute("state", "你的账号正在其他地址登录" + clientSocket.getInetAddress() + ":" + clientSocket.getPort());
                sendRequest(ServerCache.onlineUserIOCacheMap.get(getUser.getUid()), request1);
            }
            this.curUser = getUser;
            retReq.setAttribute("state", OK);
            ArrayList<User> friendIdList = new FriendService().getFriendListByUid(logUser.getUid());
            retReq.setAttribute("friend_list", friendIdList);
            ArrayList<Group> groupList = UserService.initGroupList(getUser.getUid());
            retReq.setAttribute("group_list", groupList);
            Map<Notice, User> noticeMap = NoticeService.getNotice(getUser.getUid());
            retReq.setAttribute("notice_map", noticeMap);
            
            ServerCache.onlineUsersMap.put(logUser.getUid(), logUser);
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
        final String defaultPath = "./cache/";
        User regUser = (User) request.getAttribute("user");
        Long uid = UserService.registerNewUser(regUser.getUsername(), regUser.getPassword(), regUser.getSex(), "", regUser.getPhoneNum());
        regUser.setUid(uid);
        String path = defaultPath + regUser.getUid() + ".png";
        regUser.setAvatarPath(path);
        UserService.modifyPersonalInformation(uid,path, "avatar_path");
        
        Request retRequest = new Request(REGISTER);
        User newUser = new User(uid, regUser.getPassword());
        retRequest.setAttribute("user", newUser);
        retRequest.setAttribute("state", OK);
        sendRequest(socketIO, retRequest);

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
        System.out.println("Request send to Client:" + request.getRequestType());
    }
}