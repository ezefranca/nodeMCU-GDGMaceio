
/***************************************************************
  NodeMCU e Firebase : IoT Simples e divertido
  DEVFEST 2017 - Maceió
  @ezefranca
***************************************************************/

// BIBLIOTECAS NECESSÁRIAS
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// CONFIGURAÇÕES DO FIREBASE
#define FIREBASE_HOST "gdg-maceio-30f53.firebaseio.com"
#define FIREBASE_AUTH "zORMoJ58RsJWoRUShTg2sAOqeeaK6vSZjMUr9iCQ"

// CONFIGURAÇÕES DO WIFI
#define WIFI_SSID "iPhoneSE"
#define WIFI_PASSWORD "12345677"

// PINOS UTILIZADOS NO EXEMPLO
#define LED_PIN = 13
#define BUTTON_PIN = 0

// VARIAVEL PARA GUARDAR O ESTADO DO BOTÃO
int buttonState = 0;

void setup() {

  // SETUP DA SERIAL E DOS PINOS
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  // SETUP DO WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("conectando..."); 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("conectado a rede:   ");
  Serial.print(WiFi.localIP());

  // SETUP DO FIREBASE
  // Conecta ao Firebase 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(1000);

  // DICA: Para testar se a conexão ocorreu corretamente (by @luisleao)
  Firebase.set("ledStatus", 0);
  if (Firebase.failed()) {
    Serial.print(">>> Erro ao inicializar o Firebase >>> ");
    Serial.println(Firebase.error());
  } else {
    Serial.print(">>> Firebase inicializado com sucesso >>> ");
  }
}

void setButtonStatus() {

  buttonState = digitalRead(BUTTON_PIN);
  Firebase.set("buttonStatus", buttonState);

  if (Firebase.failed()) {
    Serial.print(">>> Erro ao setar buttonStatus >>> ");
    Serial.println(Firebase.error());
  } else {
    Serial.print(">>> Erro ao obter buttonStatus >>> ");
    Serial.println(buttonState);
  }
}

void getButtonStatus() {

  int buttonValue = Firebase.getInt("buttonStatus");

  if (Firebase.failed()) {
    Serial.print(">>> Erro ao obter buttonStatus >>> ");
    Serial.println(Firebase.error());
  } else {
    digitalWrite(LED_PIN, buttonValue);
  }
}

void loop() {
  setButtonStatus();
  getButtonStatus();
  delay(50);
}