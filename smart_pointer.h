#pragma once

#include <map>
#include <stdexcept>

template<typename T>
class smart_pointer {
public:
	explicit smart_pointer();
	explicit smart_pointer(T* obj);
	explicit smart_pointer(const T& obj);
	explicit smart_pointer(T& obj);
	explicit smart_pointer(const smart_pointer<T>& obj);
	explicit smart_pointer(smart_pointer<T>& obj);
	virtual ~smart_pointer();
	smart_pointer<T>& operator=(const smart_pointer<T>& rhs);

	template<typename S>
	smart_pointer(S* obj) : data(obj) {
		ref_add();
	}

	template<typename S>
	smart_pointer(const S& obj) : data(&obj) {
		ref_add();
	}

	template<typename S>
	smart_pointer(S&& obj) : data(&obj) {
		ref_add();
	}

	template<typename S>
	smart_pointer(const smart_pointer<S>& obj) : data(obj.get()) {
		ref_add();
	}

	template<typename S>
	smart_pointer(smart_pointer<S>&& obj) : data(obj.get()) {
		ref_add();
		obj.data = NULL;
	}

	template<typename S>
	smart_pointer<T>& operator=(const smart_pointer<S>& rhs) {
		data = rhs.get();
		ref_add();
		return *this;
	}

	template<typename S>
	smart_pointer<T>& operator=(const smart_pointer<S>&& rhs) {
		data = rhs.get();
		ref_add();
		rhs->data = NULL;
		return *this;
	}

	operator T*() const;
	T& operator*() const;
	T* operator->() const;

	T* get() const;

	void ref_add();
	void ref_delete();

private:
	T* data;
	static std::map<T*,int> table;

};

template<typename T>
std::map<T*,int> smart_pointer<T>::table;