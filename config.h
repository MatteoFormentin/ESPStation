/*-----------------------------------
 *       STATION CONFIGURATION
 *----------------------------------*/

#ifndef CONFIG_H

//OTA PARAMETERS 
#define FIRMWARE_VERSION "1.0.3" //Remind to update else update will be always performed
#define MODEL "esp_station" //Update model on Meteo Server must be equal
#define METEO_SERVER_URL "meteo.matteoformentin.com" //Without ending /

//CONFIGURATION NETWORK 
#define HOSTNAME "ESPStation" //Also wifi SSID

//FUNCTION ENABLED (Comment to disable)
#define BMP280_ENABLE
#define DHT22_ENABLE
//#define SDS011_ENABLE

//PIN CONFIGURATION
#define DHT_DATA_PIN D4
#define I2C_SDA 0 //Used in BMP280 library - ESP8266 use configurable i2c pin
#define I2C_SCL 4

#define SLEEP_TIME 20  //Minutes
#define BUFFER_SIZE 50 //Do not change

#endif
