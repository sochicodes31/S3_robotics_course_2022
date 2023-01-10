# Robotics course 2022
Team: Sochi Aneke, Sakshi Sharma, Sayed Mossavi

Authors: Kevin Lhoste & Rajeev Mylapalli

This is the repository of the [LPI](https://www.learningplanetinstitute.org/en), [Dgital Master](https://master.learningplanetinstitute.org/en/digital) "Robotics" course 2022-2023 final projects.

# Course description
1. Bootcamp: Arduino and Electronics
* Shitty robots - no expereince with coding or electronics required (building remote control robots using servos, RC receover, battery and some trash like cardboard, plastic bottels, cans, wood etc)
* Introduction to Arduino
* Environment setup (installing ide and trouble shooting issue with serial port)
* Basic electronics (open & close circuits, analog vs digital signals, building basic circuits on bread board)
* Using code to play with components (led, buzzer, ldr etc)
2. Robotics 101 - Introduction
* Lecture + discussion (Introduction to robotics, applications, examples and some of the main problem statements of robotics).
* Schematics of Robots used/built during the course
* Intro to sensors and actuators - DIY version
* Intro to existing platforms - existing kits
3. Robotics 101 - DIY version
* Bulding a basic robot from scrach using DC motors and H-bridge
* Square challenge
* Speed control using PWM
4. Robotics 101 - Feedback loops
* IR/Line sensors to make Line follower
* Polling vs Interrupts
* Implementatio of encoders
* Introdcution to PID (optional for beginners)
* Using IMU
5. Mini Project
* Team formation + Ideation report
* Project week - Project mainly focusing on solving the challenge while addressing odometry or kinematics problems. Implementation of your own algorithm to optimise the results.

# Mini project guide
Fork this repository and add your team members as collaborators to your fork. Make sure it is a public repository.

Use the following template to organise your files in your repository
 
    |_lib
        |_ schematics
            |_ components.md
        |_ resources
        |_ videos
        |_ images
        |_ algorithm.md
        |_ ideation.md

    |_src
    |_README.md

#### lib
It is your project library. Create shematics folder and add schema/circuit diagram/s of your mini project. Add components.md file to list all the components you are using.
#### resources 
It consists of all the resources like scientific articles, DIY blogs or tutorials you refered to. It is upto you if you want to maker a folder and add all the .pdf files or just make resources.md file and hyperlink all resources.
#### videos
In this folders upload a video of every stages of development of your project. if adding video is complex, make video.md file and add the link of the video that people can watch.
#### images
Incase if you have any images add them here.
#### algorithm.md
This is a very important file, where you explain your project general algorithm and also include the specifics of your approach to the path planning (usage of flowchart is highly recommended).
#### ideation.md
The ideation report you shared in the google classroom. Use [this](https://docs.google.com/document/d/1_CShynGTKjrCND__M2uXStj70VsBB-udfWfXpMz84Vs/edit) template.
#### src
This folder consists of your arduino or python code.
#### README.md
It is your project readme file, connecting to all files and resources in various folders

# Resources
The overall course [content](https://docs.google.com/presentation/d/1irOeB_RKd-NETgOlSd2deLiXENa9ExU59z8WiRyq_DI/edit#slide=id.gb895fb238d_0_475)
## Github guide
1. GIT [cheatsheet](https://education.github.com/git-cheat-sheet-education.pdf)
2. Getting started with github [Hello World](https://docs.github.com/en/get-started/quickstart/hello-world)
3. [Markdown Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)

## Arduino
1. [Getting started](https://www.arduino.cc/en/Guide)
2. [Arduino software](https://www.arduino.cc/en/software)
3. Arduino for [Ubuntu](https://ubuntu.com/tutorials/install-the-arduino-ide#1-overview)
4. [Installing Libraries](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries)
5. Tutorials from [Adafruit](https://learn.adafruit.com/series/learn-arduino)
6. Monk, Simon. Programming Arduino: Getting Started with Sketches. New York: McGraw-Hill Education, 2016.
7. Tutorial Series for Arduino by Jeremy Blum on youtube.
## Raspberry
1. [Getting started](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up)
2. [Pi Imager](https://www.raspberrypi.com/software/)
3. [Remote access](https://www.raspberrypi.com/documentation/computers/remote-access.html)
4. [Another tutorial for SSH](https://raspberrypi-guide.github.io/networking/connecting-via-ssh)
5. [PI OS documentation](https://www.raspberrypi.com/documentation/computers/os.html)
## Zumo
1. [User guide](https://www.pololu.com/docs/0J57)
2. [library](https://github.com/pololu/zumo-shield-arduino-library)
## Misc
1. [Basic concepts](https://www.electronics-notes.com/articles/basic_concepts/)
2. [A summary of electronics](https://electroagenda.com/en/a-summary-of-electronics/)
3. Millman, Jacob, and Christos C. Halkias. 1972. Integrated electronics: analog and digital circuits and systems. New York: McGraw-Hill. 
4. Thomas F. Schubert; Ernest M. Kim, Fundamentals of Electronics: Book 1 Electronic Devices and Circuit Applications , Morgan & Claypool, 2015.




