//
//  event.hpp
//  codeport
//
//  Created by Uli Kusterer on 13.05.17.
//  Copyright © 2017 Uli Kusterer. All rights reserved.
//

#ifndef event_hpp
#define event_hpp

#include <string>


class action;


class event
{
public:
	void	setHandled( bool inState )	{ mHandled = inState; }
	bool	handled()					{ return mHandled; }

protected:
	bool	mHandled = true;
};


class open_file_event : public event
{
public:
	open_file_event( const std::string& inPath ) : mPath(inPath) {}
	
	const std::string	path()	{ return mPath; }
	
protected:
	std::string	mPath;
};


class action_event : public event
{
public:
	action_event( action& inSender ) : mSender(inSender) {}
	
	const action&	sender()	{ return mSender; }
	
protected:
	action&	mSender;
};


#endif /* event_hpp */
