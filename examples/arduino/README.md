## nmtools Arduino examples

- [manip](manip/) 
- [ufuncs](ufuncs/)

### Requirements
- [platformio](https://platformio.org/install)
- [simavr](https://github.com/buserror/simavr) (optional, for arduino simulation)
- [avr-gcc 9+](https://github.com/alifahrri/toolchain-avr-gcc/releases/tag/v9.2.0), required to override the default AVR toolchain which doesn't have complete core C++17 language features.

### Running the examples

Go to [manip](manip/) or [ufuncs](ufuncs/), then:
```
platformio run --target upload
```
```
platformio device monitor
```

#### Build only (for simavr)
```
platformio run --verbose -e mega
```

#### Using simavr

- Arduino UNO
```
simavr --mcu "atmega328p" .pio/build/uno/firmware.elf
```
- Arduino MEGA
```
simavr --mcu "atmega2560" .pio/build/mega/firmware.elf
```

#### STM32
```
platformio run --target upload -e nucleo_f401re && platformio device monitor
```

### Debugging

```
platformio debug && platformio debug --interface=gdb -x .pioinit
```