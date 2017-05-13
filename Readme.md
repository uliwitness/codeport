#CodePort

##What is it?

A test for how one could implement an AppKit-style responder
chain in C++, as part of a cross-platform framework.


##Structure

The main.cpp file contains all app-specific code that should
compile using only a C++ compiler.

application.mm, event.cpp, action.mm, menu.mm contain the
macOS-specific implementation of our cross-platform API.


##Actions

An action is a menu item, or something else that can trigger
a response in the responder chain. A menu is made up of a
list of actions. Each action has an onTrigger() method that
is called when the menu item is chosen, and a canTrigger()
method that is used to determine whether to enable this menu item.

###Example action

Imagine you were implementing your application's edit menu. Your
goal is to create one menu item (i.e. an action object) in your
menu bar, and to have it trigger a method somewhere in the responder
chain. To do this in codeport, we first declare our mix-in class for
this action using the action macro:

	ACTION(CopyAction)
	
Then we create a menu item that is associated with this action on
application startup, in our application class:

	class copy_sample_application : public application
	{
	public:
		virtual void didFinishLaunching( event& inEvent )
		{
			menu_ptr toolsMenu = menu::createMenu( "Edit" );
			toolsMenu->addActionWithTitle<CopyAction>( "Copy" );
			addMenu( toolsMenu );
		}
	};

Then, in any object in the responder chain, we just add our mix-in class
and implement the action's onCopyAction(event&) method. Optionally, we can
also implement the canCopyAction() method to enable/disable the item:

	class text_field : public view, public CopyAction
	{
	public:
		virtual void	onCopyAction( event& inEvent ) override;
		virtual bool	canCopyAction() override;
	};

If you get called for an action, and you want to pass the call on to the
next handler in the responder chain (e.g. because you just want to modify
an action before triggering it), you can use inEvent.setHandled(false) to
inform the caller that you wish to pass on the event.

