#define RF1 2
#define RF2 3

#define RB1 4
#define RB2 5

#define LF1 6
#define LF2 7

#define LB1 8
#define LB2 9

String receivedData = "";




void setup() {
  Serial.begin(9600);
  Serial.println("Ready to receive data");
}

void loop() {
  while (Serial.available() > 0) {
    char incomingChar = Serial.read();  

    // Check for end of line character
    if (incomingChar == '\n') {
      processCommand(receivedData);  // Process the complete string
      receivedData = "";            // Clear the string for the next command
    } else {
      receivedData += incomingChar;  // Append the character to the string
    }
  }
}

void processCommand(String command) {
  // Print the received command for debugging
  Serial.print("Received command: ");
  Serial.println(command);

  // Example: Parse linear and angular velocity from the command
  if (command.startsWith("L") && command.indexOf("A") > 0) {
    String linear = command.substring(1, command.indexOf("A"));
    String angular = command.substring(command.indexOf("A") + 1);

    float linearVelocity = linear.toFloat();
    float angularVelocity = angular.toFloat();

    // Print the parsed values
    // Serial.print("Throttle: ");
    // Serial.println(linearVelocity);
    // Serial.print("Steering: ");
    // Serial.println(angularVelocity);

    if(linearVelocity==1.0){
      whole_move_forward();
    }
    else if(linearVelocity==-1.0){
      whole_move_backward();
    }
    else{
      full_stop();
    }

    if(angularVelocity==1.0){
      whole_right_rotation();
    }
    else if(angularVelocity==-1.0){
      whole_left_rotation();
    }
    else{
      full_stop();
    }

    // Add your logic to control motors or actuators here
  } else {
    Serial.println("Invalid command format!");
  }
}


void whole_move_forward(){
  Serial.println("Rover going forward");
  move_forward(RF1, RF2);
  move_forward(LF1, LF2);
  move_forward(RB1, RB2);
  move_forward(LB1, LB2);
  delay(2000);
  full_stop();
}

void whole_move_backward(){
  Serial.println("Rover going backward");
  move_backward(RF1, RF2);
  move_backward(LF1, LF2);
  move_backward(RB1, RB2);
  move_backward(LB1, LB2);
  delay(2000);
  full_stop();
}


void whole_right_rotation(){
  Serial.println("Rover going right");
  move_forward(LF1, LF2);
  move_forward(LB1, LB2);
  move_backward(RF1, RF2);
  move_backward(RB1, RB2);
  delay(2000);
  full_stop();
}

void whole_left_rotation(){
  Serial.println("Rover going left");
  move_forward(RF1, RF2);
  move_forward(RB1, RB2);
  move_backward(LF1, LF2);
  move_backward(LB1, LB2);
  delay(2000);
  full_stop();
}



void move_forward(int pin1,int pin2){
  analogWrite(pin1,70);
  analogWrite(pin2,0);
}

void move_backward(int pin1, int pin2){
  analogWrite(pin1,0);
  analogWrite(pin2,70);
}

void full_stop(){
  stop(RF1,RF2);
  stop(LF1,LF2);
  stop(RB1,RB2);
  stop(LB1,LB2);
}

void stop(int pin1, int pin2){
  analogWrite(pin1,0);
  analogWrite(pin2,0);
}