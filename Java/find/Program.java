import java.io.File;
import java.io.FilenameFilter;

public class Program {

    public static void main(String[] args) {

        FileSearcher searcher = new FileSearcher();

        try {
            searcher.exec(args);
        }
        catch (RuntimeException ex) {
            ex.printStackTrace();
        }
    }
}
