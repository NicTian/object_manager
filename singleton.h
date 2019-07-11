#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "objectmanager.h"

template <class TYPE>
class Singleton: public Clearup
{
public:
	/// Global access point to the Singleton.
	static TYPE *instance();

	/// Cleanup method to destroy the Singleton.
	virtual void cleanup (void *param = 0);

	/// Explicitly delete the Singleton instance.
	static void close ();

protected:
	/// Default constructor.
	Singleton(void){}

	/// Contained instance.
	TYPE instance_;

	/// Pointer to the Singleton instance.
	static Singleton<TYPE> *singleton_;

	/// Get pointer to the Singleton instance.
	static Singleton<TYPE> *&instance_i()
	{
		return singleton_;
	}
};


template<class TYPE>
Singleton<TYPE> *Singleton<TYPE>::singleton_ = NULL;

template<class TYPE>
TYPE* Singleton<TYPE>::instance()
{
	Singleton<TYPE> *&singleton = Singleton<TYPE>::instance_i();
	if (singleton == NULL)
	{
		if (ObjectManager::starting_up() || ObjectManager::shutting_down())
		{
			singleton = new Singleton<TYPE>();
		}
		else
		{
			//static LOCK *lock = 0;
			//lock first
			if (singleton == NULL)
			{
				singleton = new Singleton<TYPE>();
				ObjectManager::at_exit(singleton);
			}
		}
	}
    return &singleton->instance_;
}

template<class TYPE>
void Singleton<TYPE>::cleanup (void *param)
{
	ObjectManager::remove_at_exit(param);
	delete this;
	Singleton<TYPE>::instance_i() = NULL;
}

template<class TYPE>
void Singleton<TYPE>::close()
{
	Singleton<TYPE> *&singleton = Singleton<TYPE>::instance_i();
	if (singleton)
	{
		singleton->cleanup();
		Singleton<TYPE>::instance_i() = NULL;
	}
};

#endif /* _SINGLETON_H_ */
