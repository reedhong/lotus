#include "Root.h"

namespace Lotus{
	template<> Root* Singleton<Root>::msInstance = NULL;
}