import java.util.ArrayList;
import java.util.Scanner;

class PageBreakPrintModule {
    ArrayList<Dish> dishes;
    private int maxPerCnt;//每页的显示个数
    private int pageNow;//当前显示页
    private int countPage;//总页数
    private int count = 0;
    
    PageBreakPrintModule() {
    }
    
    PageBreakPrintModule(ArrayList<Dish> dishes, int startPage, int maxPerCnt) {
        this.dishes = dishes;
        this.maxPerCnt = maxPerCnt;
        count = dishes.size();
        countPage = (dishes.size() + maxPerCnt - 1) / maxPerCnt;
        if (startPage < 1) pageNow = 1;
        else pageNow = Math.min(startPage, countPage);
        printPage(slicePage());
    }
    
    private void printPage(ArrayList<Dish> list) {
        System.out.println("Page: " + pageNow);
        String format;
        int bound = list.size();
        for (int i = 0; i < bound; i++) {
            format = String.format("%d. %s", i + 1, list.get(i));
            System.out.println(format);
        }
        System.out.println("n-next page,l-last page,f-first page,q-quit");
    }
    
    private ArrayList<Dish> slicePage() {
        return new ArrayList<>(dishes.subList(Math.max(0, (pageNow - 1) * maxPerCnt), Math.min(count, pageNow * maxPerCnt)));
    }
    
    public ArrayList<Dish> previousPage() {
        if (pageNow > 1) pageNow -= 1;
        return slicePage();
    }
    
    public ArrayList<Dish> nextPage() {
        if (pageNow < countPage) pageNow += 1;
        return slicePage();
    }
    
    public ArrayList<Dish> firstPage() {
        pageNow = 1;
        return slicePage();
    }
    
    public void innerPageBreakMode() {
        Scanner scanner = Test.scanner;
        String readString;
        do {
            readString = scanner.nextLine().trim();
        } while (parseCommand(readString));
    }
    
    public boolean parseCommand(String line) {
        if (count <= 0) {
            System.out.println("Menu is empty, exit page check mode");
            return false;
        }
        String[] arguments = line.trim().split("\\s+");
        if (arguments.length != 1) {
            System.out.println("Call inner method illegal");
            return true;
        }
        switch (arguments[0]) {
            case "n":
                if (pageNow == countPage)
                    System.out.println("This is the last page");
                else printPage(nextPage());
                break;
            case "l":
                if (pageNow == 1)
                    System.out.println("This is the first page");
                else printPage(previousPage());
                break;
            case "f":
                printPage(firstPage());
                break;
            case "":
                break;
            case "q":
                System.out.println("Exit page check mode");
                return false;
            default:
                System.out.println("Call inner method illegal");
        }
        return true;
    }
    
}
