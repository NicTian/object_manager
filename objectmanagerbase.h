#ifndef _OBJECTMANAGERBASE_H_
#define _OBJECTMANAGERBASE_H_

class ObjectManagerBase
{
protected:
	/// Default constructor.
	ObjectManagerBase(void);

	/// Destructor.
	virtual ~ObjectManagerBase(void);

public:
	/**
	 * Explicitly initialize.  Returns 0 on success, -1 on failure due
	 * to dynamic allocation failure (in which case errno is set to
	 * ENOMEM), or 1 if it had already been called.
	 */
	virtual int init(void) = 0;

	/**
	 * Explicitly destroy.  Returns 0 on success, -1 on failure because
	 * the number of fini () calls hasn't reached the number of init ()
	 * calls, or 1 if it had already been called.
	 */
	virtual int fini(void) = 0;

	enum Object_Manager_State
	{
		OBJ_MAN_UNINITIALIZED = 0,
		OBJ_MAN_INITIALIZING,
		OBJ_MAN_INITIALIZED,
		OBJ_MAN_SHUTTING_DOWN,
		OBJ_MAN_SHUT_DOWN
	};

protected:
	/**
	 * Returns 1 before ObjectManagerBase has been constructed.
	 */
	int starting_up_i(void);

	/**
	 * Returns 1 after ObjectManagerBase has been destroyed.
	 */
	int shutting_down_i(void);

	/// State of the Object_Manager;
	Object_Manager_State object_manager_state_;

	bool dynamically_allocated_;
private:
	// Disallow copying by not implementing the following . . .
	ObjectManagerBase(const ObjectManagerBase &);
	ObjectManagerBase &operator=(const ObjectManagerBase &);
};

#endif /* _OBJECTMANAGERBASE_H_ */
