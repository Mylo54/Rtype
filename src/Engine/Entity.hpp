/*
** EPITECH PROJECT, 2022
** src
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <iostream>
namespace eng
{
    class Entity {
        public:
            Entity(size_t id);
            ~Entity();

            size_t getId() const;
        protected:
        private:
            size_t _id;
    };
} // namespace eng



#endif /* !ENTITY_HPP_ */
