#include <bluefruit.h>

#define SERVICE_ID 0x6C76DEFEA4654437827601146E567164
#define CHARACTERISTIC_ID 0x9CAAF395F500451EB47E21761EDC1290

BLEDis bledis;
BLEService wodometer = BLEService(SERVICE_ID);
BLECharacteristic measurement = BLECharacteristic(CHARACTERISTIC_ID);

uint32_t value = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Bluefruit.begin();
  Bluefruit.setName("WODOMeter");
  Bluefruit.setConnectCallback(connect_callback);
  Bluefruit.setDisconnectCallback(disconnect_callback);

  bledis.setManufacturer("TBD");
  bledis.setModel("WODOMETER 1");
  bledis.begin();

  wodometer.begin();
  measurement.setProperties(CHR_PROPS_NOTIFY);
  measurement.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
  measurement.setFixedLen(4);
  measurement.begin();
  measurement.notify32(value);

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.addService(wodometer);

  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  measurement.notify32(++value);
}

void connect_callback(uint16_t conn_handle) {
  Serial.println("connected");
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason) {
  Serial.println("disconnected");
}
