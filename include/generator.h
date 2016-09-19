#ifndef I_GENERATOR_H_INCLUDE__
#define I_GENERATOR_H_INCLUDE__

namespace flowtumn {
	/**
	 * generate a any value.
	 */
	template <typename T>
	class IGenerator {
	public:
		using value_type = T;

		virtual T generator() = 0;
	};

	/**
	 * generate a RowData.
	 */
	tempalte <typename T>
	class GeneratorNoProcessingImpl
		: public IGenerator <T> {
	public:
		GeneratorNoProcessingImpl(T value)
			: value_(std::move(value))
		{}

		T generator() override {
			return this->value_;
		}

	private:
		T value_;
	};
};

#endif // I_GENERATOR_H_INCLUDE__
