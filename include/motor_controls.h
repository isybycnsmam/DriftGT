#ifndef MOTOR_CONTROLS
#define MOTOR_CONTROLS

enum MotorAction
{
    Neutral = 0,
    Stop = 1,
    Forward = 2,
    Backward = 3
};

void init_motor_controls();
void setMotor(int motor, MotorAction action, int speed);

#endif // MOTOR_CONTROLS