#define ARDUINOJSON_USE_DOUBLE 1
#define P_LAT 22
#define P_A 19
#define P_B 23
#define P_C 18
#define P_D 5
#define P_E 15
#define P_OE 16

#define CORE_1 1

#define INTERRUPT_ATTR IRAM_ATTR

#define matrix_width 64
#define matrix_height 32

#include "main.h"
#include <Arduino.h>
#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <HTTPClient.h>
#include "ESPAsyncWebServer.h"
#include "AsyncJson.h"
#include <Adafruit_I2CDevice.h>
#include <PxMatrix.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include <SPIFFS.h>
#include "cica.h"

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
DNSServer dnsServer;
AsyncWebServer server(80);
HTTPClient usd_huf_client;
HTTPClient gatewayClient;
PxMATRIX display(64, 32, P_LAT, P_OE, P_A, P_B, P_C, P_D);

TaskHandle_t displayUpdateTaskHandle = NULL;

int wifi_reconnect_counter = 0;
uint32_t timerke = 0;
uint8_t display_draw_time = 30; //30-70 is usually fine
uint16_t myRED = display.color565(255, 0, 0);
uint16_t myGREEN = display.color565(0, 255, 0);
uint16_t myBLUE = display.color565(0, 0, 255);
uint16_t myWHITE = display.color565(255, 255, 255);
uint16_t myYELLOW = display.color565(255, 255, 0);
uint16_t myCYAN = display.color565(0, 255, 255);
uint16_t myMAGENTA = display.color565(255, 0, 255);
uint16_t myBLACK = display.color565(0, 0, 0);
uint16_t myCOLORS[8] = {myRED, myGREEN, myBLUE, myWHITE, myYELLOW, myCYAN, myMAGENTA, myBLACK};

bool loadConfig()
{
  SPIFFS.begin();
  File config = SPIFFS.open("/config.json");

  StaticJsonDocument<1024> doc;

  DeserializationError error = deserializeJson(doc, config);

  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
  }

  wifi_ssid = doc["wifi"]["ssid"].as<String>(); // "WiFi"
  wifi_pass = doc["wifi"]["pass"].as<String>(); // "barishbarish5"

  settings_brightness = doc["settings"]["brightness"]; // 100
  settings_usdhuf = doc["settings"]["usdhuf"];         // 0

  JsonObject display = doc["display"];
  display_line1 = display["line1"];       // 3
  display_line2 = display["line2"];       // 6
  display_line3 = display["line3"];       // 10
  display_line4 = display["line4"];       // 11
  display_mode = display["mode"];         // 1
  display_cycle = display["cycle"];       // 0
  display_lastpage = display["lastpage"]; // 0

  JsonObject portfolio_user1 = doc["portfolio"]["user1"];
  portfolio_user1_ada = portfolio_user1["ada"];   // 0
  portfolio_user1_atom = portfolio_user1["atom"]; // 0
  portfolio_user1_bch = portfolio_user1["bch"];   // 0
  portfolio_user1_btc = portfolio_user1["btc"];   // 0
  portfolio_user1_etc = portfolio_user1["etc"];   // 0
  portfolio_user1_eth = portfolio_user1["eth"];   // 0
  portfolio_user1_ltc = portfolio_user1["ltc"];   // 0
  portfolio_user1_mkr = portfolio_user1["mkr"];   // 0
  portfolio_user1_xtz = portfolio_user1["xtz"];   // 0
  portfolio_user1_zrx = portfolio_user1["zrx"];   // 0

  JsonObject portfolio_user2 = doc["portfolio"]["user2"];
  portfolio_user2_ada = portfolio_user2["ada"];   // 0
  portfolio_user2_atom = portfolio_user2["atom"]; // 0
  portfolio_user2_bch = portfolio_user2["bch"];   // 0
  portfolio_user2_btc = portfolio_user2["btc"];   // 0
  portfolio_user2_etc = portfolio_user2["etc"];   // 0
  portfolio_user2_eth = portfolio_user2["eth"];   // 0
  portfolio_user2_ltc = portfolio_user2["ltc"];   // 0
  portfolio_user2_mkr = portfolio_user2["mkr"];   // 0
  portfolio_user2_xtz = portfolio_user2["xtz"];   // 0
  portfolio_user2_zrx = portfolio_user2["zrx"];   // 0

  config.close();

  return true;
}

bool saveConfig()
{
  SPIFFS.begin();
  File config = SPIFFS.open("/config.json", FILE_WRITE);

  StaticJsonDocument<1024> doc;

  JsonObject wifi = doc.createNestedObject("wifi");
  wifi["ssid"] = wifi_ssid;
  wifi["pass"] = wifi_pass;

  JsonObject settings = doc.createNestedObject("settings");
  settings["brightness"] = settings_brightness;
  settings["usdhuf"] = settings_usdhuf;

  JsonObject display = doc.createNestedObject("display");
  display["line1"] = display_line1;
  display["line2"] = display_line2;
  display["line3"] = display_line3;
  display["line4"] = display_line4;
  display["mode"] = display_mode;
  display["cycle"] = display_cycle;
  display["lastpage"] = display_lastpage;

  JsonObject portfolio = doc.createNestedObject("portfolio");

  JsonObject portfolio_user1 = portfolio.createNestedObject("user1");
  portfolio_user1["ada"] = portfolio_user1_ada;
  portfolio_user1["atom"] = portfolio_user1_atom;
  portfolio_user1["bch"] = portfolio_user1_bch;
  portfolio_user1["btc"] = portfolio_user1_btc;
  portfolio_user1["etc"] = portfolio_user1_etc;
  portfolio_user1["eth"] = portfolio_user1_eth;
  portfolio_user1["ltc"] = portfolio_user1_ltc;
  portfolio_user1["mkr"] = portfolio_user1_mkr;
  portfolio_user1["xtz"] = portfolio_user1_xtz;
  portfolio_user1["zrx"] = portfolio_user1_zrx;

  JsonObject portfolio_user2 = portfolio.createNestedObject("user2");
  portfolio_user2["ada"] = portfolio_user2_ada;
  portfolio_user2["atom"] = portfolio_user2_atom;
  portfolio_user2["bch"] = portfolio_user2_bch;
  portfolio_user2["btc"] = portfolio_user2_btc;
  portfolio_user2["etc"] = portfolio_user2_etc;
  portfolio_user2["eth"] = portfolio_user2_eth;
  portfolio_user2["ltc"] = portfolio_user2_ltc;
  portfolio_user2["mkr"] = portfolio_user2_mkr;
  portfolio_user2["xtz"] = portfolio_user2_xtz;
  portfolio_user2["zrx"] = portfolio_user2_zrx;

  String output;
  serializeJson(doc, output);
  config.print(output);
  config.close();

  Serial.println("CMRX config saved");

  return true;
}

void printConfig()
{
  Serial.println("CRMX config dump");
  Serial.println("======================================");
  Serial.println("wifi_ssid: " + (String)wifi_ssid);
  Serial.println("wifi_pass: " + (String)wifi_pass);

  Serial.println("settings_brightness: " + (String)settings_brightness);
  Serial.println("settings_usdhuf: " + (String)settings_usdhuf);

  Serial.println("display_line1: " + (String)display_line1);
  Serial.println("display_line2: " + (String)display_line2);
  Serial.println("display_line3: " + (String)display_line3);
  Serial.println("display_line4: " + (String)display_line4);
  Serial.println("display_mode: " + (String)display_mode);
  Serial.println("display_cycle: " + (String)display_cycle);
  Serial.println("display_lastpage: " + (String)display_lastpage);

  Serial.println("portfolio_user1_ada: " + String(portfolio_user1_ada, 8));
  Serial.println("portfolio_user1_atom: " + String(portfolio_user1_atom, 8));
  Serial.println("portfolio_user1_bch: " + String(portfolio_user1_bch, 8));
  Serial.println("portfolio_user1_btc: " + String(portfolio_user1_btc, 8));
  Serial.println("portfolio_user1_etc: " + String(portfolio_user1_etc, 8));
  Serial.println("portfolio_user1_eth: " + String(portfolio_user1_eth, 8));
  Serial.println("portfolio_user1_ltc: " + String(portfolio_user1_ltc, 8));
  Serial.println("portfolio_user1_mkr: " + String(portfolio_user1_mkr, 8));
  Serial.println("portfolio_user1_xtz: " + String(portfolio_user1_xtz, 8));
  Serial.println("portfolio_user1_zrx: " + String(portfolio_user1_zrx, 8));

  Serial.println("portfolio_user2_ada: " + String(portfolio_user2_ada, 8));
  Serial.println("portfolio_user2_atom: " + String(portfolio_user2_atom, 8));
  Serial.println("portfolio_user2_bch: " + String(portfolio_user2_bch, 8));
  Serial.println("portfolio_user2_btc: " + String(portfolio_user2_btc, 8));
  Serial.println("portfolio_user2_etc: " + String(portfolio_user2_etc, 8));
  Serial.println("portfolio_user2_eth: " + String(portfolio_user2_eth, 8));
  Serial.println("portfolio_user2_ltc: " + String(portfolio_user2_ltc, 8));
  Serial.println("portfolio_user2_mkr: " + String(portfolio_user2_mkr, 8));
  Serial.println("portfolio_user2_xtz: " + String(portfolio_user2_xtz, 8));
  Serial.println("portfolio_user2_zrx: " + String(portfolio_user2_zrx, 8));
  Serial.println("======================================");
}

String getConfigJSON()
{
  String configJSON;
  SPIFFS.begin();
  File config = SPIFFS.open("/config.json");

  while (config.available())
  {

    configJSON.concat(config.readString());
  }

  config.close();

  return configJSON;
}

AsyncCallbackJsonWebHandler *wifiset = new AsyncCallbackJsonWebHandler("/wifi", [](AsyncWebServerRequest *request, JsonVariant &json)
{
  StaticJsonDocument<1024> data;
  data = json.as<JsonObject>();

  wifi_ssid = data["wifi"]["ssid"].as<String>(); // "WiFi"
  wifi_pass = data["wifi"]["pass"].as<String>(); // "barishbarish5"

  saveConfig();

  String response;
  serializeJson(data, response);
  request->send(200, "application/json", response);
  delay(3000);
  ESP.restart();
});

AsyncCallbackJsonWebHandler *handler = new AsyncCallbackJsonWebHandler("/", [](AsyncWebServerRequest *request, JsonVariant &json)
{
  StaticJsonDocument<1024> data;
  data = json.as<JsonObject>();

  wifi_ssid = data["wifi"]["ssid"].as<String>(); // "WiFi"
  wifi_pass = data["wifi"]["pass"].as<String>(); // "barishbarish5"

  settings_brightness = data["settings"]["brightness"]; // 100

  JsonObject display = data["display"];
  display_line1 = display["line1"]; // 3
  display_line2 = display["line2"]; // 6
  display_line3 = display["line3"]; // 10
  display_line4 = display["line4"]; // 11
  display_mode = display["mode"];   // 1
  display_cycle = display["cycle"]; // 0

  JsonObject portfolio_user1 = data["portfolio"]["user1"];
  portfolio_user1_ada = portfolio_user1["ada"];   // 0
  portfolio_user1_atom = portfolio_user1["atom"]; // 0
  portfolio_user1_bch = portfolio_user1["bch"];   // 0
  portfolio_user1_btc = portfolio_user1["btc"];   // 0
  portfolio_user1_etc = portfolio_user1["etc"];   // 0
  portfolio_user1_eth = portfolio_user1["eth"];   // 0
  portfolio_user1_ltc = portfolio_user1["ltc"];   // 0
  portfolio_user1_mkr = portfolio_user1["mkr"];   // 0
  portfolio_user1_xtz = portfolio_user1["xtz"];   // 0
  portfolio_user1_zrx = portfolio_user1["zrx"];   // 0

  JsonObject portfolio_user2 = data["portfolio"]["user2"];
  portfolio_user2_ada = portfolio_user2["ada"];   // 0
  portfolio_user2_atom = portfolio_user2["atom"]; // 0
  portfolio_user2_bch = portfolio_user2["bch"];   // 0
  portfolio_user2_btc = portfolio_user2["btc"];   // 0
  portfolio_user2_etc = portfolio_user2["etc"];   // 0
  portfolio_user2_eth = portfolio_user2["eth"];   // 0
  portfolio_user2_ltc = portfolio_user2["ltc"];   // 0
  portfolio_user2_mkr = portfolio_user2["mkr"];   // 0
  portfolio_user2_xtz = portfolio_user2["xtz"];   // 0
  portfolio_user2_zrx = portfolio_user2["zrx"];   // 0

  saveConfig();
  loadConfig();

  String response;
  serializeJson(data, response);
  request->send(200, "application/json", response);
  printConfig();
});

void getCurrencyData()
{
  usd_huf_client.begin("http://free.currconv.com/api/v7/convert?q=USD_HUF&compact=ultra&apiKey=768b8363826b1395f04b");
  int response = usd_huf_client.GET();
  if (response == 200)
  {
    String payload = usd_huf_client.getString();

    Serial.println("Currency API response: " + payload);

    int startIndex = payload.indexOf(":") + 1;
    int endIndex = payload.indexOf("}");

    String cica = payload.substring(startIndex, endIndex);

    settings_usdhuf = cica.toFloat();
    saveConfig();
  }
  else
  {
    Serial.println("Currency API response: " + (String)response);
  }
  usd_huf_client.end();
}

bool getGatewayData()
{
  gatewayClient.begin("http://cica.ette.hu/crypto/");
  gatewayClient.setTimeout(5000);
  int response = gatewayClient.GET();
  if (response == 200)
  {
    String payload = gatewayClient.getString();
    gatewayClient.end();

    StaticJsonDocument<512> cryptoPrices;
    DeserializationError error = deserializeJson(cryptoPrices, payload);

    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return false;
    }

    ada_price = cryptoPrices["ada"];
    atom_price = cryptoPrices["atom"];
    bch_price = cryptoPrices["bch"];
    btc_price = cryptoPrices["btc"];
    etc_price = cryptoPrices["etc"];
    eth_price = cryptoPrices["eth"];
    ltc_price = cryptoPrices["ltc"];
    mkr_price = cryptoPrices["mkr"];
    xtz_price = cryptoPrices["xtz"];
    zrx_price = cryptoPrices["zrx"];

    return true;
  }
  else
  {
    Serial.println("Gateway response: " + (String)response);
    gatewayClient.end();
    return false;
  }
}

void calculatePortfolioSum()
{
  user1_sum_usd = ada_price * portfolio_user1_ada +
                  atom_price * portfolio_user1_atom +
                  bch_price * portfolio_user1_bch +
                  btc_price * portfolio_user1_btc +
                  etc_price * portfolio_user1_etc +
                  eth_price * portfolio_user1_eth +
                  ltc_price * portfolio_user1_ltc +
                  mkr_price * portfolio_user1_mkr +
                  xtz_price * portfolio_user1_xtz +
                  zrx_price * portfolio_user1_zrx;

  user2_sum_usd = ada_price * portfolio_user2_ada +
                  atom_price * portfolio_user2_atom +
                  bch_price * portfolio_user2_bch +
                  btc_price * portfolio_user2_btc +
                  etc_price * portfolio_user2_etc +
                  eth_price * portfolio_user2_eth +
                  ltc_price * portfolio_user2_ltc +
                  mkr_price * portfolio_user2_mkr +
                  xtz_price * portfolio_user2_xtz +
                  zrx_price * portfolio_user2_zrx;

  user1_sum_huf = user1_sum_usd * settings_usdhuf;
  user2_sum_huf = user2_sum_usd * settings_usdhuf;
}

void putPricesIntoArray()
{
  all_price[0] = ada_price;
  all_price[1] = atom_price;
  all_price[2] = bch_price;
  all_price[3] = btc_price;
  all_price[4] = etc_price;
  all_price[5] = eth_price;
  all_price[6] = ltc_price;
  all_price[7] = mkr_price;
  all_price[8] = xtz_price;
  all_price[9] = zrx_price;

  all_price[10] = user1_sum_usd;
  all_price[11] = user1_sum_huf;
  all_price[12] = user2_sum_usd;
  all_price[13] = user2_sum_huf;
}

void printPrices()
{
  Serial.println("ADA: " + (String)ada_price + "$ ATOM: " + (String)atom_price + "$ BCH: " + (String)bch_price + "$ BTC: " +
                 (String)btc_price + "$ ETC: " + (String)etc_price + "$ ETH: " + (String)eth_price + "$ LTC: " + (String)ltc_price + "$ MKR: " +
                 (String)mkr_price + "$ XTZ: " + (String)xtz_price + "$ ZRX: " + (String)zrx_price + "$");

  Serial.println("USER1: " + (String)user1_sum_usd + "$ " + (String)user1_sum_huf + "Ft USER2: " + (String)user2_sum_usd + "$ " + (String)user2_sum_huf + "Ft");
}

// WIFI HANDLER

bool handleWifi()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin((char *)wifi_ssid.c_str(), (char *)wifi_pass.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(6000);
      wifi_reconnect_counter++;
      if (wifi_reconnect_counter > 5)
      {
        Serial.printf("WiFi Failed! Switching to Access Point mode...\n");
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("NO WIFI");
        display.println("AP MODE");
        WiFi.softAP("CryptoMatrix");
        IPAddress IP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(IP);
        break;
      }
      Serial.println("WiFi not connected, trying again...");
      WiFi.begin((char *)wifi_ssid.c_str(), (char *)wifi_pass.c_str());
    }
    wifi_reconnect_counter = 0;
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    wifi_reconnect_counter = 0;
    return false;
  }
  return true;
}

// MATRIX DISPLAY

void IRAM_ATTR display_updater()
{
  portENTER_CRITICAL_ISR(&timerMux);
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  //notify task to unblock it
  vTaskNotifyGiveFromISR(displayUpdateTaskHandle, &xHigherPriorityTaskWoken);

  //display task will be unblocked
  if (xHigherPriorityTaskWoken)
  {
    //force context switch
    portYIELD_FROM_ISR();
  }
  portEXIT_CRITICAL_ISR(&timerMux);
}

void displayUpdateTask(void *)
{
  for (;;)
  {
    //block here untill timer ISR unblocks task
    if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY))
    {
      display.display();
    }
  }
}

void bootlogo()
{
  int imageHeight = 32;
  int imageWidth = 64;
  int counter = 0;
  display.setBrightness(0);
  for (int yy = 0; yy < imageHeight; yy++)
  {
    for (int xx = 0; xx < imageWidth; xx++)
    {
      display.drawPixel(xx, yy, cica[counter]);
      counter++;
    }
  }
  for (int i = 0; i < settings_brightness; i++)
  {
    display.setBrightness(i);
    delay(20);
  }
}

void drawPriceLabel(int priceLabel, int xPos, int yPos)
{
  int counter = 0;
  for (int y = 0; y < 7; y++)
  {
    for (int x = 0; x < 11; x++)
    {
      display.drawPixel(x + xPos, y + yPos, price_labels[priceLabel][counter]);
      counter++;
    }
  }
}

void drawLineview()
{
  int digits;
  display.clearDisplay();

  drawPriceLabel(display_line1, 0, 0);
  drawPriceLabel(display_line2, 0, 8);
  drawPriceLabel(display_line3, 0, 16);
  drawPriceLabel(display_line4, 0, 24);

  putPricesIntoArray();

  display.setTextWrap(false);
  display.setTextColor(display.color565(252, 123, 3));

  digits = floor(log10(all_price[display_line1]) + 1);
  if (all_price[display_line1] > 99999)
    digits -= 3;
  display.setCursor(47 - (digits * 6), 0);
  display.print(all_price[display_line1]);

  digits = floor(log10(all_price[display_line2]) + 1);
  if (all_price[display_line2] > 99999)
    digits -= 3;
  display.setCursor(47 - (digits * 6), 8);
  display.print(all_price[display_line2]);
  digits = floor(log10(all_price[display_line3]) + 1);
  if (all_price[display_line3] > 99999)
    digits -= 3;
  display.setCursor(47 - (digits * 6), 16);
  display.print(all_price[display_line3]);
  digits = floor(log10(all_price[display_line4]) + 1);
  if (all_price[display_line4] > 99999)
    digits -= 3;
  display.setCursor(47 - (digits * 6), 24);
  display.print(all_price[display_line4]);
}

// ESP SETUP

void setup()
{
  cmrx_mode = ON;
  Serial.begin(115200);
  delay(500);

  loadConfig();
  printConfig();

  display.begin(16);
  display.setBrightness(settings_brightness);

  xTaskCreatePinnedToCore(
      displayUpdateTask,        /* where display() actually runs. */
      "displayUpdateTask",      /* name of task. */
      2048,                     /* Stack size of task */
      NULL,                     /* parameter of the task */
      3,                        /* Highest priority so it is immediately launched on context switch after the ISR */
      &displayUpdateTaskHandle, /* Task handle to use for task notification */
      CORE_1);

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &display_updater, true);
  timerAlarmWrite(timer, 2000, true);
  timerAlarmEnable(timer);

  bootlogo();

  WiFi.mode(WIFI_STA);
  Serial.println("Connecting to wifi...");
  handleWifi();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (WiFi.getMode() != WIFI_MODE_STA)
              {
                request->send(SPIFFS, "/wifi.html", String(), false);
              }
              else
              {
                request->send(SPIFFS, "/index.html", String(), false);
              }
            });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/style.css", String(), false); });

  server.on("/getconfig", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", getConfigJSON()); });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send(200, "text/plain");
              for (int i = settings_brightness; i > 0; i--)
              {
                display.setBrightness(i);
                delay(20);
              }
              cmrx_mode = OFF;
            });

  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send(200, "text/plain");
              for (int i = 0; i < settings_brightness; i++)
              {
                display.setBrightness(i);
                delay(20);
              }
              cmrx_mode = ON;
            });

  server.on("/restart", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send(200, "text/plain");
              ESP.restart();
            });

  server.on("/getstatus", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              if (cmrx_mode == ON)
                request->send(200, "application/json", "{\"status\": \"on\"}");
              else
                request->send(200, "application/json", "{\"status\": \"off\"}");
            });

  server.addHandler(wifiset);
  server.addHandler(handler);

  server.begin();

  ArduinoOTA
      .onStart([]()
               {
                 String type;
                 if (ArduinoOTA.getCommand() == U_FLASH)
                   type = "sketch";
                 else // U_SPIFFS
                   type = "filesystem";
                 Serial.println("Start updating " + type);
               })
      .onEnd([]()
             { Serial.println("\nEnd"); })
      .onProgress([](unsigned int progress, unsigned int total)
                  {
                    display.clearDisplay();
                    display.setTextColor(display.color565(255, 0, 0));
                    display.setCursor(0, 0);
                    display.println("FW UPDATE!");
                    display.print(progress / (total / 100));
                    display.print("%");
                    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
                  })
      .onError([](ota_error_t error)
               {
                 Serial.printf("Error[%u]: ", error);
                 if (error == OTA_AUTH_ERROR)
                   Serial.println("Auth Failed");
                 else if (error == OTA_BEGIN_ERROR)
                   Serial.println("Begin Failed");
                 else if (error == OTA_CONNECT_ERROR)
                   Serial.println("Connect Failed");
                 else if (error == OTA_RECEIVE_ERROR)
                   Serial.println("Receive Failed");
                 else if (error == OTA_END_ERROR)
                   Serial.println("End Failed");
               });

  ArduinoOTA.begin();

  getCurrencyData();
}

// MAIN LOOP

void loop()
{
  if (WiFi.getMode() == WIFI_MODE_STA && millis() > timerke + refresh_interval)
  {
    refresh_interval = 2000;
    if (cmrx_mode == ON)
      display.setBrightness(settings_brightness);
    handleWifi();
    getGatewayData();
    calculatePortfolioSum();
    printPrices();
    switch (display_mode)
    {
    case 0:
    {
      drawLineview();
      break;
    }
    case 1: // TODO
    }

    timerke = millis();
  }
  ArduinoOTA.handle();
}