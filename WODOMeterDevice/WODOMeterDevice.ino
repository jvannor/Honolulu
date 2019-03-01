#include <bluefruit.h>

#define SERVICE_ID 0x6C76DEFEA4654437827601146E567164
#define CHARACTERISTIC_ID 0x9CAAF395F500451EB47E21761EDC1290

uint8_t svc_id[] = {0x64, 0x71, 0x56, 0x6E, 0x14, 0x01, 0x76, 0x82, 0x37, 0x44, 0x65, 0xA4, 0xFE, 0xDE, 0x76, 0x6C};
uint8_t chr_id[] = {0x90, 0x12, 0xDC, 0x1E, 0x76, 0x21, 0x7E, 0xB4, 0x1E, 0x45, 0x00, 0xF5, 0x95, 0xF3, 0xAA, 0x9C};

BLEDis bledis;
BLEService wodometer = BLEService(svc_id);
BLECharacteristic measurement = BLECharacteristic(chr_id);

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
  Bluefruit.Advertising.addService(wodometer);
  Bluefruit.Advertising.addName();
  
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
