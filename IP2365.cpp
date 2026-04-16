#include "IP2365.h"

IP2365::IP2365() {
  _i2cAddr = IP2365_I2C_ADDR;
}

bool IP2365::begin() {
  Wire.begin(); // Inicializa barramento I2C do Arduino (Pinos A4/SDA e A5/SCL no Uno)

  // Tenta comunicação com o chip
  Wire.beginTransmission(_i2cAddr);
  if (Wire.endTransmission() == 0) {
    return true; // Dispositivo IP2365 respondeu com ACK
  }
  return false; // Falha (Não conectado ou endereço I2C incorreto)
}

uint8_t IP2365::readRegister(uint8_t reg) {
  Wire.beginTransmission(_i2cAddr);
  Wire.write(reg);
  Wire.endTransmission(false); // Envia sinal de Repeated Start

  Wire.requestFrom(_i2cAddr, (uint8_t)1);
  if (Wire.available()) {
    return Wire.read();
  }
  return 0; // Retorna 0 em caso de erro na leitura
}

void IP2365::writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(_i2cAddr);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

// === Status ===
uint8_t IP2365::getChargeStatus() {
  return readRegister(REG_CHG_STAT);
}

uint8_t IP2365::getNTCStatus() {
  return readRegister(REG_NTC_STAT);
}

bool IP2365::isChargeFull() {
  uint8_t status = getChargeStatus();
  // Exemplo: Substituir '0x08' pela máscara de bits CHG_FULL do seu datasheet
  return (status & 0x08) != 0;
}

// === Configurações ===
void IP2365::setSysCtl1(uint8_t value) { writeRegister(REG_SYS_CTL1, value); }
void IP2365::setVinOvSet(uint8_t value) { writeRegister(REG_VINOV_SET, value); }
void IP2365::setNtcCtl(uint8_t value) { writeRegister(REG_NTC_CTL, value); }
void IP2365::setVinISet(uint8_t value) { writeRegister(REG_VIN_ISET, value); }
void IP2365::setBatISet(uint8_t value) { writeRegister(REG_BAT_ISET, value); }
