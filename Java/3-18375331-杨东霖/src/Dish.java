import java.util.Objects;

public class Dish {
    private String dishId;
    private String dishName;
    private Double dishPrice;
    private Integer dishTotalAmount;
    
    public Dish() {
    }
    
    public Dish(String dishId, String dishName, Double dishPrice, Integer dishTotalAmount) {
        this.dishId = dishId;
        this.dishName = dishName;
        this.dishPrice = dishPrice;
        this.dishTotalAmount = dishTotalAmount;
    }
    //bean
    public String getDishName() {
        return dishName;
    }
    
    public void setDishName(String dishName) {
        this.dishName = dishName;
    }
    
    public String getDishId() {
        return dishId;
    }
    
    public void setDishId(String dishId) {
        this.dishId = dishId;
    }
    
    public Double getDishPrice() {
        return dishPrice;
    }
    
    public void setDishPrice(Double dishPrice) {
        this.dishPrice = dishPrice;
    }
    
    public Integer getDishTotalAmount() {
        return dishTotalAmount;
    }
    
    public void setDishTotalAmount(Integer dishTotalAmount) {
        this.dishTotalAmount = dishTotalAmount;
    }
    
    @Override
    public int hashCode() {
        return dishId.hashCode();
    }
    
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Dish)) return false;
        Dish dish = (Dish) o;
        return Objects.equals(getDishId(), dish.getDishId()) &&
                Objects.equals(getDishName(), dish.getDishName()) &&
                Objects.equals(getDishPrice(), dish.getDishPrice()) &&
                Objects.equals(getDishTotalAmount(), dish.getDishTotalAmount());
    }
    
    @Override
    public String toString() {
        return String.format("DID:%s,DISH:%s,PRICE:%.1f,TOTAL:%d", dishId, dishName, dishPrice, dishTotalAmount);
    }
    
    //my func
    static public boolean isDishIdLegal(String did) {
        return did.matches("^[HCO]\\d{6}$");
    }
    
    static public boolean isDishAttributeLegal(String name) {
        return name.matches("^[A-Za-z0-9]+$");
    }
    
    static public boolean isDishAttributeLegal(Double price) {
        return price >= 0;
    }
    
    static public boolean isDishAttributeLegal(Integer total) {
        return total >= 0;
    }
    
    static public boolean isDishAttributeLegal(Dish dish) {
        return isDishIdLegal(dish.getDishId()) && isDishAttributeLegal(dish.getDishName()) && isDishAttributeLegal(dish.getDishPrice()) && isDishAttributeLegal(dish.getDishTotalAmount());
    }
    
    static public int dishIDCompareTo(String id1, String id2) {
        char ch1 = id1.charAt(0);
        char ch2 = id2.charAt(0);
        if (ch1 == ch2) {
            return id1.substring(1).compareTo(id2.substring(1));
        } else if (ch1 == 'H' || (ch1 == 'C' && ch2 == 'O')) return -1;
        else return 1;
    }
}

