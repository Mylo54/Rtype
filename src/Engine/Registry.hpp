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
                // still a bad way, we need to store the REFERENCE of a
                // but casted as an "std::any" type
                _containers[typeid(SparseArray<Component>)] = getAnyArray<Component>(a);
            }

            // Retrieve a reference to the array storing Components
            template <typename Component>
            SparseArray<Component> &getComponents(std::type_index t) {
                // Cast the SparseArray<std::any> into SparseArray<Component>
                // using std::any_cast
                // return a **REFERENCE** OF THE ARRAY IN THE MAP casted in Component type
            }

        protected:
        private:
            // Returns a copy of the sparse array with the std::any type
            template <typename Component>
            eng::SparseArray<std::any> getAnyArray(eng::SparseArray<Component> &a)
            {
                eng::SparseArray<std::any> res;
                int i = 0;

                for (auto it = a.begin(); it != a.end(); i++, it++) {
                    res.insertAt(i, it->value());
                }
                return (res);
            }

            std::unordered_map<std::type_index, SparseArray<std::any>> _containers;
    };
} // namespace eng



#endif /* !REGISTRY_HPP_ */
