#include <VB_BMP280.h>
VB_BMP280 barometer;

bool blinkState           = false;
bool barometer_connection = false;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
    while (!Serial) {
        ; // Ожидаем когда появиться Serial Port через USB
    }
    setupBarometer();
}
void loop() {
    if (barometer_connection) {
        barometer.read(); //Чтение параметров барометра
        Serial.println((String) "BMP280: P=" + barometer.pres + " MM.PT.CT - T=" + barometer.temp + " *C - B=" + barometer.alti + " M.");

        // Моргать диодом изображая активность
        blinkState = !blinkState;
        digitalWrite(LED_BUILTIN, blinkState);

        delay(500);
    }
}

void setupBarometer() {
    Serial.println("Initalizinfg I2C Devices...");

    //Высота текущей точки над уровнем моря, если не задать то 0
    barometer.start_altitude = 0;

    // Ждем подключения пока не сможем подключиться
    while (!barometer_connection) {
        Serial.println("Checking connection with device...");
        barometer_connection = barometer.begin();

        if (barometer_connection) {
            return;
        } else {
            Serial.println("BMP280 conncetion was not established");
            delay(500);
        }
    }
}
