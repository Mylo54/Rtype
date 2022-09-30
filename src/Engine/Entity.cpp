/*
** EPITECH PROJECT, 2022
** src
** File description:
** Entity
*/

#include "Entity.hpp"

eng::Entity::Entity(size_t id)
{
    this->_id = id;
}

size_t eng::Entity::getId(void) const
{
    return this->_id;
}

eng::Entity::~Entity()
{
}
