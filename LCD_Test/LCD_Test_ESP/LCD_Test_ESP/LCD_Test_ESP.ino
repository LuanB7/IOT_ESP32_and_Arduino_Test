// ESP32 no rolê

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

const int LED_PIN = 2; // LED embutido da placa ESP32

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) override {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        String command = String(rxValue.c_str());
        command.trim();

        Serial.print("Comando recebido via Web: ");
        Serial.println(command);

        // setTime(timeInSeconds) Command
        if (command.startsWith("setTime(")) {

          int startPos = command.indexOf('(');
          int endPos = command.indexOf(')');

          if (startPos != -1 && endPos > startPos) {

            String textValue = command.substring(startPos + 1, endPos);
            int secondsInt = textValue.toInt();

            Serial.printf("Valor extraído com sucesso: %d\n", secondsInt);
          }
        }
      }
    }
};

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // 1. Inicializa o dispositivo BLE com o nome visível
  BLEDevice::init("ESP32_BLE_Web");
  
  // 2. Cria o servidor e o serviço
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // 3. Cria a característica com permissão de leitura e escrita
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();

  // 4. Configuração CORRETA do Advertising (Anúncio)
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);                 // <--- OBRIGATÓRIO para o nome ser visível
  pAdvertising->setMinPreferred(0x06);                 // Ajuda em problemas de ligação com iOS/Chrome
  pAdvertising->setMinPreferred(0x12);
  
  BLEDevice::startAdvertising();                        // Inicialização global recomendada

  Serial.println("Servidor BLE iniciado com sucesso! Aguardando conexao...");
}

void loop() {
  delay(1000);
}