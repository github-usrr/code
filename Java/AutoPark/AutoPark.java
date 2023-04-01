import java.util.ArrayList;
import java.util.Arrays;

public class AutoPark {

    public String toString() {
        return carsList.toString();
    }

    public int size() {
        return carsList.size();
    }

    public AbstractCar getCar(int carIndex) {
        return carsList.get(carIndex);
    }

    public void add(AbstractCar car) {
        carsList.add(car);
    }

    public void remove(int carIndex) {
            carsList.remove(carIndex);
    }

    public void driveCars() {
        for (AbstractCar car : carsList) {
            car.drive();
        }
    }

    public void stopCars() {
        for (AbstractCar car : carsList) {
            car.stop();
        }
    }

    private ArrayList<AbstractCar> carsList = new ArrayList<>( Arrays.asList(
              new Car(80, 4)
            , new Car(90, 5)
            , new Car(70, 3)
            , new Truck(50, 2.1f)
            , new Truck(40, 1.8f)
    ) );  // initial auto park
}
