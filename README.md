# Raspberry Pi Pico FreeRTOS Starter

## Purpose

The purpose of this project is to provide a somewhat turn-key starter project
for using FreeRTOS on Raspberry Pi Pico boards.

Connect an LED to GPIO port 15 and it will flash at 1Hz.

![alt tag](setup.jpg)

## Board Support

This project should work out-of-the-box for the following boards.

- Raspberry Pi Pico
- Raspberry Pi Pico W (currently set to his in `CMakeLists.txt`)
- Raspberry Pi Pico 2
- Raspberry Pi Pico 2W

Modify this line in `CMakeLists.txt` for other board types:
```
set(PICO_BOARD pico_w CACHE STRING "Board type")
```

## Project Setup

> [!NOTE]
> This project supports the Pico SDK VS Code extension. If you use VS Code as
> your IDE, you can install the Pico SDK extension and the setup process is
> done for you.

### Requirements

1. CMake 3.20 or later
2. Raspberry Pi Pico C SDK

### Building

1. Clone the project on to your system

2. Within the project root, update the submodules to clone the FreeRTOS kernel

```shell
$ git submodule update --init FreeRTOS
```

3. Within the project root, use CMake and make to build it:

```shell
cmake .
make
```

> {!IMPORTANT}
> On Windows, use the Ninja generator from CMake.
> `cmake -B . -G Ninja`

4. Installation on the Pico:

Install `pico-freertos-starter.uf2`
by copying it to the Pico's mass storage drive which is available when you hold
the boot button on the pico while plugging it in to your computer. You can
also use picotool to install the elf binary directly to the pico using SWD
with the Raspberry Pi Debug Probe.

## Other Notes

- The simplest way to customize the build is to use the VS Code extension for the
Pico SDK. The extension provides an interface to quickly reconfigure CMake for
different boards.

- The project uses the forked version of the FreeRTOS Kernel provided by
Raspberry Pi.

## See Also

Check out the [FreeRTOS Kernel Book](https://github.com/FreeRTOS/FreeRTOS-Kernel-Book/blob/main/toc.md)
to learn more about FreeRTOS and waht it offers.
