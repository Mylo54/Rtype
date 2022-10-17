/*
** EPITECH PROJECT, 2022
** src
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include "Entity.hpp"
#include "Log.hpp"
#include <stack>
#include "SparseArray.hpp"
#include <functional>
#include <any>
#include <unordered_map>
#include <typeindex>

namespace eng
{
    /// @brief A class holding a registry
    class Registry {
        public:
            /// @brief Registry object constructor
            Registry();
            ~Registry();

            /// @brief Adds a new component array to the associatives containers
            /// and adds a new function to erase a specified index
            /// @tparam Component The type of Components you want to get
            /// @param a Your array of Components
            template <typename Component>
            void registerComponents(SparseArray<Component> a) {
                _containers[typeid(SparseArray<Component>)] = a;
                _erasers.push_back([](Registry &r, const Entity &e) -> void {
                    r.getComponents<Component>().erase(e.getId());
                });
                if (getDebugMode())
                    _log.log(_name + ": addition of a new component array of type "
                    + typeid(SparseArray<Component>).name());
            }

            /// @brief Retrieve a reference to the array storing Components
            /// @tparam Component The type of Components you want to get
            /// @return A reference to the array storing Components
            template <typename Component>
            SparseArray<Component> &getComponents() {
                std::type_index t = typeid(SparseArray<Component>);
                std::any &res = _containers[t];
                // if (getDebugMode())
                //     _log.log(_name + ": getting of component array "
                //     + typeid(SparseArray<Component>).name());
                return std::any_cast<SparseArray<Component> &>(res);
            }

            /// @brief Spawns a new entity while keeping the arrays small
            /// @return The entity
            Entity spawnEntity() {
                size_t res = _maxEntity;

                if (_freeIds.size() > 1) {
                    res = _freeIds.top();
                    _freeIds.pop();
                } else
                    _maxEntity++;
                if (getDebugMode()) {
                    _log.log(_name + ": creation of a new entity of id "
                    + std::to_string(res));
                }
                return (Entity(res));
            }

            /// @brief What will it be usefull for???
            /// @param idx The index
            /// @return The entity
            Entity entityFromIndex(std::size_t idx) {
                if (idx > _maxEntity)
                    _maxEntity = idx;
                return (Entity(idx));
            }
            
            /// @brief Remove an entity and it's previously attached components
            /// @param e The Entity
            void killEntity(Entity const &e) {
                for (int i = 0; i < _erasers.size(); i++)
                    _erasers[i](*this, e);
                if (e.getId() == _maxEntity)
                    _maxEntity--;
                else
                    _freeIds.push(e.getId());
                if (getDebugMode())
                    _log.log(_name + ": deletion of all component of id "
                    + std::to_string(e.getId()));
            }

            /// @brief Store a component with association by id of the entity
            /// @tparam Component The type of your component
            /// @param to The Entity you want associated with the component
            /// @param c The Component you want to store
            /// @return A reference to the array containing the component
            template <typename Component>
            SparseArray<Component> &addComponent(Entity const &to, Component &&c) {
                getComponents<Component>().insertAt(to.getId(), c);
                if (getDebugMode()) {
                    _log.log(_name + ": adding of component to id "
                    + std::to_string(to.getId()));
                }
                return (getComponents<Component>());
            }

            /// @brief I don't know what this function is for, also idk wtf params is...
            template <typename Component>
            SparseArray<Component> &emplaceComponent(Entity const &to, Component &&c) {
                int e = to.getId();

                if (e < getComponents<Component>().size() && getComponents<Component>()[e].has_value())
                    getComponents<Component>()[e] = c;
                else
                    getComponents<Component>().insertAt(to.getId(), c);
                if (getDebugMode()) {
                    _log.log(_name + ": emplacing of component to id "
                    + std::to_string(to.getId()));
                }
                return getComponents<Component>();
            }

            /// @brief enable/disable the debug mode
            /// @param isEnable new value of debugMode
            void setDebugMode(bool isEnable);
            /// @brief get true if debug mode is enabled, false otherwise
            /// @return the value of debugMode
            bool getDebugMode();
            /// @brief Set the name of the Registry
            /// @param name new name of the registry
            void setName(std::string name);
            /// @brief Get the name of the registry
            /// @return 
            std::string getName();
            /// @brief Set the path to the logging file
            /// @param path 
            void setLogPath(std::string path);
            
            /// @brief get the path to the logging file
            /// @return path to the logging file
            std::string getLogPath();
        protected:
        private:
            /// @brief Log object for archiving
            eng::Log _log;

            /// @brief The highest entity number
            size_t _maxEntity = 0;

            /// @brief A map storing every array of components
            std::unordered_map<std::type_index, std::any> _containers;

            /// @brief A vector storing functions to erase an index of a SparseArray
            std::vector<std::function<void(Registry &, Entity const &)>> _erasers;

            /// @brief A queue storing every ids already taken (not very sure)
            std::stack<size_t> _freeIds;

            /// @brief If true : log activated
            bool _debugMode = false;

            /// @brief Name of the Registry
            std::string _name;
    };
} // namespace eng

#endif /* !REGISTRY_HPP_ */