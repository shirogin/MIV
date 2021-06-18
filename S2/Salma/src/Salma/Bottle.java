package Salma;

import java.util.Objects;

public class Bottle {
    double bottomRadius = 2.5,
            height = 12,
            capRaduis = 1,
            neckRaduis = 1.5,
            capacity = 1.5,
            filledPercentage = 0;

    public Bottle(double height){
        this.height=height;
    }
    //methods
    void fillBottle(double capacity) {
        this.filledPercentage += (capacity * 100 / this.capacity) / 100;
    }
    void fillBottle(int capacity) {
        this.filledPercentage += (capacity * 100 / this.capacity) / 100;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null ||o instanceof Bottle) return false;
        Bottle bottle = (Bottle) o;
        return Double.compare(bottle.bottomRadius, bottomRadius) == 0 && Double.compare(bottle.height, height) == 0 && Double.compare(bottle.capRaduis, capRaduis) == 0 && Double.compare(bottle.neckRaduis, neckRaduis) == 0 && Double.compare(bottle.capacity, capacity) == 0 && Double.compare(bottle.filledPercentage, filledPercentage) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(bottomRadius, height, capRaduis, neckRaduis, capacity, filledPercentage);
    }

    @Override
    public String toString() {

        return super.toString()+" Bottle{" +
                "bottomRadius=" + bottomRadius +
                ", height=" + height +
                ", capRaduis=" + capRaduis +
                ", neckRaduis=" + neckRaduis +
                ", capacity=" + capacity +
                ", filledPercentage=" + filledPercentage +
                '}';
    }
}
