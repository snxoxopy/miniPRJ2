/* 
* motor.h
*
* Created: 2018-09-28 오후 2:22:43
* Author: usuzin
*/

#ifndef __MOTOR_H__
#define __MOTOR_H__

#define LEFT_MOTOR_DDR		 DDRB
#define LEFT_foward_PIN		 PORTB3
#define LEFT_back_PIN		 PORTB4
#define LEFT_tire_forward	 OCR3A
#define LEFT_tire_back		 OCR3B

#define RIGHT_MOTOR_DDR		 DDRE
#define RIGHT_forward_PIN	 PORTE5
#define RIGHT_back_PIN		 PORTE6
#define RIGHT_tire_forward	 OCR1B
#define RIGHT_tire_back		 OCR1A

//모터 회전 방향 설정
#define  ForwardMotor_L()			PORTB =   (1 << LEFT_foward_PIN)
#define  BackwardMotor_L()			PORTB =   (1 << LEFT_back_PIN)
#define  ForwardMotor_R()			PORTE =   (1 << RIGHT_forward_PIN)
#define  BackwardMotor_R()			PORTE =   (1 << RIGHT_back_PIN)

//모터 속도 설정
#define   SpeedMotor_L(sl)		OCR3A = sl
#define   SpeedMotor_R(sr)		OCR1B = sr

class motor
{
	public:
		motor();
		~motor();
		void left_go(int v);
		void right_go(int v);
		void stop();
		//void back();
	protected:
	private:
		void motor_init(void);
}; //motor

#endif //__MOTOR_H__
