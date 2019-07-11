#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_
#include "objectmanagerbase.h"
#include "clearup.h"

class ObjectManager : public ObjectManagerBase
{
public:
	ObjectManager (void);
	~ObjectManager (void);
	/**
	* Explicitly initialize (construct the singleton instance of) the
	* ObjectManager.  Returns 0 on success, -1 on failure, and 1
	* if it had already been called.
	*/
	virtual int init (void);

	/**
	* Explicitly destroy the singleton instance of the
	* ObjectManager.  Returns 0 on success, -1 on failure, and 1
	* if it had already been called.
	*/
	virtual int fini (void);

	/**
	* Returns 1 before the ObjectManager has been constructed.
	*/
	static int starting_up (void);

	/**
	* Returns 1 after the ObjectManager has been destroyed.
	*/
	static int shutting_down (void);

	/**
    * Register an Cleanup object for cleanup at process termination.
	*/
	static int at_exit (Clearup *object, void *param = 0);

	static int at_exit (void *object,
		CLEANUP_FUNC cleanup_hook,
		void *param = 0);

	static int remove_at_exit(void *object);

	static ObjectManager *instance(void);

	enum Preallocated_Object
	{
		PREALLOCATED_OBJECTS  // This enum value must be last!
	};

private:
	/// Register an object or array for deletion at program termination.
	/// See description of static version above for return values.
	int at_exit_i(void *object, CLEANUP_FUNC cleanup_hook, void *param);

	/// Remove an object for deletion at program termination.
	/// See description of static version above for return values.
	int remove_at_exit_i(void *object);

	/// Disallow copying by not implementing the following . . 
	ObjectManager (const ObjectManager &);
	ObjectManager &operator= (const ObjectManager &);

private:
	ExitInfo exit_info_;
	static ObjectManager *instance_;
};
#endif /* _OBJECTMANAGER_H_ */
