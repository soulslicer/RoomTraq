//
//  PHPParse.h
//  RoomTraq
//
//  Created by Yaadhav Raaj on 25/2/13.
//  Copyright (c) 2013 Raaj. All rights reserved.
//

#import <Foundation/Foundation.h>

/************************************************************************
 * PHPParse
 1.This class parses through the data and time objects from
   the getRange php script and returns a dictionary object
 ************************************************************************/

@interface PHPParse : NSObject<NSXMLParserDelegate>{
    NSMutableDictionary* dict;
    NSMutableArray* tempArray;
    NSMutableArray* dateArray;
}

-(NSMutableDictionary*)returnFinal:(NSString*)urls;

@end
