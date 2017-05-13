//
//  menu.cpp
//  codeport
//
//  Created by Uli Kusterer on 13.05.17.
//  Copyright © 2017 Uli Kusterer. All rights reserved.
//

#include "menu.hpp"
#import <Cocoa/Cocoa.h>


menu::menu( const std::string& inTitle )
{
	NSString * macTitle = [NSString stringWithUTF8String: inTitle.c_str()];
	NSMenu * theMenu = [[NSMenu alloc] initWithTitle: macTitle];
	mMenu = [[NSMenuItem alloc] initWithTitle: macTitle action: Nil keyEquivalent: @""];
	[mMenu setSubmenu: theMenu];
}


void	menu::addAction( action_ptr inAction )
{
	[mMenu.submenu addItem: inAction->mMenuItem];
	mActions.push_back(inAction);
}


action_ptr	menu::action_at( int idx )
{
	return mActions[idx];
}
