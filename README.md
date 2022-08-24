# pico_timer
Simple interrupt driven code for RP2040 for coding challenge

## Tasks
* Implement a 16-bit timer
* Toggle LED within 30ms of each time timer reaches `0xFFFF`
* At a 3s interval, using the same timer, have a separate LED blink five times

## Building & Deploying Application

### Build Process
Building will require Raspberry Pi [Pico-SDK](Link Will Go Here), but ideally I would like to 
supply a dockerfile to encapsulate the build process

Currently TBD, but build process will ideally be as simple as:

```sh
mkdir build
cd build
cmake ..
make
```

To deploy to the Raspberry Pi Pico microcontroller, hold the `BOOTSEL` button while connecting to 
a computer over USB. This will place the microcontroller into a mass-storage device mode where the 
compiled `.uf2` file can be copied over. The microcontroller should reboot and flash the application.
