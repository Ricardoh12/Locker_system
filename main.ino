#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "RWIFI";
const char *password = "r@b@tic@";
StaticJsonDocument<200> doc;
int triggerPin = 5;

const int maxBarcodes = 10;
String barcodes[maxBarcodes];
String mensagem;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 33, 32);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  HTTPClient http;
  String url = "https://dartapi3.onrender.com/dados";

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
  } else {
    Serial.print("Erro na requisição HTTP. Código de erro: ");
    Serial.println(httpCode);
  }

  http.end();
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

      if (mensagem.equals(barcodes[i])) {
        Serial.println("ok barcode");
        digitalWrite(triggerPin, HIGH);
        delay(1000);
        digitalWrite(triggerPin, LOW);
        break; // Se encontrou uma correspondência, interrompe o loop
      }
    }
  }
}

