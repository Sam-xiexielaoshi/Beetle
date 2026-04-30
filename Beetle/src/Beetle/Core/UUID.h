#pragma once
#include <xhash>

namespace Beetle {

	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		UUID(const UUID& other) = default;

		operator uint64_t() const { return m_UUID; }
	private:
		uint64_t m_UUID;
	};

}

namespace std {
	template<>
	struct hash<Beetle::UUID>
	{
		std::size_t operator()(const Beetle::UUID& uuid) const
		{
			return std::hash<uint64_t>()((uint64_t)uuid);
		}
	};
}