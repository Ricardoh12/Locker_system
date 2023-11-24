void processarDadosJSON() {
  // Converte a string JSON para um objeto JSON
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, json);

  // Itera sobre os primeiros 10 objetos
  for (int i = 0; i < 11; ++i) {
    // Obtém o valor da chave "bars_code"
    String barsCode = doc[i]["bars_code"].as<String>();

    // Atribui cada valor a uma variável diferente
    switch (i + 1) {
      case 1: barsCode1 = barsCode; break;
      case 2: barsCode2 = barsCode; break;
      case 3: barsCode3 = barsCode; break;
      case 4: barsCode4 = barsCode; break;
      case 5: barsCode5 = barsCode; break;
      case 6: barsCode6 = barsCode; break;
      case 7: barsCode7 = barsCode; break;
      case 8: barsCode8 = barsCode; break;
      case 9: barsCode9 = barsCode; break;
      case 10: barsCode10 = barsCode; break;
      case 11: barsCode10 = barsCode; break;
    }
  }