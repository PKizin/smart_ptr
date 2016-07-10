#include "smart_pointer.h"

template<typename T> smart_pointer<T>::smart_pointer() : data(NULL) {
}

template<typename T>
smart_pointer<T>::smart_pointer(T* obj) : data(obj) {
	ref_add();
}

template<typename T>
smart_pointer<T>::smart_pointer(const T& obj) : data(&obj) {
	ref_add();
}

template<typename T>
smart_pointer<T>::smart_pointer(T& obj) : data(&obj) {
	ref_add();
}

template<typename T>
smart_pointer<T>::smart_pointer(const smart_pointer<T>& obj) : data(obj.get()) {
	ref_add();
}

template<typename T>
smart_pointer<T>::smart_pointer(smart_pointer<T>& obj) : data(obj.get()) {
	ref_add();
}

template<typename T>
smart_pointer<T>::~smart_pointer() {
	ref_delete();
}

template<typename T>
smart_pointer<T>& smart_pointer<T>::operator=(const smart_pointer<T>& rhs) {
	data = rhs.get();
	ref_add();
	return *this;
}

template<typename T>
smart_pointer<T>::operator T*() const {
	return data;
}

template<typename T>
T& smart_pointer<T>::operator*() const {
	return *data;
}

template<typename T>
T* smart_pointer<T>::operator->() const {
	return data;
}

template<typename T>
T* smart_pointer<T>::get() const {
	return data;
}

template<typename T>
void smart_pointer<T>::ref_add() {
	try {
		if (data == NULL) {
			return;
		}

		if (table.find(data) == table.end()) {
			table[data] = 1;
		} else {
			table[data]++;
		}
	}
	catch (...) {
		std::logic_error("ref_add() : invalid data pointer...");
	}
}

template<typename T>
void smart_pointer<T>::ref_delete() {
	try {
		if (data == NULL) {
			return;
		}

		if (table[data] == 1) {
			table.erase(data);
			delete data;
		} else {
			table[data]--;
		}
	}
	catch (...) {
		std::logic_error("ref_delete : invalid data pointer...");
	}
}

template<typename T>
std::ostream& operator<<(std::ostream& s, const smart_pointer<T>& rhs) {
	s << *rhs;
	return s;
}