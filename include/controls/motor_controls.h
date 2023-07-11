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

void setMotor(unsigned int motor, unsigned int action, unsigned int speed);
bool validateSetMotorParameters(unsigned int motor, unsigned int actionId, unsigned int speed);

#endif // MOTOR_CONTROLS