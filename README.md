# L3G4200D - Arduino I2C library

C++ library for L3G4200D gyroscope for I2C communication with Arduino Wire library. Main features:

- read raw and scaled data,
- low pass filtering,
- gyroscope calibration procedure,
- registers setting.

The library is intended to work **without any user interference**, just open [project](https://github.com/MatthewPatyk/L3G4200D-Arduino-I2C-library/blob/master/L3G4200D_/L3G4200D_.atsln) and upload working [example](https://github.com/MatthewPatyk/L3G4200D-Arduino-I2C-library/blob/master/L3G4200D_/L3G4200D_/L3G4200D_.ino) and use it.

Library uses [I2C Interface](https://github.com/MatthewPatyk/I2C-Interface-for-Arduino-Wire-Library), [I2C Sensor Interface](https://github.com/MatthewPatyk/I2C-Sensor-Interface) to simplify and unify working with I2C devices. The library also uses [Status Class](https://github.com/MatthewPatyk/Status-Class) which is optional.

## Getting Started

The working example for this library is written in [Atmel Studio 7](http://www.microchip.com/mplab/avr-support/atmel-studio-7) with [Visual Micro](https://www.visualmicro.com/) addon. But **it is possible to run it with Arduino IDE** by [adding files to project](https://www.arduino.cc/en/Guide/Environment#toc8) (probably there will need to change the `#include` paths).

### Prerequisites

- Software:
  - [Atmel Studio 7](http://www.microchip.com/mplab/avr-support/atmel-studio-7) (tested) or Visual Studio,
  - [Visual Micro](https://www.visualmicro.com/) addon for above AS7 or VS.
- Hardware:
  - Arduino Due (tested) or Arduino Uno (any ATmega 328P) board,
  - L3G4200D board or any IMU sensor with L3G4200D.

### Wiring

| L3G4200D board | Due board | Uno board |
| :------------: | :-------: | :-------: |
|      SCL       | SCL (21)  | SCL (A4)  |
|      SDA       | SDA (20)  | SDA (A5)  |
|    VCC 3.3V    |   3.3V    |   3.3V    |
|     VCC 5V     |   - \*    |    5V     |
|      GND       |    GND    |    GND    |

\*The Due MCU cannot be exposed to the voltage above 3.3V level!

## Example

To see a real-life example open AS7 project file `L3G4200D_.atsln` and upload the `L3G4200D_.ino` to a micro-controller. You should see something like that on Serial Monitor (baud rate = 115200):

```plaintext
3	Found L3G4200D searching device with ID = 0x69
11	Angular Velocities:	X = -0.25	Y = 0.03	Z = 0.16	Temporary traveled angle:	X = -0.00	Y = 0.00	Z = 0.00
21	Angular Velocities:	X = -0.28	Y = -0.14	Z = 0.13	Temporary traveled angle:	X = -0.00	Y = -0.00	Z = 0.00
31	Angular Velocities:	X = -0.13	Y = -0.16	Z = 0.08	Temporary traveled angle:	X = -0.00	Y = -0.00	Z = 0.00
41	Angular Velocities:	X = -0.09	Y = -0.19	Z = 0.19	Temporary traveled angle:	X = -0.00	Y = -0.00	Z = 0.00
...
```

### Scale and baud rate setting

To change scale and baud rate use `L3G4200D::setDataRateAndBandwidth()`, `L3G4200D::setScale()`:

```cpp
Gyroscope.setDataRateAndBandwidth(->your_setting<-);
Gyroscope.setScale(->your_setting<-);
```

### Calibration process

To enable calibration process, in `L3G4200D_.ino` uncomment:

```cpp
//Gyroscope.performCalibrationProcedure();
```

and upload program, you should see in Serial Monitor:

```plaintext
2	Serial initialized with baudrate = 115200
3	Found L3G4200D searching device with ID = 0x69
3	Calibration in: 3 seconds! DON'T MOVE DEVICE
1003	Calibration in: 2 seconds!
2003	Calibration in: 1 seconds!
8003	Xmean = 0.19678	Ymean = -0.04611	Zmean = -0.00472
```

follow the instructions in Serial Monitor.

```plaintext
8003	In L3G4200D.h change define values
		L3G4200D_X_OFFSET to 0.19678
		L3G4200D_Y_OFFSET to -0.04611
		L3G4200D_Z_OFFSET to -0.00472
8008	Then uncomment Gyroscope.performCalibrationProcedure() in your program. Make sure that Gyroscope.calibrationSetting() is enabled
```

**Important**: by default calibration is made on **filtered data**.

#### Low pass filter and calibration parameters

Low pass filter and including calibration parameters are enabled by default, to disabled those features use `L3G4200D::lowPassFilterSetting()` and `L3G4200D::calibrationSetting()`.

You can change low pass filter **alpha parameter** in `L3G4200D.h` file, by setting the `L3G4200D_LOW_PASS_FILTER_ALPHA` define value from range `<0, 1>`.
