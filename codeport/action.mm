//
//  action.m
//  codeport
//
//  Created by Uli Kusterer on 13.05.17.
//  Copyright © 2017 Uli Kusterer. All rights reserved.
//

#import "action.hpp"
#import <Cocoa/Cocoa.h>


action_handler_ptr gFirstHandler;


action::action( const std::string & inName )
{
	mMenuItem = [[NSMenuItem alloc] initWithTitle: [NSString stringWithUTF8String: inName.c_str()] action: Nil keyEquivalent: @""];
}


action::~action()
{
	mMenuItem = nil;
}
