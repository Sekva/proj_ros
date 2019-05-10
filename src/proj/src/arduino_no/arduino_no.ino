
#include <ros.h>
#include <geometry_msgs/Point32.h>
#include <std_msgs/Float32.h>
#include <math.h>

ros::NodeHandle  nh;
std_msgs::Float32 norma;
ros::Publisher publicador("arduino_norma", &norma);
float x, y;

void messageCb( const geometry_msgs::Point32& ponto) {
  x = ponto.x;
  y = ponto.y;
 
}

ros::Subscriber<geometry_msgs::Point32> sub("arduino", &messageCb );

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.advertise(publicador);
  nh.subscribe(sub);
}

void loop() {
  norma.data = sqrt(x*x + y*y);
  publicador.publish(&norma);
  nh.spinOnce();
  
  if(norma.data > 400) {
   digitalWrite(13, HIGH-digitalRead(13));   // blink the led 
  } else {
    digitalWrite(13, LOW);   
  }
  delay(1);
}
