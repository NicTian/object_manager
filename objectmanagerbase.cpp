#include "objectmanagerbase.h"

ObjectManagerBase::ObjectManagerBase(void)
	: object_manager_state_(OBJ_MAN_UNINITIALIZED)
	, dynamically_allocated_(false)
{
}

ObjectManagerBase::~ObjectManagerBase()
{
}

int ObjectManagerBase::starting_up_i()
{
	return object_manager_state_ < OBJ_MAN_INITIALIZED;
}

int ObjectManagerBase::shutting_down_i()
{
	return object_manager_state_ > OBJ_MAN_INITIALIZED;
}
