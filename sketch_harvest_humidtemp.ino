
#include <M5Stack.h>

//通信ライブラリのインポート
#define TINY_GSM_MODEM_UBLOX
#include <TinyGsmClient.h>
#include <HTTPClient.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>

TinyGsm modem(Serial2); /* 3Gボードモデム */
TinyGsmClient ctx(modem);


//センサーライブラリのインポート
#include "UNIT_ENV.h"

SHT3X sht30;
QMP6988 qmp6988;

float tmp = 0.0;
float hum = 0.0;
float pressure = 0.0;

char serverAddress[] = "unified.soracom.io";
int port = 80;
HttpClient client = HttpClient(ctx, serverAddress, port);

void setup() {
  //初期化
  M5.begin();
  M5.lcd.setTextSize(2);
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.println("M5Stack Now Powered On");


  //モデムの初期化（APNの設定）
  M5.Lcd.print("Resterting Modem...");
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  modem.restart();
  M5.Lcd.println("Done.");

  M5.Lcd.print("Modem Info:");
  String modemInfo = modem.getModemInfo();
  M5.Lcd.println(modemInfo);

  M5.Lcd.print("Waiting to be connected..");
  while (!modem.waitForNetwork()) M5.Lcd.print(".");
  M5.Lcd.println("done.");

  M5.Lcd.print("GPRS Connecting to soracom.io..");
  modem.gprsConnect("soracom.io", "sora", "sora");
  M5.Lcd.println("done.");

  M5.Lcd.print("Network Connecting..");
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
  //センサーデータの取得
  pressure = qmp6988.calcPressure()/100;
  if(sht30.get()==0){
    tmp = sht30.cTemp;
    hum = sht30.humidity;
  }else{
    tmp=0,hum=0;
  }

  //ディスプレイのクリア（塗りつぶし）
  M5.lcd.fillRect(0,0,320,240,BLACK);

  //センサーデータの表示
  M5.lcd.setCursor(0,20);
  M5.Lcd.printf("Temp: %2.1f  \r\nHumi: %2.0f%%  \r\nPressure:%2.0fhPa\r\n", tmp, hum, pressure);

  //センサーデータのHarvestへの送信
  postCensorData(tmp, hum, pressure);

  delay(10000);

}



void postCensorData(float tmp, float hum, float pressure) {

  //Jsonドキュメント作成
  DynamicJsonDocument doc(2048);
  doc["temperature"] = tmp;
  doc["humidity"] = hum;
  doc["pressure"] = pressure;

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
