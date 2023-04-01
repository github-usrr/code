import java.io.File;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class FileSearcher {
    public void exec(String[] args) throws RuntimeException{

        if (args.length < 2 || args.length > 3) {
            throw new RuntimeException("Utility should start with 2 or 3 arguments");
        }

        if ( !args[0].equals("grep") ) {
            throw new RuntimeException("First argument should be \"grep\"");
        }

        String dirPath = (args.length == 2) ? System.getProperty("user.dir") // pwd
                                            : args[2]; // custom dir
        File directory = new File(dirPath);
        if ( !directory.isDirectory() ) {
            throw new RuntimeException("Third argument isn't a directory");
        }

        pool = Executors.newFixedThreadPool(4);
        printMatchedFiles( directory, args[1] );
        pool.shutdown();
    }

    private void printMatchedFiles(File directory, String str) {

        File[] files = directory.listFiles();
        if (files == null) return;

        for ( File f : files ) {
            if ( f.isDirectory() ) {
                printMatchedFiles(f, str);
            } else {
                pool.submit( new Worker(f, str) );  // process the File f
            }
        }
    }

    private class Worker implements Runnable {

        public Worker(File f, String str) {
            this.f = f;
            this.str = str;
        }

        @Override
        public void run() {
            BufferedReader br = null;
            try {
                br = new BufferedReader(new FileReader(f));
            }
            catch (IOException ex) {
                ex.printStackTrace();
                return;
            }

            int lineCtr = 1;
            String line;
            while (true) {
                try {
                    if ( (line = br.readLine()) == null )
                        break;
                } catch (IOException ex) {
                    ex.printStackTrace();
                    return;
                }
                if ( line.contains(str) ) {
                    synchronized (this) {
                        System.out.println( Thread.currentThread().getName() + " " +  //debug info
                                f + ":line:" + lineCtr + ": " + line );
                    }
                }
                lineCtr++;
            }

            try {
                br.close();
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }

        private File f;
        private String str;
    }

    private ExecutorService pool;
}
