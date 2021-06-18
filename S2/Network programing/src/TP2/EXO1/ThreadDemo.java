package TP2.EXO1;

public class ThreadDemo extends Thread {
    static int tIn=0;
    String threadName;
    PrintDemo pD;

    ThreadDemo(String name, PrintDemo pd) {
        super();
        this.pD = pd;
        this.threadName = name;
    }

    @Override
    public void run() {
        System.out.println(this.threadName);

        try {
            synchronized (pD){
                if (tIn > 0)
                    pD.wait();
                tIn++;
                this.pD.printCount();
                System.out.println("Done "+threadName);
                if(tIn>0) pD.notify();
                tIn--;
            }

        } catch (InterruptedException e) {
            e.printStackTrace();
        }


    }

}
