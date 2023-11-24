void leitura_serial_codigo(){
  if (Serial2.available() > 0) {
    String mensagem = Serial2.readStringUntil('\n'); // Lê a mensagem recebida
    Serial.println("Mensagem recebida: " + mensagem);
  }
}