package com.example.vui_server;

import androidx.appcompat.app.AppCompatActivity;

import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MainActivity extends AppCompatActivity {
    private TextView tvIP;
    int SERVER_PORT = 12345;
    int count = 1;
    String now_temperature;
    String now_humidity;
    String SERVER_IP;
    ServerSocket serverSocket;
    Socket linkit;
    Socket phone;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initViewElement();

        // run server
        Thread mThread = new Thread(new serverThread());
        mThread.start();

    }


    class serverThread implements Runnable {
        @Override
        public void run() {
            try {
                SERVER_IP = getLocalIpAddress();
                serverSocket = new ServerSocket(SERVER_PORT);
                // print first message in server socket
                showMessageOnUi("Server started.(" + SERVER_IP + ":" + SERVER_PORT + ")");
                while(!serverSocket.isClosed()) {
                    Socket socket = serverSocket.accept();
                    if (count == 0) {
                        linkit = socket;
                        count++;
                    } else if (count == 1){
                        phone = socket;
                    }
                    Thread newClient = new Thread(new clientThread(socket));
                    newClient.start();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }


    class clientThread implements Runnable {
        private final Socket socket;

        clientThread(final Socket socket) {
            this.socket = socket;
        }

        @Override
        public void run() {
            try {
                BufferedReader reader = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
                while (this.socket.isConnected()) {
                    String msg = reader.readLine();
                    if (msg != null && msg.length() != 0) {
                        // type
                        JSONObject recvJsonObj = new JSONObject(msg);
                        String type = recvJsonObj.getString("type");
                        String content = recvJsonObj.getString("content");


                        if (type.equals("light")) {
                            PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(linkit.getOutputStream())), true);
                            out.println(msg);
                        } else if (type.equals("temperature")) {
                            if (content.equals("read")) {
                                castMsg("temperature", now_temperature, phone);
                            } else {
                                now_temperature = content;
                            }
                        } else if (type.equals("humidity")) {
                            if (content.equals("read")) {
                                castMsg("humidity", now_humidity, phone);
                            } else {
                                now_humidity = content;
                            }
                        }
                    }
                }
                // TODO remove socket from ArrayList<Socket> clients
                socket.close();
            } catch (IOException | JSONException e) {
                e.printStackTrace();
            }
        }
    }

    private void showMessageOnUi(String str) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                tvIP.append(str + "\n");
            }
        });
    }

    private String getLocalIpAddress() throws UnknownHostException {
        WifiManager wifiManager = (WifiManager) getApplicationContext().getSystemService(WIFI_SERVICE);
        assert wifiManager != null;
        WifiInfo wifiInfo = wifiManager.getConnectionInfo();
        int ipInt = wifiInfo.getIpAddress();
        return InetAddress.getByAddress(ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(ipInt).array()).getHostAddress();
    }

    private void initViewElement() {
        tvIP = findViewById(R.id.tvIP);
    }


    public static void castMsg(String type, String content, Socket socket) throws JSONException{
        // todo pack jason message
        JSONObject jsonObj = new JSONObject();
        jsonObj.put("type", type);
        jsonObj.put("content", content);
        String tmp_msg = jsonObj.toString();

        if (socket.isConnected()) {
            try {
                PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);
                out.println(tmp_msg);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

}