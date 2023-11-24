//Conexão esp32*****************************************
#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "Vila Sul Residence";
const char *password = "residenz62";
//******************************************************


void setup() {
  Serial.begin(9600); // Inicia a comunicação serial a 9600 bps
  Serial2.begin(9600, SERIAL_8N1, 33, 32);
  connect();
  makeRequest();

}

void loop() {
  leitura_serial_codigo();
}
