# Ideation Report Template
Project Name: How to Train Your Robot (Path Finding)
Team: S3 (Sakshi Sharma, Sayed Mossavi, Sochi Aneke)
Project Link: S3

# 1. Introduction : what do you want to do  
For this final project, S3 plans to program a robot that finds the most efficient path through a maze and evades obstacles along the way.

Square: 8*8 / 50 cm per square

# 2. Market survey / Bibliography (Which algorithm will you use)
We will use the A* algorithm. 

# 3. How you will solve this problem: 
The A* algorithm improves on the Dijkstra shortest path algorithm, by including extra information by way of a heuristic function that determines which paths to explore next. This optimization results in shortest paths being found more quickly.
We will: 
Program the robot to move forward in straight line 
Turning by a 45 or 90 degree angle
Program backwards movement if necessary
Define the speed
Program obstacle evasion
Making it to the goal 
We will program the robot to move around, detect objects in its path, and redirect its path once an object is detected. We will program the robot to find the optimal and most efficient path. 

# 4. Expected List of Features
First, we will need to design and build a robot that is capable of moving through a maze.

Next, we will need to install sensors on our robot that can detect obstacles in its path. Some common sensors that can be used for this purpose include infrared sensors, ultrasonic sensors, and LIDAR sensors.

Once we have our robot hardware set up and our sensors installed, we can begin programming the robot using Arduino code. We will need to use the Arduino libraries for controlling the motors and reading the sensor data.

To find the most efficient path through the maze, our robot will need to use a pathfinding algorithm. Some common algorithms for this purpose include Dijkstra's algorithm and A* search. We can implement these algorithms using Arduino code, or we can use a pre-existing library.

Once our robot has a pathfinding algorithm, we can use the sensor data to detect obstacles in its path and avoid them. This will typically involve modifying the robot's path in real-time based on the sensor readings.

Finally, we can test our robot and fine-tune its performance as needed. This will likely involve a lot of trial and error, as well as making adjustments to the robot's hardware and code.
 

# 5. List of equipment needed (if we need to buy)
We are using a Zumo robot.
Arduino 
Jumper wires
Batteries
IR sensor



# 6. Bibliography
https://www.thezebra.com/resources/home/how-roomba-works/#:~:text=While%20we%20use%20our%20eyes,back%20away%20from%20the%20ledge.
https://neo4j.com/developer/graph-data-science/path-finding-graph-algorithms/
https://www.youtube.com/watch?v=p178eQpDI_E&feature=youtu.be
https://github.com/MikeNourian/Autonomous-Robot-with-Path-Finding-Algorithm/blob/master/main.cpp
https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
https://www.growingwiththeweb.com/2012/06/a-pathfinding-algorithm.html
https://fab.cba.mit.edu/classes/865.21/topics/path_planning/robotic.html
https://www.generationrobots.com/media/user-guide-zumo-robot-for-arduino.pdf



