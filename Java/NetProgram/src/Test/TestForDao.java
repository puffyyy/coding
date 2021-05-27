package Test;

public class TestForDao {
    public static void main(String[] args) {
        TestForDao testForDao = new TestForDao();
        testForDao.run();
        
    }
    
    public void run() {
        System.out.println(getClass().getResource(""));
        System.out.println(getClass().getClassLoader().getResource(""));
        System.out.println(getClass().getClassLoader().getResource("./image/options.png"));
        System.out.println(getClass().getClassLoader().getResource("./image/options.png").getPath());
    }
}


