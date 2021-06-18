package TP2.EXO3.EMP1;

public class Producteur extends Thread{
    private int limit;
    public Producteur(String name,int limit){
        super(null,null,name);
        this.limit=limit;
    }
}