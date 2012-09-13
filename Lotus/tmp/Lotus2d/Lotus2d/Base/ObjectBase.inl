/*
 *
 */

//------------------------------------------------------------------------------
// CObjectBase::operator new
//------------------------------------------------------------------------------

inline void* ObjectBase::operator new( size_t aSize )
{
	return  ge_allocate( aSize );
}

//------------------------------------------------------------------------------
// CObjectBase::operator delete
//------------------------------------------------------------------------------
inline void ObjectBase::operator delete( void* aPtr )
{
	ge_free( aPtr );
}

//------------------------------------------------------------------------------
// CObjectBase::operator new
//------------------------------------------------------------------------------
inline void* ObjectBase::operator new [] (size_t aSize )
	{
	return ge_allocate( aSize );
	}

//------------------------------------------------------------------------------
// CObjectBase::operator delete
//------------------------------------------------------------------------------
inline void ObjectBase::operator delete [] ( void* aPtr )
	{
	ge_free( aPtr );
	}
