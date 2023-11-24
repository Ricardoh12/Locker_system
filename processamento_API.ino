

void connect() {
  // Conectar ao WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  // Fazer requisição à API
}

void makeRequest() {
  HTTPClient http;

  // URL da API
  String url = "";
  
  Serial.print("Conectando a: ");
  Serial.println(url);

  // Fazer a requisição
  http.begin(url);

  // Obter o código de resposta
  int httpCode = http.GET();

  // Se a requisição foi bem-sucedida
  if (httpCode > 0) {
    // Obter a resposta
    String payload = http.getString();
    Serial.println("Resposta da API:");
    Serial.println(payload);
  } else {
    Serial.print("Erro na requisição HTTP. Código de erro: ");
    Serial.println(httpCode);
  }

  // Liberar recursos
  http.end();
}
