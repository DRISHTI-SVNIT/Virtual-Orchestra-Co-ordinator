# Virtual-Orchestra-Co-ordinator
An image processing project to implement a software that responds to users action as in Orchestra.

# Hardawre requirements :
* Atmel ATmega32
* USB-TTL
* Speakers
* Webcam

#Software requirements :
MATLAB R2015b

# How to use?
1. Clone the repository locally.
2. Open "AVR code" and burn "MySC1.1.hex" on ATmega32 microcontroller. Connect the PD5 pin with the speaker's positive and ground the other terminal.
3. Connect ATmega32's RX pin with USB-TTL's TX.
4. Now plug in USB-TTL in your PC and know which COM port you have plugged it in. This can be known using Device Manager or softwares like X-CTU.
5. Open MATLAB and navigate from your MATLAB file browser to the GitHub cloned repository and open "Application.m"
6. Replace your COM in the 7th line of code which is,
 s = serial('COMx','BaudRate',38400); where x is your COM number.
7. Your MATLAB should have webcam support package installed, if installed type "webcamlist" and choose whichever webcam you are using by typing the name of the webcam (shown in the command window) in the 2nd line of "Application.m".
cam = webcam('x'); where x is the name of your webcam
8. Run this MATLAB script file, you will be prompted with a New or Last parameter setup; choose New if this is the first time you are running the script.
9. Threshold the object you want to track using the slidebars. Make sure the object you are tracking has a distinct color.
10. Calibrate the parameters unless you have a fine blob of white pixels depicting your object, Hit 'OK' then.
11. The program will start to run now. Gestures control the playing and stopping of music while movement of object in horizontal plane decides the tempo of the song.
12. Make a "P" to start the music. Then move the object to and fro horizontally to change tempo according to your motion. Make a "C" to stop music and "N" to close the program.

# Practical problems in project :
* MATLAB, which is not solely based for image-processing, lags a lot while working with the image processing algorithm.
* The basic color based tracking exposes data to a wide range of noise and errors.
* The colored object must be unique in the camera frame for robust tracking.
* Efficiency issues.
* When the motion of hand/object was slow then the microcontroller delayed for a longer time; thereby leading to heaping of receiving buffer data which slowed its response a lot.

# Solutions :
* Either the algorithm needs to be optimized or a better option is writing the code in OpenCV, which is an open-source C/C++ or Python library files dedicated for Computer Vision usage. The work is already under progress in OpenCV and noticeable reduction in lag is recorded.
* Instead of color based tracking, it can be associated with shape detection, feature detection or HSV (hue saturation value) methods for better tracking.
* The heaping of receive buffer was solved by flushing all the data in buffer at the end of every iteration. The project works better now.

# Application :
* The gesture detection can be used to make the daily life machines smarter and easier to work with. This can be the next level of input after touch screens.
* The object velocity calculated can also be used to calculate the velocity of moving physical objects, e.g. cars
