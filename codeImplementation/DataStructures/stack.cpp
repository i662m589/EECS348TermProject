#include <cstdlib>

template<typename T>
class Stack {
	public:
		Stack() {
			// Should be invoked with a type (e.g. Stack<int>(), Stack<float(), etc.)
			_size = 0;
		}
		T Pop() {
			if (IsEmpty()) {
				throw "Cannot pop from empty stack!";
			}

			T toReturn = Peek();
			_setSize(_size - 1);
			return toReturn;
		}
		T Peek() {
			if (IsEmpty()) {
				throw "Cannot peek from empty stack!";
			}
			return *(_contents + _size - 1);
		}
		void Add(T item) {
			_setSize(_size + 1);
			*(_contents + _size - 1) = item;
		}
		bool IsEmpty() {
			return _size == 0;
		}
		~Stack() {
			free(_contents);
		}
	private:
		void _setSize(unsigned int size) {
			if (size == 0) {
				free(_contents);
				_size = 0;
				_contents = nullptr;
				return;
			}

			unsigned int oldSize = _size;
			T* newArray = (T*)malloc(sizeof(T) * size);

			// Copy values from old array to new array
			for (unsigned int i = 0; i < size; i++) {
				if (i >= oldSize) {
					break;
				}
				*(newArray + i) = *(_contents + i);
			}

			// Free old array, place new array in it's place
			free(_contents);
			_size = size;
			_contents = newArray;
		}

		T* _contents;
		unsigned int _size;
};