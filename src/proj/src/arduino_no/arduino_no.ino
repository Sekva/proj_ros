
#include <ros.h>
#include <geometry_msgs/Point32.h>

ros::NodeHandle  nh;


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
  nh.subscribe(sub);
}

void loop()
{  
  if( ((int) x) % 5 == 2) {
    digitalWrite(13, HIGH-digitalRead(13));
  }
  nh.spinOnce();
  delay(1);
}
