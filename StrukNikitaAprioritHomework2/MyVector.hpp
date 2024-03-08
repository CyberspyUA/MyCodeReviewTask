#ifndef CODEREVIEWTASK_MYVECTOR_HPP
#define CODEREVIEWTASK_MYVECTOR_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

/*
 * MyVector stores a collection of objects with their names.
 *
 * For each object T, MyVector stores T`s name as std::string.
 * Several objects can have similar name.
 * operator[](const std::string& name) should return the first object
 * with the given name.
 *
 * Your task is to find as many mistakes and drawbacks in this code
 * (according to the presentation) as you can.
 * Annotate these mistakes with comments.
 *
 * Once you have found all the mistakes, rewrite the code
 * so it would not change its original purpose
 * and it would contain no mistakes.
 * Try to make the code more efficient without premature optimization.
 *
 * You can change MyVector interface completely, but there are several rules:
 * 1) you should correctly and fully implement copy-on-write idiom.
 * 2) std::pair<const T&, const std::string&> operator[](int index) const must take constant time at worst.
 * 3) const T& operator[](const std::string& name) const should be present.
 * 4) both operator[] should have non-const version.
 * 5) your implementation should provide all the member types of std::vector.
 * 6) your implementation should provide the following functions:
 *    1) begin(), cbegin(), end(), cend()
 *    2) empty(), size()
 *    3) reserve(), clear()
 */

template <typename T>
/**
 * ����� ������ �������� ���������
 * (It is better to give preference to an association).
 */
class MyVector : public std::vector<T> 
{
public:
    MyVector()
    {
        m_ref_ptr = new size_t(1);
        /**
         * �������� ����� ���'�� ��� ��������� bad_alloc ��� m_ref_ptr
         * (Possible memory leak on bad_alloc exception for m_ref_ptr).
         */
        m_names = new std::vector<std::string>(); 
    }

    MyVector(const MyVector& other)
        : std::vector<T>(other),
          m_ref_ptr(other.m_ref_ptr),
          m_names(other.m_names)
    {
        /**
         * ³������ �������� �� nullptr. ������� ���� �������� ���'��
         * (There is no check for nullptr. It is possible to change unwanted memory).
         */
        (*m_ref_ptr)++; 
    }

    ~MyVector()
    {
        /**
         * ³������ �������� �� nullptr. ������� ���� �������� ���'��
         * (There is no check for nullptr. It is possible to change unwanted memory).
         */
        if (--*m_ref_ptr == 0) 
        {
            /**
             * �������� ����� ���'��.
             * (Possible memory leakage).
             */
            delete m_ref_ptr; 
            delete m_names;
        }
    }

    void push_back(const T& obj, const std::string& name)
    {
        copy_names();
        /**
         * ��� ��������������� ������ �������� �����
         * (You should use a vector inside the class).
         */
        std::vector<T>::push_back(obj); 
        m_names->push_back(name);
    }

    std::pair<const T&, const std::string&> operator[](int index) const
    {
        if (index >= std::vector<T>::size()) 
        {
            /**
             * ���'���, ������� ��� ���������� �� ���� ��������
             * (The memory allocated for the exception will not be freed).
             */
            throw new std::out_of_range("Index is out of range"); 
        }
        /**
         * ³������ �������� m_names �� nullptr. ������� ���� �������� ���'��
         * (There is no check m_names for nullptr. It is possible to change unwanted memory).
         */
        return std::pair<const T&, const std::string&>(std::vector<T>::operator[](index), (*m_names)[index]); 
    }

    const T& operator[](const std::string& name) const
    {
        std::vector<std::string>::const_iterator iter = std::find(m_names->begin(), m_names->end(), name);
        if (iter == m_names->end())
        {
            /**
             * ���'���, ������� ��� ���������� �� ���� ��������
             * (The memory allocated for the exception will not be freed).
             */
            throw new std::invalid_argument(name + " is not found in the MyVector"); 
        }
        /**
         * ��� ��������������� ������ �������� �����
         * (You should use a vector inside the class).
         */
        return std::vector<T>::operator[](iter - m_names->begin()); 
    }
    
/*
 * ����� copy_names() ����� �������� �� ���� private ����� �� �������
 * (The copy_names() method can be placed in the private field along with the variables).
 */
private:
    /**
     * ����� copy_names ������� ���� ���� m_names, ����� ���� ������� �������� ������� 1. �� ���� ��������� �� ������� �������� ���'�� �� ���������
     * (The copy_names method creates a new copy of m_names even when the reference count is 1. This may result in unnecessary memory allocations and copying).
     */
    void copy_names()
    {
        if (*m_ref_ptr == 1)
        {
            return;
        }

        size_t* temp_ref_ptr = new size_t(1);
        /**
        * �������� std::vector �� shared_ptr ��� ���������� ����������� ����
        * (Replace std::vector with shared_ptr to improve code efficiency).
        */
        std::vector<std::string>* temp_names = new std::vector<std::string>(*m_names);

        (*m_ref_ptr)--;
        m_ref_ptr = temp_ref_ptr;
        m_names = temp_names;
    }

private:
    // Use copy-on-write idiom for efficiency (not a premature optimization)
    /**
     * ��� ���������� ����������� ����������� ����, ��� ������� ������ �� ������� ��������
     * (To improve the efficiency of the program code, you should replace the vector with a shared pointer).
     */
    std::vector<std::string>* m_names;
    /**
     * ������� �� �������� vector �� shared_ptr, m_ref_ptr ��� �� �����������
     * (Since we are replacing vector with shared_ptr, m_ref_ptr is no longer needed).
     */
    size_t* m_ref_ptr;
    /**
     * �����, ������ std::vector<T> objects ��� ��������� ����.
     * Also, add a std::vector<T> objects to store the names.
     */
};


#endif //CODEREVIEWTASK_MYVECTOR_HPP