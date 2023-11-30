#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "CLARO_2G7E121E";
const char *password = "5D7E121E";
StaticJsonDocument<200> doc;


int triggerPin1 = 25;
int triggerPin2 = 26;
int triggerPin3 = 27;
int triggerPin4 = 14;
int triggerPin5 = 12;
int triggerPin6 = 15;
int triggerPin7 = 16;
int triggerPin8 = 17;
int triggerPin9 = 5;
int triggerPin10 = 18;

const int maxBarcodes = 10;
String barcodes[maxBarcodes];
String mensagem;

void connectToAPI() {
  HTTPClient http;
  String url = "https://dartapi3.onrender.com/dados";
  int maxConnectionAttempts = 20;
  int retryDelay = 5000; 
  bool connected = false;

  for (int attempt = 1; attempt <= maxConnectionAttempts; ++attempt) {
    Serial.printf("Tentativa %d de %d\n", attempt, maxConnectionAttempts);
    Serial.print("Conectando a: ");
    Serial.println(url);

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Resposta da API:");
      Serial.println(payload);

      const size_t capacity = JSON_ARRAY_SIZE(maxBarcodes) + maxBarcodes * JSON_OBJECT_SIZE(2) + 800;
      DynamicJsonDocument doc(capacity);
      deserializeJson(doc, payload);

      // Itera sobre os objetos no JSON
      for (int i = 0; i < maxBarcodes; ++i) {
        if (doc[i].containsKey("bars_code")) {
          barcodes[i] = doc[i]["bars_code"].as<String>();
          Serial.print("Bars Code ");
          Serial.print(i + 1);
          Serial.print(": ");
          Serial.println(barcodes[i]);
        }
      }

      connected = true;
      break; 
    } else {
      Serial.print("Erro na requisição HTTP. Código de erro: ");
      Serial.println(httpCode);
      delay(retryDelay); 
    }

    http.end();
  }

  if (!connected) {
    Serial.println("Falha ao conectar à API após várias tentativas.");
    
  }
}

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 33, 32);

  pinMode(triggerPin1, OUTPUT);
  pinMode(triggerPin2, OUTPUT);
  pinMode(triggerPin3, OUTPUT);
  pinMode(triggerPin4, OUTPUT);
  pinMode(triggerPin5, OUTPUT);
  pinMode(triggerPin6, OUTPUT);
  pinMode(triggerPin7, OUTPUT);
  pinMode(triggerPin8, OUTPUT);
  pinMode(triggerPin9, OUTPUT);
  pinMode(triggerPin10, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  connectToAPI();
}

void loop() {
  if (Serial2.available() > 0) {
    mensagem = Serial2.readStringUntil('\n');
    mensagem.trim();  // Remove espaços em branco no início e no final

    Serial.println("Mensagem recebida: " + mensagem);
    
    for (int i = 0; i < maxBarcodes; ++i) {
      Serial.println(barcodes[i]);
      Serial.println(barcodes[0]);

      // Limpa a string antes de comparar
      barcodes[i].trim();

      if (mensagem.equals(barcodes[0])) {
        Serial.println("ok barcode1");
        digitalWrite(triggerPin1, LOW);
        delay(10000);
        digitalWrite(triggerPin1, HIGH);
        break; // Se encontrou uma correspondência, interrompe o loop
      }
      else if (mensagem.equals(barcodes[1])) {
        Serial.println("ok barcode2");
        digitalWrite(triggerPin1, LOW);
        delay(1000);
        digitalWrite(triggerPin1, HIGH);
        break; 
      }
      else if (mensagem.equals(barcodes[2])) {
        Serial.println("ok barcode3");
        digitalWrite(triggerPin3, LOW);
        delay(1000);
        digitalWrite(triggerPin3, HIGH);
        break;
      }
      else if (mensagem.equals(barcodes[3])) {
        Serial.println("ok barcode4");
        digitalWrite(triggerPin4, LOW);
        delay(1000);
        digitalWrite(triggerPin4, HIGH);
        break; 
      }
      else if (mensagem.equals(barcodes[4])) {
        Serial.println("ok barcode5");
        digitalWrite(triggerPin5, LOW);
        delay(1000);
        digitalWrite(triggerPin5, HIGH);
        break;
      }
      else if (mensagem.equals(barcodes[5])) {
        Serial.println("ok barcode6");
        digitalWrite(triggerPin6, LOW);
        delay(1000);
        digitalWrite(triggerPin6, HIGH);
        break; 
      }
      else if (mensagem.equals(barcodes[6])) {
        Serial.println("ok barcode7");
        digitalWrite(triggerPin7, LOW);
        delay(1000);
        digitalWrite(triggerPin7, HIGH);
        break; 
      }
      else if (mensagem.equals(barcodes[7])) {
        Serial.println("ok barcode8");
        digitalWrite(triggerPin8, LOW);
        delay(1000);
        digitalWrite(triggerPin8, HIGH);
        break;
      }
      else if (mensagem.equals(barcodes[8])) {
        Serial.println("ok barcode9");
        digitalWrite(triggerPin9, LOW);
        delay(1000);
        digitalWrite(triggerPin9, HIGH);
        break; 
      }
      else if (mensagem.equals(barcodes[9])) {
        Serial.println("ok barcode10");
        digitalWrite(triggerPin10, LOW);
        delay(1000);
        digitalWrite(triggerPin10, HIGH);
        break; 
      }
    }
  }
}

