#include "objectmanager.h"

ObjectManager* ObjectManager::instance_ = NULL;

ObjectManager::ObjectManager()
{
    if (instance_ == NULL)
		instance_ = this;
	init();
}

ObjectManager::~ObjectManager()
{
	dynamically_allocated_ = false;   // Don't delete this again in fini()
	fini();
}

int ObjectManager::init()
{
	if (starting_up_i())
	{
		object_manager_state_ = OBJ_MAN_INITIALIZING;
		if (this == instance_)
		{
			//Allocate the preallocated object instances
		}
		object_manager_state_ = OBJ_MAN_INITIALIZED;
		return 0;
	}
	else
	{
		return 1;
	}
}

int ObjectManager::fini()
{
	if (shutting_down_i())
	{
		return object_manager_state_ == OBJ_MAN_SHUT_DOWN  ?  1  :  -1;
	}
	object_manager_state_ = OBJ_MAN_SHUTTING_DOWN;
	exit_info_.call_hooks();
	if (this == instance_)
	{
		// Cleanup the dynamically preallocated objects
	}
	object_manager_state_ = OBJ_MAN_SHUT_DOWN;
	if (dynamically_allocated_)
		delete this;
	if (this == instance_)
        instance_ = NULL;
	return 0;
}

int ObjectManager::starting_up()
{
	return ObjectManager::instance_ ? instance_->starting_up_i() : 1;
}

int ObjectManager::shutting_down()
{
	return ObjectManager::instance_ ? instance_->shutting_down_i() : 1;
}

int ObjectManager::at_exit(Clearup *object, void *param)
{
	return ObjectManager::instance ()->at_exit_i(object, 
		(CLEANUP_FUNC)cleanupDestroyer, param);
}

int ObjectManager::at_exit(void *object, CLEANUP_FUNC cleanup_hook, void *param)
{
	return ObjectManager::instance()->at_exit_i(object, cleanup_hook, param);
}

int ObjectManager::remove_at_exit(void *object)
{
	return ObjectManager::instance ()->remove_at_exit_i(object);
}

ObjectManager *ObjectManager::instance(void)
{
    if (instance_ == NULL)
	{
		ObjectManager *instance_pointer = new ObjectManager();
		instance_pointer->dynamically_allocated_ = true;
		return instance_pointer;
	}
	else
		return instance_;
}

int ObjectManager::at_exit_i(void *object, CLEANUP_FUNC cleanup_hook, void *param)
{
	//TODO lock
	if (shutting_down_i())
	{
		return -1;
	}
	if (exit_info_.find(object))
	{
		return -1;
	}
	return exit_info_.at_exit_i(object, cleanup_hook, param);
}

int ObjectManager::remove_at_exit_i(void *object)
{
	//TODO lock
    if (shutting_down_i())
	{
		return -1;
	}
    return exit_info_.remove(object);
}
