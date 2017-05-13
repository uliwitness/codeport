//
//  menu.hpp
//  codeport
//
//  Created by Uli Kusterer on 13.05.17.
//  Copyright © 2017 Uli Kusterer. All rights reserved.
//

#ifndef menu_hpp
#define menu_hpp

#include "action.hpp"
#include <memory>
#include <vector>


class menu;
typedef std::shared_ptr<menu> menu_ptr;


class menu : public std::enable_shared_from_this<menu>
{
public:
	static menu_ptr createMenu( const std::string& inTitle ) { return std::make_shared<menu>( inTitle ); }
	
	void		addAction( action_ptr inAction );
	action_ptr	action_at( int idx );

	explicit menu( const std::string& inTitle );

protected:
	CDPMenuItemPtr			mMenu;
	std::vector<action_ptr> mActions;
	
	friend class application;
};

#endif /* menu_hpp */
