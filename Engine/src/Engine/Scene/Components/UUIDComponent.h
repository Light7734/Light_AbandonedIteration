#pragma once

#include "Base/Base.h"

#include "Core/UUID.h"

namespace Light {
			
	struct UUIDComponent
	{
		UUID uuid;

		UUIDComponent(UUID _uuid): uuid(_uuid) {}
		UUIDComponent(const UUIDComponent&) = default;
	};

}