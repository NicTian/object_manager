#include "clearup.h"
using namespace std;

Clearup::Clearup()
{
}

Clearup::~Clearup()
{
}

void Clearup::cleanup(void *param /* = 0 */)
{
	delete this;
}

//------------------------------------------------------------------------------

ClearInfoNode::ClearInfoNode()
{
}

ClearInfoNode::ClearInfoNode(void *object, CLEANUP_FUNC cleanup_hook, void *param)
	:object_(object), cleanup_hook_(cleanup_hook), param_(param)
{
}

ClearInfoNode::~ClearInfoNode()
{
}

bool ClearInfoNode::operator==(const ClearInfoNode &o) const
{
	return o.object_ == this->object_
		&& o.cleanup_hook_ == this->cleanup_hook_
		&& o.param_ == this->param_;
}

bool ClearInfoNode::operator!=(const ClearInfoNode &o) const
{
	return !(*this == o);
}

extern "C" void cleanupDestroyer(Clearup *object, void *param)
{
	object->cleanup(param);
}

//-----------------------------------------------------------------------

ExitInfo::ExitInfo()
{
}

ExitInfo::~ExitInfo()
{
}

int ExitInfo::at_exit_i(void *object, CLEANUP_FUNC cleanup_hook, void *param)
{
	ClearInfoNode node(object, cleanup_hook, param);
	registered_objects_.push_front(node);  //FIFO
	return 0;
}

bool ExitInfo::find(void *object)
{
	list<ClearInfoNode>::iterator it = registered_objects_.begin();
	for (; it != registered_objects_.end(); ++it)
	{
		if (it->object() == object)
			return true;
	}
	return false;
}

bool ExitInfo::remove(void *object)
{
	list<ClearInfoNode>::iterator it = registered_objects_.begin();
	for (; it != registered_objects_.end(); ++it)
	{
		if (it->object() == object)
		{
			registered_objects_.erase(it);
			return true;
		}
	}
	return false;
}

void ExitInfo::call_hooks()
{
	list<ClearInfoNode>::iterator it = registered_objects_.begin();
	for (; it != registered_objects_.end(); ++it)
	{
		(*it->cleanup_hook())(it->object(), it->param());
	}
	registered_objects_.clear();
}