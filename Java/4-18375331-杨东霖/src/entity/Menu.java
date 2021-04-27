package entity;

import util.judge;

import java.util.*;
import java.util.stream.Collectors;

public class Menu {
    private final HashMap<String, Dish> menuDishMap;
    private final TreeMap<String, String> menuId2NameMap;
    
    public Menu() {
        menuDishMap = new HashMap<>();
        menuId2NameMap = new TreeMap<>(Dish::dishIDCompareTo);
    }
    
    public boolean isDishExistById(String did) {
        return menuDishMap.containsKey(did);
    }
    
    public boolean isRepeatedByName(String name) {
        if (menuId2NameMap.isEmpty()) return false;
        return menuId2NameMap.values().stream().anyMatch(name::equals);
    }
    
    //public int dishCountInMenu() {return menuDishMap.size();}
    
    /**
     * @return pragma is legal or not
     * @order nd
     */
    public int newDishAdd(Dish dish) {
        if (judge.isDishAttributeLegal(dish)) {
            if (!isRepeatedByName(dish.getDishName())) {
                menuDishMap.put(dish.getDishId(), dish);
                menuId2NameMap.put(dish.getDishId(), dish.getDishName());
                return 1;
            } else return -2;
        } else return -1;
    }
    
    /**
     * @order nd
     */
    public int newDishAdd(String did, String name, Double price, Integer total) {
        Dish dish = new Dish(did, name, price, total);
        return newDishAdd(dish);
    }
    
    // assume id is exist.
    public int updateDish(String did, String name) {
        if (!judge.isDishAttributeLegal(name)) return -1;
        Dish oldDish = getDishById(did);
        if (oldDish.getDishName().equals(name) || isRepeatedByName(name)) return -2;
        oldDish.setDishName(name);
        menuId2NameMap.replace(did, name);
        return 1;
    }
    
    public boolean updateDish(String did, Integer total) {
        if (!judge.isDishAttributeLegal(total)) return false;
        Dish oldDish = getDishById(did);
        oldDish.setDishTotalAmount(total);
        return true;
    }
    
    public boolean updateDish(String did, Double price) {
        if (!judge.isDishAttributeLegal(price)) return false;
        Dish oldDish = getDishById(did);
        oldDish.setDishPrice(price);
        return true;
    }
    
    /**
     * @return exist ? value : null
     * @order gd
     */
    public Dish getDishById(String did) {
        return menuDishMap.get(did);
    }
    
    /**
     * @return ArrayList
     * @order gd
     */
    public ArrayList<Dish> getDishByKeyWord(String keyword) {
        ArrayList<Dish> dishArr = new ArrayList<>();
        Iterator<Map.Entry<String, String>> iter = menuId2NameMap.entrySet().iterator();
        Map.Entry<String, String> entry;
        while (iter.hasNext()) {
            entry = iter.next();
            if (entry.getValue().toLowerCase(Locale.ROOT).contains(keyword.toLowerCase(Locale.ROOT)))
//                dishVec.add(menuDishMap.get(entry.getKey()));
                dishArr.add(menuDishMap.get(entry.getKey()));
        }
        return dishArr;
    }
    
    public String[] idList() {
        return menuId2NameMap.keySet().toArray(new String[0]);
    }
    
    public ArrayList<Dish> getAllDishList() {
        String[] idList = idList();
        if (idList.length <= 0) return new ArrayList<>();
        return Arrays.stream(idList).map(this::getDishById).collect(Collectors.toCollection(ArrayList::new));
    }
}