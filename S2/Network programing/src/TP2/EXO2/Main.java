package TP2.EXO2;

public class Main {
    static int Sem=0;
    public static void main(String[] args) throws InterruptedException {
        Thread TA= new Thread(new Thread1());
        Thread2 TB = new Thread2();

        TA.start();
        TB.start();
        TA.join();
        synchronized (TB){
            TB.notify();
        }
        TB.join();
    }
}
