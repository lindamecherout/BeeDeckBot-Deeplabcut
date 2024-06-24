This README explains how to set up the electronics to control the motors. In particular, how to start and stop the robotic flower's motors and the camera recording using the manual switch and the RFID door switch. It's necessary to install SONY Remote Camera Tool software (https://support.d-imaging.sony.co.jp/app/remotecameratool/en/download/) on your computer to control camera recording.

# User guide
Install all the electronic circuits. Transfer the code in this folder to the Arduino Leonardo board with the dynamixel shield. First, make sure that the electronic circuit without the RFID door is working. Press the manual switch once, the robotic flower target should move during 10 seconds and the camera start recording. If you press a second time during those 10 seconds, nothing should happen, the flower will still move and camera still recording. After this delay, the target and the recording should stop and the flower move to the position for the next start.

# Electronics
![schema électronique](https://github.com/lindamecherout/BeeDeckBot-Deeplabcut/assets/173625375/29d2d61e-4e36-4d14-8fcf-97e27bf85dcf)

![20240624_154803](https://github.com/lindamecherout/BeeDeckBot-Deeplabcut/assets/173625375/04b80a45-078e-466b-b09f-ad702f93294d)
