package TP2.EXO1;

public class TestThread {
    public static void main(String[] args) throws InterruptedException {
        PrintDemo pd=new PrintDemo();
        ThreadDemo T1=new ThreadDemo("Thread - 1",pd),
                T2=new ThreadDemo("Thread - 2",pd);

        T1.start();
        T2.start();

        T1.join();
        T2.join();
    }
}
