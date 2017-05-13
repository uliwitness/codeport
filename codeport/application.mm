//
//  application.mm
//  codeport
//
//  Created by Uli Kusterer on 13.05.17.
//  Copyright © 2017 Uli Kusterer. All rights reserved.
//

#import "application.hpp"
#import <Cocoa/Cocoa.h>


@interface CDPApplicationDelegate : NSObject <NSApplicationDelegate>
{
	application * cppApplication;
}

@end

@implementation CDPApplicationDelegate

-(id)	initWithCppApplication: (application&)inApp
{
	self = [super init];
	if( self )
	{
		cppApplication = &inApp;
	}
	return self;
}

-(BOOL)	application: (NSApplication *)sender openFile: (NSString *)filename
{
	open_file_event	evt( filename.UTF8String );
	cppApplication->openFile( evt );
	return evt.handled();
}


-(BOOL) applicationOpenUntitledFile: (NSApplication *)sender
{
	open_file_event	evt( "" );
	cppApplication->openFile( evt );
	return evt.handled();
}


-(void)	applicationDidFinishLaunching: (NSNotification *)notification
{
	cppApplication->parseArguments();
	
	event	evt;
	cppApplication->didFinishLaunching( evt );
}


-(void)	applicationWillTerminate: (NSNotification *)notification
{
	event	evt;
	cppApplication->willTerminate( evt );
}


-(IBAction) menuChoice: (NSMenuItem*)sender
{
	action * theItem = (action*)((NSValue*)sender.representedObject).pointerValue;
	action_event	evt( *theItem );
	theItem->onTrigger(evt);
}


-(BOOL) validateMenuItem:(NSMenuItem *)menuItem
{
	if( menuItem.action == @selector(menuChoice:) )
	{
		action * theItem = (action*)((NSValue*)menuItem.representedObject).pointerValue;
		
		return theItem->canTrigger() != false;
	}
	else
		return [self respondsToSelector: menuItem.action];
}

@end


application::application()
{
	mAppDelegate = [[CDPApplicationDelegate alloc] initWithCppApplication: *this];
	[[NSApplication sharedApplication] setDelegate: mAppDelegate];
}


application::~application()
{
	mAppDelegate = nil;
}


void application::parseArguments()
{
	std::string	fileToOpen;
	for( int x = 1; x < mArgC; x++ )
	{
		if( mArgV[x][0] != '-' )
		{
			fileToOpen = mArgV[x];
			open_file_event	evt( fileToOpen );
			openFile( evt );
		}
	}
}


int application::run()
{
	return NSApplicationMain( mArgC, mArgV );
}


void	application::addMenu( menu_ptr inMenu )
{
	[[[NSApplication sharedApplication] mainMenu] addItem: inMenu->mMenu];
	int	x = 0;
	for( NSMenuItem* currItem in inMenu->mMenu.submenu.itemArray )
	{
		currItem.action = @selector(menuChoice:);
		currItem.target = mAppDelegate;
		currItem.representedObject = [NSValue valueWithPointer: &(*inMenu->action_at(x++))];
	}
	mMenus.push_back( inMenu );
}

