package TP2.EXO1;

public class PrintDemo {
    public void printCount() {
        try {

            for (int i = 5; i > 0; i--) {
                System.out.println("Counter --- " + i);
            }
        } catch (Exception e) {
            System.out.println("Thread interrupted.");
        }
    }
}
