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

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutionException;
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

    private int command = 0;
    private ArrayList<String> things = new ArrayList<String>();

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
            speechConfig.setSpeechSynthesisLanguage("zh-TW");
            assert(speechConfig != null);

            synthesizer = new SpeechSynthesizer(speechConfig);
            assert(synthesizer != null);

            button.setOnClickListener(v -> {
                try {
                    SpeechConfig config = SpeechConfig.fromSubscription(speechSubscriptionKey, serviceRegion);
                    config.setSpeechRecognitionLanguage("zh-TW");
                    assert(config != null);

                    SpeechRecognizer reco = new SpeechRecognizer(config);
                    assert(reco != null);

                    if (command == 0) {
                        String message = "請問您需要什麼幫助？";
                        synthesizer.SpeakText(message);
                    }

                    Future<SpeechRecognitionResult> task = reco.recognizeOnceAsync();
                    assert(task != null);

                    // Note: this will block the UI thread, so eventually, you want to
                    //        register for the event (see full samples)
                    SpeechRecognitionResult result = task.get();
                    assert(result != null);

                    if (result.getReason() == ResultReason.RecognizedSpeech) {
                        showMessageOnUi(result.getText());

                        Thread testThread = new Thread(new Runnable() {
                            @Override
                            public void run() {
                                String message;

                                if (command == 0) {
                                    if (result.getText().equals("我要新增待辦事項。") || result.getText().contains("新增") || result.getText().contains("建立")) {
                                        message = "好的，請問待辦事項的內容是什麼呢？";
                                        synthesizer.SpeakText(message);

                                        try {
                                            SpeechConfig config2 = SpeechConfig.fromSubscription(speechSubscriptionKey, serviceRegion);
                                            config2.setSpeechRecognitionLanguage("zh-TW");
                                            assert(config2 != null);

                                            SpeechRecognizer reco2 = new SpeechRecognizer(config2);
                                            assert(reco2 != null);

                                            Future<SpeechRecognitionResult> task2 = reco2.recognizeOnceAsync();
                                            assert(task2 != null);

                                            SpeechRecognitionResult result2 = task2.get();
                                            assert(result2 != null);

                                            if (result2.getReason() == ResultReason.RecognizedSpeech) {
                                                if (result2.getText().equals("取消命令") || (result2.getText().contains("取消"))) {
                                                    message = "好的，請重新輸入命令。";
                                                    synthesizer.SpeakText(message);
                                                }
                                                else {
                                                    String thing = result2.getText();
                                                    things.add(thing);

                                                    message = "待辦事項建立成功。";
                                                    synthesizer.SpeakText(message);
                                                }
                                            }
                                        } catch (ExecutionException e) {
                                            e.printStackTrace();
                                        } catch (InterruptedException e) {
                                            e.printStackTrace();
                                        }

                                        // command = 1;
                                    } else if (result.getText().equals("我有哪些待辦事項？") || result.getText().contains("哪些")) {
                                        if (things.size() == 0) {
                                            message = "您目前沒有任何待辦事項。";
                                            synthesizer.SpeakText(message);
                                        } else {
                                            message = "您目前有" + Integer.toString(things.size()) + "件待辦事項。";
                                            synthesizer.SpeakText(message);

                                            for (int i = 0; i < things.size(); i++) {
                                                message = "第" + Integer.toString(i + 1) + "件待辦事項：" + things.get(i);
                                                synthesizer.SpeakText(message);
                                            }
                                        }
                                    } else if (result.getText().equals("刪除所有待辦事項。") || (result.getText().contains("刪除") && result.getText().contains("所有"))) {
                                        message = "好的，沒問題。";
                                        synthesizer.SpeakText(message);

                                        things.clear();
                                    } else if (result.getText().equals("刪除待辦事項。") || (result.getText().contains("刪除"))) {
                                        message = "好的，請問要刪除哪一個待辦事項呢？";
                                        synthesizer.SpeakText(message);

                                        try {
                                            SpeechConfig config2 = SpeechConfig.fromSubscription(speechSubscriptionKey, serviceRegion);
                                            config2.setSpeechRecognitionLanguage("zh-TW");
                                            assert(config2 != null);

                                            SpeechRecognizer reco2 = new SpeechRecognizer(config2);
                                            assert(reco2 != null);

                                            Future<SpeechRecognitionResult> task2 = reco2.recognizeOnceAsync();
                                            assert(task2 != null);

                                            SpeechRecognitionResult result2 = task2.get();
                                            assert(result2 != null);

                                            if (result2.getReason() == ResultReason.RecognizedSpeech) {
                                                if (result2.getText().equals("取消命令") || (result2.getText().contains("取消"))) {
                                                    message = "好的，請輸入新命令。";
                                                    synthesizer.SpeakText(message);
                                                }
                                                else {
                                                    String thing = result2.getText();

                                                    if (things.size() == 0) {
                                                        message = "您目前沒有任何待辦事項。";
                                                    } else {
                                                        for(int i = 0; i < things.size(); i++) {
                                                            if (things.get(i).equals(thing)) {
                                                                things.remove(i);
                                                                message = "成功刪除待辦事項。";
                                                            }
                                                            else if (i == things.size() - 1) {
                                                                message = "沒有在待辦清單中找到" + thing + "這項待辦事項，請再確認。";
                                                            }
                                                        }
                                                    }

                                                    synthesizer.SpeakText(message);
                                                }
                                            }
                                        } catch (ExecutionException e) {
                                            e.printStackTrace();
                                        } catch (InterruptedException e) {
                                            e.printStackTrace();
                                        }
                                    } else {
                                        message = "無法辨識命令，請確認命令是否正確。";
                                        synthesizer.SpeakText(message);
                                    }
                                }
                                else if (result.getText().equals("取消命令") || (result.getText().contains("取消"))) {
                                    message = "好的，請輸入新命令。";
                                    synthesizer.SpeakText(message);

                                    command = 0;
                                }
                                else if (command == 1) {
                                    String thing = result.getText();
                                    things.add(thing);

                                    message = "待辦事項建立成功。";
                                    synthesizer.SpeakText(message);

                                    command = 0;
                                } else {
                                    message = "不可能進入此區塊。";
                                    synthesizer.SpeakText(message);
                                }
                            }
                        });

                        testThread.start();
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
