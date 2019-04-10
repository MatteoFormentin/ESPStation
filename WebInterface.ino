#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <FS.h>
#include "config.h"


ESP8266WebServer webInterface(80);

struct APConf
{
    char ssid[BUFFER_SIZE];
    char password[BUFFER_SIZE];
};

char TOKEN[BUFFER_SIZE];

boolean ap_mode = false;

IPAddress ip_conf(192, 168, 1, 1);
IPAddress mask_conf(255, 255, 255, 0);

void setupWiFi()
{
    SPIFFS.begin();
    WiFi.hostname(HOSTNAME);
    WiFi.persistent(false);
    struct APConf ap = readApConfiguration();

    if (strcmp(ap.ssid, "") != 0)
    {
        WiFi.mode(WIFI_STA);
        WiFi.begin(ap.ssid, ap.password);
        WiFi.waitForConnectResult();
        if (WiFi.status() != WL_CONNECTED)
        {
            ap_mode = true;
            WiFi.disconnect();
        }
    }
    else
    {
        ap_mode = true;
    }

    if (ap_mode) //If timeout or ssid invalid, enable configuration ap
    {
        WiFi.mode(WIFI_AP_STA);
        WiFi.softAP(HOSTNAME, "password");
        WiFi.softAPConfig(ip_conf, ip_conf, mask_conf);
    }

    delay(100);
    setupWebInterface();
}

void handleWebInterface()
{
    webInterface.handleClient();
}

void setupWebInterface()
{
    webInterface.serveStatic("/", SPIFFS, "/ap_conf.html");
    webInterface.on("/ap_conf_submit", handleConfSubmit);
    webInterface.begin();
}

void handleConfSubmit()
{
    String ap_SSID = webInterface.arg("SSID");
    String ap_password = webInterface.arg("password");
    String token = webInterface.arg("token");

    webInterface.send(200, "text/plain", "Device will reboot and try to connect to the given Access Point. You will be disconnected. You can close this page. ");
    struct APConf ap;
    ap_SSID.toCharArray(ap.ssid, BUFFER_SIZE);
    ap_password.toCharArray(ap.password, BUFFER_SIZE);
    updateApConfiguration(ap, token);
}

void updateApConfiguration(struct APConf ap, String token)
{
    Serial.println("Start updating conf");
    if (SPIFFS.exists("/ap.conf"))
    {
        SPIFFS.remove("/ap.conf");
    }
    File conf_file = SPIFFS.open("/ap.conf", "w");

    conf_file.println(ap.ssid);
    conf_file.println(ap.password);
    conf_file.println(token);
    conf_file.close();
    ESP.restart();
}

struct APConf readApConfiguration()
{
    struct APConf ap;
    if (SPIFFS.exists("/ap.conf"))
    {
        File conf_file = SPIFFS.open("/ap.conf", "r");
        int read = conf_file.readBytesUntil('\r', ap.ssid, BUFFER_SIZE);
        ap.ssid[read] = '\0';
        conf_file.seek(1, SeekCur);
        read = conf_file.readBytesUntil('\r', ap.password, BUFFER_SIZE);
        ap.password[read] = '\0';
        conf_file.seek(1, SeekCur);
        read = conf_file.readBytesUntil('\r', TOKEN, 50);
        TOKEN[read] = '\0';
        conf_file.close();
    }
    else
    {
        ap.ssid[0] = '\0';
        ap.password[0] = '\0';
    }
    return ap;
}

bool getApMode()
{
    return ap_mode;
}

char *getToken()
{
    return TOKEN;
}

void sendDataToMeteoServer(String json)
{
    HTTPClient http;
    http.begin("http://meteo.matteoformentin.com/api/update");
    http.addHeader("Content-Type", "application/json");
    http.POST(json);
    http.end();
}

void getUpdate()
{
    Serial.println("Make request"); // may not called we reboot the ESP
    t_httpUpdate_return ret = ESPhttpUpdate.update("meteo.matteoformentin.com", 80, "/api/firmware_update/air_quality_station", FIRMWARE_VERSION);
    switch (ret)
    {
    case HTTP_UPDATE_FAILED:
        break;
    case HTTP_UPDATE_NO_UPDATES:
        break;
    case HTTP_UPDATE_OK:
        break;
    }
}
