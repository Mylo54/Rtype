/*
** EPITECH PROJECT, 2022
** src
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include "Entity.hpp"
#include "SparseArray.hpp"
#include <unordered_map>
#include <typeindex>
#include <any>

namespace eng
{
    class Registry {
        public:
            Registry() {}
            ~Registry() {}

            // Adds a new component array to the associatives container
            template <typename Component>
            void registerComponents(SparseArray<Component> &a) {
                // Cast the SparseArray<Component> into SparseArray<std::any>
                // using std::any_cast
                _containers[typeid(Component)] = a;
            }

            // Retrieve the array storing a Component
            template <typename Component>
            SparseArray<Component> &getComponents(std::type_index t) {
                // Cast the SparseArray<std::any> into SparseArray<Component>
                // using std::any_cast
                SparseArray<Component> res = std::any_cast(_containers[t].)
                // Return the casted array
                return res;
            }
        protected:
        private:
            std::unordered_map<std::type_index, SparseArray<std::any>> _containers;
    };
} // namespace eng



#endif /* !REGISTRY_HPP_ */
