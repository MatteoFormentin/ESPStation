
#include "src/BMP280/Adafruit_BMP280.h"
#include <DHT.h>
#include <DHT_U.h>
#include "src/SDS011/SDS011.h"

/*-----------------------------------
 *              BMP 280
 *----------------------------------*/
#ifdef BMP280_ENABLE

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

SDS011 sds_sensor;

void setupSDS()
{
    sds_sensor.begin(&Serial);
    delay(100);
    sds_sensor.wakeup();
}

float getPm25()
{
    float pm25, pm10;
    int error = sds_sensor.read(&pm25, &pm10);
    sds_sensor.sleep();
    if (!error)
    {
        return pm25;
    }
    else
    {
        return 0;
    }
}

float getPm10()
{
    float pm25, pm10;
    int error = sds_sensor.read(&pm25, &pm10);
    if (!error)
    {
        return pm10;
    }
    else
    {
        return 0;
    }
}

void sleepSDS()
{
    sds_sensor.sleep();
}

#endif
