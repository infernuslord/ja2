#include <vfs/Tools/vfs_allocator.h>

std::vector<vfs::IAllocator*> vfs::ObjectAllocator::_valloc;

void vfs::ObjectAllocator::registerAllocator(vfs::IAllocator* allocator)
{
	_valloc.push_back(allocator);
}
void vfs::ObjectAllocator::clear()
{
	std::vector<IAllocator*>::iterator it = _valloc.begin();
	for(; it != _valloc.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}
	_valloc.clear();
}
