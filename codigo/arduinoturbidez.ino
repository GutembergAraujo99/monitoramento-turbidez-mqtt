#include <WiFiS3.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <Servo.h>


#define WLAN_SSID       "sua rede wifi"
#define WLAN_PASS       "senha da rede"


#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   
#define AIO_USERNAME    "login adafruit"
#define AIO_KEY         "chave api"


const int pinoTurbidez = A0;
const int pinoServo = 9;

Servo meuServo;
int valorAguaLimpa = 0; 
const int diferencaDisparo = 10; 
bool motorJaRodou = false;


WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);


Adafruit_MQTT_Publish feedTurbidez = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/turbidez");
Adafruit_MQTT_Publish feedMotor = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/motor");

void conectarMQTT();

void setup() {
  Serial.begin(9600);
  delay(10);

  meuServo.attach(pinoServo); 
  meuServo.write(0); 


  Serial.print("Conectando em: ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Conectado!");

  
  Serial.println("Calibrando sensor por 7 segundos...");
  long somaInicial = 0;
  for (int i = 0; i < 140; i++) {
    somaInicial += analogRead(pinoTurbidez);
    delay(50); 
  }
  valorAguaLimpa = somaInicial / 140;
  Serial.print("Valor padrao fixado em: ");
  Serial.println(valorAguaLimpa);
}

void loop() {
  conectarMQTT();

  long somaLeituras = 0;
  for (int i = 0; i < 20; i++) {
    somaLeituras += analogRead(pinoTurbidez);
    delay(5); 
  }
  int leituraAtual = somaLeituras / 20;
  int quedaDeValor = valorAguaLimpa - leituraAtual;

  if (quedaDeValor >= diferencaDisparo) {
    if (!motorJaRodou) {
      meuServo.write(180); 
      motorJaRodou = true;
      feedMotor.publish("FECHADO"); 
    }
  } else {
    if (motorJaRodou) {
      meuServo.write(0); 
      motorJaRodou = false;
      feedMotor.publish("ABERTO"); 
    }
  }

 
  Serial.print("Enviando turbidez: ");
  Serial.println(leituraAtual);
feedTurbidez.publish((int32_t)leituraAtual);

  delay(5000); 
}


void conectarMQTT() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Conectando ao MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { 
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Tentando novamente em 5 segundos...");
       mqtt.disconnect();
       delay(5000);
       retries--;
       if (retries == 0) {
         while (1); 
       }
  }
  Serial.println("MQTT Conectado com sucesso!");
}
