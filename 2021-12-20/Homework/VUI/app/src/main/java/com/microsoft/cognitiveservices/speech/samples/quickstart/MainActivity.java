package com.microsoft.cognitiveservices.speech.samples.quickstart;

import static android.Manifest.permission.INTERNET;
import static android.Manifest.permission.RECORD_AUDIO;

import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.Button;
import android.widget.TextView;

import com.microsoft.cognitiveservices.speech.ResultReason;
import com.microsoft.cognitiveservices.speech.SpeechConfig;
import com.microsoft.cognitiveservices.speech.SpeechRecognitionResult;
import com.microsoft.cognitiveservices.speech.SpeechRecognizer;
import com.microsoft.cognitiveservices.speech.SpeechSynthesisResult;
import com.microsoft.cognitiveservices.speech.SpeechSynthesizer;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.Future;

public class MainActivity extends AppCompatActivity {

    Button button;
    TextView txt;

    // Replace below with your own subscription key
    private static final String speechSubscriptionKey = "57c8906f63f64a2aa62d271da292f72f";
    // Replace below with your own service region (e.g., "westus").
    private static final String serviceRegion = "eastasia";

    private SpeechConfig speechConfig;
    private SpeechSynthesizer synthesizer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initiViewElement();

        // Note: we need to request the permissions
        int requestCode = 5; // unique code for the permission request
        ActivityCompat.requestPermissions(MainActivity.this, new String[]{RECORD_AUDIO, INTERNET}, requestCode);

        Thread thread = new Thread(new workThread());

        thread.start();
    }

    private void initiViewElement() {
        button = (Button) findViewById(R.id.button);
        txt = (TextView) this.findViewById(R.id.hello);
    }

    private void showMessageOnUi(String string) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                txt.append(string + "\n");
            }
        });
    }

    private class workThread implements Runnable {
        @Override
        public void run() {
            // Initialize speech synthesizer and its dependencies
            speechConfig = SpeechConfig.fromSubscription(speechSubscriptionKey, serviceRegion);
            assert(speechConfig != null);

            synthesizer = new SpeechSynthesizer(speechConfig);
            assert(synthesizer != null);

            // Create client socket
            SocketAddress serverAddress = new InetSocketAddress("192.168.50.82", 12345);  // server ip and port
            Socket clientSocket = new Socket();

            try {
                while (true) {
                    clientSocket.connect(serverAddress, 500);

                    if (clientSocket.isConnected()) {
                        showMessageOnUi("Connect Successfully");
                        break;
                    }
                    else {
                        showMessageOnUi("Connect Unsuccessfully");
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            }

            // Set writer and reader
            BufferedWriter bufferedWriter = null;
            try {
                bufferedWriter = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));
            } catch (IOException e) {
                e.printStackTrace();
            }

            BufferedReader bufferedReader = null;
            try {
                bufferedReader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            } catch (IOException e) {
                e.printStackTrace();
            }

            BufferedWriter finalBufferedWriter = bufferedWriter;
            BufferedReader finalBufferedReader = bufferedReader;

            button.setOnClickListener(v -> {
                try {
                    SpeechConfig config = SpeechConfig.fromSubscription(speechSubscriptionKey, serviceRegion);
                    assert(config != null);

                    SpeechRecognizer reco = new SpeechRecognizer(config);
                    assert(reco != null);

                    Future<SpeechRecognitionResult> task = reco.recognizeOnceAsync();
                    assert(task != null);

                    // Note: this will block the UI thread, so eventually, you want to
                    //        register for the event (see full samples)
                    SpeechRecognitionResult result = task.get();
                    assert(result != null);

                    if (result.getReason() == ResultReason.RecognizedSpeech) {
                        showMessageOnUi(result.getText());

                        if (result.getText().equals("Temperature.")) {
                            Map map = new HashMap();
                            map.put("type", "temperature");
                            map.put("content", "read");

                            JSONObject jsonObject = new JSONObject(map);
                            String jsonString = jsonObject.toString();

                            try {
                                finalBufferedWriter.write(jsonString);
                                finalBufferedWriter.newLine();
                                finalBufferedWriter.flush();
                            } catch (IOException e) {
                                e.printStackTrace();
                            }

                            String content = null;
                            while (clientSocket.isConnected()) {
                                String newJsonString = finalBufferedReader.readLine();

                                if (newJsonString != null && newJsonString.length() != 0) {
                                    JSONObject newJsonObject = new JSONObject(newJsonString);
                                    content = newJsonObject.getString("content");
                                    break;
                                }
                            }

                            String message = "The current temperature is " + content + " degrees payko.";
                            synthesizer.SpeakText(message);
                        }
                        else if (result.getText().equals("Humidity.")) {
                            Map map = new HashMap();
                            map.put("type", "humidity");
                            map.put("content", "read");

                            JSONObject jsonObject = new JSONObject(map);
                            String jsonString = jsonObject.toString();

                            try {
                                finalBufferedWriter.write(jsonString);
                                finalBufferedWriter.newLine();
                                finalBufferedWriter.flush();
                            } catch (IOException e) {
                                e.printStackTrace();
                            }

                            String content = null;
                            while (clientSocket.isConnected()) {
                                String newJsonString = finalBufferedReader.readLine();

                                if (newJsonString != null && newJsonString.length() != 0) {
                                    JSONObject newJsonObject = new JSONObject(newJsonString);
                                    content = newJsonObject.getString("content");
                                    break;
                                }
                            }

                            String message = "The current humidity is " + content + " percent payko.";
                            SpeechSynthesisResult result2 = synthesizer.SpeakText(message);
                        }
                        else if (result.getText().equals("Light on.")) {
                            synthesizer.SpeakText("OK payko.");

                            Map map = new HashMap();
                            map.put("type", "light");
                            map.put("content", "on");

                            JSONObject jsonObject = new JSONObject(map);
                            String jsonString = jsonObject.toString();

                            try {
                                finalBufferedWriter.write(jsonString);
                                finalBufferedWriter.newLine();
                                finalBufferedWriter.flush();
                            } catch (IOException e) {
                                e.printStackTrace();
                            }

//                            String content = null;
//                            while(clientSocket.isConnected()) {
//                                String newJsonString = finalBufferedReader.readLine();
//
//                                if (newJsonString != null && newJsonString.length() != 0) {
//                                    JSONObject newJsonObject = new JSONObject(newJsonString);
//                                    content = newJsonObject.getString("content");
//                                    break;
//                                }
//                            }
//
//                            String message = "The light is " + content + " payko.";
//                            synthesizer.SpeakText(message);
                        }
                        else if (result.getText().equals("Light off.")) {
                            synthesizer.SpeakText("OK payko.");

                            Map map = new HashMap();
                            map.put("type", "light");
                            map.put("content", "off");

                            JSONObject jsonObject = new JSONObject(map);
                            String jsonString = jsonObject.toString();

                            try {
                                finalBufferedWriter.write(jsonString);
                                finalBufferedWriter.newLine();
                                finalBufferedWriter.flush();
                            } catch (IOException e) {
                                e.printStackTrace();
                            }

//                            String content = null;
//                            while (clientSocket.isConnected()) {
//                                String newJsonString = finalBufferedReader.readLine();
//
//                                if (newJsonString != null && newJsonString.length() != 0) {
//                                    JSONObject newJsonObject = new JSONObject(newJsonString);
//                                    content = newJsonObject.getString("content");
//                                    break;
//                                }
//                            }
//
//                            String message = "The light is " + content + " payko.";
//                            synthesizer.SpeakText(message);
                        }
                        else {
                            synthesizer.SpeakText("baga! I don't know what you said.");
                        }
                    }
                    else {
                        runOnUiThread(() -> txt.setText("Error recognizing. Did you update the subscription info?" + System.lineSeparator() + result.toString()));
                    }

                    reco.close();
                } catch (Exception ex) {
                    Log.e("SpeechSDKDemo", "unexpected " + ex.getMessage());
                    assert(false);
                }
            });
        }
    }
}
