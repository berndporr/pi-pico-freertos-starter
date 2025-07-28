# Raspberry Pi Pico FreeRTOS Starter

## Purpose

The purpose of this project is to provide a somewhat turn-key starter project
for using FreeRTOS on Raspberry Pi Pico boards.

## Board Support

This project should work out-of-the-box for the following boards.

- Raspberry Pi Pico
- Raspberry Pi Pico W
- Raspberry Pi Pico 2
- Raspberry Pi Pico 2W

This project should also work with other boards using RP2040 or RP2350
microcontrollers but may require more advanced changes. For example, boards
with extended external RAM may need to link with the `FreeRTOS-Kernel-Heap5`
library for the memory scheme and properly initialize it. For more information
about the built-in memory models for FreeRTOS, see [Chapter 3 of the FreeRTOS
Kernel Book](https://github.com/FreeRTOS/FreeRTOS-Kernel-Book/blob/main/ch03.md)

## Project Setup

> [!NOTE]
> This project supports the Pico SDK VS Code extension. If you use VS Code as
> your IDE, you can install the Pico SDK extension and ththe setup process is
> done for you.

### Requirements

1. CMake 3.20 or later
2. Raspberry Pi Pico C SDK

> [!IMPORTANT]
> The project assumes the Pico SDK is installed in your home directory and in a
> folder named `.pico-sdk`. I.e., `/Users/dev/.pico-sdk/`

### Building

1. Clone the project on to your system

2.Within the project root, update the submodules to clone the FreeRTOS kernel

```shell
$ git submodule update --init FreeRTOS
```

3. Within the project root, use CMake to generate the build scripts

```shell
$ cmake -B ./build
```

> {!IMPORTANT}
> On Windows, use the Ninja generator from CMake.
> `cmake -B ./build -G Ninja`

4. Build the project

```shell
$ cmake --build ./build
```

The built programs are in the `build` directory. You can install the UF2 file
by copying it to the Pico's mass storage drive which is available when you hold
the boot button on the pico while plugging it in to your computer. You can
also use picotool to install the elf binary directly to the pico using SWD
with the Raspberry Pi Debug Probe.

## Other Notes

- By default, the project is set up to build for the pico2 with the RP2350 in ARM
mode. You can modify the `CMakeLists.txt` file to change the board and platform
for your needs.

- The simplest way to customize the build is to use the VS Code extension for the
Pico SDK. The extension provides an interface to quickly reconfigure CMake for
different boards.

- The project uses the forked version of the FreeRTOS Kernel provided by
Raspberry Pi. This fork provides a port for the RP2350 which seems to be
absent from the mainline kernel. Unfortunately, this fork does not keep track
of the versions in the mainline repository. If you would like to use the
mainline repository you will need to port ityourself for the RP2350.

## See Also

Check out the [FreeRTOS Kernel Book](https://github.com/FreeRTOS/FreeRTOS-Kernel-Book/blob/main/toc.md)
to learn more about FreeRTOS and waht it offers.
