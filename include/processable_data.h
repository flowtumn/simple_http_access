#ifndef PROCESSABLE_DATA_H_INCLUDE__
#define PROCESSABLE_DATA_H_INCLUDE__

namepsace flowtumn {
	template <typename T>
	class ProcessableData {
	public:
		ProcessableData(T value)
			: value_(std::move(value))
		{}

	private:
		T value_;
	};
};

#endif // PROCESSABLE_DATA_H_INCLUDE__
