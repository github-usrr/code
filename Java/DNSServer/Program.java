public class Program {
    public static void main(String[] args) {

        if (args.length != 2) {
            System.err.println("Utility should start with 2 args");
            return;
        }

        if ( !args[0].matches("^(?:(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\.){3}" +
                                    "(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])$") ) {
            System.err.println("Incorrect address");
            return;
        }

        int port = Integer.parseInt(args[1]);
        if (port < 0 || port > 65535) {
            System.err.println("Incorrect port");
            return;
        }

        new DnsServer( args[0], port );
    }
}
