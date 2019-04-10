//ESPTATION v1.00
//Set NODEMCU v1

#include "config.h"
#include <ArduinoJson.h>

void setup()
{
    //CONNECTION SETUP
    setupWiFi();

    /*---- PERFORM EVERY TASK ----*/
    if (!getApMode())
    {
        /*---- INIT SENSOR ----*/
#ifdef BMP280_ENABLE
        setupBMP();
#endif

#ifdef DHT22_ENABLE
        setupDHT();
#endif

#ifdef SDS011_ENABLE
        setupSDS();
#endif
        delay(10000); //Wait some time to make sensor acquire some sample

        /*---- SEND DATA ----*/
        postData();

        /*---- SLEEP SENSOR ----*/
#ifdef SDS011_ENABLE
        sleepSDS();
#endif

        /*---- CHECK FOR FIRMWARE UPDATES ----*/
        getUpdate();

        ESP.deepSleep(SLEEP_TIME * 60000000); //In microseconds
    }
}

void loop()
{
    handleWebInterface(); //EXECUTED ONLY IF AP NOT CONNECTED
}

void postData()
{
    StaticJsonDocument<200> doc;
    doc["token"] = getToken();

#ifdef BMP280_ENABLE
    doc["pressure"] = getPressure();
#endif

#ifdef DHT22_ENABLE
    doc["temperature"] = getTemperature();
    doc["humidity"] = getHumidity();
#endif

#ifdef SDS011_ENABLE
    doc["air_quality"]["PM25"] = getPm25();
    doc["air_quality"]["PM10"] = getPm10();
#endif

    String json;
    serializeJson(doc, json);
    sendDataToMeteoServer(json);
}
