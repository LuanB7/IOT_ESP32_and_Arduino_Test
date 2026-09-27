    const SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
    const CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8";

    let esp32Characteristic = null;

    async function BLEconnect() {
      const statusDiv = document.getElementById('status');
      try {
        console.log("Buscando ESP32...");

        // 1. Solicita a conexão ao navegador
        const device = await navigator.bluetooth.requestDevice({
          filters: [{ name: 'ESP32_BLE_Web' }],
          optionalServices: [SERVICE_UUID]
        });

        console.log("Conectando ao GATT...");
        const server = await device.gatt.connect();
        const service = await server.getPrimaryService(SERVICE_UUID);
        esp32Characteristic = await service.getCharacteristic(CHARACTERISTIC_UUID);

        console.log("Status: Conectado!");
        document.body.classList.add("bt-connected");
        document.querySelector("#bt-status-txt").innerHTML = '<i class="fa-solid fa-circle-check"></i>Dispositivo conectado';
        //document.getElementById('btnOn').disabled = false;
        //document.getElementById('btnOff').disabled = false;

      } catch (error) {
        console.error(error);
        console.log("Erro ao conectar: " + error.message);
      }
    }

    async function BLEsendCommand(command) {
      if (!esp32Characteristic) return;
      try {
        const encoder = new TextEncoder();
        await esp32Characteristic.writeValue(encoder.encode(command));
      } catch (error) {
        console.error("Erro ao enviar comando:", error);
      }
    }