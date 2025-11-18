#ifndef __CONTAINER_MANAGER_H__
#define __CONTAINER_MANAGER_H__

#include "..\Library\StringList.h"
#include "ContainerInterface.h"

class ContainerManager
{
public:
	static StringList GetAvailableContainers();
	static ContainerInterface *CreateContainer(const wchar_t *pszName);
};

#endif