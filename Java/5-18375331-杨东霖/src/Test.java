import Mode.ParsingTerminal;
import util.Cache;

import java.util.Scanner;

public class Test {
    
    public static void main(String[] args) {
        Cache.scanner = new Scanner(System.in);
        Scanner scanner = Cache.scanner;
        String readString;
        do {
            readString = scanner.nextLine().trim();//read string && clean the space at begin and end.
        } while (ParsingTerminal.parseCommand(readString));
    }
}