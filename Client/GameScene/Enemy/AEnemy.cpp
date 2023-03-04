/*
** EPITECH PROJECT, 2023
** AEnemy
** File description:
** AEnemy
*/

#include "AEnemy.hpp"

namespace rtype {
    bool AEnemy::isAlreadyAnEnemyHere(size_t x, size_t y, ComponentManager &componentManager, EntityManager &entityManager, const std::string &enemy)
    {
        std::vector<std::shared_ptr<Entity>> enemies = entityManager.getEntitiesFromFamily(enemy);

        for (auto &theEnemy : enemies) {
            Sprite &sprite = componentManager.get<Sprite>(theEnemy->getId());

            if ((int)x > sprite.getX() - ENEMY_REACH && (int)x < sprite.getX() + ENEMY_REACH)
                return true;
            else if ((int)y > sprite.getY() - ENEMY_REACH && (int)y < sprite.getY() + ENEMY_REACH)
                return true;
        }
        return false;
    }

    const size_t &AEnemy::getHp() const
    {
        return _hp;
    }

    void AEnemy::setHp(size_t hp)
    {
        _hp = hp;
    }
}