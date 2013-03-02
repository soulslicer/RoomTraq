//
//  ConnectController.h
//  RoomTraq
//
//  Created by Yaadhav Raaj on 21/2/13.
//  Copyright (c) 2013 Raaj. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SetUpWiFly.h"

/************************************************************************
 * ConnectController
 1.View controller for the set-up page
 2.Calls SetUpWiFly telnet functions
 ************************************************************************/

@interface ConnectController : UIViewController{
    SetUpWiFly* wiFly;
}

-(IBAction)dismmis:(id)sender;
-(IBAction)performConnection:(id)sender;

-(void)printErrorMessage:(NSString*)msg;

@property(nonatomic,strong)UILabel* label;
@property(nonatomic,strong)IBOutlet UITextField* username;
@property(nonatomic,strong)IBOutlet UITextField* password;

@end
