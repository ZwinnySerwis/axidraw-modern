EBB Command Set Documentation

Software for the Original EggBot Kit

# EBB (EiBotBoard) Command Set, Firmware v3.0+ 

 This document details the serial command protocol used by the EBB (EiBotBoard) with firmware v3.0 and higher. Legacy documentation for prior versions is available here. 

 The EBB is an open source USB-based motor control board, designed to drive two stepper motors. The EBB may be used on its own, or found as the control board of such machines as The Original Egg-Bot, The WaterColorBot, or AxiDraw. 

## Contents

Serial communication and APIs

Introduction to the EBB firmware

Major Changes in Firmware v3.0

Updating firmware

Addressing issues

Additional resources

Command reference

1. Syntax and conventions
2. List of commands

Returned Errors

Initial I/O pin configuration

Performance

FAQ

License

## Serial communication: High-level interfaces and APIs

 The serial protocol described in this document can be used directly, for example from a serial terminal, in order to carry out simple tasks. It can also be accessed from within any program or programming environment that is capable of communicating with a USB serial device. Using this protocol from within high-level computer languages allows one to construct and execute complex motion. All EBB applications and interfaces use this serial protocol, at their lowest levels, in order to manage the motion control. 

 The serial protocol specifies the fundamental primitives of how the machine operates— for example moving from position (a1, b1) to position (a2, b2) in duration Δ t, with the pen-lift servo motor at position z. By contrast, higher level programs may perform tasks such as opening up SVG files and converting them into a set of robotic movements that can be carried out through the serial protocol. 

 Here are some possible starting points for building higher level applications: 

- The Inkscape-based drivers for the EggBot, for the WaterColorBot, and for AxiDraw are written in python, and use this serial protocol. The codebases from those projects are excellent resources for getting started. 
- The Processing-based program RoboPaint RT is designed to control the WaterColorBot through a real-time interface. This program is written in Processing (Java), and serves as a good example of how to manage the EBB through Processing. 
- RoboPaint is a stand-alone cross-platform program to drive the WaterColorBot (as well as EggBot and AxiDraw). RoboPaint is written in javascript and (while running) provides several APIs that can be used to control machines based on the EBB: 

- RoboPaint, under the hood, uses the cncserver and its RESTful API to operate. It is a relatively low level interface, with similar functionality to the serial protocol, plus a few helpful utilities. 
- The higher-level RoboPaint remote print API allows local or remote "printing" of SVG files to EBB based machines, when attached to a computer running RoboPaint. 
- The simplified ("GET only") Scratch API provides a method of controlling EBB based machines from the address bar of a web browser, or from simple programming languages that can retrieve data from an URL. 
- cncserver can be run on its own, from the command line, as a javascript-based RESTful API server to control EBB-based machines. (You can also run it by simply launching RoboPaint.) 

## Introduction to the EBB firmware

 The documentation on this page is for the to EiBotBoard Firmware v3.0 and above. If you are using an older version of the firmware (most likely in the 2.0 series), please refer to the EBB 2.8.1 documentation which documents prior syntax and prior changes to the syntax between versions (for versions prior to EBB 3.0). Individual command descriptions in this document may note changes between EBB 2.8.1 and 3.0, but generally do not describe version history prior to 2.8.1. 

 The EBB firmware was originally based on the UBW firmware. Its command documentation has an introduction to the UBW command processing framework, but this stand-alone document does not refer to it further. 

 Although the EBB firmware is a continuously evolving code base, we have, since version 2.0.1, taken care to minimize compatibility changes that would affect the most common machines using the EBB: The AxiDraw, EggBot, and WaterColorBot. If you are using one of these machines and it is working well for you, there is generally no requirement to update your firmware to a newer version. 

 There are, of course, many smaller changes in the code between the versions on older EBB firmware and the latest versions. If you are developing new applications with the EBB, we encourage you to update to the newest version. On the other hand, if you are writing new software that targets machines of various ages (for example, new EggBot software), please be aware that many of the machines out there are still using older firmware revisions. 

 As we will note in the next section, EBB firmware v3.x labels a transitional version between the v2.x syntax and planned future version syntax. While it maintains compatibility for existing applications that use the EBB (with firmware 2.x), it also introduces changes for compatibility with the future version syntax. These include deprecations of some commands and queries. There is also a new "unified" syntax -- disabled by default -- for responses to commands and queries. Enabling this syntax allows one to develop or adapt programs that use the EBB for future compatibility with a future firmware version. 

## Major Changes in Firmware v3.0

 EBB firmware v3.x is a transitional series introducing new features, optional in v3.x, which will become standard in a future firmware version, and deprecating some commands and queries. If you are updating a custom application that uses the EBB firmware and are migrating it from a pre-3.0 version, please read this section carefully as it does describe potentially breaking changes. 

 The most important change is the introduction of a future syntax mode, which is off by default, and which can be enabled by the command `CU,10,1`. Future syntax mode does not change the syntax that is used to send commands or queries to the EBB; it changes the format of responses to commands and queries. With future syntax mode enabled, these responses will use the format that is planned for a future firmware version, rather than the default "legacy" response format. The legacy response format will be removed in that future firmware version and should be considered to be deprecated. (See notes on the `CU` command.) 

 The following are potentially breaking changes in the command and structure, and commands: 

`QG` — Query General. The meanings of bits 6 and 7 has changed.

`S2` — General RC Servo Output.

 Maximum number of simultaneous RC servo outputs reduced from 24 to 8. 

 `PC`, `PG`, `T`, and commands removed as per issue #216

 The following commands and queries have been deprecated as of EBB firmware v3.0, and will be removed in a future firmware version. They are functional, but should be migrated to use suggested alternatives instead. 

- `QB` — Query Button. Migrate to:`QG`. 
- `QM` — Query Motors. Migrate to:`QG`.
- `QP` — Query Pen. Migrate to:`QG`.
- `ND` — Node count Decrement. Migrate to:`SL`
- `NI` — Node count Increment. Migrate to:`SL`
- `QN` — Query Node count. Migrate to:`QL`
- `I` — Input (digital). Migrate to:`PI`
- `O` — Output (digital). Migrate to:`PO`

 Additional deprecated commands that will be removed in a future firmware version: 

- `A` — Analog value get
- `AC` — Analog configure
- `CU,1` — Legacy syntax

 Please see the release notes for additional information about differences between versions. 

## Updating your firmware

 Instructions for updating firmware, including easy installers for Mac and Windows, can be found on the Evil Mad Scientist Wiki. 

## Addressing Issues

 If you discover something that does not work as expected in the EBB firmware, please contact us by e-mail, in our forum, or (preferably) file an issue on GitHub : https://github.com/evil-mad/EggBot/issues. 

 Please include a clear method to reproduce the issue, the expected behavior as well as the observed behavior, and the version number of the EBB firmware version that you are using. 

## Additional Resources

- Boot up configuration information
- Hardware documentation for the EBB can be found on the main EBB page.
- EBB firmware release notes for versions 2.0.1 up through the newest version.

### Syntax and conventions

 The following syntax conventions are established to assist with clarity of communication as we describe the EBB commands. 

#### EBB Syntax Conventions:

- Command format descriptions and examples are set in `code font`, with a shaded background.
- Query response format descriptions and examples are also set in the same `code font`.
- Italics are used to represent variables and adjustable parameters.
- Square brackets (`[ ]`) are used to enclose optional items.
- Angle brackets (`< >`) are used to represent individual control characters, such as ` ` for carriage return or ` ` for newline, in command and query format descriptions.
- Individual control characters may also be given by their backslash-escaped representation, as in `\r` for carriage return or `\n` for linefeed, in the context of literal command examples.
- All unitalicized text and punctuation within a command description must be used literally.

#### Additionally, please note that:

- All commands are composed of ASCII characters
- All commands are case insensitive.
- No whitespace (including spaces, tabs, or returns) is allowed within a command.
- All commands must have a total length of 256 bytes or fewer, including the terminating ` ` .

### The EBB Command Set 

- A — Analog value get
- AC — Analog Configure
- BL — enter BootLoader
- C — Configure
- CK — Check Input
- CU — Configure User Options
- CS — Clear Step position
- EM — Enable Motors
- ES — E Stop
- HM — Home or Absolute Move
- I — Input
- L3 — Low-level Move with Jerk
- LM — Low-level Move
- LT — Low-level Move, Time Limited
- MR — Memory Read
- MW — Memory Write
- ND — Node count Decrement
- NI — Node count Increment
- O — Output
- PC — Pulse Configure
- PD — Pin Direction
- PG — Pulse Go
- PI — Pin Input
- PO — Pin Output
- QB — Query Button
- QC — Query Current
- QE — Query motor Enables and microstep resolutions
- QG — Query General
- QL — Query Variable
- QM — Query Motors
- QN — Query Node count
- QP — Query Pen
- QR — Query RC Servo power state
- QS — Query Step position
- QT — Query EBB nickname Tag
- QU — Query Utility
- RB — Reboot
- R — Reset
- S2 — General RC Servo Output
- SC — Stepper and servo mode Configure
- SE — Set Engraver
- SL — Set Variable
- SM — Stepper Move
- SN — Set Node count
- SP — Set Pen State
- SR — Set RC Servo power timeout
- ST — Set EBB nickname Tag
- T — Timed Digital/Analog Read
- T3 — Low-level Move with Jerk, Time Limited
- TD — Paired "Dual T3" Low-level Move With Jerk, Time-limited
- TP — Toggle Pen
- TR — Test Rate
- V — Version Query
- XM — Stepper Move, for Mixed-axis Geometries

#### "A" — Analog value get

- Command:`A `
- Response (future mode):`A,Channel:Value,Channel:Value` . . . ` `
- Response (legacy mode; default):`A,Channel:Value,Channel:Value` . . . ` `
- Firmware versions: v2.2.3 and newer
- Execution: Immediate
- Description:

 Query all analog (ADC) input values. 

 When one or more analog channels are enabled (see `AC` command below), the "A" query will cause the EBB to return a list of all enabled channels and their associated 10 bit values. 

 The list of channels and their data will always be in sorted order from least (channel) to greatest. Only enabled channels will be present in the list. 

 The Value returned for each enabled channel will range from 0 (for 0.0 V on the input) to 1023 (for 3.3 V on the input). 

 The channel number and ADC value are both padded to 2 and 4 characters respectively in the A response. 
- Example Return Packet (future mode):`A,00:0713,02:0241,05:0089:09:1004 ` if channels 0, 2, 5 and 9 are enabled. 
- Example Return Packet (legacy mode; default):`A,00:0713,02:0241,05:0089:09:1004 ` if channels 0, 2, 5 and 9 are enabled. 
- NOTE 1: The EBB's analog inputs are only rated for up to 3.3 V. Be careful not to put higher voltages on them (including 5 V) or you may damage the pin. 
- NOTE 2: If you connect an ADC pin to GND (0.0 V) it will likely not read exactly 0. It will be a bit higher than that. (A typical value is 0023.) This is because of the way that the analog input reference voltages are supplied to the microcontroller. 
- Unchanged since firmware v2.2.3. 
- This command is deprecated in v3.0: It will continue to work up until a future firmware version, but it will be removed in that future firmware version. 

#### "AC" — Analog Configure

- Command:`AC,Channel,Enable `
- Response (future mode):`AC `
- Response (legacy mode; default):`OK `
- Firmware versions: v2.2.3 and newer
- Execution: Immediate
- Arguments:

- Channel: An integer in the range of 0 to 15 (inclusive). The analog input channel number that you wish to enable or disable. 
- Enable: A value of either 1 or 0. A value of 1 will enable the channel. A value of 0 will disable the channel.
- Description:

Configure an analog input channel.

 Use this command to turn on or turn off individual analog channels. Once a channel is turned on, it will begin converting analog values to digital values and the results of the conversions will be displayed in the returned value of the "A" Command. See "A" command above. You can turn on and off any of the 16 analog channels individually on this microcontroller. Once a channel is turned off, it will no longer show up in the "A" packet returned value list. 

 The channel numbers correspond to lines ANx on the EBB schematic and on the datasheet of the microcontroller. For example, pin 11 of the PIC, which is labeled RB2 and comes out as the RB2 pin on the servo header, has the text "RB2/AN8/CTEDG1/PMA3/VMO/REFO/RP5" next to it on the CPU symbol. This means that this pin is internally connected to Analog Channel 8. See chapter 21 of the PIC18F46J50 datasheet to read more about the ADC converter. 
- This command is deprecated in v3.0: It will continue to work up until a future firmware version, but it will be removed in that future firmware version. 

#### "BL" — Enter Bootloader

- Command:`BL `
- Response (future mode): No response
- Response (legacy mode; default): No response
- Firmware versions: v1.9.5 and newer (with changes)
- Execution: Immediate
- Description:

Enter bootloader mode.

 This command turns off interrupts and jumps into the bootloader, so that new firmware may be uploaded. This particular method of entering bootloader mode is unique in that no physical button presses are required. Once the EBB receives this command, no response is sent back to the PC. 

 Once in bootloader mode, the EBB will not be able to communicate using the same USB serial port method that the normal firmware commands use. A special bootloader PC application (that uses USB HID to communicate with the bootloader on the EBB) must be run in order to upload new firmware HEX files to the EBB. 

#### "C" — Configure (pin directions)

- Command:`C,PortA_IO,PortB_IO,PortC_IO,PortD_IO,PortE_IO `
- Response (future mode):`C `
- Response (legacy mode; default):`OK `
- Firmware versions: All
- Execution: Immediate
- Arguments:

- PortA_IO: An integer from 0 to 255. Value written to TRISA register.
- PortB_IO: An integer from 0 to 255. Value written to TRISB register.
- PortC_IO: An integer from 0 to 255. Value written to TRISC register.
- PortD_IO: An integer from 0 to 255. Value written to TRISD register.
- PortE_IO: An integer from 0 to 255. Value written to TRISE register.
- Description:

 This command takes five bytes worth of parameters, one for each TRISx register in the processor, and writes those values down into the TRIS registers. There is a TRIS register for each 8-bit wide I/O port on the processor, and it controls each pin's direction (input or output). A 0 in a pin's bit in the TRIS register sets the pin to be an output, and a 1 sets it to be an input. 

 This command is useful if you want to set up the pin directions for each and every pin on the processor at once. If you just one to set one pin at a time, use the `PC` command. 

 This command does not need to be used to configure analog inputs. The `AC` command is used for that. 

#### "CS" — Clear Step position

- Command:`CS `
- Response (future mode):`CS `
- Response (legacy mode; default):`OK `
- Firmware versions: Added in v2.4.3
- Execution: Immediate
- Description:

This command zeros out (i.e. clears) the global motor 1 step position and global motor 2 step position. It also zeros out both step accumulators.

See the `QS` command for a description of the global step positions.

#### "CK" — Check Input

- Command:`CK,pVal_1,pVal_2,pVal_3,pVal_4,pVal_5,pVal_6,pVal_7,pVal_8 `
- Response (future mode):

`CK `

`Param1=` pVal_1` `

`Param2=` pVal_2` `

`Param3=` pVal_3` `

`Param4=` pVal_4` `

`Param5=` pVal_5` `

`Param6=` pVal_6` `

`Param7=` pVal_7` `

`Param8=` pVal_8` `
- Response (legacy mode; default):

` `

`Param1=` pVal_1` `

`Param2=` pVal_2` `

`Param3=` pVal_3` `

`Param4=` pVal_4` `

`Param5=` pVal_5` `

`Param6=` pVal_6` `

`Param7=` pVal_7` `

`Param8=` pVal_8` `

`OK `
- Firmware versions: All
- Execution: Immediate
- Arguments:

- pVal_1 An unsigned one byte integer from 0 to 255.
- pVal_2 A signed one byte integer from -128 to 127.
- pVal_3 An unsigned two byte integer from 0 to 65535.
- pVal_4 A signed two byte integer from -32768 to 32767.
- pVal_5 An unsigned four byte integer from 0 to 4294967295.
- pVal_6 A signed four byte integer from -2147483648 to 2147483647.
- pVal_7 A case sensitive character.
- pVal_8 A case forced upper case character.
- Description:

 This command is used to test out the various parameter parsing routines in the EBB. Each parameter is a different data type. The command simply prints out the values it parsed to allow the developer to confirm that the parsing code is working properly. 

For pVal_7, any type-able character is accepted as input.

For pVal_8, any type-able character is accepted, and converted to upper case before printing.

#### "CU" — Configure User Options

- Command: `CU,Param_Number,Param_Value `
- Response (future mode): `CU `
- Response (legacy mode; default): `OK `
- Firmware versions: All
- Execution: Immediate
- Arguments:

- Param_Number : See below for acceptable values. Specifies what Param_Value means.
- Param_Value : An integer from -32768 to 32767. Acceptable values depend on value of Param_Number
- Description:

 The `CU` command allows for configuring various run time options. The configuration options chosen with this command do not survive a reboot, and they will return to their default values on a reset or boot. 

- Param_Number = 1 : Enable Command Response

 This sub-command enables or disables the `OK` response after the EBB receives and parses a command. Turning off the `OK` response can help speed up the execution of many back to back commands. This sub-command has no effect when Future Syntax Mode is active. 

- If Param_Value = 1, then `OK` response to commands is enabled (default at boot).
- If Param_Value = 0, then `OK` response to commands is disabled.
- Param_Number = 2 : Enable Command Parameter Limit Check

 Turning off the limit checking for the stepper motor motion commands will prevent error messages from being sent back to the PC, which may make processing of the data returned from the EBB easier. It will also slightly speed up the command parsing of these commands. 

- If Param_Value = 0, then stepper motor motion commands (`SM`,`XM`,`HM`,`LM`,`LT`,`T3`,`L3`,) will limit their parameter limit checking. 
- If Param_Value = 1, then stepper motor motion commands will perform all parameter limit checking and return error messages if any parameter limits are exceeded (default at boot). 
- Param_Number = 3 : Enable Empty FIFO Indication

 Using the red LED to indicate an empty FIFO can aid in debugging certain types of problems. When enabled, this option will cause the red LED (labeled "USR" on the board) to light any time there is no motion command in the FIFO. In other words, the LED will light any time there is no motion command waiting to be executed as soon as the current motion command is finished. 

- If Param_Value = 0, then the red LED will not be used to indicate an empty FIFO (default at boot).
- If Param_Value = 1, then the red LED will be used to indicate an empty FIFO.
- Param_Number = 4 : Set new FIFO size

 This command will set the FIFO to a new depth, measured in commands. Param_Value needs to be a decimal number between 1 and the maximum possible FIFO size. At boot, the FIFO will be one command deep. This command allows setting the FIFO depth to be larger, up to the limit returned from the `QU,2` query. Trying to set the FIFO size larger than the maximum possible FIFO size will result in the FIFO size being set to the maximum possible FIFO size. The `QU,3` query can be used to read out the current FIFO size. 

 If there are any currently executing motion commands, or if there are any commands waiting in the FIFO, the execution of this command will block and wait for the FIFO to be completely empty and any executing motion commands to finish before allowing the change to FIFO size. 

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 10 : Enable Future Syntax Mode

 When enabled, future syntax mode changes the response sent after each command or query to have a relatively consistent format. (This syntax is said to be "future syntax" because it is the formatting that will be default in a future firmware version.) 

 When the EBB boots up, future syntax mode is disabled; which we can abbreviate as being in legacy syntax mode. Legacy syntax mode does not have a consistent pattern of responses nor line endings in those responses. However, it is backward compatible with previous EBB firmware versions. 

 Whereas legacy syntax mode often (but not always) uses an `OK ` at the end of a response, future syntax mode will always print out the one or two character command, followed by ` ` if there is no additional data in the response packet. If there is additional data in the response packet, then the response packet will consist of the one or two letter command, followed by a comma, then any response data, then ` `. 

 For example, when future syntax mode is turned on, the response to the `QR` command might be `QR,1 `. For comparison, the response to the `QR` when it is off (in legacy syntax mode) would be `1 OK ` 

 Because part of the response back to the PC is generated before the command is executed, changing the syntax mode with `CU,10` produces a non-standard response. Sending `CU,10,1` when in legacy mode will result in a response of ` `. Sending `CU,10,0` when in future mode will result in a response of `CUOK `. (For future compatibility of your code, you may want to ensure that either response is acceptable.) 

- If Param_Value = 0, Legacy syntax mode: line endings and responses consistent with previous EBB firmware versions will be used (default at boot).
- If Param_Value = 1, Future syntax mode: consistent line endings and responses will be used for all commands and queries.

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 50 : Auto Enable Motors

 The stepper motor drivers are normally enabled any time any stepper motor command is executed. However, there may be times when it is desired to leave one or the other disabled while a stepper motion command is executing. The Auto Enable Motors setting allows you to turn off the automatic enabling of stepper motor drivers. This will then require you to manually enable whichever stepper driver you want using the `EM` command. 

- If Param_Value = 0, then the stepper motor drivers will not be automatically enabled at the beginning of every stepper motion command. 
- If Param_Value = 1, then the stepper motor drivers will be automatically enabled at the beginning of every stepper motion command. (Default at boot) 

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 51 : Limit Switch Mask

 If the Limit Switch Mask is nonzero, the PortB pin states will be checked every 40 μs. For any bit in the mask which is set, if that pin's state matches the corresponding bit state in the Limit Switch Target, then a Limit Switch Stop will be executed immediately. 

 A Limit Switch Stop terminates any currently executing motion command and deletes any motion command in the motion FIFO. New stepper motion commands will be ignored until the condition is cleared. To clear the Limit Switch Stop condition, set the Limit Switch Mask value to zero with `CU,51,0`. The Limit Switch Stop condition can also be cleared by executing any EM command or by resetting (e.g., rebooting) the EBB. 

 If Limit Switch Replies are enabled (`CU,53,1`) then a Limit Switch Stop will also cause the sending of a packet from the EBB. (See the Limit Switch Replies setting below.) 

- Param_Value : Any value from 0 to 255 is allowed. The Param_Value becomes the new Limit Switch Mask value. The default value for the Limit Switch Mask is 0 at reset, thus disabling the Limit Switch feature. 
- Example 1: A limit switch is connected to PortB pin 2 such that it is normally high but the switch closure brings the pin low. Send `CU,52,0` to set the target value of bit 2 to a 0, then `CU,53,1` to enable the Limit Switch Reply. Then, use `CU,51,4` to set the mask value for bit 2, arming the limit switch system. If, at some point, subsequent stepper motion commands were to create motion that closed the limit switch, that would trigger a Limit Switch Stop and send a Limit Switch Reply. Before any further motion can occur, the PC would send a `CU,51,0` command to clear the limit switch condition. 
- Example 2: There are three limit switches on PortB pins 2, 5 and 7. Each is normally low and high once closed. Send `CU,52,164` to set bits 2, 5 and 7 of the Limit Switch Target, and `CU,53,1` to enable the Limit Switch Reply. Then, use `CU,51,164` to set bits 2, 5, and 7 of the Limit Switch Mask, which enables the feature. If any of the three limit switches closes, the Limit Switch Stop would occur and the Limit Switch Reply would be sent. If it is important to know exactly which limit switch was the one that triggered the Limit Switch Stop, examine the response packet from the Limit Switch Reply. 

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 52 : Limit Switch Target

 The Limit Switch Target is used along with the Limit Switch Mask (`CU,51`) to configure the limit switch function. For bits that are set in the limit switch mask, those portB digital input values are compared to the corresponding bits in this Limit Switch Target. If the input value matches the target value, the Limit Switch Stop will be triggered. 

- Param_Value : Any value from 0 to 255 is allowed. The Param_Value becomes the new Limit Switch Target value. The default value for the Limit Switch Target is 0 at reset. 

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 53 : Enable Limit Switch Reply

- If Param_Value = 0, then no Limit Switch Reply packet will be sent when a limit switch condition is triggered (default at boot). 
- If Param_Value = 1, then, when a Limit Switch Stop is triggered, a packet will be sent from the EBB to the PC of the form `Limit switch triggered. PortB=XX\n` where `XX` is the value of the PortB inputs at the moment of the Limit Switch Stop, as two hexadecimal digits. Unlike regular EBB responses, this response is asynchronous, at the moment of the Limit Switch Stop, and not directly in response to a command or query. (The response will be made between replies from command parsing, so as to not interrupt the reply from a command.) 

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 54 : Enable Command Checksums

- If Param_Value = 0, then checksums at the end of commands are not required. (Default at boot). 
- If Param_Value = 1, then checksums at the end of commands are required. 

 Turning on checksums for commands allows the EBB to check that all of the command bytes made it successfully across USB to the EBB. USB has it's own checksums/CRCs and so guarantees proper data delivery at a lower level, but these application level checksums provide a way for the PC to know that the full command string that it created was properly received by the EBB. If checksums have been turned on, and no checksum is provided, an error message will be sent back to the PC and the command will not be executed. If checksums have been turned on and an incorrect checksum is provided, the EBB will return an error message back to the PC which will include the expected checksum and the command will not be executed. 

 To add a checksum to a command, simply add a comma and a one to three digit decimal number (from 0 to 255) at the very end of the command. The checksum should be 0x100 - (sum of all command bytes up to but not including the comma preceding the checksum). This is commonly referred to as the '8-bit checksum 2s compliment'. 

 Enabling checksums does add a small bit of additional processing time to each command, which reduces the maximum number of commands per second that the EBB can accept. 

 The website https://www.scadacore.com/tools/programming-calculators/online-checksum-calculator/ can be used to compute checksums for a command. Take the desired command, paste it into the ASCII Input field, click AnalyzeDataAscii and then look at the CheckSum8 2s Complement field. Take that value (which is in hex) and convert it to decimal to use as the checksum for your command. 

 Example 1: If you want to send the command `SM,1000,1000,1000` with a checksum, you would send `SM,1000,1000,1000,153`. The 153 on the end is the checksum of all of the bytes up to but not including the comma before the checksum. 

 Example 2: If you want to send the command `CU,54,0` (to turn off checksums) with a checksum but you don't know what the checksum should be, you could send an invalid checksum like `CU,54,0,0`. This will result in the response `!8 Err: Checksum incorrect, expected 119`. So you would know that the proper checksum value for this command is 119 and could send `CU,4,0,119`. 

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 60 : Set new power lost threshold

 This command will set a new Power_Lost_Threshold. The Param_Value needs to be a decimal number between 0 and 1023 and is in units of 0.0295V. At boot the Power_Lost_Threshold will be zero. Every 2ms the EBB will compare the voltage at the barrel jack (V+) with Power_Lost_Threshold. If V+ is ever less than Power_Lost_Threshold, then bit 6 in the result of the `QG` command will be set. Setting Power_Lost_Threshold to zero (as it is at boot) effectively disables this feature. If bit 6 of the `QG` result is set, then after the execution of `QG` it will be cleared. The `QU,60` query can be used to read back the current value of Power_Lost_Threshold at any time. After setting a new value of Power_Lost_Threshold with `CU,60` make sure to execute a `QG` query to clear bit 6 in case it was set. For example to set the Power_Lost_Threshold to 12V you would use `CU,60,404`. 

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 61 : Set new Stepper Disable Timeout value

 This command will set the Stepper_Disable_Timeout. The Param_Value needs to be a decimal number between 0 and 65534 and is in units of seconds. At boot the Stepper_Disable_Timeout is zero, which disables this feature. Any time Stepper_Disable_Timeout is not zero the feature is enabled. 

 When enabled, this feature will count down Stepper_Disable_Timeout seconds after the last motion command. When the count reaches zero, it will disable the two stepper motor drivers. This makes the stepper motors freewheel as well as reduces the current draw of the EBB significantly. If a new Stepper_Disable_Timeout value is set while the countdown is already ongoing, the countdown will begin again using the new value. If a new motion command is executed while counting down, the countdown will be stopped and will start back at Stepper_Disable_Timeout when all motion commands are complete. 

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 250 : Enable GPIO ISR Debug pins

This is an internal software debugging and testing command.

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 251 : Enable debug USART end of move values printing

This is an internal software debugging and testing command.

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 252 : Enable debug USART every ISR move values printing

This is an internal software debugging and testing command.

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 253 : Enable debug UART command echo

This is an internal software debugging and testing command.

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 254 : Enable Lock Up Mode

This is an internal software debugging and testing command.

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 255 : Enable command parsing USB debug printing

This is an internal software debugging and testing command.

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 256 : Disable parsed moves from entering FIFO

This is an internal software debugging and testing command.

 This parameter is new for `CU` in EBB firmware v3.0. 
- Param_Number = 257 : Enable RC7 indicator of command parsing

This is an internal software debugging and testing command.

 This parameter is new for `CU` in EBB firmware v3.0. 
- Version History:

`CU,50`, `CU,51`, `CU,52`, `CU,53`, `CU,250` through `CU,257` were added in v3.0.
- Deprecation notice:`CU,1` is deprecated as of EBB firmware v3.0 and will be removed in a future firmware version. `CU,10` will be allowed, but will have no effect in that future firmware version. (What is now "future" syntax will be the default syntax in future firmware version)

#### "EM" — Enable Motors

- Command:`EM,Enable1,Enable2 `
- Response (future mode):`EM `
- Response (legacy mode; default):`OK `
- Firmware versions: All
- Execution: Added to FIFO motion queue
- Arguments:

 For each stepper motor (Enable1 for motor1 and Enable2 for motor2), an integer in the range of 0 through 5, inclusive. An Enable value of 0 will disable that motor (making it freewheel), while a nonzero value will enable that motor. This command is also used to set the step resolution of the stepper motors. 

The allowed values of Enable1 are as follows:

- 0: Disable motor 1 
- 1: Enable motor 1, set global step mode to 1/16 step mode (default step mode upon reset)
- 2: Enable motor 1, set global step mode to 1/8 step mode
- 3: Enable motor 1, set global step mode to 1/4 step mode
- 4: Enable motor 1, set global step mode to 1/2 step mode
- 5: Enable motor 1, set global step mode to full step mode

The allowed values of Enable2 are as follows:

- 0: Disable motor 2
- 1 through 5: Enable motor 2 (at whatever the previously set global step mode is)
- Description:

Enable or disable stepper motors and set step mode.

 Each stepper motor may be independently enabled (energized) or disabled (causing that motor to freewheel). When disabled, the driver will stop sending current to the motor, so the motor will "freewheel" — it will not be actively driven, but instead will present little resistance to being turned by external torques. 

 When enabled, the stepper motor driver actively drives current through the coils, causing the motors to 'lock' (i.e. be very difficult to turn by external torques). 

 Each of the motor movement commands (like SM, XM, and LM) automatically enable both motors before they begin their motion, but do not change the global step mode. 

 The stepper motors may be configured to be in whole, half, quarter, eighth, or sixteenth step modes. When using a motor with a native resolution of 200 steps per revolution, these settings would produce effective stepping resolutions of 200, 400, 800, 1600, and 3200 steps per revolution, respectively. Using fine sub-steps ("microstepping") gives higher resolution at the cost of decreasing step size reproducibility and decreasing maximum step speed. Note that the microstep mode is set for both motors simultaneously, using the parameter value of Enable1. It is not possible to set the step mode separately for each motor. Thus there is just one global step mode, and it is set by the value of Enable1. 

 Because only Enable1 can set the global step mode, Enable2 simply enables or disables axis 2, and can not change the previously set step mode on its own. 

 Note that this version of the command is for current versions of the EBB hardware, v1.2 and newer. (This includes all versions manufactured since September 2010.) 
- Example:`EM,1,0\r` Enable motor 1, set global step mode to 1/16th and disable motor 2 
- Example:`EM,1,0\r` Enable motor 1, set global step mode to 1/16th and disable motor 2 
- Example:`EM,2\r` Set global step mode to 1/8 enable motor 1, and do not change motor 2's enable status. (Enable2 is optional) 
- Example:`EM,2\r` Set global step mode to 1/8 enable motor 1, and do not change motor 2's enable status. (Enable2 is optional) 
- Example:`EM,3,3\r` Set global step mode to 1/4 and enable both motors. 
- Example:`EM,3,3\r` Set global step mode to 1/4 and enable both motors. 
- Example:`EM,0,1\r` Enable motor 2, disable motor 1, and continue to use previously set global step mode 
- Example:`EM,0,1\r` Enable motor 2, disable motor 1, and continue to use previously set global step mode 
- Example:`EM,0,0\r` Disable both motors (both will freewheel) 
- Example:`EM,0,0\r` Disable both motors (both will freewheel) 
- Example:`EM,3,1\r` Enable both motors and set to 1/4 step mode 
- Example:`EM,3,1\r` Enable both motors and set to 1/4 step mode 
- Version History: Unchanged since firmware 2.8.0 

#### "ES" — E Stop

- Command:`ES[,DisableMotors] `
- Response (future mode):`ES,Interrupted `
- Response (legacy mode; default):`Interrupted OK `
- Firmware versions: v2.2.7 and newer (with changes)
- Execution: Immediate 
- Arguments:

- DisableMotors This is an optional parameter with a value of 0 or 1. If it is a 1, then both stepper drivers will be disabled. If it is 0 or not present, then the stepper drivers will be left in this current state. 
- Description:

 Use this query to abort any in-progress stepper motor moves and flush the motion FIFO. It will immediately stop the stepper motors. In addition, if any motion command was currently executing or in the FIFO when the command arrives the Interrupted return value will be a 1. 
- Returned values:

- Interrupted: 0 if no FIFO or in-progress move commands were interrupted, 1 if a motor move command was in progress or in the FIFO 
- Example Return Packet (future mode):`ES,0 ` Indicates that no stepper motion command was executing at the time, and the FIFO was empty. 
- Example Return Packet (legacy mode; default):`0 OK ` Indicates that no stepper motion command was executing at the time, and the FIFO was empty. 
- Example Return Packet (future mode):`ES,1 ` Indicates that a stepper command was interrupted (and/or that the FIFO was not empty). 
- Example Return Packet (legacy mode; default):`1 OK ` Indicates that a stepper command was interrupted (and/or that the FIFO was not empty). 

#### "HM" — Home or Absolute Move

- Command:`HM,StepFrequency[,Position1,Position2] `
- Response (future mode):`HM `
- Response (legacy mode; default):`OK `
- Firmware versions: v2.6.2 and newer (with changes)
- Execution: Added to FIFO motion queue
- Arguments:

- StepFrequency is an unsigned integer in the range from 1 to 25000. It represents the step frequency, in steps per second, representing typical speed during the movement. 
- Position1 and Position2 (optional) are 32 bit signed integers in the range of -2147483648 to 2147483647. If provided, they represents the position, relative to home, that motor1 and motor2 will travel to. If Position1 is provided Position2 must also be provided. 
- Description:

 This command will cause the two stepper motors to move from their current position, as defined by the global step counters, either to Home (0, 0) or to a new position that you specify relative to the Home position. It is worth noting that this is the only EBB motion command for which you can specify an absolute position to move to; all other motion commands are relative to the current position. This command is intended for "utility" moves, to or from a specific point, rather than for smooth or fast motion. 

 The current position at any given moment is stored in the global step counters, and can be read with the `QS` query. This position does not refer to an absolute position in physical space, but rather the location where the motors were enabled. The global step counters are reset to zero whenever the motors are enabled, disabled, or have their microstep size changed (all via the `EM` command). The step counter can also be cleared directly by the `CS` command. 

 The step rate at which the move should happen is specified as a parameter. If no destination position is specified, then the move is towards the Home position (0, 0). 

 The maximum (25000 steps/s) and minimum (0.00001164 steps/s) step speed will not be violated no matter what parameters are used. The `HM` command will limit its step speeds such that they stay within those bounds. 

 The command will wait until all previous motor motion ceases before executing. There is also a further delay, typically about 5 ms, between when the `HM` command begins execution and when its motion actually begins. 

 There is a limitation to Position1 and Position2. When they are each added to the negative of the respective current global positions to compute the number of steps necessary to complete this `HM` move, the sum must not overflow a signed 32 bit number. An overflow like this will generate an error. Note that this situation is very unlikely to occur, as 0x7FFFFFFF steps (the maximum number of steps a signed 32 bit int can represent) will take 23 hours to execute at the highest step rate (25Ks/s). 
- Version History: Available since firmware 2.7.0. In v3.0, the command was updated to allow larger input paramters and slower minimum speeds and will now always travel in a straight line. 

#### "I" — Input (digital)

- Command:`I `
- Response (future mode):`I,PortA,PortB,PortC,PortD,PortE `
- Response (legacy mode; default):`I,PortA,PortB,PortC,PortD,PortE `
- Firmware versions: All
- Execution: Immediate
- Description:

 This query reads every PORTx register (where x is A through E) and prints out each byte-wide register value as a three digit decimal number. This effectively reads the digital values on each and every pin of the processor and prints them out. If you need the value of a particular pin, you can extract it from the value printed for that port by looking at the binary bit within the byte for that pin. For example, if you wanted to read the value of RB4, you would look at the 5th bit (0x10) of the PortB byte in the return packet. 

 For pins that are set as outputs, or are set as analog inputs, or are set as something other than digital inputs, this query will still convert the voltage on the pin to a digital value of 1 or 0 (using the standard voltage thresholds specified in the processor datasheet) and return all of their values. 
- Example:`I `
- Example Return Packet (future mode):`I,128,255,130,000,007 `
- Example Return Packet (legacy mode; default):`I,128,255,130,000,007 `
- This command is deprecated in v3.0: It will continue to work up until a future firmware version, but it will be removed in that future firmware version. 

#### "LM" — Low-level Move, Step-limited

- Command:`LM,Rate1,Steps1,Accel1,Rate2,Steps2,Accel2[,Clear] `
- Response (future mode):`LM `
- Response (legacy mode; default):`OK `
- Firmware versions: v2.7.0 and above
- Execution: Added to FIFO motion queue
- Arguments:

- Rate1 and Rate2 are signed 32 bit integers in the range from -2147483648 to 2147483647. They represent step rates for axis 1 and 2, and are added to each axis step accumulator every 40 μs to determine when steps are taken. The sign of each Rate parameter can determine the initial motor direction. See direction note below. 
- Steps1 and Steps2 are signed 32 bit integers in the range from -2147483648 to 2147483647. Each number gives the movement distance — the total number of steps — for the given axis, axis 1 or axis 2. The sign of each Steps parameter can determine the initial motor direction. See direction note below. 
- Accel1 and Accel2 are signed 32 bit integers in the range from -2147483648 to 2147483647. These values are added to their respective Rate values every 40 μs and control acceleration or deceleration during a move. 
- Clear is an optional integer in the range 0 - 3. If it is 0 then neither accumulator are cleared at the start of the command. If it is 1 then the step accumulator for motor1 is zeroed at the start of the command. If it is 2, then the step accumulator for motor2 is zeroed at the start of the command. If it is 3, then both accumulators are cleared. 
- Direction note:

Normally the sign of the Rate parameters are used to indicate initial motor direction. When Rate signs are used for direction, then Steps parameters should be positive. However, if the sign of Rate is positive, then the sign of the Steps parameters can be used to control initial motor direction instead. Internally, if an axis has a negative Steps and a positive Rate, the EBB code will flip the sign on Rate and Steps as well as Accel to make the math work out. 
- Description:

 Overview: This low-level command causes one or both motors to move for a given number of steps, and allows the option of applying a constant acceleration to one or both motors during their movement. The motion terminates for each axis when the required number of steps have been made, and the command is complete when the both motors have reached their targets. 

 This command, as compared to the similar `LT` command, allows you to specify an exact step position, but is more difficult to use since the moves for the two axes may complete at different times. 

 This is a low-latency command where the input values are parsed and passed directly into motion control FIFO of the EBB. No time is lost doing any math operations or limit checking, so maximum command throughput can be achieved. (See GitHub issue #73 for more information about the motivation for this command.) While individual movement commands may be as short as a single step, there are practical limits to the rate at which commands can be issued, as discussed under Performance. 

 Methods and consequences: Each axis has a separate 32 bit Accumulator to control its timing. When the `LM` command is called, the Accumulator may be initialized to zero or left alone, depending on the value of the Clear argument. The initial value of Rate for each axis is adjusted by subtracting Accel/2 from it. Then, every 40 μs (at a rate of 25 kHz) the following operations are executed for each axis, if the total number of steps to be taken is nonzero: 

1. Update the value Rate = Rate + Accel.
2. If the new (Rate < 0), then "roll it over" with Rate = Rate + 2 31.
3. The value of Rate is added to the Accumulator.
4. If the new Accumulator value is greater than or equal to 2 31 (2147483648 decimal; 0x80000000 hex), then: 

- The motor on that axis moves one step.
- 2 31 is subtracted from the Accumulator for that axis. 
5. Check to see if the total number of steps moved equals Steps. If true, the move is complete for this axis; no further steps will be taken.
6. Check if the move is complete for both axes. If so, exit the LM command.

 A restriction on the parameters is that motion must be possible on at least one axis. That is to say, you must ensure that both Steps is nonzero and that either Rate or Accel are nonzero for at least one axis of motion, or no motion will occur. 

 Because the parameters for each axis determine how long the move will take for that axis, one axis may finish stepping before the other. In extreme cases, one axis will finish moving long before the other, which can lead to (correct but) unintuitive behavior. For example, in an XY movement command both axes could travel same distance yet have axis 1 finish well before axis 2. The apparent motion would be a diagonal XY movement for the first part of the transit time, followed by a straight movement along axis 2. To the eye, that transit appears as a "bent" line, or perhaps as two distinct movement events. 

 Computing values: The value of Rate can be computed from a motor step frequency F, in Hz, as: 

- Rate = 2 31 × 40 μs × F , or
- Rate ≈ 85,899.35 s × F.

 In the case of constant velocity, where Accel is zero, the value of Rate can thus be computed from the number of steps and desired total travel time t, in seconds, as Rate = 2 31 × 40 μs × ( Steps / t ), or Rate ≈ 85,899.35 s × ( Steps / t ). This computation (along with most of the others in the section) should be performed as a floating point operation, or at least with 64 bit precision, since Steps × 2 31 may take up to 63 bits. 

 The Accel value is added to Rate every 40 μs. It can be positive or negative. This is used to cause an axis to accelerate or decelerate during a move. The theoretical final "velocity rate" after T intervals of 40 μs each, starting with initial rate Rate is: 

- Rate Final = Rate + Accel × T

 The value of Accel can be calculated from the initial value Rate, its desired final value Rate Final, and the number T of 40 μs intervals that the movement will take: 

- Accel = ( Rate Final - Rate ) / T

 If an LM command begins with a specified Rate and Accel, as well as a (possibly unknown) initial Accumulator value C 0, then the Accumulator value C T after T intervals of 40 μs each is given by: 

- C T = C 0 + Rate × T + (1/2) Accel × T 2 

 (This formula may look familiar from elementary physics, as it has the form: x(t) = x 0 + v 0 T + (1/2) a T 2.) The number of motor steps traveled along the axis during the command can be found from this by dividing the Accumulator value C T by 2 31 and rounding down the result. Thus the step count after T intervals is given by: 

- Steps = Floor( ( C 0 + Rate × T + (1/2) Accel × T 2 ) / 2 31 ) 

 This is a quadratic equation, and the exact movement time for a given number of steps can be computed by solving for T using the quadratic formula. If you already know the final speed, then the approximate movement time t in seconds can be found by dividing the number of steps by the average step frequency over the move: 

- t ≈ Steps / F AVE = 2 × Steps / ( F 0 + F t )

 Here, F 0 and F t are the initial and final step frequencies F for the move. From this, we can also calculate the approximate move duration T in terms of 40 μs intervals, using Rate = 2 31 × 40 μs × F and t = 40 μs × T: 

- T ≈ 2 31 × Steps / R AVE = 2 32 × Steps / ( Rate + Rate Final )
- Example 1: Suppose that we wanted to start moving an axis at 45 steps/s, and end at 250 steps/s, over a total of 60 steps. By the above formulas, we know that our starting Rate is 3865471, our ending Rate Final is 21474836, and our move time is 60/((45 + 250)/2) = 0.4068 seconds (or T = 10169 intervals). We find Accel from the change in Rate over the number of intervals: (21474836 - 3865470)/10169 = 1732. We then have the following LM command: 

- `LM,3865471,60,1732,0,0,0`

 Notice that we are only using axis 1 in this example. You can of course use both axes at the same time, but you usually need to be careful that the times for each axis match up. 
- Example 2:`LM,33865471,1000,0,0,0,0\r` This example will move axis 1 at a constant speed of 45 steps/s for 1000 steps. Axis 2 does not move. 
- Example 3:`LM,85899346,10,0,17180814,2,0\r` This example will cause a 10 ms long move, where axis 1 takes a step every 1 ms, and axis 2 takes a step every 5 ms. Axis 1 will step for 10 steps, and axis 2 will step for 2 steps, and they will both finish together at the end of the 10 ms. This is a constant-rate move without acceleration or deceleration on either axis. 
- Example 4:`LM,85899346,500,0,85899346,250,0\r` This example will step both axis at a 1 ms/step rate, and axis 1 will step for 500 steps and axis 2 will step for 250 steps. This is usually not what you want in practice; it's usually better if the moves for each axis terminate at the same time. This is a "constant-rate" move without acceleration or deceleration on either axis. 
- Example 5:`LM,17180814,6,0,57266231,20,0\r` This example will create a 30 ms long move, with axis 1 stepping 6 times and axis 2 stepping 20 times. There is no acceleration or deceleration on either axis. 
- Example 6:`LM,42950000,50,13400,0,0,0\r` This example will start with axis 1 stepping at 500 steps/second and end with axis 1 stepping at 800 steps/second. It lasts for a duration of 50 steps. Axis 2 does not move. The move will take 77 ms to complete. 
- Example 7:`LM,17179000,75,-687,8592000,75,687\r` This example will start with axis 1 at 200 steps/second, and axis 2 at 100 steps/second. Over the course of 75 steps each, they will end at a speed of 100 steps/second for axis 1 (that is, decelerating) and 200 steps/second for axis 2. The move will take 500 ms. 
- Version History: Added in firmware v2.7.0. 
- Version History: As of firmware v3.0, using a negative number for either Rate argument to control motion direction is deprecated. It will still work, but this functionality has been replaced by using a negative number to either Step argument. In a future firmware version the ability to use negative Rate arguments will be removed. 

#### "L3" — Low-level Move With Jerk

- Command:`L3,Rate1,Steps1,Accel1,Jerk1,Rate2,Steps2,Accel2,Jerk2[,Clear] `
- Response (future mode):`L3 `
- Response (legacy mode; default):`OK `
- Firmware versions: v3.0 and above
- Execution: Added to FIFO motion queue
- Arguments:

- Rate1 and Rate2 are signed 32 bit integers in the range from -2147483648 to 2147483647. They represent step rates for axis 1 and 2, and are added to each axis step accumulator every 40 μs to determine when steps are taken. The sign of each Rate parameter can determine the initial motor direction. See direction note below. 
- Steps1 and Steps2 are signed 32 bit integers in the range from -2147483648 to 2147483647. Each number gives the movement distance — the total number of steps — for the given axis, axis 1 or axis 2. The sign of each Steps parameter can determine the initial motor direction. See direction note below. 
- Accel1 and Accel2 are signed 32 bit integers in the range from -2147483648 to 2147483647. These values are added to their respective Rate values every 40 μs and control acceleration or deceleration during a move. 
- Jerk1 and Jerk2 are signed 32 bit integers in the range from -2147483648 to 2147483647. These values are added to their respective Accel values every 40 μs and control jerk during a move. 
- Clear is an optional integer in the range 0 - 3. If it is 0 then neither accumulator are cleared at the start of the command. If it is 1 then the step accumulator for motor1 is zeroed at the start of the command. If it is 2, then the step accumulator for motor2 is zeroed at the start of the command. If it is 3, then both accumulators are cleared. 
- Direction note:

Normally the sign of the Rate parameters are used to indicate initial motor direction. When Rate signs are used for direction, then Steps parameters should be positive. However, if the sign of Rate is positive, then the sign of the Steps parameters can be used to control initial motor direction instead. Internally, if an axis has a negative Steps and a positive Rate, the EBB code will flip the sign on Rate, Steps, Accel, and Jerk to make the math work out. 
- Description:

 This command is extremely similar to the `LM` command. In fact, if both Jerk1 and Jerk2 are zero, this command is exactly the `LM` command. The difference is in the addition of the two jerk parameters. 

 Methods and consequences: As with `LM`, each axis has a separate 32 bit Accumulator. The initial value of Rate for each axis is adjusted by subtracting Accel/2 and adding Jerk/6. Then, every 40 μs (at a rate of 25 kHz) the following operations are executed for each axis, if the total number of steps to be taken is nonzero: 

1. Update the value Accel = Accel + Jerk.
2. Update the value Rate = Rate + Accel.
3. If the new (Rate < 0), then "roll it over" with Rate = Rate + 2 31.
4. The value of Rate is added to the Accumulator.
5. If the new Accumulator value is greater than or equal to 2 31, then: 

- The motor on that axis moves one step.
- 2 31 is subtracted from the Accumulator for that axis.
6. Check to see if the total number of steps moved equals Steps. If true, the move is complete for this axis.
7. Check if the move is complete for both axes. If so, exit the L3 command.

 The Accel/2 and Jerk/6 pre-adjustments ensure that the user-provided Rate, Accel, and Jerk values correspond to the initial conditions of the cubic motion profile. All of the formulas from the `LM` command description remain applicable, with the addition of the jerk terms. 
- Example 1: Move axis 1 forward 500 steps with constant jerk, axis 2 stationary, accumulators cleared: 

- `L3,0,500,0,100,0,0,0,0,3`

 Axis 1 starts from rest with zero acceleration and jerk of 100. Motion terminates after 500 steps on axis 1. 
- Example 2: Move both axes with initial velocity and jerk: 

- `L3,80000000,1000,0,50,40000000,600,0,-30`

 Axis 1 moves 1000 steps and axis 2 moves 600 steps, both with initial rates and jerk but zero initial acceleration. Accumulators are not cleared. 
- Version History: Added in firmware v3.0. 
- Version History: As of firmware v3.1.0, Jerk parameters are included in the sign flip when negative Steps is used to control direction. Previously, only Rate, Steps, and Accel were sign-flipped. 

#### "LT" — Low-level Move, Time-limited

- Command:`LT,Intervals,Rate1,Accel1,Rate2,Accel2[,Clear] `
- Response (future mode):`LT `
- Response (legacy mode; default):`OK `
- Firmware versions: v2.7.0 and above
- Execution: Added to FIFO motion queue
- Arguments:

- Intervals is an unsigned 32 bit integer in the range from 1 to 4294967295, which specifies the duration of time, in units of 40 μs intervals, that the command executes for. 
- Rate1 and Rate2 are signed 32 bit integers in the range from -2147483648 to 2147483647. The sign of each Rate parameter controls the direction that the axis should turn initially. The absolute value abs(Rate) of each Rate is added to its axis step Accumulator every 40 μs to determine when steps are taken. 
- Accel1 and Accel2 are signed 32 bit integers in the range from -2147483648 to 2147483647. These values are added to their respective Rate values every 40 μs and control acceleration or deceleration during a move. 
- Clear is an optional integer in the range 0 - 3. If it is 0 then neither accumulator are cleared at the start of the command. If it is 1 then the step accumulator for motor1 is zeroed at the start of the command. If it is 2, then the step accumulator for motor2 is zeroed at the start of the command. If it is 3, then both accumulators are cleared. 
- Description:

 Overview: This low-level command causes one or both motors to move for a given duration of time, and allows the option of applying a constant acceleration to one or both motors during their movement. The motion terminates for each axis when the required number of time intervals has elapsed. 

This command, as compared to the similar `LM` command, makes it much easier to construct motion sequences that smoothly follow one another, but trades off the ability to exactly specify a destination in the process. You may wish to use sequences of LT commands, followed by a `HM` command, in order to both move quickly and end up at a specific location. 

 This is a low-latency command where the input values are parsed and passed directly into motion control FIFO of the EBB. No time is lost doing any math operations or limit checking, so maximum command throughput can be achieved. While individual movement commands may be as short as a single 40 μs time interval, there are practical limits to the rate at which commands can be issued, as discussed under Performance. 

 Methods and consequences: The `LT` function is essentially identical to the `LM` in every aspect of its operation except that it terminates after a set number of intervals rather than after a set number of steps. That is to say, in the sequence of operations executed every 40 μs, when the check is made to see if the move is complete, the time elapsed — not the step count — is checked. 

 With that in mind, all of the formulas from the description of the `LM` command, for computing step rates, acceleration, distance, and time are all still applicable when working with `LT`. 

 Once exception should be noted: Since there is no Step argument in this command to indicate the direction that each motor should turn, the input Rate arguments are given a sign. The sign of Rate indicates only which direction the motor should turn. Only its absolute value | Rate| is input to the routines that calculate and manage the motor step frequency. When using the formulas from the `LM` command description, use the unsigned value | Rate|. 
- Example 1: Suppose that we wanted to start moving an axis at 45 steps/s, and end at 250 steps/s, over a total of 60 steps. Following Example 1 from `LM`, we know that our starting Rate is 3865471, our ending Rate Final is 21474836, and our move time is 60/((45 + 250)/2) = 0.4068 seconds (or T = 10169 intervals). We find Accel from the change in Rate over the number of intervals: (21474836 - 3865470)/10169 = 1732. We then have the following LT command, adding the `,3` value on the end to clear the Accumulator: 

- `LT,10169,3865471,1732,0,0,3`

 Since this command does not explicitly specify the number of steps to be traveled, you may want to carefully check your math, or use tools like `QS` or `HM` command following a move like this. 
- Example 2:`LT,25000,33865471,0,0,0\r` This example will move axis 1 at a constant speed of 45 steps/s for one second (25000 intervals). Axis 2 does not move. 
- Example 3:`LT,12500,17179000,-687,8592000,687\r` This example will start with axis 1 at 200 steps/second, and axis 2 at 100 steps/second. Over the course of 500 ms, they will end at a speed of 100 steps/second for axis 1 (that is, decelerating) and 200 steps/second for axis 2. The move will cover 75 steps on each axis. 
- Version History: Added in v2.7.0. 

#### "MR" — Memory Read

- Command:`MR,Address `
- Response (future mode):`MR,Data `
- Response (legacy mode; default):`MR,Data `
- Firmware versions: All
- Execution: Immediate
- Arguments:

- Address: An integer from 0 to 4095. Represents the address in RAM to read.
- Description:

 This query reads one byte from RAM and prints it out. The Data is always printed as a three digit decimal number. 
- Example:`MR,422\r`

This query would read from memory address 422 and print out its current value.
- Example Return Packet (future mode):`MR,071 `
- Example Return Packet (legacy mode; default):`MR,071 `

#### "MW" — Memory Write

- Command:`MW,Address,Data `
- Response (future mode):`MW `
- Response (legacy mode; default):`OK `
- Firmware versions: All
- Execution: Immediate
- Arguments:

- Address: An integer from 0 to 4095. Represents the address in RAM that Data will be written to.
- Data: An integer from 0 to 255. Represents the byte of data to write to Address.
- Description:

 This command writes one byte to RAM. In order for this command to be useful, you will need to know what addresses in RAM are useful to you. This would normally be available by reading the source code for the EBB firmware and looking at the .map file for a particular version build to see where certain variables are located in RAM 

Writing to areas in RAM that are currently in use by the firmware may result in unplanned crashes.

#### "ND" — Node Count Decrement

- Command:`ND `
- Response (future mode):`ND `
- Response (legacy mode; default):`OK `
- Firmware versions: v1.9.5 and newer
- Execution: Immediate
- Description:

This command decrements the 32 bit Node Counter by 1.

See the `QN` command for a description of the node counter and its operations.
- Version History: Added in v1.9.5
- Deprecation notice:`ND` is deprecated as of EBB firmware v3.0 and will be removed in a future firmware version. It is recommended to use SL/ QL instead.

#### "NI" — Node Count Increment

- Command:`NI `
- Response (future mode):`NI `
- Response (legacy mode; default):`OK `
- Firmware versions: v1.9.5 and newer
- Execution: Immediate
- Description:

This command increments the 32 bit Node Counter by 1.

See the `QN` command for a description of the node counter and its operations.
- Version History: Added in v1.9.5
- Deprecation notice:`NI` is deprecated as of EBB firmware v3.0 and will be removed in a future firmware version. It is recommended to use SL/ QL instead.

#### "O" — Output (digital)

- Command:`O,PortA,[PortB,PortC,PortD,PortE] `
- Response (future mode):`O `
- Response (legacy mode; default):`OK `
- Firmware versions: All
- Execution: Immediate
- Arguments:

- PortA: An integer from 0 to 255. Represents the new value to write to the LATA register.
- PortB: (optional) An integer from 0 to 255. Represents the new value to write to the LATB register.
- PortC: (optional) An integer from 0 to 255. Represents the new value to write to the LATC register.
- PortD: (optional) An integer from 0 to 255. Represents the new value to write to the LATD register.
- PortE: (optional) An integer from 0 to 255. Represents the new value to write to the LATE register.
- Description:

 This command simply takes its arguments and write them to the LATx registers. This allows you to output digital values to any or all of the pins of the microcontroller. The pins must be configured as digital outputs before this command can have an effect on the actual voltage level on a pin. 
- This command is deprecated in v3.0: It will continue to work up until a future firmware version, but it will be removed in that future firmware version. 

#### "PC" — Pulse Configure

- Command:`PC,Length0,Period0[,Length1,Period1[,Length2,Period2[,Length3,Period3]]] `
- Response (future mode):`PC `
- Response (legacy mode; default):`OK `
- Firmware versions: All
- Execution: Immediate
- Arguments:

- Length0: An integer from 0 to 65535. This length represents the number of milliseconds RB0 will go high for. 
- Period0: An integer from Length0 to 65535. Represents the number of milliseconds between rising edges on RB0. 
- Length1, Length2, Length3: (optional) Each is an integer from 0 to 65535, that represents the number of milliseconds RB x will go high for, where the value of x is 1, 2, or 3 
- Period1, Period2, Period3: (optional) Each is integer from RBx_Len to 65535, that represents the number of milliseconds between rising edges on RB x, where the value of x is 1, 2, or 3 
- Description:

 This command sets up the internal parameters for the `PG` command. The parameters come in pairs, and the first number in the pair represents the number of milliseconds that a pin (one of RB0, RB1, RB2 and RB3) goes high for, and the second number represents the number of milliseconds between rising edges for that pin. The first pair, for pin RB0, is required. The other three pairs (for RB1, RB2 and RB3) are optional and any number of them (from zero to three) can be included. Pairs which are not included are simply treated as zeros and that pin is not used for output of pulses. 

 When the `PG,1` command is sent, any pairs from the `PC` command where both values are non-zero and the Rate is greater than the Length will create pulses on that pin. 

 While the pulses are going, new `PC` commands can be sent, updating the pulse durations and repetition rates. 

 This command is only available for pins RB0, RB1, RB2 and RB3. If you wish to leave a pin alone (i.e. not create pulses on it) just set its Length and Period values to zero. 
- Example:`PC,100,150\r` After sending a `PG,1` command, this Length and Period would causes RB0 to go high for 100 milliseconds, then low for 50 milliseconds, then high for 100 milliseconds, etc. 
- Example:`PC,12,123,0,0,2000,10000\r` After sending a `PG,1` command, these parameters would cause pin RB0 to go high for a duration of 12 milliseconds, repeating every 123 milliseconds. Pin RB1 would be untouched. Pin RB2 would go high for 2 seconds every 10 seconds. And pin RB3 would be untouched (because the last pair of Length and Period are omitted and thus treated as 0,0). 
- Example:`PC,1,2,1,2,1,2,1,2\r` After sending a `S2,0,4` (to turn off RC servo output on pin RB1) and `PG,1` (to turn on pulse generation), these parameters would cause all four pins (RB0, RB1, RB2, and RB3) to output square waves with a 50% duty cycle and 500 Hz frequency. 
- Version History: Unchanged since firmware 2.6.6 
- This command is not included in v3.0: Commands PC, PG, T have been marked as "not in use" and tentatively removed in this firmware release. If your application does use one or more of these commands, please contact us and let us know. If we don't hear from at least a couple of users that these are important, we'll go ahead and remove them permanently in a future firmware version. 

#### "PD" — Pin Direction

- Command:`PD,Port,Pin,Direction `
- Response (future mode):`PD `
- Response (legacy mode; default):`OK `
- Firmware versions: All
- Execution: Immediate
- Arguments:

- Port: is one of the following letters: A,B,C,D,E. It specifies which port on the processor is to be used.
- Pin: is an integer in the range from 0 through 7. It specifies the pin to be used.
- Direction: is either 0 (output) or 1 (input) 
- Description:

This command sets one of the processor pins to be an input or an output, depending on the Direction parameter.

 This command is a very low-level I/O command. Higher level commands (like `SM`, `S2`, etc.) will not change the direction of pins that they need after boot, so if this command gets used to change the pin direction, be sure to change it back before expecting the higher level commands that need the pin to work properly. 
- Example:`PD,C,3,0\r` This command would set pin PC3 (or Port C, pin 3) as a digital output. 

#### "PG" — Pulse Go

- Command:`PG,Value `
- Response (future mode):`PG `
- Response (legacy mode; default):`OK `
- Firmware versions: All
- Execution: Immediate
- Arguments:

- Value: is either 0 or 1. A value of 0 will stop the pulses, a value of 1 will start the pulses.
- Description:

 This command turns on (`PG,1`) or turns off (`PG,0`) the Pulse Generation on pin RB0 (and optionally on RB1, and/or RB2 and/or RB3). It uses the parameters from the `PC` command to control the pulse width and repetition rate on each pin. See the `PC` — Pulse Configure command for complete details. 

 This command does not turn off any other commands. So if you want to use the Pulse Generation on pins that already have `S2` RC Servo outputs or other outputs on them, be sure to turn those other outputs off yourself before starting the Pulse Generation, or the two signals will get mixed together and create outputs you do not desire. 
- Example:`PG,1\r` This command would turn on pulse generation as per the parameters specified in the latest `PC` command. 
- Example:`PG,0\r` This command would turn off pulse generation on any pins (RB0, RB1, RB2 or RB3) which have non-zero Length and Period values from the latest `PC` command. 
- This command is not included in v3.0: Commands PC, PG, T have been marked as "not in use" and tentatively removed in this firmware release. If your application does use one or more of these commands, please contact us and let us know. If we don't hear from at least a couple of users that these are important, we'll go ahead and remove them permanently in a future firmware version. 

#### "PI" — Pin Input

- Command:`PI,Port,Pin `
- Response (future mode):`PI,Value `
- Response (legacy mode; default):`PI,Value `
- Firmware versions: All
- Execution: Immediate
- Arguments:

- Port: is one of the following letters: A,B,C,D,E. It specifies which port on the processor is to be used.
- Pin: is an integer in the range from 0 through 7. It specifies the pin to be used.
- Value: is a 0 or 1. It reflects the state of the pin when read as a digital input.
- Description:

 This query reads the given port and pin as a digital input. No matter what direction the pin is set to, or even if the pin is being used as an analog input, the pin can still be read as a digital input. 
- Example:`PI,D,2\r` This query would read pin RD2 (or Port D, pin 2) as a digital input and return the pin's value. 
- Example Return Packet (future mode):`PI,1 `
- Example Return Packet (legacy mode; default):`PI,1 `

#### "PO" — Pin Output

- Command:`PO,Port,Pin,Value `
- Response (future mode):`PO `
- Response (legacy mode; default):`OK `
- Firmware versions: All
- Execution: Immediate
- Arguments:

- Port: is one of the following letters: A,B,C,D,E. It specifies which port on the processor is to be used for the output.
- Pin: is an integer in the range from 0 through 7. It specifies the pin to be used for the output.
- Value: is either 0 or 1. It specifies the logical value to be output on the pin.
- Description:

 This command outputs a digital value of a 0 (0V) or 1 (3.3V) on one of the pins on the processor, as specified by Port and Pin. 

 This command will not change a pin's direction to output first, so you must set the pin's direction to be an output using the `PD` command first if you want anything to come out of the pin. 

 This command is a very low-level I/O command. Many other higher level commands (like `SM`, `S2`, etc.) will over-write the output state of pins that they need. This commands allows you low-level access to every pin on the processor. 
- Example:`PO,C,7,1\r` This command would set the pin RC7 (or Port C, pin 7) to a high value. 

#### "QB" — Query Button

- Command:`QB `
- Response (future mode):`QB,State `
- Response (legacy mode; default):`State OK `
- Firmware versions: v1.9.2 and newer
- Execution: Immediate
- Description:

This query checks whether the PRG button on the EBB has been pressed since the last QB query or not. 

The returned value State is 1 if the PRG button has been pressed since the last QB query, and 0 otherwise.

One of the GPIO input pins, B0, can also be used to initiate a "button press" event. B0 is normally pulled high, but if it is taken low, then that registers as though the PRG button itself was pressed. To ensure that a "button press" is registered, ensure that B0 is pulled low for at least 40 microseconds. This "alt_prg" feature is enabled by default but can be disabled with the `SC` command.
- Version History: Added in v1.9.2
- Deprecation notice:`QB` is deprecated as of EBB firmware v3.0 and will be removed in a future firmware version. It is recommended to use QG instead.

#### "QC" — Query Current

- Command:`QC `
- Response (future mode):`QC,RA0_VOLTAGE,V+_VOLTAGE `
- Response (legacy mode; default):`RA0_VOLTAGE,V+_VOLTAGE OK `
- Firmware versions: v2.2.3 and newer
- Execution: Immediate
- Description:

 This query reads two analog voltages and returns their raw 10 bit values. You can use this to read the current setpoint for the stepper motor, and to read the input power that the board is receiving. 

The two returned values are:

- RA0_VOLTAGE, the voltage on the REF_RA0 net. It is expressed as a zero-padded 4-digit 10 bit number where 0 = 0.0V and 1023 = 3.3V 

 This value yields the voltage level at the REF_RA0 input to the stepper driver chip. This is the control voltage that sets the maximum instantaneous (not average) current that the driver chips allow into the motor coils. 

 The maximum current is given approximately by I_max = RA0_VOLTAGE/1.76. Thus, a voltage of 3 V at REF_RA0 would correspond to a maximum motor current of about 1.7 A. 
- V+_VOLTAGE is the voltage on the V+ net, scaled by a voltage divider. It is expressed as a zero-padded 4-digit 10 bit number where 0 = 0.0V and 1023 = 3.3V 

 This value yields the voltage level at on the EBB's V+ power net, which is the "motor" power coming into the board, as measured after the first input protection diode. 

 The value of V+_VOLTAGE as read on the ADC pin is scaled so that it does not exceed the 3.3 V maximum analog input level for the MCU. The scaling is performed by a voltage divider (comprised of R13 and R18 on the EBB), which gives a scaling factor of (1/11) on EBB boards v2.2 and earlier, and a scaling factor of (1/9.2) on EBB boards v2.3 and newer. As there is tolerance on the resistors, these scaling factors should be considered to be only approximate. 

 If one also wishes to compare the to the voltage read to that at the power input, it is necessary to also account for both the forward voltage across the input diode: the "diode drop" across the input diode is about 0.3 V at the current levels typically encountered. 

 The value of V+_VOLTAGE may be very useful in determining whether or not the EBB is plugged into power. One might also compare the value of this voltage with and without the motors enabled, in order to monitor and detect if the power supply voltage should droop due to load on the motors. 
- Example Return Packet (future mode):`QC,0394,0300 `

This query has returned values of 394 for RA0_VOLTAGE and 300 for V+_VOLTAGE.

 The first returned value, 0394, indicates a voltage of 1.27 V at REF_RA0. This indicates that the maximum motor current is currently set to 0.72 A. 

 The second returned value, 0300, indicates a voltage of 0.96 V at the V+ ADC input. Scaling by 9.2 (for the voltage divider on an EBB v2.3) and adding 0.3 V (for the diode drop), this indicates that the "actual" input voltage is about 9.1 V. 
- Example Return Packet (legacy mode; default):`0394,0300 OK `
- Version History: Unchanged since firmware 2.2.3. 

 Note also that this query only works properly on EBB hardware v1.3 and above. (White EBBs from Evil Mad Scientist are v2.0 or newer, and EBBs from SparkFun are v2.0 and above.) 

#### "QE" — Query motor Enables and microstep resolutions

- Command:`QE `
- Response (future mode):`QE,Motor1_State,Motor2_State `
- Response (legacy mode; default):`Motor1_State,Motor2_State OK `
- Firmware versions: v2.8.0 and newer
- Execution: Immediate
- Description:

 This query reads the current state of the motor enable pins and the microstep resolution pins. It then returns two values which encode the motor enable/disable state and (if enabled) microstep resolution. 

 There is only one value for the microstepping resolution since both motor drivers share the same MS1, MS2 and MS3 lines on the EBB. So the two values returned by this command will either be the same (if both motors are enabled) or one or both of them will be zero. But they will never show that the two motors are both enabled and have different microstep resolutions. 

The two returned values are:

- Motor1_State

- 0: Motor 1 is disabled
- 1: Motor 1 is enabled and is set to full step
- 2: Motor 1 is enabled and is set to 1/2 steps
- 4: Motor 1 is enabled and is set to 1/4 steps
- 8: Motor 1 is enabled and is set to 1/8 steps
- 16: Motor 1 is enabled and is set to 1/16 steps
- Motor2_State

Same as for Motor1_State but for Motor 2. 
- Example Return Packet (future mode):`QE,16,16 `

Both motors are enabled and set to 1/16th microsteps.
- Example Return Packet (legacy mode; default):`16,16 OK `
- Example Return Packet (future mode):`QE,0,4 `

Motor 1 is disabled and motor 2 is enabled and set to 1/4 steps.
- Example Return Packet (legacy mode; default):`0,4 OK `

#### "QG" — Query General

- Command:`QG `
- Response (future mode):`QG,Status Byte `
- Response (legacy mode; default):`Status Byte `
- Firmware versions: v2.6.2 and newer
- Execution: Immediate
- Description:

 This query reads the status of eight bits of information, and returns them as a bit field expressed as a single hexadecimal byte. 

The returned status byte consists of the following status bits:

| Bit | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Decimal Value | 128 | 64 | 32 | 16 | 8 | 4 | 2 | 1 |
| Name | Limit Switch Triggered | Power Lost Flag | PRG | PEN | CMD | MTR1 | MTR2 | FIFO |

Bit 7: Limit Switch Triggered

 This bit is 1 if the limit switch triggered. It will be a 0 if the Limit Switch Trigger has not fired or if the limit switch feature is disabled. If set, executing this query will clear the bit. 

Bit 6: Power Lost Flag

 This bit is 1 if the V+ power input has gone below `Power_Lost_Threshold` since the last time the `QG` query was executed. If set, executing this query will clear the bit. See `CU,60`. 

Bit 5: PRG — PRG Button Pressed

 This bit will be 1 if the PRG button has been pushed since the last `QG` or `QB` query. Otherwise it will be 0. Note that input B0 can be used to trigger a "button push" event; see the description of `QB` for more information. 

Bit 4: PEN — Pen is up

 This bit is 1 when the pen is up, and 0 when the pen is down. The pen status is given by the position of the pen-lift servo output, which can be controlled with the `SP` command and can be read with the `QP` query. Note that this is the commanded state of the pen, and that it does physically take time to lift from or lower to the page. 

Bit 3: CMD — Command Executing

 This bit will be 1 when a command is being executed, and 0 otherwise. The command may be a command that causes motion (like a motor move command) or any other command listed in this document as 'Execution: Added to FIFO motion queue'. 

Bit 2: MTR1 — Motor 1 moving

 This bit is 1 when Motor 1 is in motion and 0 when it is idle. 

Bit 1: MTR2 — Motor 2 moving

 This bit is 1 when Motor 2 is in motion and 0 when it is idle. 

Bit 0: FIFO — FIFO motion queue not empty

 This bit will be 1 when a command is executing and a one or more commands are awaiting execution in the FIFO motion queue. It is 0 otherwise. The CMD bit will always be 1 when the FIFO bit is 1; if the FIFO is not empty, then a command is currently executing. Additional information about the motion queue can be found in the description of the `QM` query. 
- Equivalence to `QM` query:

 Bits 0, 1 2, and 3 are exactly identical to the FIFOStatus, Motor2Status, Motor1Status and CommandStatus result fields (respectively) of the `QM` query. 
- Example Return Packet (future mode):`QG,3E `

 This query return value of `3E`, which corresponds to `0011 1110` in binary, indicates that the limit switch has not been triggered, the power has not gone below the set threshold, the PRG button has been pressed, the pen is down, a command is being executed, Motor 1 and Motor 2 are moving, and the FIFO motion queue is empty. 
- Example Return Packet (legacy mode; default):`3E `

This query returns value of `3E`, which corresponds to `0011 1110` in binary, indicates that the limit switch has not been triggered, the power has not gone below the set threshold, the PRG button has been pressed, the pen is down, a command is being executed, Motor 1 and Motor 2 are moving, and the FIFO motion queue is empty.
- Version History: V3.0: bit 7 now reports if the limit switch trigger has fired. Also with v3.0 bit 6 now reports the power lost flag. If you have PC code which is relying upon the old meanings of these bits (bit 7 was showing the state of the RB5 pin and bit 6 was showing the state of the RB2 pin) it will need to be updated to use v3.0. The meaning of bit 4 has been corrected. Previous documentation versions had the state inverted. 

#### "QL" — Query Variable

- Command:`QL[,VariableIndex] `
- Response (future mode):`QL,VariableValue `
- Response (legacy mode; default):`VariableValue OK `
- Firmware versions: v1.9.2 and newer, v3.0 has added VariableIndex
- Execution: Immediate
- Arguments:

- VariableIndex is an integer between 0 and 31 and is optional. If not provided, a VariableIndex of zero will be assumed.
- Description:

 This query allows retrieval of a temporary VariableValue stored in EBB RAM. Each variable value is an unsigned byte, and up to 32 of theses values can be stored in the 32 possible VariableIndex locations. Set the value of any of the variables with the `SL` command. Because VariableIndex is optional and is assumed to be zero if not supplied, this new version of the `QL` command is backward compatible with the older version before v3.0. The VariableValue in the response is a decimal value from 0 to 255. All 32 values are set to 0 at reset. 
- Example:`QL `
- Example Return Packet (future mode):`QL,4 `
- Example Return Packet (legacy mode; default):`4 OK `
- Example:`QL,21 `
- Example Return Packet (future mode):`QL,242 `
- Example Return Packet (legacy mode; default):`242 OK `
- Version History: Added in v1.9.2
- Version History: V3.0 adds the VariableIndex parameter.

#### "QM" — Query Motors

- Command:`QM `
- Response (future mode):`QM,CommandStatus,Motor1Status,Motor2Status,FIFOStatus `
- Response (legacy mode; default):`QM,CommandStatus,Motor1Status,Motor2Status,FIFOStatus `
- Firmware versions: v2.4.4 and above
- Execution: Immediate
- Description:

 Use this query to see what the EBB is currently doing. It will return the current state of the 'motion system', each motor's current state, and the state of the FIFO. 

- CommandStatus is nonzero if any "motion commands" are presently executing, and zero otherwise.
- Motor1Status is 1 if motor 1 is currently moving, and 0 if it is idle.
- Motor2Status is 1 if motor 2 is currently moving, and 0 if it is idle.
- FIFOStatus is 1 if the FIFO is not empty, and 0 if the FIFO is empty.

 The definition of a "motion command" is any command that has a time associated with it. For example, all `SM` commands. Also, any Command (like `S2`, `SP`, or `TP`) that uses a delay or duration parameter. All of these commands cause the motion processor to perform an action that takes some length of time, which then prevents later motion commands from running until they have finished. 

 It is important to note that with all existing EBB firmware versions, only a very limited number of "motion commands" can be executing or queued simultaneously. By default, with a FIFO size of 1 command, there can only be three motion commands in play at a time. One (the first one) will be actually executing. Another one (the second) will be stored in the FIFO buffer that sits between the USB command processor and the motion engine that executes motion commands. Then the last one (the third) will be stuck in the USB command buffer, waiting for the FIFO to be emptied before it can be processed. Once these three command spots are "filled," the whole USB Command processor will block (i.e. lock up) until there is space in the FIFO and the third motion command can be processed and put into the FIFO. This means that no USB commands can be processed by the EBB once the third motion command gets "stuck" in the USB Command processor. Using the QM query can help prevent this situation by allowing the PC to know when there are no more motion commands to be executed, and so can send the next one on. 

 The same process happens if the FIFO size is increased in size using the `CU,4,x` command. There can be one command that is being executed, some number of commands in the FIFO, and if the FIFO fills up, then one command 'stuck' in USB parsing until space opens up in the FIFO. 
- Version History: Added in v2.4.4
- Deprecation notice:`QM` is deprecated as of EBB firmware v3.0 and will be removed in a future firmware version. It is recommended to use QG instead.

#### "QN" — Query node count

- Command:`QN `
- Response (future mode):`QN,NodeCount `
- Response (legacy mode; default):`NodeCount OK `
- Firmware versions: v1.9.2 and newer
- Execution: Immediate
- Description: Query the value of the Node Counter. 

 This command asks the EBB what the current value of the Node Counter is. The Node Counter is an unsigned 32-bit value that gets incremented or decremented with the `NI` and `ND` commands, or set to a particular value with the `SN` command. The Node Counter can be used to keep track of progress during various operations as needed. 

 The value of the node counter can also be manipulated with the following commands: 

- `SN` — Set Node count
- `NI` — Node count Increment
- `ND` — Node count Decrement
- `CN` — Clear node count [obsolete]
- Example Return Packet (future mode):`QN,1234567890 `
- Example Return Packet (legacy mode; default):`1234567890 ` then `OK `
- Version History: Added in v1.9.2 
- Deprecation notice:`QN` is deprecated as of EBB firmware v3.0 and will be removed in a future firmware version. It is recommended to use SL/ QL instead.

#### "QP" — Query Pen

- Command:`QP `
- Response (future mode):`QP,PenStatus `
- Response (legacy mode; default):`PenStatus OK `
- Firmware versions: v1.9 and newer
- Execution: Immediate
- Description:

 This query reads the current pen state from the EBB. It will return PenStatus of 1 if the pen is up and 0 if the pen is down. If a pen up/down command is pending in the FIFO, it will only report the new state of the pen after the pen move has been started. 
- Example Return Packet (future mode):`QP,1 `
- Example Return Packet (legacy mode; default):`1 OK `
- Version History: Added in v1.9
- Deprecation notice:`QP` is deprecated as of EBB firmware v3.0 and will be removed in a future firmware version. It is recommended to use QG instead.

#### "QR" — Query RC Servo power state

- Command:`QR `
- Response (future mode):`QR,RCServoPowerState `
- Response (legacy mode; default):`RCServoPowerState OK `
- Firmware versions: v2.6.0 and newer
- Execution: Immediate
- Description:

 This query reads the current RC Servo power control state from the EBB. It will return RCServoPowerState of 1 if the RC Servo is receiving power and 0 if it is not. 
- Example Return Packet (future mode):`QR,1 `
- Example Return Packet (legacy mode; default):`1 OK `
- Version History: Added in v2.6.0

#### "QS" — Query Step position

- Command:`QS `
- Response (future mode):`QS,GlobalMotor1StepPosition,GlobalMotor2StepPosition `
- Response (legacy mode; default):`GlobalMotor1StepPosition,GlobalMotor2StepPosition OK `
- Firmware versions: Added in v2.4.3
- Execution: Immediate
- Description:

 This query prints out the current Motor 1 and Motor 2 global step positions. Each of these positions is a 32 bit signed integer, that keeps track of the positions of each axis. The `CS` command can be used to set these positions to zero. 

 Every time a step is taken, the appropriate global step position is incremented or decremented depending on the direction of that step. 

 The global step positions can be be queried even while the motors are stepping, and it will be accurate the instant that the query is executed, but the values will change as soon as the next step is taken. It is normally good practice to wait until stepping motion is complete (you can use the `QM` query to check if the motors have stopped moving) before checking the current positions. 
- Example Return Packet (future mode):`QS,1421,-429 `
- Example Return Packet (legacy mode; default):`1421,-429 OK `
- Version History:

Added in v2.4.3

#### "QT" — Query EBB nickname Tag

- Command:`QT `
- Response (future mode):`QT,Name `
- Response (legacy mode; default):`Name OK `
- Firmware versions: v2.5.4 and newer
- Execution: Immediate
- Description:

This query gets the EBB's "nickname", which is set with the `ST` command. It simply prints out the current value of the EBB's nickname. If a nickname has not yet been set, then it will print out an empty line before sending the `OK`. The name field can be anywhere from 0 to 16 bytes in length. 
- Example Return Packet (future mode): If the EBB's nickname has been set to "East EBB" then the output of this command would be: `QT,East EBB `
- Example Return Packet (legacy mode; default): If the EBB's nickname has been set to "East EBB" then the output of this query would be: `East EBB OK `
- Version History: Added in v2.5.4

#### "QU" — Query Utility

- Command: `QU,Param_Number `
- Response (future mode): `QU,Return_Value `
- Response (legacy mode; default): `QU,Return_Value OK `
- Firmware versions: v3.0 and above
- Execution: Immediate
- Arguments:

- Param_Number : See below for acceptable values. Specifies what Return_Value means.
- Description:

 The `QU` query returns one of several values based on Param_Number. It is used to retrieve miscellaneous internal values from the firmware. Rather than creating a new query for each value, `QU` is a single query to retrieve any of the following values: 

- Param_Number = 1 : Read out captured PortB pin states at last limit switch trigger

Return_Value will be a two digit hexadecimal number from 00 to FF. It represents the state of all PortB pins at the exact time that the last limit switch trigger happened. 
- Param_Number = 2 : Read out maximum supported FIFO length

 Return_Value will be a one to three digit decimal number from 0 to 255. It represents the maximum possible size of the motion FIFO in commands. Before using `CU,4,New_FIFO_Size` to set the FIFO size, be sure to use this query to find out the maximum possible size for the FIFO for this version of firmware. 
- Param_Number = 3 : Read out current FIFO length

 Return_Value will be a one to three digit decimal number from 0 to 255. It represents the current size of the motion FIFO in commands. On boot it starts out at 1. All firmware versions prior to v3.0 had a fixed FIFO size of 1. Starting with v3.0 the FIFO size starts out at 1 but can be increased using the `CU,4,New_FIFO_Size` command. Increasing the FIFO size will allow for shorter commands and less chance of FIFO underrun. 
- Param_Number = 4 : Read out software stack high water value

 Every millisecond the EBB samples the software stack pointer. It keeps track of the highest value seen. This is called the stack high water value. This query will return that stack high water value in Return_Value as a three digit hexadecimal number. In v3.0 of the firmware the stack starts at 0xE00 and grows up, so if Return_Value is E71, then the maximum stack pointer value seen indicates that 0x71 bytes of stack were used at that point. The stack overflows if it goes over 0xEBF. 
- Param_Number = 5 : Read out software stack high water value and reset it to zero

 This query is identical to `QU,4` except that it also resets the stack high water value to zero. 
- Param_Number = 6 : Read out number of commands currently waiting in the FIFO

 This query returns the instantaneous number of waiting commands in the FIFO as a two digit decimal number. 
- Param_Number = 60 : Read out Power_Lost_Threshold

 This query will print out the current value of Power_Lost_Threshold as a one to four digit decimal number. 
- Param_Number = 61 : Read out Stepper_Disable_Timeout

 This query will print out the current value of Stepper_Disable_Timeout as a one to five digit decimal number. Note that this is not the current countdown value, but rather the 'starting point' value that was set with the `CU,61` command. 
- Param_Number = 200 : Read out current value of both axis accumulators

 This query will print out the current value of acc_union[0] and acc_union[1] as 32 bit unsigned decimal numbers. This is really only useful for software verification testing. 

#### "RB" — ReBoot

- Command:`RB `
- Response (future mode):``
- Response (legacy mode; default):``
- Firmware versions: v2.5.4 and newer
- Execution: Immediate
- Description:

 This command causes the EBB to drop off the USB, then completely reboot as if just plugged in. Useful after a name change with the `ST` command. There is no output after the command executes. 
- Version History: Added in v2.5.4 

#### "R" — Reset

- Command:`R `
- Response (future mode):`R `
- Response (legacy mode; default):`OK `
- Firmware versions: All
- Execution: Immediate
- Description:

 This command re-initializes the the internal state of the EBB to the default power on state. This includes setting all I/O pins in their power on states, stopping any ongoing timers or servo outputs, etc. It does NOT do a complete reset of the EBB - this command does not cause the EBB to drop off the USB and come back, it does not re-initialize the processor's internal register, etc. It is simply a high level EBB-application reset. If you want to completely reset the board, use the `RB` command. 
- Example:`R `
- Example Return Packet (future mode):`R `
- Example Return Packet (legacy mode; default):`OK `

#### "S2" — General RC Servo Output

- Command:`S2,Position,Output_Pin[,Rate[,Delay]] `
- Command:` S2,0 `
- Response (future mode):`S2 `
- Response (legacy mode; default):`OK `
- Firmware versions: v2.2.0 and later
- Execution: Added to FIFO motion queue (with one exception; see below)
- Arguments:

- Position, a number in the range 0 to 65535. 

The "on time" of the signal, in units of 1/12,000,000th of a second (about 83.3 ns).
- Output_Pin, a number in the range 0 to 24. 

The physical RPx pin number to use for generating the servo pulses. 
- Rate (optional), a number in the range 0 to 65535. 

The rate at which to change to the new setting.
- Delay (optional), a number in the range 0 to 65535. 

Delay before next command, milliseconds.
- Description:

 This command allows you to control the RC servo output system on the EBB, to configure generic RC servo outputs. 

 Servo channels and time slices: Including the pen-lift servo, there are (by default) 8 software-defined RC servo 'channels', which have no physical meaning other than we can output up to 8 separate signals at once. These channels are internally assigned as you use the S2 command to create additional servo outputs, up to a maximum of 8 (this maximum can be changed with the SC,8,X command). 

 Many I/O pins on the MCU have RPx numbers (please refer to the schematic), and you can output RC servo pulses on up to 8 of these RPx pins at once. 

 The RC servo system will cycle through each of the 8 channels. Each gets a 3 ms "slice" of time. Each channel is repeated every 24 ms. 

 If a given servo output is enabled, then at the beginning of its 3 ms time slot, its RPx pin is set high. Then, Position time later, the RPx pin is set low. This time is controlled by hardware (the ECCP2 in the CPU) so there is very little jitter in the pulse durations. Position is in units of 1/12,000,000 of a second, so 32000 for Position would be about 2.666 ms. A value of 0 for the Position parameter will disable servo output on the given RPn pin, and that internal servo channel will be deallocated. If the Position value is greater than the amount of time allocated for each channel (by default, 3 ms) then the smaller of the two values will be used to generate the pulse. 

 The number of available channels at boot is 8. This can be changed with the SC,8 command. The S2 RC servo output command cycles from channel 1 through channel Maximum_S2_Channels (normally 8), outputting any enabled channel's pulse from 0 ms to 3 ms. For a given channel, the repetition rate is determined by Maximum_S2_Channels * S2_Channel_Duration_MS which is normally 8 * 3 or 24 ms. Thus, each channel's output pulse will be repeated every 24 ms. However, if you change the Maximum_S2_Channels you will change the repetition rate of the pulses. The S2_Channel_Duration_MS parameter can also be adjusted with the RC,9 command. 

 Slew rate: The optional Rate argument is used to control how quickly the output changes from the current pulse width (servo position) to the new pulse width. If Rate is zero, then the move is made on the next PWM cycle (i.e. the next time the pin is pulsed). If Rate is nonzero, then the value of Rate is added to (or subtracted from) the current pulse width each time the pulse is generated until the new target is reached. This means that the units of Rate are 1/12,000,000th of a second per Maximum_S2_Channels * S2_Channel_Duration_MS or 1/12,000,000th of a second per 24 ms. The slew rate is completely independent of the Delay. 

 Delay: The Delay argument gives the number of milliseconds to delay the start of the next command in the motion queue. This is an optional argument that defaults to 0, giving no added delay, thus allowing the next motion command to begin immediately after the S2 command has started. 

 Motion Queue: In all cases but one, S2 commands are added to the motion queue, even if their Delay parameters are 0. This means that they will always execute in their correct place in the stream of SM, TP, etc. commands. (The special command `S2,0,Output_Pin ` disables the servo output for Output_Pin immediately and is not added to the queue.) 

 Collisions with SP and TP: The normal pen up/down servo control (SP and TP) commands internally use the S2 command to manage their actions through one of the software-defined channels. If desired, you can use the S2 command to disable this channel, for example if you need access to all four channels. 

 Turn-on condition: Note that the S2 command will always make Output_Pin an output before it starts outputting pulses to that pin. 

 Disabling an S2 servo output: A special command, `S2,0,Output_Pin `, will turn off the RC servo output for Output_Pin. This special command is executed immediately; unlike regular S2 commands, it is NOT added to the FIFO motion queue. 
- RPx vs pin number (and label on the board) table: 

| RPx | RP0 | RP1 | RP2 | RP3 | RP4 | RP5 | RP6 | RP7 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Pin | REF_RA0 | RA1 | RA5 | RB0 | RB1 | RB2 | RB3 | RB4 |
| Label | | | | B0 | B1 | B2 | B3 | B4 |

| RPx | RP8 | RP9 | RP10 | RP11 | RP13 | RP17 | RP18 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Pin | RB5 | RB6 | RB7 | RC0 | RC2 | RC6 | RC7 |
| Label | B5 | B6 | B7 | | | | |
- Example:`S2,24000,6\r` Use RP6 as a RC servo output, and set its on-time to 2 ms. 
- Example:`S2,0,5\r` Turn off the output on RP5 (which is pin RB2) so it stops sending any pulses. 
- Example:`S2,10000,5,0,100\r` Send a 0.83 ms pulse out pin RB2 immediately, and force a pause of 100 ms before the next motion command can start. 
- Example:`S2,27500,5,50,10\r` Start the pulse on RB2 moving from wherever it is at now towards 2.28 ms at a rate of 0.173 ms/S, with a 10 ms delay before the next motion command can begin. 
- Version History: Added in firmware v2.2.0 
- Version History: Maximum RC servo channel count reduced from 24 to 8 in v3.0. 

#### "SC" — Stepper and Servo Mode Configure

Command: `SC,Value1,Value2 `

Response (future mode): `SC `

Response (legacy mode; default): `OK `

- Value1 is an integer in the range from 0 to 255, which specifies the parameter that you are adjusting.
- Value2 is an integer in the range from 0 to 65535. It specifies the value of the parameter given by Value1.
- See the list of these parameters (Value1) and allowed values (Value2), below.

 This command allows you to configure the motor control modes that the EBB uses, including parameters of the servo or solenoid motor used for raising and lowering the pen, and how the stepper motor driver signals are directed. 

The set of parameters and their allowed values is as follows:

- `SC,1,Value2` Pen lift mechanism. Value2 may be 0, 1 or 2. Early EggBot models used a small solenoid, driven from an output signal on pin RB4. 

- `SC,1,0` Enable only the solenoid output (RB4) for pen up/down movement.
- `SC,1,1` Enable only the RC servo output (RB1) for pen up/down movement.
- `SC,1,2` Enable both the solenoid (RB4) and RC servo (RB1) outputs for pen up/down movement (default)
- `SC,2,Value2` Stepper signal control. Value2 may be 0, 1 or 2. 

- `SC,2,0` Use microcontroller to control on-board stepper driver chips (default)
- `SC,2,1` Disconnect microcontroller from the on-board stepper motor drivers and drive external step/direction motor drivers instead. In this mode, you can use the microcontroller to control external step/direction drivers based on the following pin assignments: 

- ENABLE1: RD1
- ENABLE2: RA1
- STEP1: RC6
- DIR1: RC2
- STEP2: RA5
- DIR2: RA2

 Note also that in this mode, you can externally drive the step/direction/enable lines of the on board stepper motor drivers from the pins of J4 and J5. (Please refer to the schematic for where these pins are broken out.) 
- `SC,2,2` Disconnect microcontroller from both the built-in motor drivers and external pins. All step/dir/enable pins on the PIC are set to inputs. This allows you to control the on-board stepper motor driver chips externally with your own step/dir/enable signals. Use the pins listed in the schematic from J5 and J4. 
- `SC,4,Servo_Min` Set the minimum value for the RC servo output position. Servo_Min may be in the range 1 to 65535, in units of 83.3 ns intervals. This sets the "Pen Up" position. Default: 12000 (1.0 ms) on reset. 
- `SC,5,Servo_Max` Set the maximum value for the RC servo output position. Servo_Max may be in the range 1 to 65535, in units of 83.3 ns intervals. This sets the "Pen Down" position. Default: 16000 (1.33 ms) on reset. If the `SP,3` command is sent to the EBB, this Servo_Max value will be set equal to the Servo_Min value. 
- `SC,8,Maximum_S2_Channels` Sets the number of RC servo PWM channels, each of S2_Channel_Duration_MS before cycling back to channel 1 for S2 command. Values from 1 to 8 are valid for Maximum_S2_Channels. Default: 8 on reset. 
- `SC,9,S2_Channel_Duration_MS` Set the number of milliseconds before firing the next enabled channel for the S2 command. Values from 1 to 6 are valid for S2_Channel_Duration_MS. Default: 3 ms on reset. 
- `SC,10,Servo_Rate` Set rate of change of the servo position, for both raising and lowering movements. Same units as Rate parameter in `S2` command. 
- `SC,11,Servo_Rate_Up` Set the rate of change of the servo when going up. Same units as Rate parameter in `S2` command. 
- `SC,12,Servo_Rate_Down` Set the rate of change of the servo when going down. Same units as Rate parameter in `S2` command. 
- `SC,13,Use_Alt_Prg` - turns on (1) or off (0) alternate pause button function on RB0. On by default. For EBB v1.1 boards, it uses RB2 instead. See the description of `QB` for more information. 

Example: `SC,4,8000\r` Set the pen-up position to give a servo output of 8000, about 0.66 ms.

Example: `SC,1,1\r` Enable only the RC servo for pen lift; disable solenoid control output.

 Version History: Maximum_S2_Channels maximum value changed from 24 to 8 in version 3.0. 

#### "SE" — Set Engraver

- Command:`SE,State[,Power[,Use_Motion_Queue]] `
- Response (future mode):`SE `
- Response (legacy mode; default):`OK `
- Firmware versions: v2.1.0 and newer (with changes) 
- Execution: Added to FIFO motion queue
- Arguments:

- State may be either 0 to disable or 1 to enable the engraver output.
- Power is an optional argument, with allowed values of integers in the range 0 to 1023.
- Use_Motion_Queue is an optional argument, with allowed values of 0 (immediate) or 1 (use motion queue).
- Description:

 This command is used to enable and disable the engraver PWM output on RB3 (called B3 on the board), and also set its output power. Use SE,0 to disable this feature. 

 The Power argument represents the power (duty cycle of the PWM signal), where 0 is always off and 1023 is always on. If this optional argument is not included, then the power will be set at 512 (50%) duty cycle. 

 If the Use_Motion_Queue parameter has the value of 1, then this SE command will be added to the motion queue just like SM and SP commands, and thus will be executed when the previous motion commands have finished. Note that if you need to use this argument, the Power argument is not optional. If Use_Motion_Queue has value 0 (or if it is omitted) the command is executed immediately, and is not added to the queue. 
- Example:`SE,1,1023\r` Turns on the engraver output with maximum power
- Example:`SE,0\r` Turns off the engraver output
- Example:`SE,0,0,1\r` Adds a command to the motion queue, that (when executed) turns off the engraver output.
- Version History: Unchanged since firmware v2.4.1

#### "SL" — Set Variable

- Command:`SL,VariableValue[,VariableIndex] `
- Response (future mode):`SL `
- Response (legacy mode; default):`OK `
- Firmware versions: v1.9.2 and newer, v3.0 has added VariableIndex
- Execution: Immediate
- Arguments:

- VariableValue is an integer between 0 and 255 and is required.
- VariableIndex is an integer between 0 and 31 and is optional. If not provided, a VariableIndex of zero will be assumed.
- Description:

 This command allows storage of temporary values in the EBB RAM. Each variable value is an unsigned byte, and up to 32 of theses values can be stored in the 32 possible VariableIndex locations. The values can be read out by using the `QL[,VariableIndex]` query. Because VariableIndex is optional and is assumed to be zero if not supplied, this new version of the `SL` command is backward compatible with the older version before v3.0. The values are not retained across EBB reboots or resets; they are all cleared to 0 at reset. 
- Example:`SL,4\r` Sets the value of variable zero to the value of 4.
- Example:`SL,125,19\r` Sets the value of variable 19 to the value of 125.
- Version History: Added in v1.9.2
- Version History: In v3.0 the optional VariableIndex parameter was added.

#### "SM" — Stepper Move

- Command:`SM,Duration,AxisSteps1[,AxisSteps2[,Clear]] `
- Response (future mode):`SM `
- Response (legacy mode; default):`OK `
- Firmware versions: All (with changes)
- Execution: Added to FIFO motion queue
- Arguments:

- Duration is an unsigned 32 bit integer in the range from 1 to 4294967295, which specifies the duration of time, in units of milliseconds, that the command executes for. 
- AxisSteps1 and AxisSteps2 are signed 32 bit integers in the range from -2147483648 to 2147483647, giving movement distance in steps. 
- Clear is an optional integer in the range 0 to 3. A value of 0 (or if not provided) leaves both accumulators unchanged. A value of 1 clears the axis 1 step accumulator to zero before the move begins. A value of 2 clears the axis 2 step accumulator. A value of 3 clears both accumulators. 
- Description:

 Use this command to make the motors draw a straight line at constant velocity, or to add a delay to the motion queue. 

 If both AxisSteps1 and AxisSteps2 are zero, then a delay of Duration ms is executed. AxisSteps2 is an optional value, and if it is not included in the command, zero steps are assumed for axis 2. If Clear is used, then AxisSteps2 is required. 

 The sign of AxisSteps1 and AxisSteps2 represent the direction each motor should turn. 

 The minimum speed at which the EBB can generate steps for each motor is 0.00001164 steps/second. The maximum speed is 25,000 steps/second. If the SM command finds that the step rate for either axis falls outside the allowed range, it will return an error and the move will not execute. (If limit checks have been disabled with `CU,1,0`, the rate will be silently clamped to the nearest limit instead.) 

 While individual movement commands may be as short as a single step, there are practical limits to the rate at which commands can be issued, as discussed under Performance. 

 If the command is used as a delay, Duration is capped at 100000 ms. 

 Note that internally the EBB generates an Interrupt Service Routine (ISR) at the 25 kHz rate. Each time the ISR fires, the EBB determines if a step needs to be taken for a given axis or not. The practical result of this is that all steps will be 'quantized' to the 25 kHz (40 μs) time intervals, and thus as the step rate gets close to 25 kHz the 'correct' time between steps will not be generated, but instead each step will land on a 40 μs tick in time. In almost all cases normally used by the EBB, this doesn't make any difference because the overall proper length for the entire move will be correct. 

 Note that internally, Duration is converted to a 32-bit floating point value during rate calculation. Floating point values can exactly represent integers only up to 16,777,216 (approximately 4 hours 39 minutes). For Duration values above this threshold, small rounding errors may occur in the computed step rate. In practice, this is unlikely to matter for typical use cases. 

A value of 0 for Duration is invalid and will be rejected.

If both AxisStep1 and AxisStep2 are zero then a Duration value above 100000 will be capped at 100000.
- Example:`SM,1000,250,-766\r` Move axis 1 by 250 steps and axis2 by -766 steps, in 1000 ms of duration. 
- Version History: Parameter values expanded to 32 bits and minimum speed lowered in v3.0. 

#### "SN" — Set node count 

- Command:`SN,Value `
- Response (future mode):`SN `
- Response (legacy mode; default):`OK `
- Firmware versions: v1.9.5 and newer
- Execution: Immediate
- Arguments:

- Value is an unsigned 32-bit integer.
- Description:

This command sets the Node Counter to Value.

See the `QN` command for a description of the node counter and its operations.
- Example:`SN,123456789\r` Set node counter to 123456789.
- Version History: Added in v1.9.5

#### "SP" — Set Pen State 

- Command:`SP,Value[,Duration[,PortB_Pin]] `
- Response (future mode):`SP `
- Response (legacy mode; default):`OK `
- Firmware versions: All (with changes)
- Execution: Added to FIFO motion queue for some parameter values, not added to FIFO motion queue for others
- Arguments:

- Value is either 0, 1, 2 or 3.
- Duration (optional) is an integer from 1 to 65535, which gives a delay in milliseconds.
- PortB_Pin (optional) is an integer from 0 through 7.
- Description:

This command instructs the pen to go up or down.

- When a Value of 0 is used, a servo move will be added to the FIFO motion queue which will move the servo to the Servo_Max position (as set by the `SC,5` command below, which is normally the pen-down position).
- When a Value of 1 is used, a servo move will be added to the FIFO motion queue which will move the servo to the Servo_Min position (as set by the `SC,4` command below, which is normally the pen-up position).
- When a Value of 2 is used, the servo will be immediately start a move to the Servo_Min position (as set by the `SC,4` command), bypassing the FIFO motion queue. The Duration parameter is ignored if present.
- When a Value of 3 is used, the servo will be immediately start a move to the Servo_Min position (as set by the `SC,4` command), bypassing the FIFO motion queue. The value of Servo_Max will also be set equal to Servo_Min, and any servo commands currently in the FIFO motion queue will have their target positions set to Servo_Min. This not only immediately begins lifting the pen off the paper, but it also prevents any queued servo moves from lowering the pen back down onto the paper. The Duration parameter is ignored if present.

 Note that conventionally, we have used the Servo_Min (`SC,4`) value as the 'Pen up position', and the Servo_Max (`SC,5`) value as the 'Pen down position'. 

 The Duration argument is in milliseconds. It represents the total length of time between when the pen move is started, and when the next command will be executed. Note that this is not related to how fast the pen moves, which is set with the `SC` command. Rather, it is an intentional delay of a given Duration, to force the EBB not to execute the next command (often an `SM`) for some length of time, which allows the pen move to complete and possibly some extra settling time before moving the other motors. 

If no Duration argument is specified, a value of 0 milliseconds is used internally.

 The optional PortB_Pin argument allows one to specify which portB pin of the MCU the output will use. If none is specified, pin 1 (the default) will be used. 

 Default positions: The default position for the RC servo output (RB1) on reset is the 'Pen up position' (Servo_Min), and at boot Servo_Min is set to 12000 which results in a pulse width of 1.0 ms on boot. Servo_Max is set to 16000 on boot, so the down position will be 1.33 ms unless changed with the "SC,5" Command. 

 Digital outputs: On older EBB hardware versions 1.1, 1.2 and 1.3, this command will make the solenoid output turn on and off. On all EBB versions it will make the RC servo output on RB1 move to the up or down position. Also, by default, it will turn on RB4 or turn off RB4 as a simple digital output, so that you could use this to trigger a laser for example. 
- Example:`SP,1 ` Move pen-lift servo motor to servo_min position. 
- Version History: Added in firmware 2.2.4 
- Version History: Value parameter values of 2 and 3 added in version 3.0.1. 

#### "SR" — Set RC Servo power timeout value

- Command:`SR,Value[,State] `
- Response (future mode):`SR `
- Response (legacy mode; default):`OK `
- Firmware versions: v2.6.0 and above
- Execution: Immediate
- Arguments:

- Value is a decimal unsigned long integer (32-bit) representing the number of milliseconds to wait after the last servo move before shutting off power to the RC Servo (RB1).
- State is value of either 0 or 1, and is optional. It represents an immediate new state for the servo power (1 = on, 0 = off).
- Description:

This command sets a new RC Servo power timeout value and optionally a new immediate power state.

The Value argument is in milliseconds.

If Value is 0, then the auto-poweroff feature is disabled and the power will not be turned off to the RC servo once applied.

On boot, the EBB will use a default value of 60 seconds. This means that 60 seconds after the last servo motion command, the RC servo power will be turned off.

On boot, the power to the RC Servo (on pin RB1) will be off.

Whenever any command that moves the RC Servo is received, power will also be turned on to the RC Servo connector (RB1), and the RC Servo countdown timer will be started. When the timer reaches 0, the power to the RC servo connector will be shut off.

Only EBB boards v2.5 and above have the necessary power switch hardware. On other versions of the EBB hardware, the power to the servo is always on.

Pin RA3 of the MCU is used to control the RC Servo power. So from software version 2.6.0 and above, this pin is now dedicated to RC Servo power control and can't be easily used for other things.
- Example:`SR,60000,1 ` Set new RC servo power timeout value to 1 minute and turn power to the servo on. 
- Version History: Unchanged since firmware v2.6.5 

#### "ST" — Set EBB nickname Tag

- Command:`ST,NewNameString `
- Response (future mode):`ST `
- Response (legacy mode; default):`OK `
- Firmware versions: v2.5.5 and newer
- Execution: Immediate
- Arguments:

- NewNameString: A string of ASCII characters from 0 to 16 characters in length.
- Description:

This command sets the EBB's "nickname". This is an arbitrary, user settable string, which is stored in flash memory across reboots.

 After setting the EBBs nickname and rebooting, the EBB's USB Device Name will have the nickname appended at the end, after a comma. So if no name is set the Device Name will be "EiBotBoard,". But if the nickname is set to "East EBB", then the Device Name will be "EiBotBoard,East EBB". (The exact device name that appears to your computer is platform dependent.) The nickname will also appear as the USB device's "serial number." Note that the change may not be recognized by your computer until after you reboot the EBB. See the `RB` command. 

 The nickname string can be any combination of ASCII characters, including an empty string which will clear the EBB's nickname. For best compatibility, use a nickname that is 3-16 characters in length, without apostrophes or quotation marks (single or double quotes) within the name. 

 Since calling this command requires a change to a particular flash memory cell-- which can only be changed a finite number of times -- it is best practice to avoid any use that involves automated, repeated changes to the nickname tag. 

Use the `QT` command to retrieve the nickname at any time.
- Version History: Unchanged since firmware v2.5.5

#### "T" — Timed Analog/Digital Query

- Command:`T,Duration,Mode `
- Response (future mode):`T `
- Response (legacy mode; default):`OK `
- Firmware versions: All
- Execution: Immediate
- Arguments:

- Duration is from 1 to 65535 and represents the delay, in milliseconds, between reads for a given mode.
- Mode is 0 for digital or 1 for analog.
- Description:

 This query turns on (or off) the timed digital (I packet) or analog (A packet) queries of pins. Using the T query you can set up a repeated query of input pins, and the generation of an I or A packet back to the PC. Each of the two modes (analog/digital) is independent of the other and can have a different duration time. 

 For example, to turn the digital queries of all pins on, with a time of 250 ms between queries, use `T,250,0`. Then, every 250 ms, the EBB will query all of the pins, and send an I response packet to the PC. This I response packet is exactly the same as the response to an `I` query, and simply contains the binary values of each pin of each port. To turn on the analog queries of any enabled analog inputs every 400 ms, use `T,400,1`. This will cause the EBB to query all enabled analog inputs every 400 ms and send back an A packet (exactly the same as the reply to the `A` query) repeatedly. Note that while digital mode will query every pin, analog mode will only query (and report) the pins that are current configured as analog inputs. Pins do not have to be set to be digital inputs to be queried - no matter what the pin is set to, the `I` response packet will query the pin's digital state. 

 To turn off a mode, use 0 for the duration parameter. Thus `T,0,0` will turn off digital mode, and `T,0,1` will turn off analog mode. 

 The EBB is actually sampling the digital input pins at an extremely precise time interval of whatever you sent in the T query. The values of the pins are stored in a buffer, and then packet responses are generated whenever there is 'free time' on the USB back to the PC. So you can count the I packet responses between rising or falling edges of pin values and know the time between those events to the precision of the value of Duration. This is true for digital mode. For analog mode the inputs are sampled every 1 ms. Each time the `A` timer times out, the latest set of analog values is used to create a new `A` packet and that is then sent out. 

 Just because the EBB can kick out `I` and `A` packets every 1 ms (at its fastest) doesn't mean that your PC app can read them in that fast. Some terminal emulators are not able to keep up with this data rate coming back from the EBB, and what happens is that the EBB's internal buffers overflow. This will generate error messages being sent back from the EBB. If you write your own custom application to receive data from the EBB, make sure to not read in one byte at a time from the serial port - always ask for large amounts (10K or more) and then internally parse the contents of the data coming in. (Realizing that the last packet may not be complete.) 

 If an attempt is made to have all 13 channels of analog be reported any faster than every 4 ms, then an internal EBB buffer overflow occurs. Be careful with the speed you choose for A packets. The maximum speed is based upon how many analog channels are being sent back. 
- Example:`T,250,0 ` Turn on digital reading of pins and generation of `I` packet every 250 ms. 
- Note: If the `I` or `A` packet responses stop coming back after you've done a `T` query, and you didn't stop them yourself (with a `T,0,0` or `T,0,1`) then what's happened is that the internal buffer in the EBB for `I` or `A` packet data has been filled up. (There is room for 3 `I` packets and 3 `A` packets.) This means that the USB system is too busy to get the packet responses back to the PC fast enough. You need to have less USB traffic (from other devices) or increase the time between packet responses. 
- This command is not included in v3.0: Commands PC, PG, T have been marked as "not in use" and tentatively removed in this firmware release. If your application does use one or more of these commands, please contact us and let us know. If we don't hear from at least a couple of users that these are important, we'll go ahead and remove them permanently in a future firmware version. 

#### "T3" — Low-level Move With Jerk, Time-limited

- Command:`T3,Intervals,Rate1,Accel1,Jerk1,Rate2,Accel2,Jerk2[,Clear] `
- Response (future mode):`T3 `
- Response (legacy mode; default):`OK `
- Firmware versions: 3.0 and above
- Execution: Added to FIFO motion queue
- Arguments:

- Intervals is an unsigned 32 bit integer in the range from 1 to 4294967295, which specifies the duration of time, in units of 40 μs intervals, that the command executes for. 
- Rate1 and Rate2 are signed 32 bit integers in the range from -2147483648 to 2147483647. They represent step rates for axis 1 and 2, and are added to each axis step accumulator every 40 μs to determine when steps are taken. The sign of each Rate parameter determines the initial motor direction. 
- Accel1 and Accel2 are signed 32 bit integers in the range from -2147483648 to 2147483647. These values are added to their respective Rate values every 40 μs and control acceleration or deceleration during a move. 
- Jerk1 and Jerk2 are signed 32 bit integers in the range from -2147483648 to 2147483647. These values are added to their respective Accel values every 40 μs and control jerk during a move. 
- Clear is an optional integer in the range 0 - 3. If it is 0 then neither accumulator are cleared at the start of the command. If it is 1 then the step accumulator for motor1 is zeroed at the start of the command. If it is 2, then the step accumulator for motor2 is zeroed at the start of the command. If it is 3, then both accumulators are cleared. 
- Description:

 This command is extremely similar to the `LT` command. In fact, if both Jerk1 and Jerk2 are zero, this command is identical to the `LT` command. The difference is in the addition of the two jerk parameters. 

 Methods and consequences: As with `LT` (and `LM`), the initial value of Rate for each axis is adjusted by subtracting Accel/2 and adding Jerk/6 before the move begins. Then, on each 40 μs tick, the jerk value is added to the acceleration, the acceleration is added to the rate, and the rate is added to the step accumulator. The command terminates after the specified number of Intervals has elapsed. 

 The Accel/2 and Jerk/6 pre-adjustments ensure that the user-provided Rate, Accel, and Jerk values correspond to the initial conditions of the cubic motion profile. All formulas from the `LM` command description remain applicable, with the addition of the jerk terms. 
- Example 1: Axis 1 accelerates from rest with constant jerk for 5000 intervals (0.2 s), axis 2 stationary, accumulators cleared: 

- `T3,5000,0,0,100,0,0,0,3`

 Axis 1 starts with zero rate and zero acceleration; jerk of 100 causes the acceleration to increase linearly. 
- Example 2: Both axes move with initial rates, acceleration, and jerk for 10000 intervals (0.4 s): 

- `T3,10000,50000000,10000,5,30000000,8000,-3`

 Accumulators are not cleared, allowing continuation from a prior move. 

#### "TD" — Paired "Dual T3" Low-level Move With Jerk, Time-limited

- Command:`TD,Intervals,Rate1A,Rate1B,Accel1,Jerk1,Rate2A,Rate2B,Accel2,Jerk2[,Clear] `
- Response (future mode):`TD `
- Response (legacy mode; default):`OK `
- Firmware versions: 3.0.1 and above
- Execution: Added to FIFO motion queue
- Arguments:

- Intervals is an unsigned 32 bit integer in the range from 1 to 4294967295, which specifies the duration of time, in units of 40 μs intervals, that each of the two `T3` commands executes for. The full execution time of the `TD` code> command is 2 × Intervals. 
- Rate1A, Rate1B, Rate2A and Rate2B are signed 32 bit integers in the range from -2147483648 to 2147483647. They represent step rates for axis 1 and 2, and are added to each axis step accumulator every 40 μs to determine when steps are taken. The sign of each Rate parameter determines the initial motor direction. See below for an explanation of where each set of rates is used. 
- Accel1 and Accel2 are signed 32 bit integers in the range from -2147483648 to 2147483647. These values are added to their respective Rate values every 40 μs and control acceleration or deceleration during a move. 
- Jerk1 and Jerk2 are signed 32 bit integers in the range from -2147483648 to 2147483647. These values are added to their respective Accel values every 40 μs and control jerk during a move. 
- Clear is an optional integer in the range 0 - 3. If it is 0 then neither accumulator are cleared at the start of the command. If it is 1 then the step accumulator for motor1 is zeroed at the start of the command. If it is 2, then the step accumulator for motor2 is zeroed at the start of the command. If it is 3, then both accumulators are cleared. 
- Description:

 This command is for creating specially-crafted back-to-back time-limited moves with jerk. Internally, the `TD` command takes its parameter values and creates two `T3` commands that are loaded into the FIFO. It is a faster way to create "S-curves" accelerations than sending two `T3` commands separately. 

 Note that each `T3` command created by `TD` independently receives the Rate pre-adjustment described in the `T3` documentation (subtracting Accel/2 and adding Jerk/6). 

The `TD` command loads the two `T3` commands as follows: 

1. `T3,Intervals,Rate1A,0,Jerk1,Rate2A,0,Jerk2[,Clear] `
2. `T3,Intervals,Rate1B,Accel1,-Jerk1,Rate2B,Accel2,-Jerk2,0 `
- Example: S-curve acceleration on axis 1 from rest, 1000 intervals per half (2000 total = 0.08 s), axis 2 stationary, accumulators cleared: 

- `TD,1000,0,49950016,100000,100,0,0,0,0,3`

 First half: jerk = +100, zero initial acceleration. Second half: jerk = −100, peak acceleration = 100000. Rate1B = 49950016 is the exact discrete midpoint rate. 

#### "TP" — Toggle Pen 

Command: `TP[,Duration] `

Response (future mode): `TP `

Response (legacy mode; default): `OK `

Firmware versions: v1.9 and newer 

Execution: Immediate

- Duration: (Optional) an integer in the range of 1 to 65535, giving an delay in milliseconds.

 This command toggles the state of the pen (up->down and down->up). EBB firmware resets with pen in 'up' (Servo_Min) state. 

 Note that conventionally, we have used the Servo_Min (`SC,4`) value as the 'Pen up position', and the Servo_Max (`SC,5`) value as the 'Pen down position'. 

 The optional Duration argument is in milliseconds. It represents the total length of time between when the pen move is started, and when the next command will be executed. Note that this is not related to how fast the pen moves, which is set with the `SC` command. Rather, it is an intentional delay of a given Duration, to force the EBB not to execute the next command (often an `SM`) for some length of time, which allows the pen move to complete and possibly some extra settling time before moving the other motors. 

 If no Duration argument is specified, a value of 0 milliseconds is used internally. 

 Version History: Unchanged since firmware v2.2.1 

#### "TR" — Test Rate

- Command:`TR,StepRate,AxisSteps1[,AxisSteps2[,Clear]] `
- Response (future mode):`TR `
- Response (legacy mode; default):`OK `
- Firmware versions: Added in v3.0
- Execution: Added to FIFO motion queue
- Arguments:

- StepRate is an unsigned 32 bit integer in the range from 0 to 4294967295, which specifies step rate in steps/second for the move. 
- AxisSteps1 and AxisSteps2 are signed 32 bit integers in the range from -2147483648 to 2147483647, giving movement distance in steps. 
- Clear is an optional integer in the range 0 - 3. If it is 0 then neither accumulator are cleared at the start of the command. If it is 1 then the step accumulator for motor1 is zeroed at the start of the command. If it is 2, then the step accumulator for motor2 is zeroed at the start of the command. If it is 3, then both accumulators are cleared. 
- Description:

 This command is used to test some of the refactored math in version 3.0. 
- Version History: Added in v3.0. 

#### "V" — Version query

- Command:`V `
- Response (future mode):`V,EBBv13_and_above EB Firmware Version 2.4.2 `
- Response (legacy mode; default):`EBBv13_and_above EB Firmware Version 2.4.2 `
- Firmware versions: All
- Execution: Immediate 
- Description:

 This command prints out the version string of the firmware currently running on the EBB. The actual version string returned may be different from the example above. 

#### "XM" — Stepper Move, for Mixed-axis Geometries

- Command:`XM,Duration,AxisStepsA,AxisStepsB[,Clear] `
- Response (future mode):`XM `
- Response (legacy mode; default):`OK `
- Firmware versions: v2.3.0 and newer
- Execution: Added to FIFO motion queue
- Arguments:

- Duration is an integer in the range from 1 to 2147483647, giving time in milliseconds. 
- AxisStepsA and AxisStepsB are integers, each in the range from -2147483648 to 2147483647, giving movement distances in steps. 
- Clear is an optional integer in the range 0 to 3. A value of 0 (or if not provided) leaves both accumulators unchanged. A value of 1 clears the axis 1 step accumulator to zero before the move begins. A value of 2 clears the axis 2 step accumulator. A value of 3 clears both accumulators. 
- Description:

 This command takes the AxisStepsA and AxisStepsB values, and creates a call to the `SM` command with the SM command's AxisSteps1 value as AxisStepsA + AxisStepsB, and AxisSteps2 as AxisStepsA - AxisStepsB. Because of these additions and subtractions, be certain that the values provided for AxisStepsA and AxisStepsB do not cause an overflow or underflow of a 32 bit signed value when the addition and subtraction happen. 

 This command is designed to allow cleaner operation of machines with mixed-axis geometry, including CoreXY, H-Bot gantry machines, and current AxiDraw models. 

 If both AxisStepsA and AxisStepsB are zero, then a delay of duration ms is executed. 

 The minimum speed at which the EBB can generate steps for each motor is 0.00001164 steps/second. The maximum speed is 25,000 steps/second. If the XM command finds that the step rate for either axis falls outside the allowed range, it will output an error message and the move will not execute. (If limit checks have been disabled with `CU,1,0`, the rate will be silently clamped to the nearest limit instead.) Note that the range is checked on Axis 1 and Axis 2, NOT on Axis A and Axis B. (That is, the range is checked after performing the sum and difference.) While individual movement commands may be as short as a single step, there are practical limits to the rate at which commands can be issued, as discussed under Performance. 

 Note: In current firmware, if a rate error is detected, the error message may be followed by an OK response. 

 Note that internally the EBB generates an ISR at the 25 kHz rate. Each time the ISR fires, the EBB determines if a step needs to be taken for a given axis or not. The practical result of this is that all steps will be 'quantized' to the 25 kHz (40 μs) time intervals, and thus as the step rate gets close to 25 kHz the 'correct' time between steps will not be generated, but instead each step will land on a 40 μs tick in time. In almost all cases normally used by the EBB, this doesn't make any difference because the overall proper length for the entire move will be correct. 

 Note that internally, Duration is converted to a 32-bit floating point value during rate calculation. Floating point values can exactly represent integers only up to 16,777,216 (approximately 4 hours 39 minutes). For Duration values above this threshold, small rounding errors may occur in the computed step rate. In practice, this is unlikely to matter for typical use cases. 

A value of 0 for Duration is invalid and will be rejected.

If both AxisStepsA and AxisStepsB are zero then a Duration value above 100000 will be capped at 100000.
- Example:`XM,1000,550,-1234\r` Move 550 steps in the A direction and -1234 steps in the B direction, in duration 1000 ms. 
- Version History: Added in v2.3.0 Version History: Increased range of parameters and lowered slowest allowed step rate in v3.0. 

## Returned Errors

 When the EBB detects an error while it is parsing a command, it will return an error code. All possible error codes are listed here, along with a description of what causes the error. Once the first error is detected while parsing a command, the parsing is aborted, the command is aborted, the error is printed, and then the proper line ending is printed, taking into account Future vs. Legacy mode. 

 When an error is found, the line ending after printing out the error will either be `\n` when in Future Syntax Mode, or will be `OK\r\n` when in Legacy Syntax Mode. When in Legacy Syntax Mode, the `OK\r\n` used when there is an error overrides whatever other line ending there may be for the current command. 

 Not every possible syntax error will result in the correct error code being reported.

- `!0 Err: step rate too high`

This error indicates an internal math error happened during move command processing.
- `!0 Err: step rate too low`

This error indicates an internal math error happened during move command processing.
- `!0 Err: step rate too high`

This error indicates an internal math error happened during move command processing.
- `!0 Err: step rate too low`

This error indicates an internal math error happened during move command processing.
- `!1 Err: Invalid step rate`

This error indicates an internal math error happened during move command processing.
- `!2 Err: TX Buffer overrun`

This error indicates that the buffered return data to the PC exceeded 63 bytes in length. This is an internal EBB firmware error as there are no commands that return this much data.
- `!3 Err: RX Buffer overrun`

This error indicates that the current command exceeded 255 bytes in length. This error is an internal EBB firmware error.
- `!4 Err: Missing parameter(s)`

This error indicates that the parser found a line ending in the current command but expected a comma followed by at least one more parameter.

For example, if you sent `SM,100` the EBB will respond with `SM,!4 Err: Missing parameter(s)` (in Future Syntax Mode).
- `!5 Err: Need comma next, found: 'X'`

This error indicates that the parser was expecting to see a comma next in the command but instead saw character 'X'.

For example, if you sent `SM,100A` the EBB will respond with `SM,!5 Err: Need comma next, found: 'A'` (in Future Syntax Mode).
- `!6 Err: Invalid parameter value`

This error indicates that one of the parameters to the current command is too large, too small, or of the wrong type.

For example if you sent `TP,-1` the EBB will respond with `TP,!6 Err: Invalid parameter value` (in Future Syntax Mode).
- `!7 Err: Extra parameter`

This error indicates that the parser found an extra comma in the current command when it expected a line ending.

For example if you sent `SM,1,1,1,0,0` the EBB will respond with `SM,!7 Err: Extra parameter` (in Future Syntax Mode).
- `!8 Err: Unknown command 'X:YY'`

 This error indicates that the one character command 'X' was not recognized as a valid command name. It also prints out the hexadecimal value of the character that was sent. This can be useful if a non-printable character was sent, where the X will be just a blank space. 

 As an example, if the command `B` is sent, the reply is a single line `B,!8 Err: Unknown command 'B:42'` (in Future Syntax mode). 
- `!8 Err: Unknown command 'XX:YYYY'`

 This error indicates that the two character command 'XX' was not recognized as a valid command name. It also prints out the hexadecimal value of each of the two characters that were sent. This can be useful if non-printable characters were sent, where one or both of the Xs will print as blank spaces. 

 As an example, if the command `BB` is sent, the reply is a single line `BB,!8 Err: Unknown command 'BB:4242'` (in Future Syntax mode). 
- `!9 Err: Checksum incorrect, expected XXX`

When checksums are turned on (`CU,54,1`), this error indicates that a checksum was found but that it was incorrect, and it prints out the expected checksum as XXX.

For example, if you send `V,100` when checksums are turned on, the EBB will reply with `V,!9 Err: Checksum incorrect, expected 170` (in Future Syntax Mode).
- `!10 Err: No checksum found but required`

When checksums are turned on (`CU,54,1`), this error indicates that there was no checksum found at the end of the command.

For example, if you send `V` when checksums are turned on, the EBB will reply with `V,!10 Err: No checksum found but required` (in Future Syntax Mode).

## Initial I/O pin configuration

In addition to the stepper motor outputs, many applications make use of one or more digital I/O pins. 

The most accessible and commonly used of the I/O pins are those in PortB. The eight pins in PortB are physically arranged into 3-pin "header connections", with ground, +5V power, and the "signal" I/O pin itself, from the edge of the board towards the center. Four of these connectors are located "below" the stepper motor terminals, and are labeled as B1, B0, B2, and B3, in order from the "bottom" edge of the board towards the stepper terminals. These four connections are pre-populated with header pins. Four additional connections, B4, B5, B6, and B7 are located on the "bottom" edge of the board, and are not pre-populated with header pins. 

On EBB boards v2.5 and above, the 5V power to the pen servo (RB1) is controlled by software, and defaults to an off state at reset; see the `SR` command. 

Pins B1, B0, B2 and B3 are not 5-volt tolerant and any voltage above about 3.6V will damage them. Pins B4, B5, B6 and B7 are 5-volt tolerant and will not be damaged by voltages up to 5.5V. 

Because all Port B pins (B0 through B7) have weak pull up resistors, any of these pins can be used to read a switch by connecting a switch between the Port B pin and GND. Use the `PI` command to read the state of the switch. If that pin is not already an input at boot (see table below) you can make it an input using the `PD` command. 

In addition to the pins of PortB, additional broken-out I/O pins accessible on the EBB include: PortA: RA0,1,2,3,5, PortC: RC0,1,2,6,7, PortD: RD: 0,1,4,5,6,7, and PortE: RE0. Every pin on PortB, PortC and RA6 can source or sink up to 25mA each. All other pins can source or sink up to 4mA each. Note that pins RA0, RC1, RD4, RD5, RD6, RD7 and RE0 are brought out to the I/O header but already have existing analog or digital functions mapped to them and so should only be used for monitoring these signals rather than as GPIO. 

All pins of PortB have weak pull ups to 3.3V, which can source between 80 and 400 μA, and are enabled any time the pin is an input. Pull ups are not available on the other (Port A, C, D, E) GPIO pins. Many of the I/O pins can be used for general purpose digital I/O (GPIO), and some can also be used as RC servo outputs, within the limits of `S2`. With the exceptions listed in the table below and RA0, RC1, RD4, RD5, RD6, RD7 and RE0, all of the broken-out I/O pins are initially configured at boot as digital inputs. 

Certain PortB signal pins are specially configured at boot time for typical applications, as summarized in the table below. 

| Pin | Default Direction | Default State | 5V Tolerant | Typical application |
| --- | --- | --- | --- | --- |
| RB0 | Input | Weak pull up | No | Alternate PRG/Pause button input; see `QB` |
| RB1 | Output | RC Servo Pulses | No | Pen lift servo output; see `SC`, `SP` |
| RB2 | Input | Weak pull up | No | General |
| RB3 | Output | Low | No | Engraver or laser PWM output control |
| RB4 | Output | Low | Yes | Alternate Pen Up/Down I/O (solenoid/laser) |
| RB5 | Input | Weak pull up | Yes | General |
| RB6 | Input | Weak pull up | Yes | General |
| RB7 | Input | Weak pull up | Yes | General |

## Performance

The EBB has some basic performance limits, which do vary with new firmware releases. 

One performance aspect is the duration of the step pulses sent to the stepper driver chips. While the pulses produced by the EBB firmware will always be long enough to guarantee proper operation with the built-in drivers, it is possible to use some of the GPIO pins on the EBB to connect external step/dir driver electronics to drive much larger systems. In this case, the external drivers may have a minimum step pulse length, and so it can be important to know this timing information in that case. 

 Output step pulse duration for external stepper drivers: 

- EBB firmware 2.7.0 and above: 1.6 - 2.3 μs.
- EBB firmware 2.6.5 and below: 2.8 - 3.0 μs.

 Another important performance measure is the maximum rate at which sequential movement commands can be streamed to the EBB. This rate is expressed as the shortest move duration that can be sent to the EBB as a continuous stream of identical motion commands, such that there are no gaps between the last step of one move and the first step of the next move. For a high enough sustained rate of sufficiently short movement commands, the EBB will not be able to parse and queue each command prior to starting the subsequent move. The available CPU time available for parsing and queueing commands does depend on the active step rate, as the EBB shares CPU time between command parsing and step generation. 

 The following table shows the minimum move duration, in milliseconds, which the EBB can sustain indefinitely without gaps, using different move commands. All times were measured with step rates of approximately 25 kHz on both motors — a worst case condition rarely achieved in typical applications. 

| Command | Firmware >= 3.0.0 | Firmware >= 2.7.0 and < 3.0.0 | Firmware < 2.7.0 |
| --- | --- | --- | --- |
| SM | 2 ms | 3-4 ms | 4-7 ms |
| LM | 4 ms | 3-4 ms | 4-6 ms |
| L3 | 4 ms | --- | --- |

 The times in the table above are measured under conditions where the PC sending the commands is able to sustain the same data rate. In practice, PCs — especially Windows PCs — can have occasional brief gaps when sending long strings of USB commands. The incidence of these gaps depend upon the system configuration, CPU speed, load, other USB communication, and additional factors. Best practice is to try and use fewer, longer-duration movement commands (rather than more, shorter-duration commands) whenever possible, to minimize the effects of both EBB CPU time constraints and any USB performance issues on the PC. 

## Frequently Asked Questions

 Q1) How can I calculate how long it will take to move from one RC servo position to another? Specifically in relation to the standard pen-arm servo that is activated with the `SP,1` and `SP,0` commands. 

 A1) By default, with the latest version of EBB firmware, we add (or subtract) the rate value from the current pulse duration every time the pulse fires until the current pulse duration equals the target duration. Normally we have 8 servo channels available, and each gets 3 ms, so that means that each channel can fire once every 24 ms. So the rate value gets added or subtracted from the current pulse duration every 24 ms. 

 For example, if you're currently at a position (pulse duration) of 10000 and you send a new command to move to position 15000, then you have a 'distance' of 5000 to go. So when we start out, our current duration is 10000 and our target is 15000. If our rate value is 100, then it will take 50 of these 24 ms periods to get from 10000 to 15000, or 1.2 seconds total. 

 Now, when you're using the `SP,0` and `SP,1` commands, the Servo_Min (defaults to 16000, or 1.33 ms) and Servo_Max (defaults to 20000, or 1.6 ms) get used as the positions. And the Servo_Rate_Up and Servo_Rate_Down get used as the rates. So the formula is as follows: 

 ((Servo_Max - Servo_Min) * .024)/ Servo_Rate = total time to move 

 For the example above. ((15000 - 10000) * .024)/100 = 1.2 seconds. 

 Q2) What do the LED patterns mean? 

 A2) There are two applications that live on the EBB: The bootloader and the main EBB firmware. They each have different LED blink patterns. There is a green power LED labeled 3.3V which is always lit as long as either the USB or barrel jack connector is receiving power. It is located next to the large electrolytic capacitor. 

 The LED timing mechanism used by both bootloader and main EBB applications is sensitive to the commands currently being executed. For example, the timing of the alternating LED pattern when the bootloader is running will change as a new EBB firmware application is being actively programmed. 

 Bootloader When the bootloader is running (only used to update main EBB firmware), the two LEDs between the USB and barrel jack connectors can take on two different states: 

| Pattern | Description | USR/Red | USB/Green |
| --- | --- | --- | --- |
| Idle | Waiting for USB connection with host | Off | On |
| Alternating | USB connection established to host | 200 ms on, 200 ms off, alternating with Green | 200 ms on, 200 ms off, alternating with Red |

 Main EBB Firmware When the main EBB firmware is running (normal operating mode) the two LEDs between the USB and barrel jack connectors can take on three different states: 

| Pattern | Description | USR/Red | USB/Green |
| --- | --- | --- | --- |
| Fast Blink | No connection to USB host | Off | 60 ms on, 60 ms off |
| Slow Blink | Connected to USB host but not enumerated | Off | 750 ms on, 750 ms off |
| Short Long Blink | Fully enumerated and communicating with USB host | Off | 365 ms on, 365 ms off, 1.25s on, 365 ms off |

 The Fast Blink pattern is almost never seen in practice, since the USB host normally enumerates the EBB immediately upon connection with a USB cable. However, if proper drivers are not installed on the host or if there is some other problem with the USB enumeration process the Fast Blink pattern can be observed and used as a debugging aid.