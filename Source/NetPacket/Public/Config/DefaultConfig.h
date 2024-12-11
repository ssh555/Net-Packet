#pragma once
#include "nppch.h"
#include "NetSerializableStructGenerator.h"

namespace NetPacket
{
	const std::string NetStructConfig::DefaultConfig = R"(
namespace NetPacket
{
	class MyClass
	{
	public:
		MyClass(T value) : value(value) {}
	
		void print() const {
			std::cout << "Value: " << value << std::endl;
		}
	
	private:
		T value;
	};
}
)";

}