#include <cstdlib>

template<typename T>
class Stack {
	public:
		/*
			A stack data structure.
			This constructor should be called with a template type supplied, such as with Stack<int>(), Stack<float>(), etc.
		*/
		Stack() {
			_size = 0;
		}

		/*
			Removes the top-most value on the stack and returns it.
			This function will throw an exception if the stack is empty.
		*/
		T Pop() {
			if (IsEmpty()) {
				throw "Cannot pop from empty stack!";
			}

			T toReturn = Peek();
			_setSize(_size - 1);
			return toReturn;
		}

		/*
			Returns the top-most value on the stack, without altering its contents.
			This funciton will throw an exception if the stack is empty.
		*/
		T Peek() const {
			if (IsEmpty()) {
				throw "Cannot peek from empty stack!";
			}
			return *(_contents + _size - 1);
		}

		/*
			Adds an item to the top of the stack.
			@param {T} item the item to be added to the stack.
		*/
		void Add(T item) {
			_setSize(_size + 1);
			*(_contents + _size - 1) = item;
		}

		/*
			Returns whether the stack is empty.
		*/
		bool IsEmpty() const {
			return _size == 0;
		}
		/*
			Returns the size of the stack.
		*/
		unsigned int Size() const {
			return _size;
		}

		/*
			Simply frees the contents of the stack from memory.
		*/
		~Stack() {
			free(_contents);
		}
	private:
		/*
			Changes the size of the graph.
			@param {number} size The new size of the graph
		*/
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