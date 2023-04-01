public class Car extends AbstractCar {

    Car(final float speed, final int seatsCount) {
        super(speed);
        this.seatsCount = seatsCount;
    }

    public void takePassengers() {
        System.out.println( "Car takes " +
                String.format("%d", seatsCount-1) + " passengers");
    }

    public String toString() {
        return "(Car: speed:" + String.format("%.1f", speed)
                + ", seats:" + String.format("%d", seatsCount) + ")";
    }

    public int getSeatsCount() {
        return seatsCount;
    }

    private final int seatsCount;
}
