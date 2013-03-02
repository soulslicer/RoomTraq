//
//  SetUpWiFly.h
//  RoomTraq
//
//  Created by Yaadhav Raaj on 21/2/13.
//  Copyright (c) 2013 Raaj. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GCDAsyncSocket.h"

/************************************************************************
 * SetUpWiFly
 1.This class interfaces with the WiFly chip and set's it's parameters
 2.iOS Device must be connected to the WiFly Ad-Hoc Network
 ************************************************************************/

@class ConnectController;
@interface SetUpWiFly : NSObject{
    ConnectController* connectController;
    GCDAsyncSocket *asyncSocket;
    NSTimer* timer;
}

@property(nonatomic,strong)ConnectController* connectController;
@property(nonatomic,strong)NSString* username;
@property(nonatomic,strong)NSString* pass;

- (void)performConnection;
- (void)sendBuf;



@end
