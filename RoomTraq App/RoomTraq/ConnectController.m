//
//  ConnectController.m
//  RoomTraq
//
//  Created by Yaadhav Raaj on 21/2/13.
//  Copyright (c) 2013 Raaj. All rights reserved.
//

#import "ConnectController.h"
#import "SVProgressHUD.h"


@interface ConnectController ()

@end

@implementation ConnectController

-(void)printErrorMessage:(NSString*)msg{
    UIAlertView* alert=[[UIAlertView alloc]initWithTitle:@"Error" message:msg delegate:nil cancelButtonTitle:@"Okay" otherButtonTitles:nil, nil];
    [alert show];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(IBAction)dismmis:(id)sender{
    [self dismissModalViewControllerAnimated:YES];
}

- (void)viewDidLoad
{
    wiFly=[[SetUpWiFly alloc]init];
    wiFly.connectController=self;
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (IBAction)performConnection:(id)sender{
    NSLog(@"Perform connection");
    
    if([self.username.text isEqualToString:@""] || [self.password.text isEqualToString:@""]){
        [SVProgressHUD showErrorWithStatus:@"No Entry"];
        return;
    }
    
    wiFly.username=self.username.text;
    wiFly.pass=self.password.text;
    [wiFly performConnection];
}

- (IBAction)sendBuf:(id)sender{
    NSLog(@"sendbuf");
    [wiFly sendBuf];
}


@end
