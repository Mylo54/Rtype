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
#include <queue>
#include <functional>
#include <any>

namespace eng
{
    class Registry {
        public:
            Registry() {}
            ~Registry() {}

            /// @brief Adds a new component array to the associatives containers
            /// @tparam Component The type of Components you want to get
            /// @param a Your array of Components
            template <typename Component>
            void registerComponents(SparseArray<Component> a) {
                _containers[typeid(SparseArray<Component>)] = a;

                /// @todo Here this line should push a function to erase a component at a specified index
                //_erasers.push_back(/*here*/;
            }

            /// @brief Retrieve a reference to the array storing Components
            /// @tparam Component The type of Components you want to get
            /// @return A reference to the array storing Components
            template <typename Component>
            SparseArray<Component> &getComponents() {
                std::type_index t = typeid(SparseArray<Component>);
                std::any &res = _containers[t];

                return std::any_cast<SparseArray<Component> &>(res);
            }

            /// @brief Spawns a new entity
            /// @return The entity
            Entity spawnEntity() {
                // Not sure abt the return and should have an accessible id (ie. _idsTaken)
                return (Entity(rand()));
            }
            Entity entityFromIndex(std::size_t idx);
            void killEntity(Entity const &e);

            /// @brief Store a component with association by id of the entity
            /// @tparam Component The type of your component
            /// @param to The Entity you want associated with the component
            /// @param c The Component you want to store
            /// @return A reference to the array containing the component
            template <typename Component>
            SparseArray<Component> &addComponent(Entity const &to, Component &&c) {
                return (getComponents<Component>()->insertAt(to.getId(), c));
            }

            /// @brief I don't know what this function is for, also idk wtf params is...
            template <typename Component, typename... Params>
            typename SparseArray<Component>::reference_type emplaceComponent(Entity const &to, Params &&...p);

        protected:
        private:
            /// @brief A map storing every array of components
            std::unordered_map<std::type_index, std::any> _containers;

            /// @brief A vector storing functions to erase an index of a SparseArray
            std::vector<std::function<void(Registry &, Entity const &)>> _erasers;

            /// @brief A queue storing every ids already taken (not very sure)
            std::queue<size_t> _idsTaken;
    };
} // namespace eng

#endif /* !REGISTRY_HPP_ */
