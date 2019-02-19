# Overview

**This demo includes uArm Swift Pro,mini fan seeed module and openMV Kit.If openMV detects human face,the uArm Swift Pro will follow the face of human and turn on the fan at the same time.If the openMV don't detect face,the uArm Swift Pro will enter the patrol mode to look for face,the fan will be closed in this mode.**

## How to install software

### 1.Install openMV firmware
* Download  [OpenMV IDE](https://openmv.io/pages/download) and install it.
* Open main.py file in openMV_Kit_code folder using openMV IDE.
* Connect the openMV and PC using microUSB wire.
![](https://github.com/uArm-Developer/OpenMV-Examples/blob/master/uArm_face_track_demo/image/pc_openmv.jpg)
* Click the "Connect" button to connect the openMV with OpenMV IDE.
![](https://github.com/uArm-Developer/OpenMV-Examples/blob/master/uArm_face_track_demo/image/openmv_ide_connect.jpg)
* Click the "Start" button to start run the demo code.
![](https://github.com/uArm-Developer/OpenMV-Examples/blob/master/uArm_face_track_demo/image/openmv_ide_start.jpg)
* Move the openMV to detech face.Make sure the image is clear and it can detach face,otherwise it is necessary to adjust the camera.
![](https://github.com/uArm-Developer/OpenMV-Examples/blob/master/uArm_face_track_demo/image/openmv_ide_image.jpg)
* Move the main.py to the disk and replace the old one.
![](https://github.com/uArm-Developer/OpenMV-Examples/blob/master/uArm_face_track_demo/image/usb_drive.jpg)
* Remove the microUSB wire.

### 2.Install Arduino mega2560 firmware
* Connect Arduino mega2560 and PC using USB wire.
![](https://github.com/uArm-Developer/OpenMV-Examples/blob/master/uArm_face_track_demo/image/pc_arduino.jpg)
* Open fan_uarm_face.ino.
* Add flexiTimer2.Zip libary from lib folder.
* Click "Upload" button to upload firmware to Arduino mega2560.

### 3.Install uArm Swift Pro firmware
* Connect uArm Swift Pro and PC using microUSB wire.
* Upload uArmSwiftPro_2ndUART.hex using [XLoader](http://xloader.russemotto.com/XLoader.zip)
![](https://github.com/uArm-Developer/OpenMV-Examples/blob/master/uArm_face_track_demo/image/xloader.jpg)

## How to install hardware
* Fix the openMV in uArm Swift Pro.
![](https://github.com/uArm-Developer/OpenMV-Examples/blob/master/uArm_face_track_demo/image/install_openmv.jpg)
* Connect mini fan seeed module and the seeedinterface board.
![](https://github.com/uArm-Developer/OpenMV-Examples/blob/master/uArm_face_track_demo/image/install_fan.jpg)
* Connect the seeedinterface board in uArm Swift Pro and fix the fan.
![](https://github.com/uArm-Developer/OpenMV-Examples/blob/master/uArm_face_track_demo/image/fix_fan.jpg)
* Connect uArm Swift Pro with Arduino mega2560 using the TYPE-C wire and power on the uArm Swift Pro.
![](https://github.com/uArm-Developer/OpenMV-Examples/blob/master/uArm_face_track_demo/image/connect_uarm.jpg)
* Arduino mega2560 connect USB wire.
![](https://github.com/uArm-Developer/OpenMV-Examples/blob/master/uArm_face_track_demo/image/connect_arduino.jpg)
* Reset the Arduino mega2560,and test the demo.If the openMV detects human face,the led of openMV will blink.





