#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
using namespace std;

#define TIME_STEP 32
using namespace webots;

int main(int argc, char **argv) {
  Robot *robot = new Robot();
  DistanceSensor *ds[3];
  char dsNames[3][10] = {"ds_right", "ds_left", "ds_middle"};
  for (int i = 0; i < 3; i++) {
    ds[i] = robot->getDistanceSensor(dsNames[i]);
    ds[i]->enable(TIME_STEP);
  }

  Motor *wheels[4];
  char wheels_names[4][8] = {"wheel1", "wheel2", "wheel3", "wheel4"};
  for (int i = 0; i < 4; i++) {
    wheels[i] = robot->getMotor(wheels_names[i]);
    wheels[i]->setPosition(INFINITY);
    wheels[i]->setVelocity(0.0);
  }
  
  while (robot->step(TIME_STEP) != -1) { 
    double right_ir_val = ds[0]->getValue();
    double mid_ir_val = ds[2]->getValue();
    double left_ir_val = ds[1]->getValue();
    
   cout<<"right_ir_val: "<< right_ir_val<<", mid_ir_val: "<< mid_ir_val<<", left_ir_val: "<< left_ir_val<< endl; 
   // cout<<"mid_ir_val"<< mid_ir_val<< endl; 
   // cout<<"left_ir_val"<< left_ir_val<< endl; 

    double speed=3.0;
    double leftSpeed = speed;
    
    double rightSpeed = speed;
    double threshold=55;
    
    if ((left_ir_val<threshold) && (right_ir_val<threshold) && (mid_ir_val>=threshold)){
       leftSpeed = -speed;
       rightSpeed = -speed;
    }
    
    if ((left_ir_val<threshold) && (right_ir_val>=threshold) && (mid_ir_val>=threshold)){
          leftSpeed = -speed;
          rightSpeed = 0.0;
     
    }
    
    if ((left_ir_val>=threshold) && (right_ir_val<threshold) && (mid_ir_val>=threshold)){
          leftSpeed = 0.0;
          rightSpeed = -speed;

    }
    if ((left_ir_val>=threshold) && (right_ir_val<threshold) && (mid_ir_val<threshold)){
          leftSpeed = 0.0;
          rightSpeed = -speed;

    }
    if ((left_ir_val<threshold) && (right_ir_val>=threshold) && (mid_ir_val<threshold)){
                  leftSpeed = -speed;
                  rightSpeed = 0.0;
    }

    if ((left_ir_val<threshold) && (right_ir_val<threshold) && (mid_ir_val<threshold)){
              leftSpeed = -speed;
             rightSpeed = -speed;
    }
    wheels[0]->setVelocity(leftSpeed);
    wheels[1]->setVelocity(rightSpeed);
    wheels[2]->setVelocity(leftSpeed);
    wheels[3]->setVelocity(rightSpeed);
  }
  delete robot;
  return 0;  // EXIT_SUCCESS
}