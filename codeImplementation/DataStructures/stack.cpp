template<typename T>
class Stack {
	public:
		Stack() {
			_size = 0;
		}
		T Pop() {
			throw "Not Implemented";
		}
		T Peek() {
			throw "Not Implemented";
		}
		void Append(T item) {
			throw "Not Implemented";
		}
		bool IsEmpty() {
			return _size == 0;
		}
	private:
		T* _contents;
		unsigned int _size;
};