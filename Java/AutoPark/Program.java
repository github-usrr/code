public class Program {

    public static void main(String[] args) {

        // test 1
        AutoPark park = new AutoPark();
        System.out.println( park );

        park.add(new Car(100, 2));
        System.out.println( park );

        park.remove(park.size() - 1);
        System.out.println( park );

        // test 2
        System.out.println("\n");
        park.getCar(0).setSpeed(10);
        System.out.println("Car's speed is still " + park.getCar(0).getSpeed());
        park.getCar(0).drive();
        System.out.println("And now Car's speed is " + park.getCar(0).getSpeed());

        // test 3
        System.out.println("\n");
        park.driveCars();
        park.stopCars();

        // test 4
        System.out.println("\n");
        park.getCar(0).takePassengers();
        park.getCar(4).takePassengers();
    }
}
