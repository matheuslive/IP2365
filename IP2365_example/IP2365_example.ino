#include "IP2365.h"

IP2365 carregador;

void setup() {
  // Configura a comunicação Serial para 115200 bps
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Iniciando comunicacao I2C com o IP2365...");

  // Liga o barramento e verifica se o chip responde
  if (carregador.begin()) {
    Serial.println("IP2365 detectado com sucesso!");

    // Exemplo de configuração (Apenas referencial)
    // carregador.setBatISet(0xXX); // Configura corrente da bateria
  } else {
    Serial.println("Erro: IP2365 nao encontrado. Verifique os pinos SDA (A4) e SCL (A5).");
    while (1); // Para a execução do código aqui
  }
}

void loop() {
  // Lendo registradores
  uint8_t statusCarga = carregador.getChargeStatus();
  uint8_t statusNTC = carregador.getNTCStatus();

  // Exibindo no monitor serial
  Serial.print("Registrador CHG_STAT : 0x");
  if (statusCarga < 16) Serial.print("0"); // formatação
  Serial.println(statusCarga, HEX);

  if (carregador.isChargeFull()) {
    Serial.println("-> STATUS: Bateria Totalmente Carregada.");
  } else {
    Serial.println("-> STATUS: Carregando / Descarregando / Aguardando.");
  }

  Serial.print("Registrador NTC_STAT : 0x");
  if (statusNTC < 16) Serial.print("0");
  Serial.println(statusNTC, HEX);

  Serial.println("----------------------------------------");
  delay(3000); // Atualiza os dados a cada 3 segundos
}
