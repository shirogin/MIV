package TP4.EXO4;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface eEventLogger extends Remote {
    public void makeNote(String note) throws RemoteException;
    public String getList() throws RemoteException;
}
