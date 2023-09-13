#pragma once
#include <iostream>
#include <array>
#include <cassert>
template <class Type, size_t Capacity>
struct SlotMap
{
    using Key = struct { int id; int gen; };
    SlotMap()
    {
        init();
        std::cout << Capacity << "\n";
    }
    size_t getSize()
    {
        return m_size;
    }
    Key pushBack(Type&& newVal)
    {
        if (m_size < Capacity)
        {
            int firstFree = m_freeList;
            auto& slot = m_index[m_freeList];

            m_erase[m_size] = m_freeList;

            m_freeList = m_index[m_freeList].id;

            m_data[m_size] = std::move(newVal);

            slot.id = m_size;
            slot.gen = m_gen;
            m_size++;
            m_gen++;

            return { firstFree, slot.gen };
        }
        return {};
    }
    Key pushBack(Type const& newVal)
    {
        Type copy(newVal);
        return pushBack(std::move(copy));
    }
    bool remove(Key key)
    {
        if (m_size == 0 || !isValidKey(key)) return false;

        int nextFree = m_freeList;
        m_freeList = key.id;

        int dataId = m_index[key.id].id;

        m_index[m_freeList].id = nextFree;


        if (dataId != m_size - 1)
        {
            m_data[dataId] = m_data[m_size - 1];
            m_erase[dataId] = m_erase[m_size - 1];

            m_index[m_erase[dataId]].id = dataId;


        }
        m_index[m_freeList].gen = m_gen;
        m_gen++;
        m_size--;
        return true;
    }
    Type& operator[](Key key)
    {
        assert(isValidKey(key));
        return m_data[m_index[key.id].id];
    }
    
private:
    bool isValidKey(Key key)
    {
        if (key.id >= Capacity || key.id < 0) return false;
        return m_index[key.id].gen == key.gen;
    }

    void init()
    {
        m_size = 0;
        m_freeList = 0;
        m_gen = 0;
        for (int i = 0; i < Capacity - 1; i++)
        {
            m_index[i].id = i + 1;
        }
        m_index[Capacity - 1].id = -1; //ultimo elemento no deberia apuntar a ningun lado
    }
    std::array<Key, Capacity> m_index;
    std::array<Type, Capacity> m_data;
    std::array<int, Capacity> m_erase;
    int m_size;
    int m_freeList;
    int m_gen;
};