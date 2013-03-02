//
//  TableClass.h
//  RoomTraq
//
//  Created by Yaadhav Raaj on 25/2/13.
//  Copyright (c) 2013 Raaj. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PHPParse.h"

/************************************************************************
 * TableClass
 1.View controller for Table View
 2.Displays last count and pulls table from server
 ************************************************************************/

@interface TableClass : UIViewController<UITableViewDataSource, UITableViewDelegate, UISearchBarDelegate>{
    
    //Table objects
    UITableView *table;
    NSMutableDictionary *allNames;
    NSArray *keys;
    
    //Server objects
    NSURLConnection* connection1;
    NSURLConnection* connection2;
    NSData* responseData;
    NSDictionary* json;
    PHPParse* parse;
    
    //Start-end dates
    NSString* startDate;
    NSString* endDate;
}

@property (nonatomic,strong)NSString* startDate;
@property (nonatomic,strong)NSString* endDate;

@property (nonatomic,strong) IBOutlet UITableView *table;
@property (nonatomic,strong)IBOutlet UILabel* labelCount;
@property(nonatomic,strong)IBOutlet UIDatePicker* datePicker;
@property(nonatomic,strong)IBOutlet UISegmentedControl* segment;

-(IBAction)dismmis:(id)sender;
-(IBAction)refresh:(id)sender;
-(IBAction)dateRange:(id)sender;
-(IBAction)selectorChange:(id)sender;
-(IBAction)dateChanged:(id)sender;



@end
