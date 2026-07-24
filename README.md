# __Example: *teseo_vic3da_simosgetpos_uart*__

How to use TESEO_VIC3DA part API.

This example demonstrates the use of `teseo_vic3da` GNSS module. The NUCLEO board and the GNSS module communicate via UART, using a register callback function for data handling. The user can connect the NUCLEO board to a PC and use a serial terminal application (such as Tera Term) to view real-time GNSS data transmitted through the NUCLEO board.


## __1. Detailed scenario__

__Initialization phase__: At the beginning of the `main()` function, the `mx_system_init()` function is called to initialize the peripherals. Next `app_init()` function is called to initialize teseo_vic3da GNSS (indicated on terminal as well), teseo_vic3da callbacks and GNSS_parser.

The application executes the following __example steps__:
- __Step 1__: Checks EXEC_STATUS variable which holds the condition value, if it is not equal to EXEC_STATUS_ERROR it will continue to run in while loop.
- __Step 2__: Further, in `app_process()` function first we get GNSS message, check if it is not a null value. Then it goes through check sanity where message length and buffer values are checked.
- __Step 3__: Further, `GNSS_PARSER_ParseMsg()` function parse the message signal and `GNSS_DATA_GetValidInfo()` function gets the valid message and then releases using `teseo_vic3da_drv_release_message()` through UART and displayed on the terminal.

__End of example__: It is an endless example that loops infinitely from step 2.

After firmware is flashed into NUCLEO board, teseo_vic3da is initilaized and is also printed on terminal
```

>[INFO] teseo_vic3da initialization completed

```
If valid GNSS signals are not available, you will get prints as Last position is not valid.
```
>[INFO] teseo_vic3da initialization completed
Last position wasn't valid.



>Last position wasn't valid.



>Last position wasn't valid.



>Last position wasn't valid.



>Last position wasn't valid.



>Last position wasn't valid.



>Last position wasn't valid.



>Last position wasn't valid.



>Last position wasn't valid.
```

When GNSS signals are available and valid, it will print logs on terminal based on your current location.
```
>UTC:                   [ 04:08:39 ]
Latitude:               [ 28' 29'' 16.446000" N ]
Longitude:              [ 77' 29'' 29.708400" E ]
Satellites locked:      [ 18 ]
HDOP:                   [ 2.2 ]
Altitude:               [ 181.80m ]
Geoid infos:            [ -39M ]
Diff update:            [ 0 ]


>UTC:                   [ 04:08:40 ]
Latitude:               [ 28' 29'' 16.447200" N ]
Longitude:              [ 77' 29'' 29.707800" E ]
Satellites locked:      [ 19 ]
HDOP:                   [ 1.6 ]
Altitude:               [ 181.80m ]
Geoid infos:            [ -39M ]
Diff update:            [ 0 ]


>UTC:                   [ 04:08:41 ]
Latitude:               [ 28' 29'' 16.447200" N ]
Longitude:              [ 77' 29'' 29.707800" E ]
Satellites locked:      [ 19 ]
HDOP:                   [ 1.6 ]
Altitude:               [ 181.80m ]
Geoid infos:            [ -39M ]
Diff update:            [ 0 ]


>UTC:                   [ 04:08:42 ]
Latitude:               [ 28' 29'' 16.448400" N ]
Longitude:              [ 77' 29'' 29.708400" E ]
Satellites locked:      [ 19 ]
HDOP:                   [ 1.6 ]
Altitude:               [ 181.80m ]
Geoid infos:            [ -39M ]
Diff update:            [ 0 ]


>UTC:                   [ 04:08:42 ]
Latitude:               [ 28' 29'' 16.448400" N ]
Longitude:              [ 77' 29'' 29.708400" E ]
Satellites locked:      [ 19 ]
HDOP:                   [ 1.6 ]
Altitude:               [ 181.80m ]
Geoid infos:            [ -39M ]
Diff update:            [ 0 ]


>UTC:                   [ 04:08:43 ]
Latitude:               [ 28' 29'' 16.453200" N ]
Longitude:              [ 77' 29'' 29.718000" E ]
Satellites locked:      [ 19 ]
HDOP:                   [ 1.6 ]
Altitude:               [ 181.94m ]
Geoid infos:            [ -39M ]
Diff update:            [ 0 ]


>UTC:                   [ 04:08:44 ]
Latitude:               [ 28' 29'' 16.456200" N ]
Longitude:              [ 77' 29'' 29.723400" E ]
Satellites locked:      [ 19 ]
HDOP:                   [ 1.6 ]
Altitude:               [ 181.94m ]
Geoid infos:            [ -39M ]
Diff update:            [ 0 ]


>UTC:                   [ 04:08:45 ]
Latitude:               [ 28' 29'' 16.458600" N ]
Longitude:              [ 77' 29'' 29.725800" E ]
Satellites locked:      [ 19 ]
HDOP:                   [ 1.6 ]
Altitude:               [ 182.07m ]
Geoid infos:            [ -39M ]
Diff update:            [ 0 ]


>UTC:                   [ 04:08:46 ]
Latitude:               [ 28' 29'' 16.458600" N ]
Longitude:              [ 77' 29'' 29.725800" E ]
Satellites locked:      [ 19 ]
HDOP:                   [ 1.6 ]
Altitude:               [ 182.07m ]
Geoid infos:            [ -39M ]
Diff update:            [ 0 ]


>UTC:                   [ 04:08:46 ]
Latitude:               [ 28' 29'' 16.459200" N ]
Longitude:              [ 77' 29'' 29.726400" E ]
Satellites locked:      [ 19 ]
HDOP:                   [ 1.6 ]
Altitude:               [ 182.08m ]
Geoid infos:            [ -39M ]
Diff update:            [ 0 ]


>UTC:                   [ 04:08:47 ]
Latitude:               [ 28' 29'' 16.459200" N ]
Longitude:              [ 77' 29'' 29.726400" E ]
Satellites locked:      [ 19 ]
HDOP:                   [ 1.6 ]
Altitude:               [ 182.08m ]
Geoid infos:            [ -39M ]
Diff update:            [ 0 ]


>UTC:                   [ 04:08:48 ]
Latitude:               [ 28' 29'' 16.459200" N ]
Longitude:              [ 77' 29'' 29.726400" E ]
Satellites locked:      [ 20 ]
HDOP:                   [ 1.5 ]
Altitude:               [ 182.10m ]
Geoid infos:            [ -39M ]
Diff update:            [ 0 ]


>UTC:                   [ 04:08:49 ]
Latitude:               [ 28' 29'' 16.459200" N ]
Longitude:              [ 77' 29'' 29.726400" E ]
Satellites locked:      [ 20 ]
HDOP:                   [ 1.5 ]
Altitude:               [ 182.10m ]
Geoid infos:            [ -39M ]
Diff update:            [ 0 ]

```

## __2. Example configuration__

This example demonstrates the following drivers:
- parts teseo_vic3da.c/.h
- parts teseo_vic3da_conf.h
- parts teseo_vic3da_queue.c/.h
- parts teseo_vic3da/interfaces/uart/teseo_vic3da_io.c/.h


In this example the `teseo_vic3da` component is configured through the UART IO operations defined under `interfaces/uart` folder.
Once the uart is initialized, the `teseo_vic3da` can be initialized too through the call of `teseo_vic3da_drv_init()` API.
After this step, the GNSS will be ready for getting the data, parsing it and then logging the signals.


## __3. Hardware environment and setup__

### __3.1. Generic Setup__

This section describes the hardware setup principles that apply to any board.

### __3.2. Specific board setups__

<details>
<summary>On STM32C5 series.</summary>
  <summary>On board NUCLEO-C562RE</summary>

  | Board connector | MCU pin | Signal name | ARDUINO <br> connector pin |
  | :-------------: | :-----: | :---------: | :------------------------: |
  |       CN5-6     |   PA5   |  Wakeup     |          D13               |
  |       CN9-8     |   PA8   |  Reset      |          D7                |
  |       CN5-1     |   PA9   |  UART_Tx    |          D8                |
  |       CN9-3     |   PA10  |  UART_Rx    |          D2                |
</details>

## __4. Software setup__

To create a functional project, complete the following steps:
- Select the appropriate IoC2 file based on the combination of NUCLEO and X-NUCLEO boards. For example, use c562re_gnss2a1_teseo_vic3da_simosgetpos_uart.ioc2 for NUCLEO-C562RE and X-NUCLEO-GNSS2A1.
- Open the IoC2 file with STM32CubeMX2.
- Select the preferred toolchain and generate the source code.
- Copy the main.c, main.h, example.c, and example.h files into the project folder of the generated code.
- Open the Integrated Development Environment (IDE), add the example.c and example.h files to the project.
- Add the USE_TRACE=1 to the global variables of the project.
- Compile the project.

## __5. Troubleshooting__

No specific debug tips.


## __6. See Also__

More information about TESEO_VIC3DA part driver can be found in the [TESEO_VIC3DA Part Driver](https://stm32cubedocs-dev.st.com/stm32cube-docs/part-drivers-teseo/1.1.0/en/index.html)

More information about the STM32 ecosystem can be found in the [STM32 MCU Developer Zone](https://www.st.com/content/st_com/en/stm32-mcu-developer-zone.html).


## __7. License__

Copyright (c) 2026 STMicroelectronics.

This software is licensed under terms that can be found in the LICENSE file in the root directory
of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.

