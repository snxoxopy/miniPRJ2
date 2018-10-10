/* 
* motor.h
*
* Created: 2018-09-28 오후 2:22:43
* Author: usuzin
*/

#ifndef __MOTOR_H__
#define __MOTOR_H__

#define LEFT_MOTOR_DDR		 DDRB
#define LEFT_foward_PIN		 PORTB5
#define LEFT_back_PIN		 PORTB6
//#define LEFT_tire_forward	 OCR1A
//#define LEFT_tire_back		 OCR1B

#define RIGHT_MOTOR_DDR		 DDRE
#define RIGHT_forward_PIN	 PORTE3
#define RIGHT_back_PIN		 PORTE4
//#define RIGHT_tire_forward	 OCR3A
//#define RIGHT_tire_back		 OCR3B

//모터 회전 방향 설정
#define  ForwardMotor_L()			PORTB =   (1 << LEFT_foward_PIN)
#define  BackwardMotor_L()			PORTB =   (1 << LEFT_back_PIN)

#define  ForwardMotor_R()			PORTE =   (1 << RIGHT_forward_PIN)
#define  BackwardMotor_R()			PORTE =   (1 << RIGHT_back_PIN)

//모터 속도 설정
#define   SpeedMotor_L(sl)		OCR1A = sl	//PB5
#define	  SpeedMotor_LB(bl)		OCR1B = bl	//PB6
		
#define   SpeedMotor_R(sr)		OCR3A = sr	//PE3
#define   SpeedMotor_RB(br)		OCR3B = br	//PE4


class motor
{
	public:
		motor();
		~motor();
		void go(int v);
		void T_left(int v);
		void T_right(int v);
		void back(int v);
		void stop();
	protected:
	private:
		void motor_init(void);
}; //motor

#endif //__MOTOR_H__
