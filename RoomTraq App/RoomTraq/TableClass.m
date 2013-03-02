//
//  TableClass.m
//  RoomTraq
//
//  Created by Yaadhav Raaj on 25/2/13.
//  Copyright (c) 2013 Raaj. All rights reserved.
//

#import "TableClass.h"
#import "SVProgressHUD.h"
#import "PHPParse.h"

@interface TableClass ()

@end

@implementation TableClass
@synthesize labelCount,segment,datePicker,endDate,startDate,table;

/////////////////EVENT HANDLERS////////////////////

-(IBAction)selectorChange:(id)sender{
    
}

-(IBAction)dismmis:(id)sender{
    NSLog(@"dismiss");
    [self dismissModalViewControllerAnimated:YES];
}

-(IBAction)refresh:(id)sender{
    NSLog(@"refresh");
    [self refreshData];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (IBAction)dateRange:(id)sender{
    NSLog(@"daterange");
}

-(IBAction)dateChanged:(id)sender{
    NSLog(@"%d",segment.selectedSegmentIndex);
    NSDate* date=datePicker.date;
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"yyyy-MM-dd%20hh:mm:ss"];
    NSString *stringFromDate = [formatter stringFromDate:date];
    NSLog(@"%@",stringFromDate);
    
    if(segment.selectedSegmentIndex==0)
        startDate=stringFromDate;
    else
        endDate=stringFromDate;
    
    NSString *path1 = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
    NSString* plistpath1 = [path1 stringByAppendingPathComponent:@"vars.plist"];
    
    NSArray* arr=[[NSArray alloc]initWithObjects:startDate,endDate ,nil];
    [arr writeToFile:plistpath1 atomically:YES];
}

/////////////////CONNECTION////////////////////

NSURLConnection* connection1;
NSURLConnection* connection2;
NSData* responseData;
NSDictionary* json;
-(void)refreshData{
    [SVProgressHUD show];
    NSMutableURLRequest *request =
    [[NSMutableURLRequest alloc] initWithURL:
     [NSURL URLWithString:@"http://raaj.homeip.net/getCountLast.php"]];
    connection1=[[NSURLConnection alloc] initWithRequest:request delegate:self];
    
    NSLog(@"CONNECTION2");
    parse=[[PHPParse alloc]init];
    allNames=NULL;
    allNames=[[NSMutableDictionary alloc]init];
    keys=[[NSArray alloc]init];
    
    NSString *path2 = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
    NSString* plistpath2 = [path2 stringByAppendingPathComponent:@"vars.plist"];
    NSArray* arr=[[NSArray alloc]initWithContentsOfFile:plistpath2];
    startDate=[arr objectAtIndex:0];
    endDate=[arr objectAtIndex:1];
    
    NSString* build=[NSString stringWithFormat:@"http://raaj.homeip.net/getRange.php?start=%@&end=%@",startDate,endDate];
    
    NSLog(@"%@",build);
    allNames=[parse returnFinal:build];

    NSString *path1 = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
    NSString* plistpath1 = [path1 stringByAppendingPathComponent:@"aa.plist"];
    
    bool x=[allNames writeToFile:plistpath1 atomically:YES];
    if(x) NSLog(@"written");
    
    allNames=[[NSMutableDictionary alloc]initWithContentsOfFile:plistpath1];
    
    keys=[allNames allKeys];
    table.delegate=self;
    [table reloadData];
    NSLog(@"updated");

}

- (void)connection:(NSURLConnection*)connection didReceiveResponse:(NSURLResponse *)response
{
    NSLog(@"Did Receive Response %@", response);
    responseData = [[NSMutableData alloc]init];
}
- (void)connection:(NSURLConnection*)connection didReceiveData:(NSData*)data
{
    responseData=data;
}
- (void)connection:(NSURLConnection*)connection didFailWithError:(NSError*)error
{
    NSLog(@"Did Fail");
}
- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    NSLog(@"Did Finish");
    [SVProgressHUD dismiss];
    
    if(connection==connection1){
    NSString* newStr = [[NSString alloc] initWithData:responseData
                                             encoding:NSUTF8StringEncoding];
    NSLog(@"%@",newStr);
        labelCount.text=newStr;
    }
}

////////////////////////////CONNECTION////////////////////


- (void)viewDidLoad
{
    NSString *path1 = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
    NSString* plistpath1 = [path1 stringByAppendingPathComponent:@"aa.plist"];
    NSMutableDictionary *dict = [[NSMutableDictionary alloc]
                          initWithContentsOfFile:plistpath1];
    
    if(dict==NULL)
        NSLog(@"error");
    
    allNames = dict;
    
    keys=[dict allKeys];
    
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

#pragma mark -
#pragma mark Table View Data Source Methods

// Customize the number of sections in the table view.
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    NSLog(@"%d",[keys count]);
    return [keys count];
}

// Customize the number of rows in the table view.
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    //---check the current year based on the section index---
    NSString *year = [keys objectAtIndex:section];
    
    NSArray *movieSection = [allNames objectForKey:year];
    
    //---return the number of movies for that year as the number of rows in that
    // section ---
    return [movieSection count];
	
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *SectionsTableIdentifier = @"SectionsTableIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:
							 SectionsTableIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc]
                initWithStyle:UITableViewCellStyleSubtitle
                reuseIdentifier:SectionsTableIdentifier];
    }

    NSString *year = [keys objectAtIndex:[indexPath section]];
    NSArray *movieSection = [allNames objectForKey:year];
    NSArray* final=[movieSection objectAtIndex:[indexPath row]];
    
    NSString* count=[NSString stringWithFormat:@"Count: %@",[final objectAtIndex:1]];
    cell.textLabel.text = count;
    NSString* time=[NSString stringWithFormat:@"Count: %@",[final objectAtIndex:2]];
    cell.detailTextLabel.text = time;

	
    return cell;
}

- (NSString *)tableView:(UITableView *)tableView
titleForHeaderInSection:(NSInteger)section {
	//---get the year as the section header---
	NSString *year = [keys objectAtIndex:section];
    return year;
}
//
//- (NSArray *)sectionIndexTitlesForTableView:(UITableView *)tableView {
//	return keys;
//}

@end
