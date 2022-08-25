# pico_timer
Simple interrupt driven code for RP2040 for coding challenge

## Tasks
* Implement a 16-bit timer
* Toggle LED within 30ms of each time timer reaches `0xFFFF`
* At a 3s interval, using the same timer, have a separate LED blink five times

## Building & Deploying Application

### Setting Up Environment
1. `./buildContainer.sh` to create local docker image to house cross-compilation tools (should only need to be called once)
2. `./launchContainer.sh` to launch an instance of the docker container (used whenever we need to compile)
3. `./prepEnvironment.sh` to clone/pull the most updated version of the C/C++ SDK for the RP2040 (generally used once)

### Build Process
Building will require Raspberry Pi Pico's SDK. The above mentioned scripts should handle the dependencies such that all one should require is Docker.

Actual build process TBD, but will ideally be as simple as:

```sh
mkdir build
cd build
cmake ..
make
```

### Deploying Application

To deploy to the Raspberry Pi Pico microcontroller, hold the `BOOTSEL` button while connecting to 
a computer over USB. This will place the microcontroller into a mass-storage device mode where the 
compiled `.uf2` file can be copied over. The microcontroller should reboot and flash the application.
