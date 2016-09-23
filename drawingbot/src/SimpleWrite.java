package drawingbot;

import java.io.*;
import java.util.*;
import javax.comm.*;

public class SimpleWrite {
    static Enumeration portList;
    static CommPortIdentifier portId;
    static String messageString = "Hello, world!\n";
    static SerialPort serialPort;
    static OutputStream outputStream;

    public SimpleWrite(){
        portList = CommPortIdentifier.getPortIdentifiers();

        while (portList.hasMoreElements()) {
            portId = (CommPortIdentifier) portList.nextElement();
            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
                 if (portId.getName().equals("COM1")) {
                //if (portId.getName().equals("/dev/term/a")) {
                    try {
                        serialPort = (SerialPort)
                            portId.open("SimpleWriteApp", 2000);
                    } catch (PortInUseException e) {}
                    try {
                        outputStream = serialPort.getOutputStream();
                    } catch (IOException e) {}
                    try {
                        serialPort.setSerialPortParams(9600,
                            SerialPort.DATABITS_8,
                            SerialPort.STOPBITS_1,
                            SerialPort.PARITY_NONE);
                    } catch (UnsupportedCommOperationException e) {}
                    
                }
            }
        }
    }
    
    public void write(int x, int y){
        messageString=x+" "+y+"\n";
        try {           if(outputStream!=null)
                        outputStream.write(messageString.getBytes());
                    } catch (IOException e) {}
    }
    
    public static void main(String[] args) {
        SimpleWrite simpleWrite=new SimpleWrite();
        simpleWrite.write(0, 0);
    }
}