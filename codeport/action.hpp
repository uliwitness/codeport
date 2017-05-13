//
//  action.h
//  codeport
//
//  Created by Uli Kusterer on 13.05.17.
//  Copyright © 2017 Uli Kusterer. All rights reserved.
//

#include "event.hpp"
#include <string>
#include <functional>
#include <memory>


#if __OBJC__
@class NSMenuItem;
typedef NSMenuItem * CDPMenuItemPtr;
#else
typedef struct NSMenuItem * CDPMenuItemPtr;
#endif


class action_handler;
class action;


typedef std::shared_ptr<action> action_ptr;
typedef std::weak_ptr<action_handler> action_handler_ptr;


extern action_handler_ptr gFirstHandler;


#define ACTION(n)	class n : public virtual action_handler\
					{\
					public:\
						virtual	void onAction( event& inEvent, n* dummy )	{ on ## n(inEvent); } \
						virtual	void on ## n( event& ) = 0;\
						virtual	bool canDoAction( n* dummy )	{ return can ## n(); } \
						virtual	bool can ## n()					{ return true; }\
					};




class action_handler
{
public:
	virtual ~action_handler() {}
	
	action_handler_ptr	nextHandler()									{ return mNextHandler; }
	void				setNextHandler( action_handler_ptr inHandler )	{ mNextHandler = inHandler; }

protected:
	action_handler_ptr	mNextHandler;
};


class action : public std::enable_shared_from_this<action>
{
public:
	static action_ptr createAction( const std::string & inName ) { return std::make_shared<action>(inName); }
	
	virtual void	onTrigger( action_event& inEvent )	{ inEvent.setHandled(false); }
	virtual bool	canTrigger()						{ return false; }
	
	explicit action( const std::string & inName );
	virtual ~action();

protected:
	CDPMenuItemPtr						mMenuItem;
	
	friend class menu;
};


template<class action_handler_sub> class action_for : public action
{
public:
	static action_ptr createAction( const std::string & inName ) { return std::make_shared<action_for<action_handler_sub>>(inName); }
	
	virtual void	onTrigger( action_event& inEvent ) override
	{
		std::shared_ptr<action_handler> currHandler = gFirstHandler.lock();
		while( currHandler )
		{
			action_handler_sub * theSub = dynamic_cast<action_handler_sub*>(&(*currHandler));
			if( theSub && theSub->canDoAction( theSub ) )
			{
				theSub->onAction( inEvent, theSub );
				if( inEvent.handled() )
					break;
			}
			currHandler = currHandler->nextHandler().lock();
		}
	}
	virtual bool	canTrigger() override
	{
		std::shared_ptr<action_handler> currHandler = gFirstHandler.lock();
		while( currHandler )
		{
			action_handler_sub * theSub = dynamic_cast<action_handler_sub*>(&(*currHandler));
			if( theSub )
			{
				if( theSub->canDoAction( theSub ) )
					return true;
			}
			currHandler = currHandler->nextHandler().lock();
		}
		return false;
	}

	explicit action_for( const std::string & inName ) : action(inName) {}
};
