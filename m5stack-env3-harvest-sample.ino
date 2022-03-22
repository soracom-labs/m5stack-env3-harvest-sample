#include <M5Stack.h>

//通信ライブラリ
#define TINY_GSM_MODEM_UBLOX
#include <TinyGsmClient.h>
#include <HTTPClient.h>
#include <ArduinoHttpClient.h>

TinyGsm modem(Serial2); /* 3Gボードモデム */
TinyGsmClient ctx(modem);

const char* serverAddress = "unified.soracom.io";
const int port = 80;
HttpClient client = HttpClient(ctx, serverAddress, port);

//センサーライブラリ
#include "UNIT_ENV.h"

SHT3X sht30;
QMP6988 qmp6988;

//Jsonライブラリ
#include <ArduinoJson.h>

void setup() {
  //初期化
  M5.begin();
  M5.lcd.setTextSize(2);
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.println("M5Stack Now Powered On");


  //モデムの初期化（APNの設定）
  M5.Lcd.print("Restarting Modem...");
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  modem.restart();
  M5.Lcd.println("Done.");

  M5.Lcd.print("Modem Info:");
  String modemInfo = modem.getModemInfo();
  M5.Lcd.println(modemInfo);

  M5.Lcd.print("Waiting to be registered..");
  while (!modem.waitForNetwork()) M5.Lcd.print(".");
  M5.Lcd.println("done.");

  M5.Lcd.print("Creating PDP context with APN soracom.io..");
  modem.gprsConnect("soracom.io", "sora", "sora");
  M5.Lcd.println("done.");

  M5.Lcd.print("Connecting to the network..");
  while (!modem.isNetworkConnected()) M5.Lcd.print(".");
  M5.Lcd.println("done.");

  M5.Lcd.print("My IP addr:");
  IPAddress ipaddr = modem.localIP();
  M5.Lcd.print(ipaddr);


  //センサーモジュールの初期化
  Wire.begin();
  qmp6988.init();

  delay(2000);
}

void loop() {
  float t = 0.0; // temperature
  float h = 0.0; // humidity
  float p = 0.0; // pressure

  //センサーデータの取得
  p = qmp6988.calcPressure()/100;
  if (sht30.get() == 0) {
    t = sht30.cTemp;
    h = sht30.humidity;
  }

  //ディスプレイのクリア（塗りつぶし）
  M5.lcd.fillRect(0, 0, 320, 240, BLACK);

  //センサーデータの表示
  M5.lcd.setCursor(0, 20);
  M5.Lcd.printf("Temp: %2.1f  \r\nHumi: %2.0f%%  \r\nPressure:%2.0fhPa\r\n", t, h, p);

  //センサーデータのHarvestへの送信
  postSensorData(t, h, p);

  delay(10000);
}

void postSensorData(float t, float h, float p) {
  //Jsonドキュメント作成
  DynamicJsonDocument doc(2048);
  doc["temperature"] = t;
  doc["humidity"] = h;
  doc["pressure"] = p;

  //Jsonドキュメントのシリアライズ
  String json;
  serializeJson(doc, json);

  //データ送信
  M5.Lcd.print("Sending POST request..");
  String contentType = "application/json";

  int err = client.post("/", contentType, json);

  //エラーハンドリング
   if (err != 0) {
    M5.Lcd.println("failed.");
    return;
  }
  //送信結果確認
  M5.Lcd.println("done.");

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  M5.Lcd.print("Status code: ");
  M5.Lcd.println(statusCode);
}
