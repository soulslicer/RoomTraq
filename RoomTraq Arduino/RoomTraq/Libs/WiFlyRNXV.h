/*
 * WiFlyRNXV.h
 *
 * Created: 2/19/2013 11:29:18 PM
 *  Author: Raaj
 */ 

#ifndef WIFLYRNXV_H_
#define WIFLYRNXV_H_

/************************************************************************
 * WiFly
 
 1. Clean WiFly serial driver written from scratch
 2. Used to interface with main class to send and receive data
 ************************************************************************/

//Include Paths
#include <SoftwareSerial.h>
#include <Streaming.h>
#include <avr/pgmspace.h>

//RX TX Pins
#define ARDUINO_RX_PIN				2
#define ARDUINO_TX_PIN				3

//Default ports as set in WiFly
#define WIFLY_DEFAULT_REMOTE_PORT	80
#define WIFLY_DEFAULT_LOCAL_PORT	2000
#define WIFLY_DEFAULT_BAUD_RATE		9600

//Char Buffer Sizes for Command and Response
#define COMMAND_BUFFER_SIZE			64
#define SMALL_COMMAND_BUFFER_SIZE	20
#define RESPONSE_BUFFER_SIZE		80
#define INDICATOR_BUFFER_SIZE		16

//CMD Wait Times based on manual
#define COMMAND_MODE_GUARD_TIME 	300
#define DEFAULT_WAIT_TIME			1000UL
#define ATTN_WAIT_TIME				1000UL
#define JOIN_WAIT_TIME 				10000UL
#define TIMEOUT_TIME				3000

//Define commands
const char* const COMMAND_MODE="$$$";
const char* const COMMAND_EXIT="exit";

using namespace std;

class WiFlyRNXV{

	public:
	WiFlyRNXV(byte pinReceive, byte pinSend);					//Constructor with Pins for UART
	SoftwareSerial uart;										//SoftwareSerial driver
	
	void start();
	void end();
	void RebootWiFly();
	void EnterAdHoc();
	void FactoryRESET();
	void SetHTTP();
	void SendResponse(char* value);
	boolean AdHocConnected();
	boolean AdHocEnded();
	boolean EnterCommandMode();
	boolean ExitCommandMode();
	boolean CheckWiFiStatus();
	

	private:
	boolean inCommandMode;
	boolean wifiStatus;
	char* getBufferResponse();
	boolean checkBufferResponse(char* compareValue,int timeout);
	boolean checkCharResponse(char compareValue,int timeout);
	int compareBufferResponse(char* compareFirst,char* compareSecond);

};



#endif /* WIFLYRNXV_H_ */