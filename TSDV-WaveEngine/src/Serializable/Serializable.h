#pragma once

#include <fstream>

namespace WaveEngine
{
	class Serializable
	{
	public:
		virtual void Serialize(std::ostream&) const = 0;
		virtual void Deserialize(std::istream&) = 0;
	};
}
