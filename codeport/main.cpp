//
//  main.cpp
//  codeport
//
//  Created by Uli Kusterer on 13.05.17.
//  Copyright © 2017 Uli Kusterer. All rights reserved.
//

#import "application.hpp"
#include <iostream>


ACTION(FirstAction)
ACTION(SecondAction)
ACTION(ThirdAction)


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
	
	virtual void onFirstAction( event& inEvent )	{ std::cout << "First Action Override." << std::endl; mCanThirdAction = !mCanThirdAction; }
	// Implement ThirdAction but only enable it once the user chooses the first action:
	virtual void onThirdAction( event& inEvent )	{ std::cout << "Third Action Override." << std::endl; }
	virtual bool canThirdAction()					{ return mCanThirdAction; }

protected:
	bool	mCanThirdAction = false;
};


int main( int argc, const char * argv[] )
{
	std::shared_ptr<codeport_sample_application> app( new codeport_sample_application() );
	gFirstHandler = app;
	app->setArguments( argc, argv );
	return app->run();
}
