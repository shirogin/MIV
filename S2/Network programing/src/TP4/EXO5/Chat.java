package TP4.EXO5;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Chat extends Remote {
    public void makeNote(String note) throws RemoteException;
    public String getList() throws RemoteException;
}
