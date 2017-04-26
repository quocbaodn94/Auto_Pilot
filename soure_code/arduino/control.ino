#include <Wire.h> 
#include <Servo.h>
Servo motor;
Servo servo;
float lastmillis = 0;
int rpm = 1;
int revs = 0;
float curSpeed = 0;
int motorSpeed;
String inAngle = "";    // biến inString dùng để lưu giá trị từ input
int angle;

void setup() {
  // Mở cổng Serial với mức baudrate 115200
  Serial.begin(115200);
  motor.attach(9);
  servo.attach(10);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, rpm_fan, FALLING);
  lastmillis = millis()/1000.0;
  for (motorSpeed = 1500;motorSpeed <= 1680;motorSpeed  = motorSpeed + 10)
    {
      motor.writeMicroseconds(motorSpeed);
      delay(100);
    }
    delay(1000);
    motor.writeMicroseconds(1670);
}
/*void runMotor(int inSpeed){
  for (
}*/

void loop() {
  // Đọc giá trị từ Serial
  //motor.writeMicroseconds(1670);
  if (millis() - lastmillis*1000 >= 1000){ //Uptade every one second, this will be like reading frecuency
      detachInterrupt(0);
      rpm = revs * 60 / 5;  
      // Speed = 2*pi*r × RPM × (60/1000) km/hr
      // Here radius(r) = 0.03 metres
      curSpeed = (2*3.1415926536*0.03*rpm*60)/1000; 
      // lines to print the above values     
      // Show speeds
      Serial.print( curSpeed ); // this now shows mm/sec with no remainder
      Serial.print( " km/h" );
      Serial.println( );
      revs = 0; 
      lastmillis = millis()/1000.0;
      attachInterrupt(0, rpm_fan, FALLING);
      }
   
    // Nếu inChar là một ký tự xuống dòng. Ta in kết quả ra
      
    
}
void rpm_fan(){
  revs++;
}
void serialEvent()
{
   while(Serial.available()){
      char inChar = Serial.read(); 
      if(inChar != '.'){
      inAngle = inAngle + inChar;
      }
      else{
        angle = -inAngle.toInt();
        if(angle < 45 && angle > -45){
          angle=map(angle,-90,90,0,180);
          servo.write(angle);
          motor.writeMicroseconds(1670);
        }
        inAngle = "";
      }
     if(inChar == '*'){
       motor.writeMicroseconds(1500);
       delay(100);
       servo.write(90);
       
       break;
     }
   }
}
