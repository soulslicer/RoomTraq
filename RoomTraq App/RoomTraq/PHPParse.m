//
//  PHPParse.m
//  RoomTraq
//
//  Created by Yaadhav Raaj on 25/2/13.
//  Copyright (c) 2013 Raaj. All rights reserved.
//

#import "PHPParse.h"

@implementation PHPParse


BOOL sensor1=false;
BOOL value=false;
BOOL idx=false;
BOOL entryCount=false;
BOOL timestamp=false;

-(NSMutableDictionary*)returnFinal:(NSString*)urls{
    NSURL* url=[[NSURL alloc]initWithString:urls];
    NSXMLParser* parser=[[NSXMLParser alloc]initWithContentsOfURL:url];
    dict=[[NSMutableDictionary alloc]init];
    tempArray=[[NSMutableArray alloc]init];
    dateArray=[[NSMutableArray alloc]init];
    [parser setDelegate:self];
    [parser parse];
    
    if(dict==NULL)
        NSLog(@"Error in Parsing");
    
    NSLog(@"Parsing Done");
    return dict;
}

-(void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName attributes:(NSDictionary *)attributeDict{
    
    //NSLog(@"run");
    
    if([elementName isEqualToString:@"sensor1"]){
        sensor1=YES;
    }
    
    if([elementName isEqualToString:@"value"]){
        value=YES;
    }
    
    if([elementName isEqualToString:@"id"]){
        idx=YES;
    }
    
    if([elementName isEqualToString:@"entryCount"]){
        entryCount=YES;
    }
    
    if([elementName isEqualToString:@"timestamp"]){
        timestamp=YES;
    }
        
}

- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string{
    
    if(value){
        tempArray=[[NSMutableArray alloc]init];
        value=false;
    }
    
    if(idx){
        [tempArray insertObject:string atIndex:0];
        idx=false;
    }
    
    if(entryCount){
        [tempArray insertObject:string atIndex:1];
        entryCount=false;
    }
    
    if(timestamp){
        [tempArray insertObject:string atIndex:2];
        timestamp=false;
        
        NSArray* z=[string componentsSeparatedByString:@" "];
        NSString* comp=[z objectAtIndex:0];        
        
        //check for key, if not make
        NSArray* arr=[dict objectForKey:comp];
        if(arr==NULL){
            dateArray=[[NSMutableArray alloc]init];
            [dict setObject:dateArray forKey:comp];
        }
        
        [dateArray addObject:tempArray];
        [dict setObject:dateArray forKey:comp];
        timestamp=false;

    }
    
}


- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName{
    
    
}


@end
