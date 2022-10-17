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
    /// @brief A class holding entity
    class Entity {
        public:
            /// @brief Entity object constructor
            /// @param id 
            Entity(size_t id);
            ~Entity();

            /// @brief get the id of the entity
            /// @return the id of the entity
            size_t getId() const;
        protected:
        private:
            size_t _id;
    };
} // namespace eng



#endif /* !ENTITY_HPP_ */
