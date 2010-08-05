#ifndef _VFS_ALLOCATOR_H_
#define _VFS_ALLOCATOR_H_

#include <vfs/vfs_config.h>
#include <vector>

namespace vfs
{
	// needs to be destructible
	class VFS_API IAllocator
	{
	public:
		virtual ~IAllocator() {};
	};

	template<typename T>
	class VFS_API ObjBlockAllocator : public IAllocator
	{
	public:
		ObjBlockAllocator(unsigned int blockSize=1024)
			: IAllocator(), BLOCK_SIZE(blockSize), _ObjNew(0) {};
		const unsigned int BLOCK_SIZE;
		///
		T* New(unsigned int *ID = NULL)
		{
			unsigned int block_id = _ObjNew/BLOCK_SIZE;
			unsigned int file_id = _ObjNew % BLOCK_SIZE;
			if(block_id >= _ObjPool.size())
			{
				tBlock* b = new tBlock();
				b->resize(BLOCK_SIZE);
				_ObjPool.push_back(b);
			}
			tBlock* block = _ObjPool[block_id];
			T* obj = &(*block)[file_id];
			if(ID)
			{
				*ID = _ObjNew;
			}
			_ObjNew++;
			return obj;
		}
		///
		virtual ~ObjBlockAllocator()
		{
			for(unsigned int i = 0; i < _ObjPool.size(); ++i)
			{
				delete _ObjPool[i];
			}
		}
	private:
		void operator=(ObjBlockAllocator<T> const& t);

		typedef std::vector<T>	tBlock;
		std::vector<tBlock*>	_ObjPool;
		unsigned int			_ObjNew;
	};


	class VFS_API ObjectAllocator
	{
	public:
		static void registerAllocator(IAllocator* allocator);
		
		static void clear();
	private:
		static std::vector<IAllocator*> _valloc;
	};
} // namespace vfs

#endif // _VFS_ALLOCATOR_H_
