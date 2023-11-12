// Include necessary libraries

#define ROWS 16
#define COLS 16
#define IR_THRESHOLD 500

#define en_left 5
#define en_right 6
#define left_motor_forward 7
#define left_motor_backward 8
#define right_motor_forward 9 
#define right_motor_backward 10

#define left_sensor 11
#define right_sensor 12 
#define forward_sensor_1 13
#define forward_sensor_2 14

bool visited[ROWS][COLS];

// Function to initialize the visited array
void initializeVisited() {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      visited[i][j] = false;
    }
  }
}

// Function to move the micromouse forward
void moveForward() {
  // Motor control code to move forward
   analogWrite(left_motor_forward, HIGH);
   analogWrite(left_motor_backward, LOW);
   analogWrite(right_motor_forward, HIGH);
   analogWrite(right_motor_backward, LOW);
   
}

// Function to turn the micromouse left
void turnLeft() {
  // Motor control code to turn left
   analogWrite(left_motor_forward, LOW);
   analogWrite(left_motor_backward, HIGH);
   analogWrite(right_motor_forward, HIGH);
   analogWrite(right_motor_backward, LOW);
   
}

// Function to turn the micromouse right
void turnRight() {
  // Motor control code to turn right
     analogWrite(left_motor_forward, HIGH);
   analogWrite(left_motor_backward, LOW);
   analogWrite(right_motor_forward, LOW);
   analogWrite(right_motor_backward, HIGH);
   
}

// Function to read data from IR sensors
int readIRSensorLeft() {
  int left_value = analogRead(left_sensor);
  return (left_value > IR_THRESHOLD) ? 1 : 0;
}

int readIRSensorRight() {
  int right_value = analogRead(right_sensor);
  return (right_value > IR_THRESHOLD) ? 1 : 0;
}

int readIRSensorFront_1() {
  int forward_value_1 = analogRead(forward_sensor_1);
  return (forward_value_1 > IR_THRESHOLD) ? 1 : 0;
}

int readIRSensorFront_2() {
  int forward_value_2 = analogRead(forward_sensor_2);
  return (forward_value_2 > IR_THRESHOLD) ? 1 : 0;
}


// Flood fill algorithm with sensor integration
void floodFill(int row, int col) {
  if (row < 0 || row >= ROWS || col < 0 || col >= COLS || visited[row][col]) {
    return;
  }

  // Mark the current cell as visited
  visited[row][col] = true;

  // Read sensor data to make decisions
  
  int left_value = readIRSensorLeft();
  int right_value = readIRSensorRight();
  int forward_value_1 = readIRSensorFront_1();
  int forward_value_2 = readIRSensorFront_2();


  // Implement logic to decide the next move based on sensor data
  // Adjust motor control actions accordingly

  // Move to adjacent cells (you can customize the order)
  floodFill(row + 1, col);  // Move down
  // Perform motor control actions for the current cell after moving down
  turnLeft();  // Example: Turn left

  floodFill(row - 1, col);  // Move up
  // Perform motor control actions for the current cell after moving up
  turnRight();  // Example: Turn right

  floodFill(row, col + 1);  // Move right
  // Perform motor control actions for the current cell after moving right
  moveForward();  // Example: Move forward

  floodFill(row, col - 1);  // Move left
  // Perform motor control actions for the current cell after moving left
  moveForward();  // Example: Move forward
}

void setup() {
  // Your setup code here
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);

  pinMode(left_sensor, INPUT);
  pinMode(right_sensor, INPUT);
  pinMode(forward_sensor_1, INPUT);
  pinMode(forward_sensor_2, INPUT);

  Serial.begin(9600);

  
}

void loop() {
  // Your main loop code here

  // Example usage of flood fill with sensor integration
  initializeVisited();
  floodFill(0, 0);  // Replace with your actual starting position
}
