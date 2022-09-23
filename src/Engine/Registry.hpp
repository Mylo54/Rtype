/*
** EPITECH PROJECT, 2022
** src
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include "Entity.hpp"


namespace eng
{
    class Registry {
        public:
            Registry();
            ~Registry();

            Entity spawnEntity();
            Entity entityFromIndex(size_t index);
            void killEntity(Entity const &e);
        protected:
        private:
    };
} // namespace eng



#endif /* !REGISTRY_HPP_ */
