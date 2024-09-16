#include <Arduino.h>
#include <SPI.h>
#include <MPU9250.h>

/*
--VCC: 2.4V to 3.6V power source.
--GND: ground.
--FSYNC: not used, should be grounded.
--SDA / SDI: connect to MOSI.
--SCL / SCLK: connect to SCK.
--AD0 / SDO: connect to MISO.
--nCS: connect to chip select pin (Any digital pin)
*/

#define SPI_CLOCK 8000000 // 8MHz clock works.

#ifdef NODEMCU
#define SPI1_SCK_PIN D5
#define SPI1_SDI_PIN D6
#define SPI1_SDO_PIN D7
#define NCS_PIN D4
#endif

MPU9250 mpu(SPI_CLOCK, NCS_PIN);

void setup()
{
  Serial.begin(115200);
#ifdef NODEMCU
  SPI.begin();
#endif

  mpu.init(true);

  uint8_t wai = mpu.whoami();

  Serial.print("address: "); // here 0x70
  Serial.println(wai);

  mpu.calib_acc();
  mpu.calib_mag();
}

void loop()
{

  mpu.read_all();

  Serial.print(mpu.gyro_data[0]);
  Serial.print('\t');
  Serial.print(mpu.gyro_data[1]);
  Serial.print('\t');
  Serial.print(mpu.gyro_data[2]);
  Serial.print('\t');
  Serial.print(mpu.accel_data[0]);
  Serial.print('\t');
  Serial.print(mpu.accel_data[1]);
  Serial.print('\t');
  Serial.print(mpu.accel_data[2]);
  Serial.print('\t');
  Serial.print(mpu.mag_data[0]);
  Serial.print('\t');
  Serial.print(mpu.mag_data[1]);
  Serial.print('\t');
  Serial.print(mpu.mag_data[2]);
  Serial.print('\t');
  Serial.println(mpu.temperature);

  delay(10);
}