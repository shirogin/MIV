package TP2.EXO2;

public class Thread1 implements Runnable {
    @Override
    public void run() {
        System.out.println("Affichage du thread A :");
        try {
            for (int i = 2; i <= 6; i++) {
                Thread.sleep(100);
                System.out.println(i + "ème ligne du thread A");
            }

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
