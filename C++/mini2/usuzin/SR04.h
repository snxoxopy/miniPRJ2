/* 
* SR04.h
*
* Created: 2018-10-10 오후 4:27:08
* Author: kccistc
*/


#ifndef __SR04_H__
#define __SR04_H__

#define PRESCALER 1024

class SR04
{

//functions
public:
	SR04();
	~SR04();
	void SR04_init(void);
	unsigned int measure_distance(void);
	
protected:
private:
	//SR04( const SR04 &c );
	//SR04& operator=( const SR04 &c );

}; //SR04

#endif //__SR04_H__
