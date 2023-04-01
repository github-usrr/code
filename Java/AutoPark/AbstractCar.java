public abstract class AbstractCar implements Driven, Stoppable {

    AbstractCar(float speed) {
        this.speed = speed;
        isStopped = true;
    }

    public abstract void takePassengers();

    public void drive() {
        isStopped = false;
        System.out.println("Car is moving, speed = " + String.format("%.1f", speed));
    }

    public void stop() {
        isStopped = true;
        System.out.println("Car has been stopped");
    }

    public void signal() {
        System.out.println("beep");
    }

    public float getSpeed() {
        return isStopped ? 0 : speed;
    }

    public void setSpeed(float speed) {
        this.speed = speed;
    }

    protected float speed;  // km/h
    private boolean isStopped;  // so that getSpeed() returns 0 when car is stopped
}
