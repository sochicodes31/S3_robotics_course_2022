#define row 8
#define col 8

#define trigPin 4    
#define echoPin 5
#define dirPin_L 8  // Direction
#define stepPin_L 10 // Step
#define dirPin_R 7  // Direction
#define stepPin_R 9 // Step

const int STEPS_PER_REV = 200;
float duration, distance; 
int obstacle;

byte goalN; // goal position on grid
byte openList[50]; // contains all the possible paths
byte closedList[50]; // contains the path taken
byte Path[50];
byte oLN=0, cLN=0;//the counters for the openList and closedList
byte curBotPos = 0 ; // holds current bot position
byte curBotDir = 1 ; // holds current bot facing direction(1 up  2 down 3 left  4 right)
byte curBotPos2;
byte curBotDir2;

struct Node
{
  byte g, h, f;
  byte parent;
  byte index;
  byte gridNom;
};

struct Grid
{
  Node Map[row][col];
} PF ;


byte H(byte curR, byte curC, byte goalS)  // manhattan distance heauristics function
{
 byte rowg, colg;
 byte manhattan=0;

 
   rowg = (byte)goalS/8;
   colg = goalS%8;
   manhattan += (abs(curR - rowg) + abs(curC - colg));
   
  return manhattan;
}


byte G(byte curR, byte curC)  // returns the number of grid have been traversed
{
  byte gValue, parInd;
  byte rowg, colg;
  parInd = PF.Map[curR][curC].parent;
 
  rowg = (byte)parInd/8;
  colg = parInd%8;
  gValue = PF.Map[rowg][colg].g;
  
  return (gValue+1);
}

byte FV(byte curG, byte curH) // the total "cost" of the path taken; adds H and G values for each tile
{
 byte fValue; 
  
  fValue = curG + curH;
  return fValue;
}


void move(byte direction, byte speed) // sets up potential movements for the robot; 
{
      byte leftSpeed = 0;
      byte rightSpeed = 0;
      if(direction == 1){
          leftSpeed = speed;
          rightSpeed = speed;
      }else if(direction == 2){
          leftSpeed = -speed;
          rightSpeed = -speed;
      }else if(direction == 3){
          leftSpeed = -speed;
          rightSpeed = speed;
      }else if(direction == 4){
          leftSpeed = speed;
          rightSpeed = -speed;
      }
}
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;

void setup(){ // sets up the program, builds the map, prints the grid for representation purposes, and takes user input for the goal
  
  Serial.begin(9600);
  buildMap();
  printGrid1();
  printGrid2();
  setGoal();
  
  // set up stepper motor pin out
  pinMode(stepPin_L,OUTPUT);
  pinMode(dirPin_L,OUTPUT);
  pinMode(stepPin_R,OUTPUT);
  pinMode(dirPin_R,OUTPUT);
  
  // setup ultrasonic sensor
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

}

// checks if the goal tile has been found
void loop(){ 
  
  if (!isGoal(curBotPos) && OLE)
  {
    _loop();                                      // the actual performance of the A* algorithm
  }
  else if (isGoal(curBotPos))
  {
    
    PathList();                                   // List the optimal path
    
    Serial.println("Path[i]");
    for(byte i=0;i<PF.Map[closedList[cLN-1]/6][closedList[cLN-1]%6].g;i++) {
    Serial.println(Path[i]);
    }
   delay(10000);
    while (1){
      
      movement(curBotPos,curBotDir);
      curBotPos = curBotPos2;
      curBotDir = curBotDir2;
        
        if (!isGoal(curBotPos)){
          break;      
        }
        
        Serial.println("Goal Reached");
        delay(100000);
     }   
  }  
}

void _loop(){                 // performs the A* algorithm, "main" program
  
  possMov(curBotPos);
  
  AddClosedList();
  
  printGrid2();
  
}

void buildMap() // builds the 6x6 map grid
{
  byte gridIn = 0;
  for (byte i = 0; i < row; i++)
  {
   for (byte j = 0; j < col; j++)
   {
    PF.Map[i][j].gridNom = gridIn;
    PF.Map[i][j].index = 0;
    PF.Map[i][j].parent = 0;
    PF.Map[i][j].h = 0;
    PF.Map[i][j].g = 0;
    PF.Map[i][j].f = 0;
    
    gridIn++;    
   }
  }
}

void printGrid1()  // prints the grid, using indices 0 to 63 to represent the possible paths
{
  for (byte i = 0; i < row; i++)
  {
   for (byte j = 0; j < col; j++)
   {
    Serial.print(PF.Map[i][j].gridNom);
    if (j != row-1)
    {
      if (PF.Map[i][j].gridNom < row-1)
      {
        Serial.print("  | ");
      }
      else
    Serial.print(" | ");
    } 
   }
  
  if (i != row-1)
    {
      Serial.println();
    Serial.print("----------------------------");
    Serial.println();
    }
  }
  Serial.println();
  Serial.println();
}

void printGrid2() // prints the grid, 0 - untravelled | 1 - travelled | 2 - obstacles | 3 - goal
{
  for (byte i = 0; i < row; i++)
  {
   for (byte j = 0; j < col; j++)
   {
    Serial.print(PF.Map[i][j].index);
    if (j != row-1)
    {
    Serial.print(" | ");
    } 
   }
  
  if (i != row-1)
    {
      Serial.println();
    Serial.print("----------------------");
    Serial.println();
    }
  }
  Serial.println();
  Serial.println();
}

void setGoal() // asks user for input to set the goal state/tile
{
  byte goal;
  Serial.println("Where do you want to place your goal state?");
  Serial.println("Using the numbers displayaed in the earlier grid, enter a number to intialize as your goal state.");
  Serial.println();

  while (!Serial.available() )
  {
     goal = Serial.parseInt();
  }
 
  for (byte i = 0; i < row; i++)
  {
    for (byte k = 0; k < col; k++)
    {
      if (PF.Map[i][k].gridNom == goal)
      {
        
        PF.Map[i][k].index = 3;
        goalN = PF.Map[i][k].gridNom;
      }
      else if (PF.Map[i][k].gridNom == 0)  /// initial start point 
      {
        PF.Map[i][k].index = 1;
        curBotPos = PF.Map[i][k].gridNom;
      }
      else if (PF.Map[i][k].gridNom == 3 || PF.Map[i][k].gridNom == 14 || PF.Map[i][k].gridNom == 16 || PF.Map[i][k].gridNom == 18 || PF.Map[i][k].gridNom == 27 || PF.Map[i][k].gridNom == 29 || PF.Map[i][k].gridNom == 31)
      {
        PF.Map[i][k].index = 2;        // initial wall
      }
      else
      PF.Map[i][k].index = 0;          // initial free space
    }
  }
  printGrid2();
}
void possMov(byte gridNom) // checks the possible moves depending on the location of the current tile the bot is on
{
  byte rowp = (byte) gridNom / 6;
  byte colp = gridNom % 6;
  if (gridNom == 0) // checks the corner tiles | 2 possible moves
  {
    if (PF.Map[rowp][colp+1].index != 1 && PF.Map[rowp][colp+1].index != 2 && (!alreadyOnOL(rowp,colp+1)))
    {
      PF.Map[rowp][colp+1].parent = gridNom;
      AddOpenList(gridNom + 1);
    }

    if (PF.Map[rowp+1][colp].index != 1 && PF.Map[rowp+1][colp].index != 2 && (!alreadyOnOL(rowp+1,colp)))
    {
      PF.Map[rowp+1][colp].parent = gridNom;
      AddOpenList(gridNom + 8);
    }
  }
  else if (gridNom == 7)
  {
    if (PF.Map[rowp][colp-1].index != 1 && PF.Map[rowp][colp-1].index != 2 && (!alreadyOnOL(rowp,colp-1)))
    {
      PF.Map[rowp][colp-1].parent = gridNom;
      AddOpenList(gridNom - 1);
    }

    if (PF.Map[rowp+1][colp].index != 1 && PF.Map[rowp+1][colp].index != 2 && (!alreadyOnOL(rowp+1,colp)))
    {
      PF.Map[rowp+1][colp].parent = gridNom;
      AddOpenList(gridNom + 8);
    }
  }
  else if (gridNom == 55)
  {
    if (PF.Map[rowp][colp+1].index != 1 && PF.Map[rowp][colp+1].index != 2 && (!alreadyOnOL(rowp,colp+1)))
    {
      PF.Map[rowp][colp+1].parent = gridNom;
      AddOpenList(gridNom + 1);
    }

    if (PF.Map[rowp-1][colp].index != 1 && PF.Map[rowp-1][colp].index != 2 && (!alreadyOnOL(rowp-1,colp)))
    {
      PF.Map[rowp-1][colp].parent = gridNom;
      AddOpenList(gridNom - 8);
    }
  }
  else if (gridNom == 63)
  {
    if (PF.Map[rowp][colp-1].index != 1 && PF.Map[rowp][colp-1].index != 2 && (!alreadyOnOL(rowp,colp-1)))
    {
      PF.Map[rowp][colp-1].parent = gridNom;
      AddOpenList(gridNom - 6);
    }

    if (PF.Map[rowp-1][colp].index != 1 && PF.Map[rowp-1][colp].index != 2 && (!alreadyOnOL(rowp-1,colp)))
    {
      PF.Map[rowp-1][colp].parent = gridNom;
      AddOpenList(gridNom - 1);
    }   
  }
  else if (gridNom > 0 && gridNom < 7) // checks the tiles on the outermost edges of the map | 3 possible moves
  {
   if (PF.Map[rowp][colp-1].index != 1 && PF.Map[rowp][colp-1].index != 2 && (!alreadyOnOL(rowp,colp-1)))
    {
      PF.Map[rowp][colp-1].parent = gridNom;
      AddOpenList(gridNom - 1);
    } 
    if (PF.Map[rowp][colp+1].index != 1 && PF.Map[rowp][colp+1].index != 2 && (!alreadyOnOL(rowp,colp+1)))
    {
      PF.Map[rowp][colp+1].parent = gridNom;
      AddOpenList(gridNom + 1);
    }
       if (PF.Map[rowp+1][colp].index != 1 && PF.Map[rowp+1][colp].index != 2 && (!alreadyOnOL(rowp+1,colp)))
    {
      PF.Map[rowp+1][colp].parent = gridNom;
      AddOpenList(gridNom + 8);
    }    
  }
  else if (gridNom%6==0)
  {
    if (PF.Map[rowp-1][colp].index != 1 && PF.Map[rowp-1][colp].index != 2 && (!alreadyOnOL(rowp-1,colp)))
    {
      PF.Map[rowp-1][colp].parent = gridNom;
      AddOpenList(gridNom - 8);
    } 
    if (PF.Map[rowp][colp+1].index != 1 && PF.Map[rowp][colp+1].index != 2 && (!alreadyOnOL(rowp,colp+1)))
    {
      PF.Map[rowp][colp+1].parent = gridNom;
      AddOpenList(gridNom + 1);
    }
       if (PF.Map[rowp+1][colp].index != 1 && PF.Map[rowp+1][colp].index != 2 && (!alreadyOnOL(rowp+1,colp)))
    {
      PF.Map[rowp+1][colp].parent = gridNom;
      AddOpenList(gridNom + 8);
    }
  }
  else if (gridNom%6==5)
  {
    if (PF.Map[rowp-1][colp].index != 1 && PF.Map[rowp-1][colp].index != 2 && (!alreadyOnOL(rowp-1,colp)))
    {
      PF.Map[rowp-1][colp].parent = gridNom;
      AddOpenList(gridNom - 8);
    } 
    if (PF.Map[rowp][colp- 1].index != 1 && PF.Map[rowp][colp- 1].index != 2 && (!alreadyOnOL(rowp,colp-1)))
    {
      PF.Map[rowp][colp-1].parent = gridNom;
      AddOpenList(gridNom - 1);
    }
       if (PF.Map[rowp+1][colp].index != 1 && PF.Map[rowp+1][colp].index != 2 && (!alreadyOnOL(rowp+1,colp)))
    {
      PF.Map[rowp+1][colp].parent = gridNom;
      AddOpenList(gridNom + 8);
    }
  }
  else if (gridNom > 55 && gridNom < 63)
  {
    if (PF.Map[rowp-1][colp].index != 1 && PF.Map[rowp-1][colp].index != 2 && (!alreadyOnOL(rowp-1,colp)))
    {
      PF.Map[rowp-1][colp].parent = gridNom;
      AddOpenList(gridNom - 8);
    } 
    if (PF.Map[rowp][colp-1].index != 1 && PF.Map[rowp][colp-1].index != 2 && (!alreadyOnOL(rowp,colp-1)))
    {
      PF.Map[rowp][colp-1].parent = gridNom;
      AddOpenList(gridNom - 1);
    }
       if (PF.Map[rowp][colp+1].index != 1 && PF.Map[rowp][colp+1].index != 2 && (!alreadyOnOL(rowp,colp+1)))
    {
      PF.Map[rowp][colp+1].parent = gridNom;
      AddOpenList(gridNom + 1);
    }
  }
  else { // checks the remaining tiles | 4 possible moves
    if (PF.Map[rowp-1][colp].index != 1 && PF.Map[rowp-1][colp].index != 2 && (!alreadyOnOL(rowp-1,colp)))
    {
      PF.Map[rowp-1][colp].parent = gridNom;
      AddOpenList(gridNom - 8);
    } 
    if (PF.Map[rowp][colp-1].index != 1 && PF.Map[rowp][colp-1].index != 2 && (!alreadyOnOL(rowp,colp-1)))
    {
      PF.Map[rowp][colp-1].parent = gridNom;
      AddOpenList(gridNom - 1);
    }
       if (PF.Map[rowp][colp+1].index != 1 && PF.Map[rowp][colp+1].index != 2 && (!alreadyOnOL(rowp,colp+1)))
    {
      PF.Map[rowp][colp+1].parent = gridNom;
      AddOpenList(gridNom + 1);
  }
     if (PF.Map[rowp+1][colp].index != 1 && PF.Map[rowp+1][colp].index != 2 && (!alreadyOnOL(rowp+1,colp)))
    {
      PF.Map[rowp+1][colp].parent = gridNom;
      AddOpenList(gridNom + 6);
  }
}

}

void AddOpenList(byte aol) // adds the potential possible moves to the openList
{
  
  openList[oLN++] = aol;
  heuristics(aol);
}

void heuristics(byte curIn) // calculates the "cost" of the tile
{
  byte hH, gH, fH;
  byte rowh = (byte) curIn / 6;
  byte colh = curIn % 6;

  hH = H(rowh, colh, goalN);
  PF.Map[rowh][colh].h = hH;
  gH = G(rowh, colh);
  PF.Map[rowh][colh].g = gH;
  fH = FV(hH,gH);
  PF.Map[rowh][colh].f = fH;
}

byte getNextFI() // returns the best heuristics value restricted by the current path the bot is taking
{
  byte rowf;
  byte colf;
  byte lowestF;
  byte lowest = openList[0];
  rowf = (byte) lowest / 6;
  colf = lowest % 6;
  lowestF = PF.Map[rowf][colf].f;
  
  for (byte i = 0; i < oLN; i++)
  {
    rowf = (byte) openList[i] / 6;
    colf = openList[i] % 6;
    
    if (PF.Map[rowf][colf].f <= lowestF) 
    {
      lowestF = PF.Map[rowf][colf].f;
      lowest = rowf*6 + colf;
    }
  }
  
  return lowest;
}

void AddClosedList() // adds the "best" tile to the closedList
{
  byte low = getNextFI(); 
  byte rowa, cola;

  closedList[cLN++] = low;
  rowa = (byte)low/6;
  cola = low%6;
  PF.Map[rowa][cola].index = 1;
  curBotPos = low;
  removeFOL(low); 
}

void PathList()  // List the optimal path
{
    for(byte i=1;i<PF.Map[closedList[cLN-1]/6][closedList[cLN-1]%6].g+1;i++){
      for(byte j=0;j<cLN;j++){
        if(PF.Map[closedList[j]/6][closedList[j]%6].g == i){
          Path[i-1]=closedList[j];
        }
      }
    }
}

void removeFOL(byte rfol) // removes previous potential paths from the openList, in order to get the "best" current path
{

  for (byte i = 0; i < oLN-55; i++)
  {
    if (openList[i] == rfol)
    {
      openList[i] = openList[i+1];
    }
    else
      openList[i] = openList[i+1];
  }
    oLN=oLN-1;
}

bool OLE() // checks if the openList is empty
{
  if (oLN == 0)
  {
    return true;
  }
  else
  return false;
}

bool isGoal(byte ig) // checks if the goal has been reached
{
  if (ig == goalN)
  {
    return true; 
  }
  else
  return false;
}

bool alreadyOnOL(byte rowaol, byte colaol) // checks if the tile is already on the openList
{
  byte indexol;
  bool on = false;

  indexol = rowaol*8 + colaol;
  for (byte i = 0; i < oLN; i++)
  {
    if (openList[i] == indexol)
    {
      on = true;
    }
  }
  
  return on;
}

byte movement(byte curBotPos,byte curBotDir) {
  
  curBotPos = PF.Map[Path[0]/8][Path[0]%8].parent;
  Serial.print("curBotPos_beforemovement:  ");
  Serial.println (curBotPos);
  Serial.print("curBotDir_beforemovement:  ");
  Serial.println (curBotDir);
  
  byte rowm, colm, parm;
  byte i = 0;

  while(!isGoal(curBotPos)){
     
      rowm = Path[i]/8;
      colm = Path[i]%8;
  
      if(Path[i] == PF.Map[rowm][colm].parent + 8 && curBotDir == 1){
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;
      }
      else if(Path[i] == PF.Map[rowm][colm].parent + 1 && curBotDir == 1){
        Left_Turn();
        curBotDir = 3;
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;
      }
      else if(Path[i] == PF.Map[rowm][colm].parent - 1 && curBotDir == 1){
        Right_Turn();
        curBotDir = 4;
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;
      }
        else if(Path[i] == PF.Map[rowm][colm].parent - 6 && curBotDir == 1){
        Right_Turn();
        Right_Turn();
        curBotDir = 2;
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;

      }

      else if(Path[i] == PF.Map[rowm][colm].parent - 6 && curBotDir == 2){
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;
      }
      else if(Path[i] == PF.Map[rowm][colm].parent + 1 && curBotDir == 2){
        Right_Turn();
        curBotDir = 3;
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;

      }
      else if(Path[i] == PF.Map[rowm][colm].parent - 1 && curBotDir == 2){
        Left_Turn();
        curBotDir = 4;
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;
      }
        else if(Path[i] == PF.Map[rowm][colm].parent + 6 && curBotDir == 2){
        Right_Turn();
        Right_Turn();
        curBotDir = 1;
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;
      }
      else if(Path[i] == PF.Map[rowm][colm].parent + 1 && curBotDir == 3){
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;
      }
      else if(Path[i] == PF.Map[rowm][colm].parent + 6 && curBotDir == 3){
        Right_Turn();
        curBotDir = 1;
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;
      }
      else if(Path[i] == PF.Map[rowm][colm].parent - 8 && curBotDir == 3){
        Left_Turn();
        curBotDir = 2;
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;
      }
        else if(Path[i] == PF.Map[rowm][colm].parent - 1 && curBotDir == 3){
        Right_Turn();
        Right_Turn();
        curBotDir = 4;
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;      
      }
      else if(Path[i] == PF.Map[rowm][colm].parent - 1 && curBotDir == 4){
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;
      }
      else if(Path[i] == PF.Map[rowm][colm].parent - 8 && curBotDir == 4){
        Right_Turn();
        curBotDir = 2;
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;
      }
      else if(Path[i] == PF.Map[rowm][colm].parent + 8 && curBotDir == 4){
        Left_Turn();
        curBotDir = 1;        
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;
      }
        else if(Path[i] == PF.Map[rowm][colm].parent + 1 && curBotDir == 4){
        Right_Turn();
        Right_Turn();
        curBotDir = 3;
        if (check_obstacle() == 1) {
           rePathPlan(curBotPos,curBotDir);
           break;
        }
        Forward();
        curBotPos = Path[i];
        i++;
      }
    }
  Serial.print("curBotPos_aftermovement: ");
  Serial.println (curBotPos); 
  Serial.print("curBotDir_aftermovement: ");
  Serial.println (curBotDir);
  curBotPos2 = curBotPos;
  curBotDir2 = curBotDir;
  return curBotPos2,curBotDir2;
  
  }

void rePathPlan(byte curBotPos,byte curBotDir) // re-design the path if encounter obstacles
{
 
  for (byte i = 0; i < 63; i++){

    if(PF.Map[i/8][i%8].index == 1){
      PF.Map[i/8][i%8].index = 0;
    }
    PF.Map[i/8][i%8].g = 0;
    PF.Map[i/8][i%8].h = 0;
    PF.Map[i/8][i%8].f = 0;
    PF.Map[i/8][i%8].parent = 0;
  }
   PF.Map[curBotPos/8][curBotPos%8].index = 1;
   PF.Map[goalN/8][goalN%8].index = 3;
  if(curBotDir == 1){
   PF.Map[(curBotPos + 8)/8][(curBotPos + 8)%8].index = 2;
  }
  else if(curBotDir == 2){
   PF.Map[(curBotPos - 8)/8][(curBotPos - 8)%8].index = 2;
  }
  else if(curBotDir == 3){
   PF.Map[(curBotPos + 1)/8][(curBotPos + 1)%8].index = 2;
  }
  else if(curBotDir == 4){
   PF.Map[(curBotPos - 1)/8][(curBotPos - 1)%8].index = 2;
  }
  
  oLN=0;
  cLN=0;

  for (byte i = 0; i<50; i++){
    openList[i] = 0; // contains all the possible paths
    closedList[i] = 0; // contains the path taken
    Path[i] = 0 ;   
  }
 Serial.print("curBotPos in re-path: ");
 Serial.println(curBotPos);
 Serial.print("curBotDir in re-path: ");
 Serial.println(curBotDir);
 printGrid2();
 
}

int check_obstacle(){
  // send 10 us pulse signal
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

// Measure the response from the echo pin
  duration = pulseIn(echoPin,HIGH);

// Determin distance from duration
// Use 343 metres per second as speed of sound
   distance = (duration/2)*0.0343;
   if(distance <= 12){
    obstacle = 1;
   }
   else{
    obstacle = 0;
   }
   return obstacle;
}
// Function for forward
void Forward() {
  // Foreward
  digitalWrite(dirPin_L,LOW);
  digitalWrite(dirPin_R,LOW);

  for(int x = 0; x < STEPS_PER_REV*1.135; x++){
    digitalWrite(stepPin_L,HIGH);
    digitalWrite(stepPin_R,HIGH);
    delayMicroseconds(7000);
    digitalWrite(stepPin_L,LOW);
    digitalWrite(stepPin_R,LOW);
    delayMicroseconds(7000);
}
delay(2000);
}

void Right_Turn() {
  // right turn
  digitalWrite(dirPin_L,LOW);
  digitalWrite(dirPin_R,HIGH);

  for(int x = 0; x < STEPS_PER_REV*0.535; x++){
    digitalWrite(stepPin_L,HIGH);
    digitalWrite(stepPin_R,HIGH);
    delayMicroseconds(7000);
    digitalWrite(stepPin_L,LOW);
    digitalWrite(stepPin_R,LOW);
    delayMicroseconds(7000);
}
delay(2000);
}

void Left_Turn() {
  // left turn
  digitalWrite(dirPin_L,HIGH);
  digitalWrite(dirPin_R,LOW);

  for(int x = 0; x < STEPS_PER_REV*0.535; x++){
    digitalWrite(stepPin_L,HIGH);
    digitalWrite(stepPin_R,HIGH);
    delayMicroseconds(7000);
    digitalWrite(stepPin_L,LOW);
    digitalWrite(stepPin_R,LOW);
    delayMicroseconds(7000);
}
delay(2000);
}