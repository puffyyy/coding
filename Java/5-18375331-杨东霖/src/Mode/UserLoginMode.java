package Mode;

import entity.*;
import util.Cache;
import util.judge;

import java.util.*;

import static Mode.ParsingTerminal.parse_gd;
import static Mode.ParsingTerminal.parse_pm;
import static util.judge.isDouble;

public class UserLoginMode {
    public Person loginPerson;
    
    public UserLoginMode(Person loginPerson) {
        this.loginPerson = loginPerson;
    }
    
    public void loginMode() {
        Scanner scanner = Cache.scanner;
        System.out.println("Login success");
        String readString;
        do {
            readString = scanner.nextLine().trim();
        } while (parseCommand(readString));
    }
    
    private boolean parseCommand(String line) {
        String[] arg = line.trim().split("\\s+");
        boolean parsed = false;
        switch (loginPerson.getPersonType()) {
            case Customer:
                parsed = CustomerMode.parse_customerMethod(arg, loginPerson);
                break;
            case Cook:
                parsed = KitchenMode.parse_waiterMethod(arg, loginPerson);
                break;
            case Waiter:
                parsed = WaiterMode.parse_waiterMethod(arg, loginPerson);
                break;
        }
        if (!parsed)
            switch (arg[0]) {
                case "myinfo":
                    parse_info(arg);
                    break;
                case "back":
                    parse_back(arg);
                    return false;
                case "QUIT":
                    parse_quit(arg);
                    return false;//duplicate
                case "chgpw":
                    parse_chgpw(arg);
                    break;
                case "":
                    break;
                default:
                    System.out.println("Command not exist");
            }
        return true;
    }
    
    private void parse_chgpw(String[] arg) {
        if (arg.length == 3) {
            if (judge.isPersonPwdLegal(arg[1])) {
                if (arg[1].equals(arg[2])) {
                    loginPerson.setPersonPwd(arg[1]);
                    System.out.println("Change password success");
                } else System.out.println("Not match");
            } else System.out.println("New password illegal");
        } else System.out.println("Params' count illegal");
    }
    
    private void parse_back(String[] arg) {
        System.out.println(arg.length == 1 ? "Logout success" : "Params' count illegal");
    }
    
    private void parse_info(String[] arg) {
        if (arg.length == 1) {
            String format = String.format("[info]\n" +
                            "| name:\t%s\n" +
                            "| Sex:\t%c\n" +
                            "| Pho:\t%s\n" +
                            "| PID:\t%s\n" +
                            "| Pwd:\t%s\n" +
                            "| Type:\t%s"
                    , loginPerson.getPersonName(), loginPerson.getSex()
                    , loginPerson.getPersonMobileNumber(), loginPerson.getPersonId()
                    , loginPerson.getPersonPwd(), loginPerson.getPersonType());
            System.out.println(format);
        } else System.out.println("Params' count illegal");
    }
    
    private void parse_quit(String[] arg) {
        if (arg.length == 1) {
            System.out.println("----- Good Bye! -----");
            System.exit(0);
        } else System.out.println("Params' count illegal");
    }
    
    static class CustomerMode {
        static List<String> customerMethodList = Arrays.asList("rc", "gb", "aplVIP", "gd", "pm", "order", "co", "confirm");
        static Customer customer;
        
        public static boolean parse_customerMethod(String[] arg, Person customer) {
            CustomerMode.customer = (Customer) customer;
            int index = customerMethodList.indexOf(arg[0]);
            if (index == -1) return false;
            else {
                switch (index) {
                    case 0:
                        parse_rc(arg);
                        break;
                    case 1:
                        parse_gb(arg);
                        break;
                    case 2:
                        parse_aplVIP(arg);
                        break;
                    case 3:
                        parse_gd(arg);
                        break;
                    case 4:
                        parse_pm(arg);
                        break;
                    case 5:
                        parse_order(arg);
                        break;
                    case 6:
                        parse_co(arg);
                        break;
                    case 7:
                        parse_confirm(arg);
                        break;
                }
            }
            return true;
        }
        
        private static void parse_co(String[] arg) {
            if (arg.length == 1) {
                if (customer.getOrderList().isAllConfirmed()) {
                    System.out.println("No order");
                } else {//Definitely has an order
                    Map<Dish, Integer> dishes = customer.getOrderList().getCurNewOrder().getDishMapCnt();
                    Iterator<Map.Entry<Dish, Integer>> iter = dishes.entrySet().iterator();
                    Map.Entry<Dish, Integer> entry;
                    int i = 0;
                    Dish dish;
                    int cnt;
                    double sum = 0.0;
                    while (iter.hasNext()) {
                        entry = iter.next();
                        dish = entry.getKey();
                        cnt = entry.getValue();
                        sum += dish.getDishPrice() * cnt;
                        System.out.printf("%d.DID:%s,DISH:%s,PRICE:%.1f,NUM:%d\n", ++i, dish.getDishId(), dish.getDishName(), dish.getDishPrice(), cnt);
                    }
                    System.out.println("|\nSUM:" + sum);
                }
            } else System.out.println("Params' count illegal");
        }
        
        private static void parse_confirm(String[] arg) {
            if (arg.length == 1) {
                if (customer.getOrderList().isAllConfirmed()) {
                    System.out.println("No order can be confirmed");
                } else {
                    customer.getOrderList().confirmOrder();
                    System.out.println("Order Confirmed");
                }
            } else System.out.println("Params' count illegal");
        }
        
        private static void parse_order(String[] arg) {
            if (arg.length == 1) {
                OrderMode orderMode = new OrderMode(customer);
                orderMode.orderMode();
            } else System.out.println("Params' count illegal");
        }
        
        private static void parse_aplVIP(String[] arg) {
            if (arg.length == 1) {
                if (customer.isApplyVIPSuccess()) {
                    System.out.println("Apply VIP success");
                } else System.out.println("Please recharge more");
            } else System.out.println("Params' count illegal");
        }
        
        private static void parse_gb(String[] arg) {
            if (arg.length == 1) {
                System.out.println("Balance: " + customer.getAccountBalance());
            } else System.out.println("Params' count illegal");
        }
        
        private static void parse_rc(String[] arg) {
            if (arg.length == 2) {
                if (isDouble(arg[1])) {
                    double amount = Double.parseDouble(arg[1]);
                    if (amount >= 100 && amount < 1000) customer.recharge(amount);
                    else System.out.println("Recharge input illegal");
                } else System.out.println("Recharge input illegal");
            } else System.out.println("Params' count illegal");
        }
    }
    
    static class WaiterMode {
        static List<String> waiterMethodList = Arrays.asList("gl", "mo", "sr", "rw");
        static Waiter waiter;
        
        public static boolean parse_waiterMethod(String[] arg, Person waiter) {
            WaiterMode.waiter = (Waiter) waiter;
            int index = waiterMethodList.indexOf(arg[0]);
            if (index == -1) return false;
            else {
                switch (index) {
                    case 0:
                        parse_gl(arg);
                        break;
                    case 1:
                        parse_mo(arg);
                        break;
                    case 2:
                        parse_sr(arg);
                        break;
                    case 3:
                        parse_rw(arg);
                        break;
                }
            }
            return true;
        }
        
        private static void parse_rw(String[] arg) {
            if (arg.length == 3) {
                Customer customer = (Customer) PersonList.getInstance().getPersonById(arg[1]);
                if (isDouble(arg[2])) {
                    double amount = Double.parseDouble(arg[2]);
                    if (amount >= 100 && amount < 1000) {
                        customer.recharge(amount);
                        customer.isApplyVIPSuccess();
                    }
                    else System.out.println("Recharge input illegal");
                } else System.out.println("Recharge input illegal");
            } else System.out.println("Params' count illegal");
        }
        
        private static void parse_sr(String[] arg) {
            if (arg.length == 2) {
                Order order = null;
                LinkedList<Order> servedOrderList = waiter.getServedOrderList();
                for (Order o : servedOrderList) {
                    if (o.getOrderID().equals(arg[1])) {
                        order = o;
                    }
                }
                if (order != null) {
                    if (order.isCooked()) {
                        if (!order.isCheckOut()) {
                            Customer customer = (Customer) PersonList.getInstance().getPersonById(order.getCustomerID());
                            double billPrice = order.calOrderPrice();
                            if (customer.isVIP()) {
                                billPrice *= 0.8;
                            }
                            if (billPrice <= customer.getAccountBalance()) {
                                customer.checkout(billPrice);
                                order.setCheckOut(true);
                                waiter.serveOrderCntDec();
                                System.out.printf("OID:%s,DISH:%s,TOTAL:%.1f,BALANCE:%.1f\n",
                                        order.getOrderID(), order.orderPriceDetail(), billPrice, customer.getAccountBalance());
                            } else System.out.println("Insufficient balance");
                        } else System.out.println("Order already checkout");
                    } else System.out.println("Order not cooked");
                } else System.out.println("Order serve illegal");
            } else System.out.println("Params' count illegal");
        }
        
        private static void parse_mo(String[] arg) {
            if (arg.length == 1)
                if (waiter.getUnmanagedOrderList().size() == 0) System.out.println("No serving order");
                else {
                    waiter.manageOrder();
                    System.out.println("Manage order success");
                }
            else System.out.println("Params' count illegal");
        }
        
        private static void parse_gl(String[] arg) {
            if (arg.length == 1) {
                LinkedList<Order> arr = waiter.getUnmanagedOrderList();
                Iterator<Order> iter = arr.iterator();
                Order o;
                if (arr.size() == 0) System.out.println("No serving order");
                else {
                    int i = 0;
                    while (iter.hasNext()) {
                        o = iter.next();
                        System.out.printf("%d. OID:%s,DISH:%s\n", ++i, o.getOrderID(), o.toString());
                    }
                }
            } else System.out.println("Params' count illegal");
        }
    }
    
    static class KitchenMode {
        static List<String> KitchenMethodList = Collections.singletonList("cook");
        static Cook cook;
        
        public static boolean parse_waiterMethod(String[] arg, Person cook) {
            KitchenMode.cook = (Cook) cook;
            int index = KitchenMethodList.indexOf(arg[0]);
            if (index == -1) return false;
            else if (index == 0) {
                parse_cook(arg);
            }
            return true;
        }
        
        private static void parse_cook(String[] arg) {
            if (arg.length == 1) {
                Order order = Kitchen.getInstance().cook();
                if (order != null) {
                    System.out.println("Finish order:" + order.getOrderID());
                }
            } else System.out.println("Params' count illegal");
        }
        
    }
}
