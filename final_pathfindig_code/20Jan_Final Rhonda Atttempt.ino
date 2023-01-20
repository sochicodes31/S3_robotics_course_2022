// libraries
#include <ZumoShield.h>

//Zumo robot set-up
ZumoMotors motors;

//14 steps, 15 decisions to make
#define PATH_LEN 15 

//speeds of wheels for forward movement and turns
#define TURN_SPEED      382
#define DURATION_FORWARD     1000
#define LEFT_SPEED 200
#define RIGHT_SPEED 200

char orientation;
//grid path from the Google Classroom, 0's represent available squares, 1's represent obstacles
int grid[8][8]=	{
         {0,0,0,0,1,0,0,1},
				 {0,0,1,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0},
				 {0,1,0,1,0,0,0,1},
				 {0,0,0,0,0,0,0,0},
				 {0,1,0,0,1,1,0,0},
         {0,0,0,0,0,0,0,0},
         {0,0,0,1,1,0,0,0},
         };

void setup() {
  Serial.begin(9600);
}

//functions for how to move Rhonda the robot
void backward() {
   motors.setSpeeds(-LEFT_SPEED, -RIGHT_SPEED); //move backward
   delay(DURATION_FORWARD);
}
void forward() {
  motors.setSpeeds(LEFT_SPEED, RIGHT_SPEED); //move forward
   delay(DURATION_FORWARD);
}
void turn_right() {
  motors.setSpeeds(LEFT_SPEED, -RIGHT_SPEED); //turn right
   delay(TURN_SPEED);
}
void turn_left() {
  motors.setSpeeds(-LEFT_SPEED, RIGHT_SPEED); //turn left
   delay(TURN_SPEED);
}
void go_right() { //turn right, move forward, re-orient north
  turn_right();
   forward(); 
   turn_left();
}
void go_left() { //turn left, move forward, re-orient north
  turn_left();
   forward(); 
   turn_right();
}

//code a path that avoids obstacles defined in photo on Classroom
int path[PATH_LEN][2] = { //array is 14 steps with 2 variables x,y 
  {0,0},
  {1,0},
  {2,0},
  {2,1},
  {3,1},
  {4,1},
  {4,2},
  {4,3},
  {5,3},
  {5,4},
  {5,5},
  {6,5},
  {6,6},
  {6,7},
  {7,7}
};

//sets up current and next positions
int runPath(int curX,int curY,int nextX,int nextY ){
  int returnValue = 1;

//goNext tells Rhonda how to make decisions for which direction to move within the grid
    char direction = goNext(curX, curY, nextX, nextY);

    if (direction == 'r'){
        go_right();
    }
    else if (direction == 'l'){
        go_left();
    }
    else if (direction == 'f'){
        forward();
    }
  return returnValue;
}

char goNext(int x,int y,int w,int z){
    if (x == w && y < z){
        return 'f';
        }
    if (x == w && y > z){
        return 'b';
        }
    if (x < w && y == z){
        return 'l';
        }
    if (x > w && y == z){
        return 'r';
        }
}
int count = 0;

void loop() { //decision making loop
  if(count == 0){
    for(int i = 0; i < PATH_LEN -1 ; i++){
          int currentX =  path[i][0];
          int currentY = path[i][1];
          if(i == PATH_LEN -1){ // goal reached
            break;
          }      
          int nextX = path[i+1][0];
          int nextY = path[i+1][1];
      
        runPath(currentX, currentY, nextX, nextY); 
      }
      count++;
    }
}