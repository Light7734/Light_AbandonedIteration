#pragma once

#include "Base/Base.hpp"
#include "Core/UUID.hpp"

namespace Light {

struct UUIDComponent
{
	UUID uuid;

	UUIDComponent(UUID _uuid)
	    : uuid(_uuid) {}
	UUIDComponent(const UUIDComponent&) = default;
};

} // namespace Light