#ifndef DECRYPT_H_INCLUDE__
#define DECRYPT_H_INCLUDE__

#include <string>

namespace flowTumn {
	class IDecrypt {
	public:
		virtual std::string decrypt() = 0;
	};
	
	class DecryptAES256 {
	public:
		DecryptAES256(std::string key, std::string secret)
			: key_(std::move(key))
			, secret_(std::move(secret))
		{}

	private:
		std::string key_;
		std::string secret_;
	};
};

#endif // DECRYPT_H_INCLUDE__
