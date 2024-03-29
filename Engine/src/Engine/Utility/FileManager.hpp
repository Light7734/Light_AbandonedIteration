#pragma once

#include "Base/Base.hpp"

#include <stb_image.h>

namespace Light {

class BasicFileHandle
{
public:
	BasicFileHandle(uint8_t* data = nullptr, uint32_t size = 0ull, const std::string& path = "", const std::string& name = "", const std::string& extension = "")
	    : m_Data(data), m_Size(size), m_Path(path), m_Name(name), m_Extension(extension)
	{
	}

	virtual void Release()
	{
		delete m_Data;
		m_Data = nullptr;
		m_Size = 0ull;
	}

	// getters
	inline uint8_t* GetData() { return m_Data; }
	inline uint32_t GetSize() { return m_Size; }

	inline const std::string& GetPath() { return m_Path; }
	inline const std::string& GetName() { return m_Name; }
	inline const std::string& GetExtension() { return m_Extension; }

	inline const std::string& GetNameWithExtension() { return m_Name + '.' + m_Extension; }

	inline bool IsValid() const { return !!m_Data; }

	// operators
	inline operator bool() const { return IsValid(); }

protected:
	// made protected for custom Free():
	uint8_t* m_Data;
	uint32_t m_Size;

private:
	const std::string m_Path, m_Name, m_Extension;
};

class ImageFileHandle: public BasicFileHandle
{
public:
	ImageFileHandle(uint8_t* data, uint32_t size, const std::string& path, const std::string& name, const std::string& extension,
	                uint32_t width, uint32_t height, uint32_t components, uint32_t desiredComponents)
	    : BasicFileHandle(data, size, path, name, extension), m_Width(width), m_Height(height), m_Components(components), m_DesiredComponents(desiredComponents)
	{
	}

	void Release() override
	{
		stbi_image_free(reinterpret_cast<void*>(m_Data));
		m_Data = nullptr;
		m_Size = 0ull;
	}

	// getters
	inline uint32_t GetWidth() const { return m_Width; }
	inline uint32_t GetHeight() const { return m_Height; }
	inline uint32_t GetComponents() const { return m_Components; }
	inline uint32_t GetDesiredComponents() const { return m_DesiredComponents; }

private:
	uint32_t m_Width, m_Height, m_Components, m_DesiredComponents;
};

class FileManager
{
public:
	static BasicFileHandle ReadTextFile(const std::string& path);
	static ImageFileHandle ReadImageFile(const std::string& path, int32_t desiredComponents);
};

} // namespace Light