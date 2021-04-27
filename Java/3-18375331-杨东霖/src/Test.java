import java.util.Scanner;

public class Test {
    public static Scanner scanner = new Scanner(System.in);
    
    public static void main(String[] args) {
        String readString;
        Menu menu = new Menu();
        do {
            readString = scanner.nextLine().trim();//read string && clean the space at begin and end.
        } while (ParsingTerminal.parseCommand(readString, menu));
    }
}

