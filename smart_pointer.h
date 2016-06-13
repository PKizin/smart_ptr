#pragma once

#include <map>
#include <stdexcept>

template<typename T>
class smart_pointer {
public:
	explicit smart_pointer();
	explicit smart_pointer(T* obj);
	explicit smart_pointer(const T& obj);
	explicit smart_pointer(const smart_pointer<T>& obj);
	~smart_pointer();
	smart_pointer<T>& operator=(const smart_pointer<T>& rhs);

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