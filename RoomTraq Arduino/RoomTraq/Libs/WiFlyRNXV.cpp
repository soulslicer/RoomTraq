/*
 * WiFlyRNXV.cpp
 *
 * Created: 2/19/2013 11:39:21 PM
 *  Author: Raaj
 */ 

#include "WiFlyRNXV.h"


//Constructor-Start listen on uart
WiFlyRNXV::WiFlyRNXV(byte pinReceive, byte pinSend) : uart (pinReceive, pinSend){
	inCommandMode=false;
	wifiStatus=false;
}

void WiFlyRNXV::start(){
	uart.begin(WIFLY_DEFAULT_BAUD_RATE);
	uart.listen();
	uart.flush();
}

void WiFlyRNXV::end(){
	uart.end();
}

//Check if two strings/char* are the same
boolean checkForString(char* responseBuffer,char* compare){
	char * pch=NULL;
	pch = strstr (responseBuffer,compare);
	if(pch==NULL)
	return false;
	else
	return true;
}

//Simply empty the buffer into the a char* and return (64 size)
char* WiFlyRNXV::getBufferResponse(){
	
	//Variables
	char* responseBuffer;
	int  bufpos = 0;											//Buffer position
	char chResponse = 'A';										//Initial character response
	int  bufsize = RESPONSE_BUFFER_SIZE -1;						//terminating null for bufsize
	
	//Reset the buffer
	responseBuffer = (char*) malloc(RESPONSE_BUFFER_SIZE);
	memset (responseBuffer, '\0', bufsize);
	
	//Fill the buffer
	while(uart.available()){
		
		chResponse = uart.read();
		//Serial.print(chResponse);
		if(bufpos<bufsize){
			responseBuffer[bufpos]=chResponse;
			bufpos++;
		}else{
			Serial.println("buffer overflow");
			bufpos=0;
		}
	}	
	
	//Serial.println(responseBuffer);
	Serial.println("");
	return responseBuffer;
}

//Check buffer with a particular 
boolean WiFlyRNXV::checkBufferResponse(char* compareValue,int timeout){
	
	//Variables
	char* responseBuffer;										//Buffer for response
	boolean bufRead = true;										//Finish Reading
	int  bufpos = 0;											//Buffer position
	char chResponse = 'A';										//Initial character response
	int  bufsize = RESPONSE_BUFFER_SIZE -1;						//terminating null for bufsize
	boolean compareSuccess=false;								//Compare Success

	//Reset the buffer
	responseBuffer = (char*) malloc(RESPONSE_BUFFER_SIZE);
	memset (responseBuffer, '\0', bufsize);

	//Fill the buffer
	unsigned long startTime = millis();
	while(bufRead){
		
		//Start getting values
		if(uart.available()){
			chResponse = uart.read();
			
			//Check this, buffer overflow
			if(bufpos<bufsize){
				responseBuffer[bufpos]=chResponse;
				bufpos++;
			}else{
				Serial.println("Buffer overflow");
				bufpos=0;
			}
		}

		//Check for existence of the comparison string, or if timeout stop
		if(checkForString(responseBuffer,compareValue)){
			compareSuccess=true;
			bufRead=false;
		}else if((millis()-startTime)>timeout){
			compareSuccess=false;
			bufRead=false;
		}
	}
	
	Serial.println(responseBuffer);
	uart.flush();
	return compareSuccess;
}	

//Check buffer with a particular
boolean WiFlyRNXV::checkCharResponse(char compareValue,int timeout){
	
	//Variables
	boolean bufRead = true;										//Finish Reading
	char chResponse = 'A';										//Initial character response
	boolean compareSuccess=false;								//Compare Success

	//Fill the buffer
	unsigned long startTime = millis();
	while(bufRead){
		
		//Start getting values
		if(uart.available()){
			chResponse = uart.read();
			if(chResponse=compareValue){
				bufRead=false;
				compareSuccess=true;
			}
		}else if((millis()-startTime)>timeout){
			compareSuccess=false;
			bufRead=false;
		}
	}
	
	//Serial.println(responseBuffer);
	uart.flush();
	return compareSuccess;
}

//Check buffer with a particular
int WiFlyRNXV::compareBufferResponse(char* compareFirst,char* compareSecond){
	
	//Variables
	char* responseBuffer;										//Buffer for response
	boolean bufRead = true;										//Finish Reading
	int  bufpos = 0;											//Buffer position
	char chResponse = 'A';										//Initial character response
	int  bufsize = RESPONSE_BUFFER_SIZE -1;						//terminating null for bufsize
	boolean compareSuccess=false;								//Compare Success
	int compareCase=0;											//Compare Case

	//Reset the buffer
	responseBuffer = (char*) malloc(RESPONSE_BUFFER_SIZE);
	memset (responseBuffer, '\0', bufsize);

	//Fill the buffer
	unsigned long startTime = millis();
	while(bufRead){
		
		//Start getting values
		if(uart.available()){
			chResponse = uart.read();
			//Serial.print(chResponse);
			//Check this, buffer overflow
			if(bufpos<bufsize){
				responseBuffer[bufpos]=chResponse;
				bufpos++;
			}else{
				Serial.println("Buffer overflow");
				bufpos=0;
			}
		}

		//Check for existence of the comparison string, or if timeout stop
		if(checkForString(responseBuffer,compareFirst)){
			compareSuccess=true;
			compareCase=1;
			bufRead=false;
		}if(checkForString(responseBuffer,compareSecond)){
			compareCase=2;
			compareSuccess=true;
			bufRead=false;
		}else if((millis()-startTime)>1000){
			compareCase=0;
			compareSuccess=false;
			bufRead=false;
		}
	}
	
	uart.flush();
	return compareCase;
}

//Enter Command Mode
boolean WiFlyRNXV::EnterCommandMode(){
	uart.flush();
	uart.print(COMMAND_MODE);
	delay(COMMAND_MODE_GUARD_TIME);
	if(checkBufferResponse("CMD",TIMEOUT_TIME))
		inCommandMode=true;
	else
		inCommandMode=false;	
		
	return inCommandMode;
}

//Exit Command Mode
boolean WiFlyRNXV::ExitCommandMode(){
	uart.println("exit");
	delay(COMMAND_MODE_GUARD_TIME);
	inCommandMode=false;
	
	return inCommandMode;
}

//Exit Command Mode
void WiFlyRNXV::RebootWiFly(){
	if(!inCommandMode)	EnterCommandMode();
	delay(100);
	uart.print("reboot\r");
	inCommandMode=false;
}

//Check WiFi Status
boolean WiFlyRNXV::CheckWiFiStatus(){
	
	if(inCommandMode){
		ExitCommandMode();
		delay(1000);
	}
	
	if(checkBufferResponse("OK",TIMEOUT_TIME))
		wifiStatus=true;
	else
		wifiStatus=false;
	
		
	return wifiStatus;

}

void WiFlyRNXV::FactoryRESET(){
	if(!inCommandMode)	EnterCommandMode();
	int delayW=500;
	delay(delayW);
	
	Serial.println("factory RESET"); uart.flush();
	uart.println("factory RESET"); delay(delayW); getBufferResponse();
	Serial.println("reboot"); uart.flush();
	uart.println("reboot"); delay(delayW); getBufferResponse();
	delay(2000);
	Serial.println("Factory RESET done");
	inCommandMode=false;
}

void WiFlyRNXV::EnterAdHoc(){
	
	int delayW=500;
	
	if(!inCommandMode)	EnterCommandMode();
	Serial.println("Attempting cmd mode");
	
	delay(delayW);
	// Setup adhoc network
	Serial.println("set ip address 169.254.1.1"); uart.flush();
	uart.println("set ip address 169.254.1.1"); delay(delayW); //getBufferResponse();
	Serial.println("set ip netmask 255.255.0.0"); uart.flush();
	uart.println("set ip netmask 255.255.0.0"); delay(delayW); //getBufferResponse();
	Serial.println("set ip dhcp 0"); uart.flush();
	uart.println("set ip dhcp 0"); delay(delayW); //getBufferResponse();
	Serial.println("set wlan ssid WiFly-GSX-XX"); uart.flush();
	uart.println("set wlan ssid WiFly-GSX-XX"); delay(delayW); //getBufferResponse();
	Serial.println("set wlan channel 1"); uart.flush();
	uart.println("set wlan channel 1"); delay(delayW); //getBufferResponse();

	// Create adhoc network
	Serial.println("set wlan join 4"); uart.flush();
	uart.println("set wlan join 4"); delay(delayW); //getBufferResponse();
	Serial.println("save"); uart.flush();
	uart.println("save"); delay(delayW); //getBufferResponse();
	Serial.println("reboot"); uart.flush();
	uart.println("reboot"); delay(delayW); //getBufferResponse();
	delay(2000);
	
	inCommandMode=false;
	
	uart.flush();
	Serial.println("Done AdHoc");
}

boolean WiFlyRNXV::AdHocConnected(){
	boolean check=false;
	if(uart.available()) check=checkBufferResponse("Connected",TIMEOUT_TIME);
	if(check){
		Serial.println("Connected!!!");
		return true;
	}else{
		return false;
	}
}

boolean WiFlyRNXV::AdHocEnded(){
	boolean check=false;
	if(uart.available()){	
		 check=true;
		 Serial.println("datarec");
		 delay(4000);
		 uart.flush();
	}		 
	if(check){
		Serial.println("READY!");
		return true;
	}else{
		return false;
	}
}

void WiFlyRNXV::SetHTTP(){
	int delayW=500;
	
	if(!inCommandMode)	EnterCommandMode();
	Serial.println("Attempting cmd mode");
	
	delay(delayW);
	Serial.println("set ip proto 18"); uart.flush();
	uart.println("set ip proto 18"); delay(delayW); //getBufferResponse();
	Serial.println("set dns name www.raaj.homeip.net"); uart.flush();
	uart.println("set dns name www.raaj.homeip.net"); delay(delayW); //getBufferResponse();
	Serial.println("set ip address 0"); uart.flush();
	uart.println("set ip address 0"); delay(delayW); //getBufferResponse();
	Serial.println("set com remote 0"); uart.flush();
	uart.println("set com remote 0"); delay(delayW); //getBufferResponse();

	Serial.println("save"); uart.flush();
	uart.println("save"); delay(delayW); //getBufferResponse();
	Serial.println("exit"); uart.flush();
	uart.println("exit"); delay(delayW); //getBufferResponse();
	delay(2000);
	
	inCommandMode=false;
	Serial.println("Done SetHTTP");
	uart.flush();	
}


char responseArr[128];
void WiFlyRNXV::SendResponse(char* value){
	int delayW=500;
	Serial.println("sendreponse");
	uart.print("$$$");
	
	delay(delayW);
	Serial.println("open www.raaj.homeip.net 80"); uart.flush();
	uart.println("open www.raaj.homeip.net 80"); //delay(delayW); //getBufferResponse();
	//uart.flush();
	
	//wait for open
	boolean xx=checkBufferResponse("*OPEN*",6000);

		Serial.println("port open");
		delay(2000);
		
		char* response="GET /addtoDB.php?count=";
		responseArr[0] = '\0';
		strcat(responseArr, response);
		strcat(responseArr,value);
		uart.print(responseArr);

		boolean pp=checkCharResponse('(',8000);
		if(pp)
			Serial.println("success");
	
	uart.println("exit");
	inCommandMode=false;
}

