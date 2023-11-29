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
  String url = "https://dartapi3.onrender.com/dados";
  
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
    const size_t capacity = JSON_ARRAY_SIZE(10) + 10*JSON_OBJECT_SIZE(2) + 800;
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, payload);

    const int maxBarcodes = 10;
    String barcodes[maxBarcodes];

    // Itera sobre os objetos no JSON
    for (int i = 0; i < maxBarcodes; ++i) {
      // Verifica se o objeto existe antes de acessá-lo
      if (doc[i].containsKey("bars_code")) {
        barcodes[i] = doc[i]["bars_code"].as<String>();
        Serial.print("Bars Code ");
        Serial.print(i + 1);
        Serial.print(": ");
        //Serial.println(barcodes[i]);
        Serial.println(barcodes[i]);
      
    }
    }
   }else {
    Serial.print("Erro na requisição HTTP. Código de erro: ");
    Serial.println(httpCode);
  }

  // Liberar recursos
  http.end();
}
