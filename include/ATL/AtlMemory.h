
#ifndef AVLIB_ATL_MEMORY_H
#define AVLIB_ATL_MEMORY_H

#include "AVLCommon/Config.h"
#include <cstddef>

namespace avl
{

	AVL_FUNCTION void* AvlDbgAlloc( std::size_t n, const char* file, int line );
	AVL_FUNCTION void* AvlAlloc( std::size_t n );
	AVL_FUNCTION void AvlFree( void* ptr );

} // namespace avl


namespace atl
{

#if defined(_DEBUG) && defined(_MSC_VER)

	inline void* AtlDbgAlloc( std::size_t n, const char* file, int line ) throw()
	{
		return avl::AvlDbgAlloc(n, file, line);
	}

#	define AtlAlloc( n ) AtlDbgAlloc( (n), __FILE__, __LINE__ )

#else // _DEBUG

	inline void* AtlAlloc( std::size_t n ) throw()
	{
		return avl::AvlAlloc(n);
	}

#endif // _DEBUG

	inline void AtlFree( void* ptr )
	{
		avl::AvlFree(ptr);
	}

} // namespace atl


#endif // AVLIB_ATL_MEMORY_H
