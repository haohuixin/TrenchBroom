//
//  WadLoader.h
//  TrenchBroom
//
//  Created by Kristian Duske on 20.01.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

extern NSString* const EndOfStreamException;

@class Wad;

@interface WadLoader : NSObject {
    uint8_t intbuffer[4];
}

- (Wad *)loadFromData:(NSData *)someData;

@end
