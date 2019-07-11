#ifndef _CLEARUP_H_
#define _CLEARUP_H_
#include <list>

typedef void (*CLEANUP_FUNC)(void *object, void *param);

class Clearup
{
public:
	/// No-op constructor.
	Clearup(void);

	/// Destructor.
	virtual ~Clearup(void);

	/// Cleanup method that, by default, simply deletes itself.
	virtual void cleanup(void *param = 0);
};

extern "C" void cleanupDestroyer(Clearup *, void *param = 0);

class ClearInfoNode
{
public:
	ClearInfoNode();
	ClearInfoNode(void *object, CLEANUP_FUNC cleanup_hook, void *param);
	~ClearInfoNode();

	/// Equality operator.
	bool operator==(const ClearInfoNode &o) const;

	/// Inequality operator.
	bool operator!=(const ClearInfoNode &o) const;

	void* object() {return object_;}

	CLEANUP_FUNC cleanup_hook() {return cleanup_hook_;}

	void *param () {return param_;}
private:
	/// Point to object that gets passed into the <cleanup_hook_>.
	void *object_;

	/// Cleanup hook that gets called back.
	CLEANUP_FUNC cleanup_hook_;

	/// Parameter passed to the <cleanup_hook_>.
	void *param_;
};

class ExitInfo
{
public:
  /// Default constructor.
  ExitInfo();

  /// Destructor.
  ~ExitInfo();

  /// Use to register a cleanup hook.
  int at_exit_i (void *object, CLEANUP_FUNC cleanup_hook, void *param);

  /// Look for a registered cleanup hook object.  Returns true if already
  /// registered, false if not.
  bool find (void *object);

  /// Remove a registered cleanup hook object.  Returns true if removed
  /// false if not.
  bool remove (void *object);

  /// Call all registered cleanup hooks, in reverse order of
  /// registration.
  void call_hooks ();

private:
  /**
   * Keeps track of all registered objects.
   */
  std::list<ClearInfoNode> registered_objects_;
};


#endif /* _CLEARUP_H_ */
