# Robotics course 2022

Authors: Kevin Lhoste & Rajeev Mylapalli

This is the repository of the [LPI](https://www.learningplanetinstitute.org/en) [Dgital Master](https://master.learningplanetinstitute.org/en/digital) "Robotics" course 2022-2023 final projects.

# Course description
1. Bootcamp: Arduino and Electronics
..* Shitty robots - no expereince with coding or electronics required (building remote control robots using servos, RC receover, battery and some trash like cardboard, plastic bottels, cans, wood etc)
..* Introduction to Arduino
..* Environment setup (installing ide and trouble shooting issue with serial port)
..* Basic electronics (open & close circuits, analog vs digital signals, building basic circuits on bread board)
..* Using code to play with components (led, buzzer, ldr etc)
2. Robotics 101 - Introduction
..* Lecture + discussion
... Introduction to robotics, applications, examples and some of the main problem statements of robotics.
..* Schematics of Robots used/built during the course
..* Intro to sensors and actuators - DIY version
..* Intro to existing platforms - existing kits
3. Robotics 101 - DIY version
..* Bulding a basic robot from scrach using DC motors and H-bridge
..* Square challenge
..* Speed control using PWM
4. Robotics 101 - Feedback loops
..* IR/Line sensors to make Line follower
..* Polling vs Interrupts
..* Implementatio of encoders
..* Introdcution to PID (optional for beginners)
..* Using IMU
5. Mini Project
..* Team formation + Ideation report
..* Project week
... Project mainly focusing on solving the challenge while addressing odometry or kinematics problems. Implementation of your own algorithm to optimise the results.

# Mini project guide
Fork this repository and add your team members as collaborators to your fork. Make sure it is a public repository.

Use the following template to organise your files
root
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

..* lib
... it is your project library. create shematics folder and add schema/circuit diagram/s of your mini project
... add components.md file to list all the components you are using
..* resources 
... consists of all the resources like scientific articles, DIY blogs or tutorials you refered to.
... it is upto you if you want to maker a folder and add all the .pdf files or just make resources.md file and hyperlink all resources
..* videos
... in this folders upload a video of every stages of development of your project. if adding video is complex, make video.md file and add the link of the video that people can watch
..* images
... incase if you have any images add them here
..* algorithm.md
... This is a very important file, where you explain your project general algorithm and also include the specifics of your approach to the path planning (usage of flowchart is highly recommended)
..* ideation.md
... the ideation report you shared in the google classroom. Use [this](https://docs.google.com/document/d/1_CShynGTKjrCND__M2uXStj70VsBB-udfWfXpMz84Vs/edit) template.
..* src
... This folder consists of your arduino or python code.
..* README.md
... your project readme file, connecting to all files and resources in various folders

# Resources
The overall course [content](https://docs.google.com/presentation/d/1irOeB_RKd-NETgOlSd2deLiXENa9ExU59z8WiRyq_DI/edit#slide=id.gb895fb238d_0_475)
## Github guide
..* GIT [cheatsheet](https://education.github.com/git-cheat-sheet-education.pdf)
..* Getting started with github [Hello World](https://docs.github.com/en/get-started/quickstart/hello-world)
..* [Markdown Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)

## Arduino
..* [Getting started](https://www.arduino.cc/en/Guide)
..* [Arduino software](https://www.arduino.cc/en/software)
..* Arduino for [Ubuntu](https://ubuntu.com/tutorials/install-the-arduino-ide#1-overview)
..* [Installing Libraries](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries)
..* Tutorials from [Adafruit](https://learn.adafruit.com/series/learn-arduino)
..* Monk, Simon. Programming Arduino: Getting Started with Sketches. New York: McGraw-Hill Education, 2016.
..* Tutorial Series for Arduino by Jeremy Blum on youtube.
## Raspberry
..* [Getting started](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up)
..* [Pi Imager](https://www.raspberrypi.com/software/)
..* [Remote access](https://www.raspberrypi.com/documentation/computers/remote-access.html)
..* [Another tutorial for SSH](https://raspberrypi-guide.github.io/networking/connecting-via-ssh)
..* [PI OS documentation](https://www.raspberrypi.com/documentation/computers/os.html)
## Zumo
..* [User guide](https://www.pololu.com/docs/0J57)
..* [library](https://github.com/pololu/zumo-shield-arduino-library)
## Misc
..* [Basic concepts](https://www.electronics-notes.com/articles/basic_concepts/)
..* [A summary of electronics](https://electroagenda.com/en/a-summary-of-electronics/)
..* Millman, Jacob, and Christos C. Halkias. 1972. Integrated electronics: analog and digital circuits and systems. New York: McGraw-Hill. 
..* Thomas F. Schubert; Ernest M. Kim, Fundamentals of Electronics: Book 1 Electronic Devices and Circuit Applications , Morgan & Claypool, 2015.




