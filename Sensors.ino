/*-----------------------------------
 *              BMP 280
 *----------------------------------*/
#ifdef BMP280_ENABLE
#include "src/BMP280/Adafruit_BMP280.h"

Adafruit_BMP280 bmp;

void setupBMP()
{
    bmp.begin();
}

float getPressure()
{
    return bmp.readPressure();
}
#endif

/*-----------------------------------
 *              DHT 22
 *----------------------------------*/
#ifdef DHT22_ENABLE

#include <DHT.h>
#include <DHT_U.h>

DHT_Unified dht(DHT_DATA_PIN, DHT22);

void setupDHT()
{
}

float getTemperature()
{
    sensors_event_t temp;
    dht.temperature().getEvent(&temp);
    return temp.temperature;
}

float getHumidity()
{
    sensors_event_t hum;
    dht.humidity().getEvent(&hum);
    return hum.relative_humidity;
}
#endif

/*-----------------------------------
 *              SDS011
 *----------------------------------*/
#ifdef SDS011_ENABLE
#include "src/SDS011/SDS011.h"
float pm25, pm10;

SDS011 sds_sensor;

void setupSDS()
{
    sds_sensor.begin(&Serial);
    delay(100);
    sds_sensor.wakeup();
}

void getSDSData()
{

    float temp_pm25, temp_pm10;
    int error = sds_sensor.read(&temp_pm25, &temp_pm10);
    sds_sensor.sleep();
    if (!error)
    {
        pm25 = temp_pm25;
        pm10 = temp_pm10;
    }
    else
    {
        pm25 = -1;
        pm10 = -1;
    }
}

float getPm25()
{
    return pm25;
}

float getPm10()
{
    return pm10;
}

void sleepSDS()
{
    sds_sensor.sleep();
}

#endif
