# Mechatronics_with_OMAPL138DSP
This repository contains code from the in-lab portions of Mechatronics with Prof. Dan Block at UIUC. The labs worked with the OMAP-L138 DSP+ARM processor on a robot car assembled and designed by Prof. Block. Course content available at http://coecsl.ece.illinois.edu/ge423/ although this link gets updated each semester (and I know the processor was changed the semester after I took the course). Each lab was completed in small steps with a lab partner.  
  
Please do not steal the code if you are currently in the course, there is no guarentee that any of it is correct or up to date.  

## Content
I've done my best to separate each portion of each lab into small projects contained in their own folders. When I was talking the course, all of the code compiled and worked as intended but because I am editing the file structure and naming conventions it is very possible that the same code will not run correctly if it were plugged in to the same robot car today because of configuration file errors. The only file I wrote logic in will be named <code>user_<i>folderName</i>.c</code> in the <code>source</code> folder, where <i>folderName</i> is the name of the folder it is found under. Code Composer Studio's interface was also often used to edit the project's configuration file, which will be named <code><i>folderName</i>.cfg</code> in the <code>SYSBIOS</code> folder, to add Clock objects.  
  
A skeleton of the original files provided by the course can be created by running the executable [<code>Sp2019OMAPL138ProjCreator.exe</code>](https://github.com/monk200/Mechatronics_with_OMAPL138DSP/blob/main/labfiles/Sp2019OMAPL138ProjCreatorFiles/Sp2019OMAPL138ProjCreator.exe) under <code>labfiles\Sp2019OMAPL138ProjCreatorFiles</code>.  

* [LEDctrlWithSwitches](https://github.com/monk200/Mechatronics_with_OMAPL138DSP/blob/main/LEDctrlWithSwitches/source/user_LEDctrlWithSwitches.c): The first task simply turned LEDs on while their corresponding switch was being pressed by creating the function <code>checkswitches()</code> in the main C file and a Clock object named <code>CLK_checkswitches</code> in the [configuration file](https://github.com/monk200/Mechatronics_with_OMAPL138DSP/blob/main/LEDctrlWithSwitches/SYSBIOS/LEDctrlWithSwitches.cfg).
* [LEDsCountInBinary](https://github.com/monk200/Mechatronics_with_OMAPL138DSP/blob/main/LEDsCountInBinary/source/user_LEDsCountInBinary.c): Controls 5 LEDs on the robot to count in binary, incrementing every second and pausing the count if switch1 is pressed. Setting the correct LEDs was done in the function <code>set5LEDS(cnt)</code> and pausing the count was done in the fucntion <code>countit()</code>, both in the main C file. A Clock object named <code>CLK_countit</code> in the [configuration file](https://github.com/monk200/Mechatronics_with_OMAPL138DSP/blob/main/LEDsCountInBinary/SYSBIOS/LEDsCountInBinary.cfg) was also created to be able to increment the count once every second.  

## Setup
All the code done in this class was edited and debugged using Code Composer Studio and the terminal emulator Tera Term. The robot car needs its serial port cable to be plugged into a JTAG USB attachment and the terminal emulator needs to be set to communicate with the COM port that the JTAG is plugged into and communicating at a 115200 baud rate. The COM port can be determined by searching through your computer's Device Manager. Turn the robot on and press any key while clicked into the terminal to boot Linux. After this, click the "Debug" button in Code Composer. Before pressing play to run the code, type "boot" into the terminal and hit enter, then wait until Linux is done booting. This will create a JTAG link and the process needs to be reapeated whenever the robot is restarted or if the connect become flakey.
