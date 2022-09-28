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
#include <stack>
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
                /// this currently doesn't work
                //_erasers.push_back(&Registery::erase<Component>);
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

            /// @brief Spawns a new entity while keeping the arrays small
            /// @return The entity
            Entity spawnEntity() {
                size_t res = _maxEntity + 1;

                if (_freeIds.size() > 1) {
                    res = _freeIds.top();
                    _freeIds.pop();
                }
                return (Entity(res));
            }

            /// @brief What will it be usefull for???
            /// @param idx The index
            /// @return The entity
            Entity entityFromIndex(std::size_t idx);
            
            /// @brief Remove an entity and it's previously attached components
            /// @param e The Entity
            void killEntity(Entity const &e) {
                /// @todo Remove all component associated to the entity here

                if (e.getId() == _maxEntity)
                    _maxEntity--;
                else
                    _freeIds.push(e.getId());
            }

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
            /// @brief Erase a component at an index in associative array
            /// @tparam Component The component type
            /// @param r The registry from which to erase it
            /// @param e The entity (index)
            template<typename Component>
            void erase(Registry &r, Entity const &e) {
                r.getComponents<Component>()->erase(e.getId());
            }

            /// @brief The highest entity number
            size_t _maxEntity;

            /// @brief A map storing every array of components
            std::unordered_map<std::type_index, std::any> _containers;

            /// @brief A vector storing functions to erase an index of a SparseArray
            std::vector<std::function<void(Registry &, Entity const &)>> _erasers;

            /// @brief A queue storing every ids already taken (not very sure)
            std::stack<size_t> _freeIds;
    };
} // namespace eng

#endif /* !REGISTRY_HPP_ */
