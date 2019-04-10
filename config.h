/*-----------------------------------
 *       STATION CONFIGURATION
 *----------------------------------*/

#ifndef CONFIG_H

#define FIRMWARE_VERSION "1.0.0" //For OTA
#define HOSTNAME "ESPStation"

#define SLEEP_TIME 10 //Minutes
#define BUFFER_SIZE 50

//FUNCTION ENABLED
#define BMP280_ENABLE 1
#define DHT22_ENABLE 1
#define SDS011_ENABLE 1

//PIN CONFIGURATION
#define DHT_DATA_PIN D6
#define I2C_SDA 0 //Used in BMP280 library
#define I2C_SCL 4

#endif
