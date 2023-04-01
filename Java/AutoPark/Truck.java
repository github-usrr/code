public class Truck extends AbstractCar {

    Truck(final float speed, final float cargoWeight) {
        super(speed);
        this.cargoWeight = cargoWeight;
    }

    public void takePassengers() {
        System.out.println( "Truck takes only one passenger");
    }

    public String toString() {
        return "(Truck: speed:" + String.format("%f", speed)
                + ", cargo:" + String.format("%.1f", cargoWeight) + " tons)";
    }

    public float getCargoWeight() {
        return cargoWeight;
    }

    public void setCargoWeight(float cargoWeight) {
        this.cargoWeight = cargoWeight;
    }

    private float cargoWeight;  // Weight in tons
}