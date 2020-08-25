#pragma once
#include <iostream>

using namespace std;

template <class T>
class Array {
	T* array;
	int size;
	bool err;
	long add;
	long find;
	long del;
	int sizekeep;

public:

	void reset() {
		add = 0;
		find = 0;
		del = 0;
	}

	bool get_err() { 
		return err; 
	}
	long get_add() { 
		return add; 
	}
	long get_find() { 
		return find;
	}
	long get_del() { 
		return del;
	}

	Array() :size(10), array(NULL), add(0), find(0), del(0), err(false) {}

	Array(int size) {
		this->size = size;
		array = new T[this->size];
		for (int i = 0; i < this->size; i++) {
			array[i] = rand();
		}
		sizekeep = size;
	};
	Array(const Array<T> &A) {
		this->size = A.size;
		this->array = new T[A.size];
	};

	~Array(void) {
		size = 0;
		delete[] array;
	};

	int Size() {
		return this->size;
	};

	void Clean(){
		this->size = 0;
		delete[] array;
		err = false;
		add = 0;
		find = 0;
		del = 0;
	};

	void Clear(int size) {
		this->size = 0;
		delete[] array;
		err = false;
		add = 0;
		find = 0;
		del = 0;
		sizekeep = size;
	};

	



	bool IsEmpty(){
		if (this->size == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}

	bool Presence(T value) {
		
		for (int i = 0; i < this->size; i++)
			if (this->array[i] == value) {
				return 1;
			}
		return 0;
	}

	T ReadByVal(T val) {
		for (int i = 0; i < this->size; i++) {
				find++;
				if (this->array[i] == val) {
					return this->array[i];
				}
			}
	}

	int ReadByPosition(int position) {
		if (position - 1 < 0 || position - 1 >= this->size)
			return 0;
		else
			for (int i = 0; i < this->size; i++) {
				find++;
				if (i == position - 1) {
					return this->array[i];
				}
			}
	}
	bool ChangeByPosition(int position, T newVal) {
		if (position - 1 < 0 || position - 1 >= this->size)
			return 0;
		else
			for (int i = 0; i < this->size; i++)
				if (i == position - 1) {
					this->array[i] = newVal;
					return 1;
				}
	}
	void Values() {
		for (int i = 0; i < this->size; i++) {
			cout << this->array[i] << " ";
		}
		cout << endl;
	}

	int Position(T val) {
		for (int i = 0; i < this->size; i++)
			if (this->array[i] == val) {
				return i + 1;
			}
		return 0;
	}

	bool Add(T val) {
		if (size < sizekeep)
		{
			T* temp = new T[this->size];
			for (int i = 0; i < this->size; i++) {
				temp[i] = this->array[i];
			}
			this->size++;
			this->array = new T[this->size];
			for (int i = 0; i < this->size - 1; i++) {
				this->array[i] = temp[i];
			}
			this->array[size - 1] = val;
			return 1;
		}
		else {
			return 0;
		}
	}

	bool AddToPosition(T val, int position) {
		if (size < sizekeep) {
			if (position - 1 < 0 || position - 1 > this->size) {
				return 0;
			}
			T* temp = new T[this->size];
			for (int i = 0; i < this->size; i++) {
				temp[i] = this->array[i];
			}
			this->size++;
			this->array = new T[this->size];
			for (int i = 0; i < position - 1; i++) {
				this->array[i] = temp[i];
			}
			this->array[position - 1] = val;
			for (int i = position; i < this->size; i++) {
				this->array[i] = temp[i - 1];
				add++;
			}
			return 1;
		}
		else {
			return 0;
		}
	}

	int SetSize() {
		return this->size;
	}

	bool DeleteByValue(T val) {
		int i;
		bool check = 0;
		for (i = 0; i < size; i++) {
			if (array[i] == val) {
				check = 1;
				break;
			}
		}
		if (check) {
			for (i; i < size; ++i)
			{
				array[i] = array[i + 1];
			}
			size--;
			return 1;
		}
		else {
			return 0;
		}
		return 1;
	}

	bool DeleteByPosition(int position) {
		if (position - 1 < 0 || position - 1 >= this->size + 1) {
			return 0;
		}
		else {
			for (int i = position - 1; i < size; ++i)
			{
				array[i] = array[i + 1];
				del++;
			}
			size--;
		}
		return 1;
	}
	T& operator [](const int& i) {
		if (this->size > i&& i > 0)
			return array[i];
	}

	friend ostream& operator<< (ostream& o, const Array<T>& s)
	{
		for(int i = 0; i < s.size; i++)
			o << s.array[i] << " ";
		return o;
	}

	

	//template <class T>
	class Iterator {
		T* cur;
		int poz = 0;
		int size;
	public:
		
		T& read() {
			return *cur;
		}

		void Check() {
			try //код, который может привести к ошибке, располагается тут
			{
				if (*cur == -33686019)
				{
					throw 123; //генерировать целое число 123
				}
				cout << "Value - " << *cur << ". Pozition - " << poz + 1 << endl;
			}
			catch (int i)//сюда передастся число 123
			{
				cout << "Выход за границы списка" << endl;
			}
			
		}

		Iterator(T* first) : cur(first) {}

		void GetSize(int size) {
			this->size = size;
		}

		bool Change(T val){
			if (poz < 1 || poz > size)
				return false;
			else {
				*cur = val;
				return true;
			}
		}

		void ToEnd() {
			poz = size - 1 ;
		}

		T& operator+(int n) {
			//if (sizeof(cur) > poz) {
				this->poz = this->poz + n;
				return *(cur + n);
			//}
				
		}
		T& operator-(int n) {
			//if (poz > 0) {
				//if (this-> poz > 0) {
					this->poz = this->poz - n;
					return *(cur - n);
				//}
				//else {
				//	return 0;
				//}
			//}
		}
		T& operator++(int) {
			//if (sizeof(cur) > poz) {
				this->poz++;
				return *cur++;
			//}
		}
		T& operator--(int) {
			//if (this->poz > 0) {
				//if (sizeof(cur) > poz) {
					this->poz--;
					return *cur--;
				//}
			//}
		}
		T& operator++() {
			//if (sizeof(cur) > poz) {
				this->poz++;
				return *++cur;
			//}
		}
		T& operator--() {
			//if (poz > 0) {
				//if (sizeof(cur) > poz) {
					this->poz--;
					return *--cur;
				//}
			//}
		}
		
		T& operator* () { return *cur; }
		T& operator= (T val) { 
			*cur = val;
			return* cur;
		}
	};
	
	Iterator begin() { return array; }
	Iterator end() { return array+size-1; }	

	int test_insert(int position) {
		int count = 0;
		
			if (position - 1 < 0 || position - 1 > this->size) {
				return 0;
			}
			T* temp = new T[this->size];
			for (int i = 0; i < this->size; i++) {
				temp[i] = this->array[i];
			}
			this->size++;
			this->array = new T[this->size];
			for (int i = 0; i < position - 1; i++) {
				this->array[i] = temp[i];
			}
			this->array[position - 1] = rand() % 1000;
			for (int i = position; i < this->size; i++) {
				this->array[i] = temp[i - 1];
				count++;
				
			}
			return count;
		
	}

	int test_delete(int position) {
		int count = 0;
		if (position - 1 < 0 || position - 1 >= this->size + 1) {
			return 0;
		}
		else {
			for (int i = position - 1; i < size; ++i)
			{
				array[i] = array[i + 1];
				count++;
			}
			size--;
		}
		return count;

	}
	int test_search(T val) {
		int count = 0;

		bool check = 0;
		for (int i = 0; i < size; i++) {
				count++;
			if (array[i] == val) {
				break;
			}
		}
		return count;

	}
};




