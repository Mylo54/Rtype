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
            void registerComponents(SparseArray<Component> a) {
                _containers[typeid(SparseArray<Component>)] = a;
            }

            // Retrieve a reference to the array storing Components
            template <typename Component>
            SparseArray<Component> &getComponents(void) {
                std::type_index t = typeid(SparseArray<Component>);
                std::any &res = _containers[t];

                return std::any_cast<SparseArray<Component> &>(res);
            }

        protected:
        private:
            // A map storing every array of components
            // Key: type index
            // Val: std::any -> SparseArray<Component>
            std::unordered_map<std::type_index, std::any> _containers;
    };
} // namespace eng



#endif /* !REGISTRY_HPP_ */
