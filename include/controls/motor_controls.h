#ifndef MOTOR_CONTROLS
#define MOTOR_CONTROLS

enum MotorAction
{
    Neutral = 0,
    Stop = 1,
    Forward = 2,
    Backward = 3
};

void initMotorControls();

void turnOffAllMotors();
void setMotor(unsigned int motor_index, unsigned int action, unsigned int speed);
bool validateSetMotorParameters(unsigned int motor_index, unsigned int action, unsigned int speed);

#endif // MOTOR_CONTROLS