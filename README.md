# SaraKIT-dsPIC33-bldg-gimbal-motor
SaraKIT - using dsPIC33 with Raspberry Pi 4 to control BLDC motors (gimbal motors) with an encoder (FOC) using SPI communication with DMA.

https://sarakit.saraai.com

DMA note:
https://forums.raspberrypi.com/viewtopic.php?p=609380#p609380

# Project Basics
## Project title
: SaraKIT
## Project teaser
: Raspberry Pi expansion board that adds advanced voice control, precise motor control and various sensors for robotics and AI projects.

# Details About Your Product
## A simple paragraph or two describing your product

SaraKIT is a Raspberry Pi CM4 expansion board that enables advanced voice control and precise motor control. It features three sensitive microphones with sound localization for voice recognition up to 5m away, two independent BLDC motor controllers providing quiet, fast and precise control for gimbal motors, CSI interface with two cameras on a flexible cable, two accelerometers, a gyroscope, and a temperature sensor. In short, SaraKIT is a versatile solution for those who want to build modern and efficient voice-controlled products, robots, and interact with smart home or office devices.

## A high-resolution product image on a white background with no embedded text or logos
$${\color{red}to-improve}$$

<img src="https://saraai.com/_SaraKIT/crowdsupply/mainimage.png" width=100%>

## A ballpark estimate of the product price
- 149$ ?

we plan to sell SaraKIT in a boxed version, but we are also thinking about selling it with an additional casing in 3 versions?

# Details About Your Project
## A paragraph describing several use-cases for your product

We provide a ready-made solution and many examples, but the imagination and creativity of the user determine the range of applications:

## SaraKIT with ChatGPT
Using our SaraKIT electronics, we can build a device with ChatGPT support in a housing printed on a 3D printer with the function of tracking and recognition the user's face:<br>
<img src="https://sarakit.saraai.com/images/_pan_tilt/DSC02892.JPG" width=48%>
<img src="https://sarakit.saraai.com/images/_pan_tilt/DSC02853.JPG" width=48%><br>
the operation of the device is shown in this video:<br>
![SaraEye](https://saraai.com/_SaraEye/Movies/SaraEyeWithChatGPT_en.mp4)<br>
Of course, for simple integration with ChatGPT, the PCB itself is enough, without cameras, motors, or special housing.

## Support for Alexa and Google Home
but on a look-only basis (no wake words "Alexa" or "ok Google":<br>
![alexa](https://saraai.com/_SaraEye/Movies/AlexaSaraEye4k.mp4) <br>
<img src="https://sarakit.saraai.com/images/_case/DSC02781.JPG" width=48%>
<img src="https://sarakit.saraai.com/images/_case/DSC02794.JPG" width=48%><br>

## SaraKIT with BLDC Gimbal Motor Demo (FOC)
This example shows how to control motor speed, torque and angle of BLDC gimbal motors using the Field Oriented Control (FOC) algorithm (or not) in C++/Python.<br>
![bldc](https://saraai.com/_SaraKIT/video/SaraKIT_BLDC_Gimbal_Motors.mp4)<br>
BLDC motors have become increasingly popular due to their smooth operation, high torque, and precise control. In this guide, we will explore the use of BLDC motors using SaraKIT, and compare them to other commonly used motors such as stepper motors and servos.<br><br>
In this video, I demonstrate how easy it is to control BLDC gimbal motors, and also discuss the advantages and disadvantages of solutions based on servos or stepper motors. I also show the difference in controlling gimbal motors that have a decoder and those that do not.<br><br>
Gimbal motors with a decoder are controlled using the Field Oriented Control (FOC) algorithm. The condensed knowledge presented here is based on many materials from the internet, such as the "Simple Field Oriented Control BLDC driver" for Arduino systems. In future videos, we will show how to use gimbal control to create a self-balancing robot, RC car, precise Pan/Tilt camera control, or creating a voice assistant based on Amazon Alexa, Google Home, or ChatGPT that does not require continuous calling of the keyword "Alexa...", but just looking at it.<br><br>
![changetomp4](https://sarakit.saraai.com/images/SaraKIT_field_oriented_control_FOC.gif)
Code examples in Pascal and C++ is created for Raspberry Pi 4 in CM4 version. SaraKIT requires 12-24VDC min. 20W when you use motors in your project, you should use a correspondingly larger power supply. For mobile devices, we recommend a simple connection to the PowerBank (PD2.0 PD3.0 Fast Charging and QC4 with USB-C output) with a special PD 12v cable. Or by connecting a USB cable via USB-C Pd Trigger Module Pd 12v.

## Self Balancing Robot
Example of use, demonstration of the speed and power of BLDC motors<br>
<video src='https://saraai.com/_SaraKIT/video/SaraKIT_SelfBalancingRobot.mp4' width=75%></video>
<br>

https://saraai.com/_SaraKIT/video/SaraKIT_SelfBalancingRobot.mp4?width=200&height=200

test1

<figure class="video_container">
  <video controls="true" allowfullscreen="true" poster="path/to/poster_image.png">
    <source src="https://saraai.com/_SaraKIT/video/SaraKIT_SelfBalancingRobot.mp4" type="video/mp4">
  </video>
</figure>

test2

<figure class="video_container">
  <video controls="true" allowfullscreen="true">
    <source src="https://saraai.com/_SaraKIT/video/SaraKIT_SelfBalancingRobot.mp4" type="video/mp4">
  </video>
</figure>

test3

<figure class="video_container">
  <iframe src="https://saraai.com/_SaraKIT/video/SaraKIT_SelfBalancingRobot.mp4" frameborder="0" allowfullscreen="true"> </iframe>
</figure>

test3b

<figure class="video_container">
  <iframe src="//www.youtube.com/embed/hYSFt0cGJSE" frameborder="0" allowfullscreen="true"> </iframe>
</figure>

test3c

<!-- blank line -->
<figure class="video_container">
  <iframe src="//www.youtube.com/embed/hYSFt0cGJSE" frameborder="0" allowfullscreen="true"> </iframe>
</figure>
<!-- blank line -->

test4

<video width="908" height="242" autoplay loop muted>
  <source src="https://allplayershare.com/news/ALLPlayerSharePromo908.mp4" type="video/mp4">
  <img src="https://allplayershare.com/news/shotpopup.jpg">
</video>


This movie showcases one of the applications of SaraKIT, an extension kit for Raspberry Pi 4 in CM4 version.

The SaraKIT kit includes most of the necessary elements:
- Two FOC gimbal motor drivers for BLDC motors
- An accelerometer with a gyroscope
- Support for motor encoders
- 3 sensitive microphones for voice control
- Two camera outputs for live streaming from a moving vehicle
- The ability to connect power from easily available Power Banks (PD2.0 PD3.0 Fast Charging and QC4 with USB-C output) with a special PD 12v cable or by connecting a USB cable via USB-C Pd Trigger Module Pd 12v.

Additionally, you will need two BLDC gimbal motors, two encoders, two motor-to-brick adapters, and some building blocks. The design of the vehicle is up to you. The brick adapters can be easily 3D-printed (the relevant stl and obj files are included on our website) or purchased for a few dollars from our site.

This robot demonstrates the power of BLDC gimbal motors; it is very difficult to overturn, quiet, and fast, and does not require heavy loads to be placed high up.

You can find C++ and Python code for Raspberry Pi4 in the
SaraKIT Github repository

## Video with a ready example using Lego bricks:
https://youtu.be/ufgM8Ylnlrg
Camera Pan/Tilt

## Control of a silent precision camera or two cameras (Stereo Vision - Depth) with two BLDC motors
https://sarakit.saraai.com/example-of-use/camera-pan-tilt
we are working on more demonstrations

## Unboxing
![unboxing](https://saraai.com/_SaraKIT/video/SaraKIT_Unboxing.mp4)



## A list of features and technical specifications

SaraKIT is a carrier board for the Raspberry Pi CM4. It is equipped with 3 microphones with sound localization function and a stereo output for implementing artificial intelligence and voice projects. Two independent BLDC drivers allow for quiet and precise motor control in mobile device projects. A CSI interface with two cameras. Two accelerometers, a gyroscope, and a temperature sensor.

- Raspberry PI CM4 compatible socket 
- Audio based on ZL38063
- three mirophones SPH0655 
- Sensitivity -37dB ±1dB @ 94dB SPL
- SNR 66dB
- Amplified stereo output 2x6W 4Ohm
- Two three-phase bldc drivers DRV8313 65Vmax 3A-peek
- Two Encoder input (may be reprogramed as GPIO)
- 11 GPIO( UART, I2C, PWM..)
- Two camera interfaces CSI
- Digital Accelerometer LIS3DH, 3-Axis, 2g/4g/8g/16g, 16-bit, I2C/SPI interfaces
- always-on 3D accelerometer and 3D gyroscope and temperature LSM6DS3TR 
- Embedded,programmable 16-bit microcontroller with 32KB memory dsPIC33 
- Host USB

## Hardware Overview:
<img src="https://sarakit.saraai.com/images/hw_diag_v2_0.png" width=48%><br>

## Hardware Logic:
<img src="https://sarakit.saraai.com/images/hw_logic_2.png" width=48%><br>

## Power supply:

SaraKIT requires 12-24VDC min. 24W when you use motors in your project, you should use a correspondingly larger power supply.

![](https://sarakit.saraai.com/images/SaraKIT-RaspberryPi-PowerBank-PD-12v.gif)

For mobile devices, we recommend a simple connection to the PowerBank (PD2.0 PD3.0 Fast Charging and QC4 with USB-C output) with a special PD 12v cable. Or by connecting a USB cable via USB-C Pd Trigger Module Pd 12v

## SaraKit Mainboard peripherials

<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  overflow:hidden;padding:10px 5px;word-break:normal;}
.tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
.tg .tg-0pky{border-color:inherit;text-align:left;vertical-align:top}
</style>
<table class="tg">
<thead>
  <tr>
    <td class="tg-0pky" rowspan="2"><img src="https://sarakit.saraai.com/images/_mainboard/SaraKIT_GPIOPIN.jpg" width=50%></td>
    <td class="tg-0pky">Pin</td>
    <td class="tg-0pky">Function</td>
  </tr>
  <tr>
    <td class="tg-0pky">1</td>
    <td class="tg-0pky">RPi_CM4 G2/I2C SDA</td>
  </tr>
  <tr>
    <td class="tg-0pky">2</td>
    <td class="tg-0pky">RPi_CM4 G13/IR_LED PWM</td>
  </tr>
  <tr>
    <td class="tg-0pky">3</td>
    <td class="tg-0pky">RPi_CM4 G3/I2C SCL</td>
  </tr>

</thead>
</table>

| GPIO J104 | Pin | Function  |
|:----------:|:----------:|:------------------------|
|<img src="https://sarakit.saraai.com/images/_mainboard/SaraKIT_GPIOPIN.jpg" width=50%><br> | sss | aaa|
| |1|RPi_CM4 G2/I2C SDA|
| |2|RPi_CM4 G13/IR_LED PWM|
- 3	= RPi_CM4 G3/I2C SCL
- 4	= RPi_CM4 G22/AUDIO DET
- 5	= RPi_CM4 G5/PIR_INT
- 6	= RPi_CM4 G23/FILTER_CTRL
- 7	= RPi_CM4 G6/LED_DI
- 8	= RPi_CM4 GPIO24
- 9	= GND
- 10 = RPi_CM4 GPIO25

### GPIO J105

Pin	Function
- 1-2 =	12V xA
- 3-4 = 5V xA
- 5-6 = 3.3V xA
- 7 = RPi_CM4 G14/TX0
- 8 = RPi_CM4 G15/RX0
- 9-10 = GND

### Audio output RIGHT J300, Left J301
Amplified 2x6W 4Ω output
![j300](https://sarakit.saraai.com/images/_mainboard/SaraKIT_AudioOutPIN.jpg)

Pin	Function
- 1	- OUTN
- 2	- OUTP

### MOTOR A J400, MOTOR B J401
![j400](https://sarakit.saraai.com/images/_mainboard/SaraKIT_MotorsPIN.jpg)
Pin	Function
- 1	= Phase 1
- 2	= Phase 2
- 3	= Phase 3

### Encoder input J402,J404
![j400](https://sarakit.saraai.com/images/_mainboard/SaraKIT_EncodersPIN.jpg)
Pin	Function
- 1	= 3.3V
- 2	= dsPIC RB2 (PWM input)
- 3	= GND

### dsPIC programming interface J403
![j400](https://sarakit.saraai.com/images/_mainboard/SaraKIT_dsPICPIN.jpg)
Pin	Function
- 1	= RST
- 2	= 3.3V
- 3	= GND
- 4	= PGD2
- 5	= PGC2

### Assembly Drawing:
The SaraKit is set of three elements:

- Raspberry Pi Compute Module 4 Carier board
- dual CSI camera flex cable 17cm (Flex)
- Raspberry Pi camera  standard CSI  connection adapter (Hub)

J2 and J3 connectors are standard CSI connectors. You can connect cameras compatible with Raspberry PI

## A public link to open source information such as the following (we cannot host these files for you):


