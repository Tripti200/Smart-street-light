#include<ESP8266WiFi.h>

#include<BlynkSimpleEsp8266.h>

int start_light,end_light;
int LDR_Pin=A0; //LDR - andhera aur ujala check karta hai ::  0-1023   /   2^10
char blynk_auth[] = "Ra3oDWp6-PKdOdDOWGGzfe8hzfmaGRK4";             // Blynk_Auth_Token

const char *ssid =  "123";                            // replace with your wifi ssid and wpa2 key
const char *pass =  "12345678";

WidgetLED p1(V1);                   // led

void setup() {
  // put your setup code here, to run once:
  pinMode(V0,INPUT);    //start_light
  pinMode(V2,INPUT);    //end_light
  pinMode(V4,OUTPUT);   //LED
  Serial.begin(9600);

  Serial.println("");
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Blynk.begin(blynk_auth,ssid,pass);
}

void loop() {

  Blynk.run();                                                              // Blynk magic 
  
  // put your main code here, to run repeatedly:
  start_light=digitalRead(V0);
  if(start_light==0 && analogRead(LDR_Pin)<300){
    Serial.println("light on");
    digitalWrite(V4,HIGH);
    p1.on();
    delay(100);
  }
  end_light=digitalRead(V2);
  if(end_light==0){
    Serial.println("light off");
    digitalWrite(V4,LOW);
    p1.off();
    delay(100);
  }
}
