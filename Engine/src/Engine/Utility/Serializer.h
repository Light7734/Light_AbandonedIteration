#pragma once

#include "Base/Base.h"

#include "Scene/Scene.h"
#include "Scene/Entity.h"

#include <yaml-cpp/yaml.h>

namespace Light {

	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);

		void Serialize(const std::string& filePath);
		bool Deserialize(const std::string& filePath);

		void SerializeBinary(const std::string& filePath);
		bool DeserializeBinary(const std::string& filePath);

	private:
		void SerializeEntity(YAML::Emitter& out, Entity entity);

	private:
		Ref<Scene> m_Scene;
	};


}