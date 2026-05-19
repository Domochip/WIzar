#ifndef WIzar_h
#define WIzar_h

#include "Main.h"
#include "base/MQTTMan.h"
#include "base/Application.h"

const char appDataPredefPassword[] PROGMEM = "ewcXoCt4HHjZUvY1";

#include "data/status2.html.gz.h"
#include "data/config2.html.gz.h"

#include <izar_wmbus.h>

class WIzar : public Application
{
private:
#define HA_MQTT_GENERIC 0

  typedef struct
  {
    byte type = HA_MQTT_GENERIC;
    uint32_t port = 1883;
    char username[128 + 1] = {0};
    char password[150 + 1] = {0};
    struct
    {
      char baseTopic[64 + 1] = {0};
    } generic;
  } MQTT;

#define HA_PROTO_DISABLED 0
#define HA_PROTO_MQTT 1

  typedef struct
  {
    byte protocol = HA_PROTO_DISABLED;
    char hostname[64 + 1] = {0};
    MQTT mqtt;
  } HomeAutomation;

  IzarWmbus _izarWmbusReader;
  IzarResultData _izarData;
  uint32_t _meterId;

  HomeAutomation _ha;
  int _haSendResult = 1;
  WiFiClient _wifiClient;

  MQTTMan _mqttMan;

  void setConfigDefaultValues();
  bool parseConfigJSON(JsonDocument &doc, bool fromWebPage);
  void fillConfigJSON(JsonDocument &doc, bool forSaveFile);
  void fillStatusJSON(JsonDocument &doc);
  bool appInit(bool reInit);
  const PROGMEM char *getHTMLContent(WebPageForPlaceHolder wp);
  size_t getHTMLContentSize(WebPageForPlaceHolder wp);
  void appInitWebServer(WebServer &server);
  void appRun();

public:
  WIzar();
};

#endif
