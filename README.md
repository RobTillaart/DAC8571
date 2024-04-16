
[![Arduino CI](https://github.com/RobTillaart/DAC8571/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DAC8571/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DAC8571/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DAC8571/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DAC8571/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/DAC8571.svg)](https://github.com/RobTillaart/DAC8571/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/DAC8571/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/DAC8571.svg?maxAge=3600)](https://github.com/RobTillaart/DAC8571/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/DAC8571.svg)](https://registry.platformio.org/libraries/robtillaart/DAC8571)


# DAC8571

Arduino library for DAC8571 I2C 16 bit DAC.


## Description

**Experimental**

The DAC8571 is a small low-power, 16-bit voltage Power-On Reset to Zero output DAC.


#### Compatibles

TODO


## I2C

#### Address


|  Address  |   A0   |
|:---------:|:------:|
|   0x4C    |   LOW  |
|   0x4E    |  HIGH  |


#### I2C multiplexing

Sometimes you need to control more devices than possible with the default
address range the device provides.
This is possible with an I2C multiplexer e.g. TCA9548 which creates up 
to eight channels (think of it as I2C subnets) which can use the complete 
address range of the device. 

Drawback of using a multiplexer is that it takes more administration in 
your code e.g. which device is on which channel. 
This will slow down the access, which must be taken into account when
deciding which devices are on which channel.
Also note that switching between channels will slow down other devices 
too if they are behind the multiplexer.

- https://github.com/RobTillaart/TCA9548


#### Related

- https://github.com/RobTillaart/AD5680 (18 bit DAC)
- https://github.com/RobTillaart/DAC8550
- https://github.com/RobTillaart/DAC8551
- https://github.com/RobTillaart/DAC8552
- https://github.com/RobTillaart/DAC8554
- https://github.com/RobTillaart/DAC8571
- https://github.com/RobTillaart/MCP_DAC
- https://github.com/RobTillaart/MCP_ADC


## Interface

```cpp
#include "DAC8571.h"
```

#### Constructor

- **DAC8571(uint8_t address = 0x4C, TwoWire \*wire = &Wire)** constructor with I2C address.
Default is 0x4C, optional set the WireN I2C bus.
- **bool begin(uint16_t value = 0)** Set initial value for the DAC, typical zero (power on default).
Returns false if address out of range, or if device cannot be seen on the I2C bus.
Returns **true** if successful.
- **bool isConnected()** test to see if address can be reached on the I2C bus.
- **uint8_t getAddress()** returns address set in constructor.


#### CORE

The DAC8571 has one 16 bit DAC. Output value 0..65535 == 0..Vref Volts (datasheet).

- **bool write(uint16_t value = 0)** writes a value 0..65535 to the DAC.
- **uint16_t lastWrite()** get last value written from cache (fast).
- **uint16_t read()** get last written value from device.


#### MODI

The DAC8571 can be written in different modi (datasheet page 19).
Not all modi are supported yet, these need testing.  
Setting the mode will be applied for all writes until mode is changed.

|  mode  |  support  |  meaning  |
|:------:|:---------:|:----------|
|   0    |     Y     |  store value in temporary register. preparation for (2, 3 and 4)
|   1    |  default  |  update DAC with value written.
|   2    |     Y     |  writes the temporary register to DAC, ignores new value.
|   3    |     N     |  broadcast update. Not supported yet.
|   4    |     N     |  broadcast update. Not supported yet.
| other  |     Y     |  maps unto default mode 1.


#### Broadcast mode

TO INVESTIGATE (page 19)


#### Error codes

- **int lastError()** always check this value after a read / write to see if it was OK (== 0).
After the read the error value is reset to OK.

|  Error code             |  Value  |  Notes  |
|:------------------------|:-------:|:--------|
|  DAC8571_OK             |  0x00   |
|  DAC8571_PIN_ERROR      |  0x81   |
|  DAC8571_I2C_ERROR      |  0x82   |
|  DAC8571_MODE_ERROR     |  0x83   |
|  DAC8571_CHANNEL_ERROR  |  0x84   |
|  DAC8571_ADDRESS_ERROR  |  0x85   |


## Operations

See examples.


## Future

#### Must

- improve documentation
- test with hardware
- test different write modi 


#### Should

- add examples
  - demo, wire1, etc
  - Wire1
- replace magic numbers


#### Could

- investigate broadcast support


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


