//
//  application.hpp
//  codeport
//
//  Created by Uli Kusterer on 13.05.17.
//  Copyright © 2017 Uli Kusterer. All rights reserved.
//


#pragma once


#include "event.hpp"
#include "menu.hpp"
#include <stddef.h>
#include <memory>


#if __OBJC__
@class CDPApplicationDelegate;
typedef CDPApplicationDelegate * CDPApplicationDelegatePtr;
#else
typedef struct CDPApplicationDelegate * CDPApplicationDelegatePtr;
#endif


class application
{
public:
	application();
	virtual ~application();
	
	void setArguments( int argc, const char** argv ) { mArgC = argc; mArgV = argv; }
	
	int run();
	
	virtual void	didFinishLaunching( event& inEvent )	{ inEvent.setHandled(false); }
	virtual void	willTerminate( event& inEvent )			{ inEvent.setHandled(false); }
	virtual void	openFile( open_file_event& inEvent )	{ inEvent.setHandled(false); }
	
	void	addMenu( menu_ptr inMenu );
	
	void	parseArguments();

protected:
	CDPApplicationDelegatePtr	mAppDelegate;
	int							mArgC = 0;
	const char			**		mArgV;
	std::vector<menu_ptr>		mMenus;
};
