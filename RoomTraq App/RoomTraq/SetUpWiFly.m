//
//  SetUpWiFly.m
//  RoomTraq
//
//  Created by Yaadhav Raaj on 21/2/13.
//  Copyright (c) 2013 Raaj. All rights reserved.
//

#import "SetUpWiFly.h"
#import "ConnectController.h"
#import "SVProgressHUD.h"

@implementation SetUpWiFly
@synthesize connectController;
@synthesize username;
@synthesize pass;

//Preset WiFly parameters
NSString* serverAdd=@"169.254.1.1";
uint16_t port = 2000;

//Timeout
-(void)timeOut{
    NSLog(@"Timed out");
    [timer invalidate];
    [asyncSocket disconnect];
    [SVProgressHUD dismiss];
    [SVProgressHUD showErrorWithStatus:@"Error try again"];
}

//Start timeout timer
- (void)startTimer{
    timer=[NSTimer scheduledTimerWithTimeInterval:4
                                     target:self
                                   selector:@selector(timeOut)
                                   userInfo:nil
                                    repeats:YES];
}

//Attempts to telnet to WiFly
- (void)performConnection
{
    asyncSocket = [[GCDAsyncSocket alloc] initWithDelegate:self delegateQueue:dispatch_get_main_queue()];
    NSError *error = nil;

    if (![asyncSocket connectToHost:serverAdd onPort:port error:&error])
    {
        NSLog(@"Unable to connect due to invalid configuration: %@", error);
    }
    else
    {
        NSLog(@"Connecting...IP:%@, port:%i", serverAdd, port);
    }
    
    [self startTimer];
    [SVProgressHUD showWithStatus:@"Connecting.."];
}

//Connection Established
- (void)socket:(GCDAsyncSocket *)sock didConnectToHost:(NSString *)host port:(UInt16)port
{
    [timer invalidate];
    NSLog(@"socket:%p didConnectToHost:%@ port:%hu", sock, host, port);
    [sock readDataWithTimeout:-1 tag:0];
    [self sendBuf];
    
}

//Writing
- (void)socket:(GCDAsyncSocket *)sock didWriteDataWithTag:(long)tag
{
    NSLog(@"socket:didWriteDataWithTag:");
    [sock readDataWithTimeout:-1 tag:0];
    
}

//Display response from WiFly
- (void)socket:(GCDAsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag
{
    NSString *response = [[NSString alloc] initWithData:data  encoding:NSASCIIStringEncoding];
    NSLog(@"read response:%@", response);
    [sock readDataWithTimeout:-1 tag:0];
    
}

//Write serial to WiFly via telnet
-(void)writeData:(NSString*)command{
    NSLog(@"write: %@",command);
    NSData *requestData = [command dataUsingEncoding:NSASCIIStringEncoding];
    [asyncSocket writeData:requestData withTimeout:-1.0 tag:0];
}

//Writes preset username and password
- (void)sendBuf
{
    [self writeData:@"$$$"];
    NSString* buildSSID=[NSString stringWithFormat:@"set wlan ssid %@\r",username];
    [self writeData:buildSSID];
    NSString* buildPass=[NSString stringWithFormat:@"set wlan phrase %@\r",pass];
    [self writeData:buildPass];

    [self writeData:@"set wlan join 1\r"];
    [self writeData:@"set wlan channel 0\r"];
    [self writeData:@"set ip dhcp 1\r"];
    [self writeData:@"save\r"];
    [self writeData:@"reboot\r"];
    
    [SVProgressHUD dismiss];
    [SVProgressHUD showSuccessWithStatus:@"RoomTraq Set"];
    
}

@end
