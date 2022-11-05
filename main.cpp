#include "mbed.h"
#include "BME280.h"
#include "LiquidCrystal_I2C.h"

// I2C SDA pin
#define SDA_PIN         D14
// I2C SCL pin
#define SCL_PIN         D15


// Blinking rate in milliseconds
#define BLINKING_RATE   500ms
// I2C address of the BME280 sensor
#define BME280_ADDR     0xEC
// I2C address of the LCD
#define LCD_ADDR        0x27

/* Create a BME280 sensor object connected with I2C protocol
*   @param   sda     SDA I2C Pin
*   @param   scl     SCL I2C Pin
*   @param   addr    I2C address of BME280 module
*/
BME bme280(SDA_PIN, SCL_PIN, BME280_ADDR);


/* Create an LCD object connected with I2C protocol
*   @param   addr    I2C address of BME280 module
*   @param   size_x  Number of columns of the LCD
*   @param   size_y  Number of rows of the LCD
*   @param   sda     SDA I2C Pin
*   @param   scl     SCL I2C Pin
*/
LiquidCrystal_I2C lcd(LCD_ADDR, 20, 4, SDA_PIN, SCL_PIN);
uint8_t droplet[8] =
{0b00100,
0b00100,
0b01010,
0b01010,
0b11001,
0b11101,
0b11111,
0b01110};

uint8_t thermometer[8] =
{0b00100,
0b01010,
0b01010,
0b01010,
0b01010,
0b11101,
0b11111,
0b01110};

int main()
{
    float temp{}, hum_air{}, press{};
    lcd.init();
    lcd.backlight();
    lcd.createChar(0,thermometer);
    lcd.createChar(1,droplet);

    int BMPE_id = bme280.init();    // initialise and get sensor id

    if(!BMPE_id) {
        printf("No sensor detected!!\n");
        while(1){
            ThisThread::sleep_for(200ms);
        }
    }
    temp = bme280.getTemperature();
    hum_air = bme280.getHumidity();
    press = bme280.getPressure()*1;
    lcd.print("Testing");
    lcd.setCursor(0, 1);
    lcd.write(0);
    lcd.print(temp);
    lcd.write(0b11011111);
    lcd.print("C");
    lcd.setCursor(0, 2);
    lcd.write(1);
    lcd.print(hum_air);
    lcd.print("%");
    lcd.setCursor(0, 3);
    lcd.print("Pres:");
    lcd.print(press);
    lcd.print("hPa");
    lcd.blink();
}