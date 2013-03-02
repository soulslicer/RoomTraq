/*
 * DistanceDriver.cpp
 *
 * Created: 2/23/2013 3:03:36 PM
 *  Author: Raaj
 */ 

#include "DistanceDriver.h"

DistanceDriver::DistanceDriver(byte pinReceiveURM1, byte pinSendURM1,byte pinReceiveURM2, byte pinSendURM2){
	urm1.begin(pinReceiveURM1,pinSendURM1,9600); 
	urm1.end();
	urm2.begin(pinReceiveURM2,pinSendURM2,9600);
	urm2.end();
	baseValue=85;
	entryCount=0;
}

bool diffDetect1=false;
byte detectCount1=0;
bool urm1First=false;
bool diffDetect2=false;
byte detectCount2=0;
bool urm2First=false;
bool lock1=false;
bool lock2=false;


int delayP=3;
int detectDef=3;
int distanceThresh=8;

void DistanceDriver::pingCount(){
	
	//Getting Distance
	int urm1Val=0;
	urm1.beginBasic(9600);

	if(urm1.requestMeasurementOrTimeout(DISTANCE, urm1Val)==DISTANCE){
		if(urm1Val>baseValue || urm1Val<0 || urm1Val==-257){
			urm1Val=baseValue;
			urm1.end();
		}else{
			urm1.end();
			delay(delayP);
		}
	}else{
		urm1Val=baseValue;
		urm1.end();
	}	
	
	
	int urm2val=0;
	
	urm2.beginBasic(9600);
	if(urm2.requestMeasurementOrTimeout(DISTANCE, urm2val)==DISTANCE){
		if(urm2val>baseValue || urm1Val<0 || urm2val==-257){
			urm2val=baseValue;
			urm2.end();
		}else{

			urm2.end();
			delay(delayP);
		}
	}else{
		urm2val=baseValue;
		urm2.end();
	}	
	
	
	/*
	Serial.print("Measurement1: ");
	Serial.print(urm1Val);
	Serial.print("  Measurement2: ");
	Serial.print(urm2val);
	Serial.println("");
	*/

	//return;
	
	/*
	1. if baseval-urm1 diff is > 50, trigger bool diffDetect1
	2. on secondrun if diffDetect is true, if baseval-urm1 diff is > 50 again, trigger urm1First true, diffDetect1 to false
	3. if urm1First is true, check if urm1 is back to baseval, by checking baseval-urm<50
	4. ^^ if so, increment entryCount
	
	*/
	//return;
	
	//URM1
	if(lock2==false){
		if(urm1First==true){
			if((urm1Val>distanceThresh) && (urm2val>distanceThresh)){ //user left
				entryCount++;
				urm1First=false;
				lock1=false;
			
				Serial.println("");
				Serial.println("");
				Serial.print("ENTRY: EntryCount: ");
				Serial.print(entryCount);
				Serial.println("");
				Serial.println("");
			
				return;
			}else{
				return;
			}
		}
		if(diffDetect1==true){
			if(urm1Val<distanceThresh){
				
				detectCount1++;
				if(detectCount1>=detectDef){
					urm1First=true;
					diffDetect1=false;
					detectCount1=0;
					Serial.println("***********Trigger urm1*************");
				}
			
				return;
			}else{
				detectCount1=0;
				diffDetect1=false;
				lock1=false;
				return;
			}
		}
		if(urm1Val<distanceThresh){
			//Serial.println("lock1");
			 lock1=true;
			 diffDetect1=true;
		}
	}		
	
	//URM2
	if(lock1==false){
		if(urm2First==true){
			if((urm1Val>distanceThresh) && (urm2val>distanceThresh)){ //user left
				entryCount--;
				urm2First=false;
				lock2=false;
			
				Serial.println("");
				Serial.println("");
				Serial.print("EXIT: EntryCount: ");
				Serial.print(entryCount);
				Serial.println("");
				Serial.println("");
			
				return;
			}else{
				return;
			}
	}
	if(diffDetect2==true){
		if(urm2val<distanceThresh){
			
			detectCount2++;
			if(detectCount2>=detectDef){
				urm2First=true;
				diffDetect2=false;
				detectCount2=0;
				Serial.println("***********Trigger urm2*************");
			}

			return;
		}else{
			detectCount2=0;
			diffDetect2=false;
			lock2=false;
			return;
		}
	}
	if(urm2val<distanceThresh){
		//Serial.println("lock2");
		lock2=true;
		diffDetect2=true;
	}
}	
	
}

void DistanceDriver::setBaseValue(int value){
	baseValue=value;
}

void DistanceDriver::getCount(bool sensor){
	if(sensor==URM1){
		
	}
}