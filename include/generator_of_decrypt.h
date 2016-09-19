#ifndef GENERATOR_OF_DECRYPT_H_INCLUDE__
#define GENERATOR_OF_DECRYPT_H_INCLUDE__

#include "generator.h"

namespace flowTumn {
	/**
	 * generate of Decrypt.
	 */
	tempalte <typename T, typename D>
	class GeneratorOfDecrypt
		: public IGenerator <T> {
	public:
		GeneratorNoProcessingImpl(T value)
			: value_(std::move(value))
		{}

		T generator() override {
			return this->decryptor_(this->value_);
		}

	private:
		T value_;
		D decryptor_;
	};
};

#endif // GENERATOR_OF_DECRYPT_H_INCLUDE__
