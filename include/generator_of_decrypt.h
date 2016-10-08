#ifndef GENERATOR_OF_DECRYPT_H_INCLUDE__
#define GENERATOR_OF_DECRYPT_H_INCLUDE__

#include "generator.h"

namespace flowTumn {
#if 0
	/**
	 * generate of Decrypt.
	 */
	template <typename T, typename D>
	class GeneratorOfDecrypt
		: public flowTumn::IGenerator <T> {
	public:
        GeneratorOfDecrypt(T value)
			: value_(std::move(value))
		{}

		T generator() override {
			return this->decryptor_(this->value_);
		}

	private:
		T value_;
		D decryptor_;
	};
#endif
};

#endif // GENERATOR_OF_DECRYPT_H_INCLUDE__
