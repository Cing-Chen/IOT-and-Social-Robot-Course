#include <LWiFi.h>
#include <Arduino_JSON.h>
#include <DHT.h>
#include <Grove_LED_Bar.h>
#include <Wire.h>
#include <mpu9250_blockly.h>

const char* ssid = "TELDAP"; //Sunny-Huawei-Y9-2019 0968902921  
const char* password = "TELDAP4F"; //TELDAP4F

const char * host = "192.168.0.229"; // TODO: server ip 192.168.43.79 (172.20.10.6:7100)
const uint16_t port = 7100; // TODO: server port 12345

WiFiClient client;

DHT __dht2(2,DHT22);
MPU9250Block mpu;

String Linkitstatus="none";
int buttonPin=6;
int times=0;
double axcheck;
double axhistory;
double aycheck;
double ayhistory;
double azcheck,azhistory;
double Firecheck;
int val=0;
int safe=0;
int ledstatus=0;
int earthquakecheck=0;
int firecheck=0;

void pin_change(void){
  val = 0;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(12,OUTPUT); // led
  digitalWrite(12,LOW); //led
  pinMode(17,INPUT); //button
  attachInterrupt(buttonPin, pin_change, RISING);
  Wire.begin(); // xyz
  Serial.begin(9600);
  Serial.println("Run Temp&Humid...");
  __dht2.begin(); 
  Serial.println("Run MPU9250Block...");
  mpu.begin();
  Serial.println("Waiting conenct server...");
 
 //Mxyz_init_calibrated ();

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Humid:");
  Serial.println(__dht2.readHumidity());
  Serial.print("Temp:");
  Serial.println(__dht2.readTemperature());
  Firecheck= __dht2.readTemperature();
  
  const double ax = mpu.getAccX();
  const double ay = mpu.getAccY();
  const double az = mpu.getAccZ();
  
  Serial.print("ax,ay,az:");
  Serial.print(ax);
  Serial.print(",");
  Serial.print(ay);
  Serial.print(",");
  Serial.println(az);

  if(times==0)
  {
    axhistory=ax;
    ayhistory=ay;
    azhistory=az;
    times=1;
  }else{
    axcheck=ax-axhistory;
    aycheck=ay-ayhistory;
    azcheck=az-azhistory;
    if(axcheck<0)
    {
      axcheck=axcheck*(-1);
    }
    if(aycheck<0){
      aycheck=aycheck*(-1);
    }
    if(azcheck<0){
      azcheck=azcheck*(-1);
    }
    axhistory=ax;
    ayhistory=ay;
    azhistory=az;
    Serial.println("check earthquake");
    Serial.print(axcheck);
    Serial.print(",");
    Serial.print(aycheck);
    Serial.print(",");
    Serial.println(azcheck);
  }
  if(HIGH == digitalRead(17) && ledstatus==0){
    digitalWrite(12,HIGH);
    ledstatus=1;
  }else if(HIGH == digitalRead(17) && ledstatus==1){
    digitalWrite(12,LOW);
    ledstatus=0;
  }
  
  //Serial.println("");
  if(client.connected()) {
    JSONVar JSONSos;
    JSONSos["type"] = "disaster";
      
    //JSONVar JSONlight;
    //JSONlight["type"] = "light";
    //JSONlight["content"] = analogRead(A0);

    //String JSONlightString = JSON.stringify(JSONlight) + "\n";
    //client.print(JSONlightString);
    if(earthquakecheck==0 && axcheck>0.02 || earthquakecheck==0 && aycheck>0.02 || earthquakecheck==0 && azcheck>0.02){
      safe=1;
      val=1;
      earthquakecheck=1;
      Linkitstatus="earthquake";
      JSONSos["content"] = Linkitstatus;
      String JSONsendSos = JSON.stringify(JSONSos) + "\n";
      client.print(JSONsendSos);
    }else if(earthquakecheck==1 && axcheck<0.01 && aycheck<0.01 && azcheck<0.01){
      Linkitstatus="end";
      earthquakecheck=0;
      JSONSos["content"] = Linkitstatus;
      String JSONsendSos = JSON.stringify(JSONSos) + "\n";
      client.print(JSONsendSos);
    }
    
    if(Firecheck>30)
    {
      Serial.println("!!-Temp Error-!!!");
    }
    else if(Firecheck<30 && Firecheck>25 && firecheck==0){
      Linkitstatus="fire";
      safe=1;
      val=1;
      firecheck=1;
      JSONSos["content"] = Linkitstatus;
      String JSONsendSos = JSON.stringify(JSONSos) + "\n";
      client.print(JSONsendSos);
    }
    else if(Firecheck<23 && firecheck==1)
    {
      Linkitstatus="end";
      firecheck=0;
      JSONSos["content"] = Linkitstatus;
      String JSONsendSos = JSON.stringify(JSONSos) + "\n";
      client.print(JSONsendSos);
    }
    

    if(Linkitstatus=="earthquake"||Linkitstatus=="fire"){
      //digitalWrite(17,LOW);
      digitalWrite(12,LOW);
    }

   // if(Linkitstatus=="fire"){
   //   while(true){
   //     if(safe==0){
          
   //       break;
   //     }
        
   //     if(val==1){
   //       if(Linkitstatus=="fire"){
   //         Serial.println("Fire.......");
   //       }
   //       else if(Linkitstatus=="earthquake"){
   //       Serial.println("Earthquake.......");
   //       }
   //       delay(500);
   //     }
   //     else{
   //       safe=0;
   //       Linkitstatus="none";
   //       Serial.println("Safe click!");
   //     }
   //   }
   // }
  }
  else
  {
    if(!client.connect(host, port)) {
      
      Serial.println("Connection to host failed");
      delay(1000);
    }
    else {
      Serial.println("Connected to server successful!");
    }
  }
}
