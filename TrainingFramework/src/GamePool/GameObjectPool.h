#pragma once
#include "Singleton.h"
#include "utilities.h"
#include "memory"

template <class T>
class GameObjectPool
{
public:
    GameObjectPool()
    {
        for (int i = 0; i < m_poolSize; i++)
            pool.push_back(std::make_shared<T>());
    };

    ~GameObjectPool() {};

    std::shared_ptr<T> GetFromPool()
    {
        if (!pool.empty())
        {
            std::shared_ptr<T> object = pool.front();
            object->EnableObject();
            pool.pop_front();
            return object;
        }
        else
        {
            return nullptr;
        }
    };

    void    ReturnToPool(std::shared_ptr<T> object)
    {
        object->Reset();
        pool.push_back(object);
    };

    std::list<std::shared_ptr<T>> GetPool()
    {
        return pool;
    }

protected:
    std::list<std::shared_ptr<T>> pool;
    GLint   m_poolLimit;
    GLint   m_poolSize;
};

