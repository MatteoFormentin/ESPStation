# ESPStation

ESP8266 based weather station for Meteo Server data logging  

## Modular Design

Can log Temperature, Humidity (DHT22), Pressure (BMP280), Air Quality (SDS011). Sensor can be enabled/disabled in config.h file.

## Simple Network and API Token configuration

If network is not configured, ESP Station switch to AP mode and create a network for setup purpose. Just head to 192.168.1.1 and fill the form.

## Low Power Operation

ESP Station use ESP8266 deep sleep to save power when not in use. Sensors are also turned off.

## Software Update

Automatic software update from Meteo Server (OTA). Different configuration of the station can be differentiate by setting MODEL in configuration so that a different update can be served.
  
*© 2019 Matteo Formentin*
www.matteformentin.com