#include <vector>
using namespace std;

template<typename T>
class Stack {
	public:
		/*
			Removes the top-most value on the stack and returns it.
			This function will throw an exception if the stack is empty.
		*/
		T Pop() {
			if (IsEmpty()) {
				throw "Cannot pop from empty stack!";
			}

			T toReturn = Peek();
			_contents.pop_back();
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
			return _contents.at(Size() - 1);
		}

		/*
			Adds an item to the top of the stack.
			@param {T} item the item to be added to the stack.
		*/
		void Add(T item) {
			_contents.push_back(item);
		}

		/*
			Returns whether the stack is empty.
		*/
		bool IsEmpty() const {
			return Size() == 0;
		}
		/*
			Returns the size of the stack.
		*/
		unsigned int Size() const {
			return _contents.size();
		}
	private:
		vector<T> _contents;
};