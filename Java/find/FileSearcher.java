import java.io.File;

public class FileSearcher {
    public void exec(String[] args) throws RuntimeException {

        if ( !args[0].equals("find") ) {
            throw new RuntimeException("First argument of FileSearcher should be \"find\"");
        }

        String dirPath = (args.length == 2) ? System.getProperty("user.dir") // pwd
                                            : args[2]; // custom dir

        File directory = new File(dirPath);
        if ( !directory.isDirectory() ) {
            throw new RuntimeException("3rd argument of FileSearcher isn't a directory");
        }

        printMatchedFiles( directory, ".*" + args[1] + ".*" );
    }

    private void printMatchedFiles(File directory, String regex) {

        File[] files = directory.listFiles();
        if (files == null) return;

        for ( File f : files ) {
            if ( f.isDirectory() ) {
                printMatchedFiles(f, regex);
            }
            else if ( f.getName().matches(regex) ) {
                System.out.println(f.getAbsolutePath());
            }
        }
    }
}
