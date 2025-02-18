
#include "ti_msp_dl_config.h"                       // LINE FOLLOWING ROBOT WITHOUT A SPEED CONTROL

#define IRSensor1              (DL_GPIO_PIN_12) // LEFT pin
#define IOMUX_IRSENSOR_1       (IOMUX_PINCM29)

#define IRSensor2              (DL_GPIO_PIN_10) // RIGHT pin
#define IOMUX_IRSENSOR_2       (IOMUX_PINCM27)

// Motor M1 Configuration
#define MOTOR_13               (DL_GPIO_PIN_13)
#define IOMUX_MOTOR_13         (IOMUX_PINCM30)

#define MOTOR_14               (DL_GPIO_PIN_14)
#define IOMUX_MOTOR_14         (IOMUX_PINCM31)

// Motor M2 Configuration
#define MOTOR_23               (DL_GPIO_PIN_23)
#define IOMUX_MOTOR_23         (IOMUX_PINCM51)

#define MOTOR_24               (DL_GPIO_PIN_24)
#define IOMUX_MOTOR_24         (IOMUX_PINCM52)

#define Motor_PORT             (GPIOB)


void delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < (ms * 1000); i++);
}


int main(void) {

    SYSCFG_DL_init();


    DL_GPIO_initDigitalInput(IOMUX_IRSENSOR_1);
    DL_GPIO_initDigitalInput(IOMUX_IRSENSOR_2);


    DL_GPIO_initDigitalOutput(IOMUX_MOTOR_13);
    DL_GPIO_initDigitalOutput(IOMUX_MOTOR_14);
    DL_GPIO_initDigitalOutput(IOMUX_MOTOR_23);
    DL_GPIO_initDigitalOutput(IOMUX_MOTOR_24);

    DL_GPIO_enableOutput(Motor_PORT, MOTOR_13);
    DL_GPIO_enableOutput(Motor_PORT, MOTOR_14);
    DL_GPIO_enableOutput(Motor_PORT, MOTOR_23);
    DL_GPIO_enableOutput(Motor_PORT, MOTOR_24);

    int leftSensor;
    int rightSensor;
    while (1) {
        leftSensor = DL_GPIO_readPins(Motor_PORT, IRSensor1);
        rightSensor = DL_GPIO_readPins(Motor_PORT, IRSensor2);


        if (!leftSensor  && !rightSensor ) {

            DL_GPIO_setPins(Motor_PORT, MOTOR_13);
            DL_GPIO_clearPins(Motor_PORT, MOTOR_14);
            DL_GPIO_setPins(Motor_PORT, MOTOR_23);
            DL_GPIO_clearPins(Motor_PORT, MOTOR_24);
            delay_ms(1000);
            DL_GPIO_clearPins(Motor_PORT, MOTOR_13);
            DL_GPIO_clearPins(Motor_PORT, MOTOR_14);
            DL_GPIO_clearPins(Motor_PORT, MOTOR_23);
            DL_GPIO_clearPins(Motor_PORT, MOTOR_24);
            delay_ms(1000); //



        } else if (leftSensor && !rightSensor ) {

            DL_GPIO_setPins(Motor_PORT, MOTOR_13);
            DL_GPIO_clearPins(Motor_PORT, MOTOR_14);
            DL_GPIO_clearPins(Motor_PORT, MOTOR_23);
            DL_GPIO_clearPins(Motor_PORT, MOTOR_24);

        }

        else if (!leftSensor && rightSensor) {

            DL_GPIO_clearPins(Motor_PORT, MOTOR_13);
            DL_GPIO_clearPins(Motor_PORT, MOTOR_14);
            DL_GPIO_setPins(Motor_PORT, MOTOR_23);
            DL_GPIO_clearPins(Motor_PORT, MOTOR_24);

        }


         else {

            DL_GPIO_clearPins(Motor_PORT, MOTOR_13);
            DL_GPIO_clearPins(Motor_PORT, MOTOR_14);
            DL_GPIO_clearPins(Motor_PORT, MOTOR_23);
            DL_GPIO_clearPins(Motor_PORT, MOTOR_24); /        }

    }
}







#include "ti_msp_dl_config.h"              // LINE FOLLOWING ROBOT WITH USING SPEED CONTROL MAKE A SMOOTH RUN ON THE TRACK

#define IRSensor1              (DL_GPIO_PIN_12) // LEFT pin
#define IOMUX_IRSENSOR_1       (IOMUX_PINCM29)

#define IRSensor2              (DL_GPIO_PIN_10) // RIGHT pin
#define IOMUX_IRSENSOR_2       (IOMUX_PINCM27)

// Motor M1 Configuration
#define MOTOR_13               (DL_GPIO_PIN_13)
#define IOMUX_MOTOR_13         (IOMUX_PINCM30)

#define MOTOR_14               (DL_GPIO_PIN_14)
#define IOMUX_MOTOR_14         (IOMUX_PINCM31)

// Motor M2 Configuration
#define MOTOR_23               (DL_GPIO_PIN_23)
#define IOMUX_MOTOR_23         (IOMUX_PINCM51)

#define MOTOR_24               (DL_GPIO_PIN_24)
#define IOMUX_MOTOR_24         (IOMUX_PINCM52)

#define Motor_PORT             (GPIOB)

// Improved delay function (approximate microseconds)
void delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < (ms * 1000); i++);
}


void updatePWM(int count1,int count2){
    DL_TimerG_stopCounter(PWM_0_INST);
    DL_TimerG_setCaptCompUpdateMethod(PWM_0_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_0_INST, count1, DL_TIMER_CC_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_0_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_0_INST, count2, DL_TIMER_CC_1_INDEX);
    DL_TimerG_startCounter(PWM_0_INST);  // Start the PWM counter
}

int main(void) {
    SYSCFG_DL_init();

    DL_GPIO_initDigitalInput(IOMUX_IRSENSOR_1);
    DL_GPIO_initDigitalInput(IOMUX_IRSENSOR_2);

    DL_TimerG_stopCounter(PWM_0_INST);


    DL_TimerG_setCaptCompUpdateMethod(PWM_0_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_0_INST, 199, DL_TIMER_CC_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_0_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_0_INST, 199, DL_TIMER_CC_1_INDEX);

    int leftSensor;
    int rightSensor;
    while (1) {
            int count1,count2;

        leftSensor = DL_GPIO_readPins(Motor_PORT, IRSensor1);
        rightSensor = DL_GPIO_readPins(Motor_PORT, IRSensor2);

        if (!leftSensor  && !rightSensor ) {
            updatePWM(500,500);
        } else if (leftSensor && !rightSensor ) {
            updatePWM(500,999);
        }

        else if (!leftSensor && rightSensor) {
            updatePWM(999,500);
        }
         else {
         }
    }
}


