# Washing machine - project for embedded systems.

Application simulates DE1-SoC Board behaviour.
Is written in C++ with use of SystemC system-level modeling language which allows processes to communicate in a simulated real-time environment by mimics the hardware description languages VHDL and Verilog
#
## Application modules:
- CPU 1 with 6 SC_CTHREADs
- CPU 2 with 1 SC_CTHREAD
- 10 Switches (SW_0 to SW_9)
- 10 Leds (LED_0 to LED_9)
- HEX display
#	  
## Expected behaviour: 

| - | - |
|---|---|
| Washing machine have six washing programs. <br/>Each one represents diffrent washing temperature | - |
| Switches from SW_0 to SW_5 are program's switches | - |
| Program is launched only when one switch from <br/>program's switches is turned on  | [&nbsp;&nbsp;&nbsp;SW0,&nbsp;&nbsp;&nbsp;SW1,&nbsp;&nbsp;&nbsp;SW2,&nbsp;&nbsp;&nbsp;SW3,&nbsp;&nbsp;&nbsp;SW4,&nbsp;&nbsp;&nbsp;SW5] |
| Each switch has associated LED. LED_0 light's on<br/>when SW_0 is turned on etc.  | [LED_0, LED_1, LED_2, LED_3, LED_4, LED_5] |
| For each active program HEX should display<br/>associated temperature.      | [&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;30,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;35,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;40,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;60,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;80,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;90] |
| SW_6, SW_7, SW_8, SW_9 are ignored<br/>LED_6, LED_7, LED_8 are not in use<br/>LED_9 light's on mean error | - |
| Only one program can be active at the time | - |
|  If more then one switch between SW_0 and SW_5<br/>is turned on, there is en error.<br/> HEX displays ERR, all leds are off except for LED_9 | - |
#
## Requirements: 
- Visual Studio 
- Accellera's SystemC 2.3.3

Installation 
Instruction file is included in SystemC's folders. You can download it from official Accellera's page.

#
## Example

![Home page](https://github.com/arekss16/WashingMachineSystemC/blob/master/readme_files/WASHER.gif?raw=true)


