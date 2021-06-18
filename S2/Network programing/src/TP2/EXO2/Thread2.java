package TP2.EXO2;

public class Thread2 extends Thread {
    @Override
    public void run() {

        try {
            synchronized (this){
                wait();
                System.out.println("Affichage du thread B :");
                for (int i = 2; i <= 6; i++) {
                    Thread.sleep(100);
                    System.out.println(i + "ème ligne du thread B");

                }
            }

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
