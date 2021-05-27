package Mode;

import entity.Customer;
import entity.Dish;
import entity.Menu;
import entity.Order;
import util.Cache;
import util.judge;

import java.util.Scanner;

public class OrderMode {
    private final Order order;
    
    public OrderMode(Customer customer) {
        order = customer.getOrderList().getCurNewOrder();
    }
    
    public void orderMode() {
        Scanner scanner = Cache.scanner;
        String readString;
        do {
            readString = scanner.nextLine().trim();
        } while (parseCommand(readString));
    }
    
    private boolean parseCommand(String readString) {
        String[] arg = readString.trim().split("\\s+");
        switch (arg[0]) {
            case "add":
                parse_add(arg);
                break;
            case "finish":
                return parse_finish(arg);
            default:
                System.out.println("Command not exist");
                break;
        }
        return true;
    }
    
    private boolean parse_finish(String[] arg) {
        if (arg.length == 1) {
            if (order.getDishSize() == 0) {
                System.out.println("Please select at least one dish to your order");
            } else {
                return false;// exit
            }
        } else System.out.println("Params' count illegal");
        return true;
    }
    
    private void parse_add(String[] arg) {
        if (arg.length >= 2) {
            // function search id
            Menu menu = Menu.getInstance();
            if (arg[1].equals("-i")) {
                if (arg.length == 4) {
                    if (judge.isDishIdLegal(arg[2])) {
                        Dish getDish = menu.getDishById(arg[2]);
                        parse_add_addDish(arg, getDish);
                    } else System.out.println("Did input illegal");
                } else System.out.println("Params' count illegal");
            } else if (arg[1].equals("-n")) {
                if (arg.length == 4) {
                    Dish getDish = menu.getDishByName(arg[2]);
                    parse_add_addDish(arg, getDish);
                } else System.out.println("Params' count illegal");
            } else System.out.println("Command not exist");
        } else System.out.println("Command not exist");
    }
    
    private void parse_add_addDish(String[] arg, Dish getDish) {
        if (getDish != null) {
            int cnt = Integer.parseInt(arg[3]);
            if (getDish.getDishTotalAmount() == 0)
                System.out.println("Dish selected is sold out");
            else if (cnt <= getDish.getDishTotalAmount()) {
                order.addDish(getDish, cnt);
            } else {
                System.out.println("Dish is out of stock");
            }
        } else System.out.println("Dish selected not exist");
    }
}