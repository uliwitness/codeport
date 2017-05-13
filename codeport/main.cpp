//
//  main.cpp
//  codeport
//
//  Created by Uli Kusterer on 13.05.17.
//  Copyright © 2017 Uli Kusterer. All rights reserved.
//

#import "application.hpp"
#include <iostream>


/* Declare the actions that menu items can trigger:
	Each ACTION(foo) below declares a mix-in class named Foo
	that any object that can handle this action should inherit from,
	and in it an onfoo(event&) method that you must override to add
	your behaviour. In addition, you also can override a
		bool canfoo()
	method that returns whether the menu item should be enabled or not.
	
	These actions would be things like "Quit" or "Copy" or "Paste" or
	"Open File".
*/
ACTION(FirstAction)
ACTION(SecondAction)
ACTION(ThirdAction)


/*
	Declare our application subclass and create our menus and items,
	and implement the action of one that is handled at the application level.
*/
class codeport_sample_application : public application, public FirstAction, public ThirdAction
{
public:
	virtual void didFinishLaunching( event& inEvent )
	{
		menu_ptr toolsMenu = menu::createMenu( "Tools" );
		toolsMenu->addActionWithTitle<FirstAction>( "First" );
		toolsMenu->addActionWithTitle<SecondAction>( "Second" );
		toolsMenu->addActionWithTitle<ThirdAction>( "third" );
		addMenu( toolsMenu );
	}
	
	// Implement FirstAction behaviour. It will automatically be enabled:
	virtual void onFirstAction( event& inEvent )	{ std::cout << "First Action Override." << std::endl; mCanThirdAction = !mCanThirdAction; }
	// Don't implement SecondAction at all.
	// Implement ThirdAction but only enable it once the user chooses the first action:
	virtual void onThirdAction( event& inEvent )	{ std::cout << "Third Action Override." << std::endl; }
	virtual bool canThirdAction()					{ return mCanThirdAction; }

protected:
	bool	mCanThirdAction = false;
};


int main( int argc, const char * argv[] )
{
	std::shared_ptr<codeport_sample_application> app( new codeport_sample_application() );
	app->setArguments( argc, argv );
	gFirstHandler = app;	// In a real app, this would be set to the current text field/front window etc. Each handler can have a nextHandler set to which it will forward messages (e.g. text field, window, application).
	return app->run();
}
