#include "GameObjectPool.h"

GameObjectPool::GameObjectPool(int size) {
    m_poolSize = size;
    for (int i = 0; i < size; i++) {
        std::shared_ptr<Projectile>* obj = new std::shared_ptr<Projectile>();
        m_gameObjectPool.push_back(obj);
    }
}

GameObjectPool::~GameObjectPool() {
    for (auto obj : m_gameObjectPool) {
        delete obj;
    }
    m_gameObjectPool.clear();
}

std::shared_ptr<Projectile>* GameObjectPool::GetGameObject() {
    std::shared_ptr<Projectile>* obj = nullptr;
    if (m_gameObjectPool.size() > 0) {
        obj = m_gameObjectPool.front();
        m_gameObjectPool.pop_front();
    }
    else {
        obj = new std::shared_ptr<Projectile>();
    }
    return obj;
}

void GameObjectPool::ReturnGameObject(std::shared_ptr<Projectile>* obj) {
    m_gameObjectPool.push_back(obj);
}
