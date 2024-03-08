#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include <memory>
#include <string>
#include <iostream>

template <typename T>
class MyVectorRefactored
{
public:
	MyVectorRefactored() : m_names(std::make_shared<std::vector<std::string>>())
	{
		
	}
	MyVectorRefactored(const MyVectorRefactored& other) : objects(other.objects), m_names(other.m_names)
	{

	}
	MyVectorRefactored(MyVectorRefactored&& other) noexcept
	{
		objects = other.objects;
		m_names = other.m_names;
	}
	~MyVectorRefactored() = default;
	MyVectorRefactored& operator=(const MyVectorRefactored& other)
	{
		objects = other.objects;
		m_names = other.m_names;
		return *this;
	}
	void push_back(const T& obj, const std::string& name)
	{
		copy_names();

		objects.push_back(obj);
		m_names->push_back(name);
	}
	std::pair <const T&, const std::string&> operator[](int index) const
	{
		if(index >= objects.size())
		{
			throw std::out_of_range("Index is out of range");
		}
		return std::pair<const T&, const std::string&>(objects.operator[](index), (*m_names)[index]);
	}
	T& operator[](const std::string& name)
	{
		std::vector<std::string>::const_iterator iterNames = std::find(m_names->begin(), m_names->end(), name);
		if(iterNames == m_names->end())
		{
			throw std::invalid_argument(name + " is not found!");
		}
		return objects.operator[](iterNames - m_names->begin());
	}
private:
	//Big O: constant time.
	void copy_names()
	{
		if(m_names.unique() || m_names == nullptr)
		{
			return;
		}
		if(m_names != nullptr)
		{
			std::cout << "Coping a name\n";
			std::shared_ptr<std::vector<std::string>> namesCopy = std::make_shared<std::vector<std::string>>(*m_names);
			m_names = namesCopy;
		}
	}
	std::shared_ptr<std::vector<std::string>> m_names;
	std::vector<T> objects;
};
