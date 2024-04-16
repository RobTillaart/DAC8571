//
//    FILE: DAC8571_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/DAC8571
//
// NOTE: output is written in markdown format of a table
//       (so easy to include in the readme.md ;)
//       can be changed to tab based or comma based output


#include "DAC8571.h"

DAC8571 dev(0x48);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DAC8571_LIB_VERSION: ");
  Serial.println(DAC8571_LIB_VERSION);

  Wire.begin();

  dev.begin();

  if (! dev.isConnected())
  {
    Serial.println("\nFailed to connect\n");
    // while(1);
  }
  delay(100);

  test1();
}


void loop()
{
}


/////////////////////////////////////////////////////////////////////////

void test1()
{
  Serial.println(F("| - Wire clock KHz - | - write() us - | - read() us - |"));
  Serial.println(F("|:----:|:----:|:----:|"));
  for (uint8_t i = 1; i < 14; i++)
  {
    uint32_t clk = 50000UL * i;
    Serial.print("| ");
    Serial.print(clk/1000);
    Wire.setClock(clk);
    test_DAC();
    delay(10);
    Serial.println(" |");
  }
  Serial.println();
}


void test_DAC()
{
  start = micros();
  for (uint16_t i = 0; i < 1000; i++)
  {
    uint16_t val = i;
    dev.write(val);
  }
  stop = micros();
  Serial.print(" | ");
  Serial.print((stop - start) * 0.001);
}


//  -- END OF FILE --
