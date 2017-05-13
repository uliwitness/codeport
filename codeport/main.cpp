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


class codeport_sample_application : public application, public FirstAction
{
public:
	virtual void didFinishLaunching( event& inEvent )
	{
		menu_ptr toolsMenu = menu::createMenu( "Tools" );
		action_ptr firstItem = action_for<FirstAction>::createAction( "First" );
		toolsMenu->addAction( firstItem );
		action_ptr secondItem = action_for<SecondAction>::createAction( "Second" );
		toolsMenu->addAction( secondItem );
		addMenu( toolsMenu );
	}
	
	virtual void onFirstAction( event& inEvent )	{ std::cout << "First Action Override." << std::endl; }
};


int main( int argc, const char * argv[] )
{
	std::shared_ptr<codeport_sample_application> app( new codeport_sample_application() );
	gFirstHandler = app;
	app->setArguments( argc, argv );
	return app->run();
}
