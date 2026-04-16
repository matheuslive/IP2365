#ifndef IP2365_H
#define IP2365_H

#include <Arduino.h>
#include <Wire.h>

// Endereço I2C padrão do IP2365 (Formato 7 bits para o Arduino).
// Nota: Em chips da Injoinic, os endereços comuns costumam ser 0x75 ou 0xEA >> 1.
#define IP2365_I2C_ADDR 0x75

// --- MAPA DE REGISTRADORES ---
// IMPORTANTE: Preencha com os endereços hexadecimais corretos do seu Datasheet
#define REG_SYS_CTL1   0x00
#define REG_VINOV_SET  0x01
#define REG_NTC_CTL    0x02
#define REG_R_ISET     0x03
#define REG_VIN_ISET   0x04
#define REG_BAT_ISET   0x05
#define REG_LED_REG    0x06

// Registradores de Status
#define REG_CHG_STAT   0x07
#define REG_NTC_STAT   0x08

class IP2365 {
  public:
    IP2365();

    // Inicializa a interface I2C e verifica se o chip está conectado
    bool begin();

    // Funções de comunicação I2C diretas
    uint8_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t value);

    // Funções para Leitura de Status
    uint8_t getChargeStatus();
    uint8_t getNTCStatus();
    bool isChargeFull();

    // Funções para Escrita de Configuração
    void setSysCtl1(uint8_t value);
    void setVinOvSet(uint8_t value);
    void setNtcCtl(uint8_t value);
    void setVinISet(uint8_t value);
    void setBatISet(uint8_t value);

  private:
    uint8_t _i2cAddr;
};

#endif
