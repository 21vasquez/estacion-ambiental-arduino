# Estación Ambiental Bluetooth (Arduino Uno + Web Serial)

Sistema portátil de monitoreo ambiental que lee temperatura, humedad, luz y calidad de aire con un **Arduino Uno**, transmite los datos vía **Bluetooth HC-05** y los visualiza/exporta a CSV en un dashboard web en tiempo real.

## Componentes
* Arduino Uno
* Módulo Bluetooth HC-05
* Sensor AHT20 (temperatura y humedad)
* Sensor TEMT6000 (luz ambiente)
* Sensor MQ-135 (calidad de aire)
* Resistencias de 1 kΩ y 2 kΩ (divisor de voltaje para RXD del HC-05)

## Conexiones
| Módulo | Pin del módulo | Pin Arduino Uno | Notas |
| :--- | :--- | :--- | :--- |
| **HC-05** | VCC / GND / TXD / RXD | 5V / GND / Pin 10 / Pin 11 | Pin 11 a RXD con divisor 1 kΩ + 2 kΩ |
| **TEMT6000** | VCC / GND / SIG | 5V / GND / A0 | Salida analógica |
| **MQ-135** | VCC / GND / A0 | 5V / GND / A1 | Requiere precalentamiento (~20 s) |
| **AHT20** | VCC / GND / SDA / SCL | 5V (o 3.3V) / GND / A4 / A5 | Bus I2C |

## Uso
1. Instala la librería **Adafruit AHTX0** en Arduino IDE.
2. Sube `arduino/estacion_ambiental/estacion_ambiental.ino` al Arduino Uno.
3. Empareja el **HC-05** en Windows (PIN `1234`) y anota su puerto **COM saliente**.
4. Abre `index.html` en **Google Chrome** o **Microsoft Edge**, haz clic en **Conectar HC-05** y selecciona el puerto COM saliente.
