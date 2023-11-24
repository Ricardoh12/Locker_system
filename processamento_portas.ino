void processarDadosJSON() {
  if (mensagem == barsCode1) {
    digitalWrite(PIN_ESPECIFICO_PARA_BARSCODE1, HIGH);
  } else if (mensagem == barsCode2) {
    digitalWrite(PIN_ESPECIFICO_PARA_BARSCODE2, HIGH);
  }
}