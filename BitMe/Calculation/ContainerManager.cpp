#include "stdafx.h"
#include "ContainerManager.h"

#include "AsfInterface.h"
#include "AviInterface.h"
#include "FlvInterface.h"
#include "MatroskaInterface.h"
#include "Mp4Interface.h"
#include "MpgInterface.h"
#include "MtsInterface.h"
#include "M2tsInterface.h"
#include "MxfInterface.h"
#include "OggInterface.h"
#include "RmInterface.h"
#include "VobInterface.h"

#include "TestInterface.h"

StringList ContainerManager::GetAvailableContainers()
{
	StringList s;

	s.push_back(AsfInterface().getName());
	s.push_back(AviInterface().getName());
	s.push_back(FlvInterface().getName());
	s.push_back(MatroskaInterface().getName());
	s.push_back(Mp4Interface().getName());
	s.push_back(MpgInterface().getName());
	s.push_back(MtsInterface().getName());
	s.push_back(M2tsInterface().getName());
	s.push_back(MxfInterface().getName());
	//s.push_back(OggInterface().getName());
	s.push_back(RmInterface().getName());
	s.push_back(VobInterface().getName());

	//s.push_back(TestInterface().getName());

	return (s);
}

ContainerInterface *ContainerManager::CreateContainer(const wchar_t *pszName)
{
	if (pszName)
	{
		if (!wcscmp(pszName, AsfInterface().getName().c_str()))			return (new AsfInterface);
		if (!wcscmp(pszName, AviInterface().getName().c_str()))			return (new AviInterface);
		if (!wcscmp(pszName, FlvInterface().getName().c_str()))			return (new FlvInterface);
		if (!wcscmp(pszName, MatroskaInterface().getName().c_str()))	return (new MatroskaInterface);
		if (!wcscmp(pszName, Mp4Interface().getName().c_str()))			return (new Mp4Interface);
		if (!wcscmp(pszName, MpgInterface().getName().c_str()))			return (new MpgInterface);
		if (!wcscmp(pszName, MtsInterface().getName().c_str()))			return (new MtsInterface);
		if (!wcscmp(pszName, M2tsInterface().getName().c_str()))		return (new M2tsInterface);
		if (!wcscmp(pszName, MxfInterface().getName().c_str()))			return (new MxfInterface);
		//if (!wcscmp(pszName, OggInterface().getName().c_str()))			return (new OggInterface);
		if (!wcscmp(pszName, RmInterface().getName().c_str()))			return (new RmInterface);
		if (!wcscmp(pszName, VobInterface().getName().c_str()))			return (new VobInterface);

		//if (!wcscmp(pszName, TestInterface().getName().c_str()))		return (new TestInterface);
	}

	return (NULL);
}