/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** IRegistry
*/

#ifndef IREGISTRY_HPP_
#define IREGISTRY_HPP_

#include "Entity.hpp"
#include "SparseArray.hpp"
#include "Log.hpp"
#include <unordered_map>
#include <typeindex>
#include <stack>
#include <functional>
#include <any>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstdio>

namespace eng
{
    class IRegistry {
        public:
            virtual ~IRegistry() = default;
            /// @brief Adds a new component array to the associatives containers
            /// and adds a new function to erase a specified index
            /// @tparam Component The type of Components you want to get
            /// @param a Your array of Components
            template <typename Component>
            void registerComponents(SparseArray<Component> a);

            /// @brief Retrieve a reference to the array storing Components
            /// @tparam Component The type of Components you want to get
            /// @return A reference to the array storing Components
            template <typename Component>
            SparseArray<Component> &getComponents();

            /// @brief Spawns a new entity while keeping the arrays small
            /// @return The entity
            virtual Entity spawnEntity() = 0;

            /// @brief What will it be usefull for???
            /// @param idx The index
            /// @return The entity
            virtual Entity entityFromIndex(std::size_t idx) = 0;
            
            /// @brief Remove an entity and it's previously attached components
            /// @param e The Entity
            virtual void killEntity(Entity const &e) = 0;

            /// @brief Store a component with association by id of the entity
            /// @tparam Component The type of your component
            /// @param to The Entity you want associated with the component
            /// @param c The Component you want to store
            /// @return A reference to the array containing the component
            template <typename Component>
            SparseArray<Component> &addComponent(Entity const &to, Component &&c);

            /// @brief I don't know what this function is for, also idk wtf params is...
            template <typename Component, typename... Params>
            typename SparseArray<Component>::reference_type emplaceComponent(Entity const &to, Params &&...p);

            /// @brief enable/disable the debug mode
            /// @param isEnable new value of debugMode
            virtual void setDebugMode(bool isEnable) = 0;

            /// @brief get true if debug mode is enabled, false otherwise
            /// @return the value of debugMode
            virtual bool getDebugMode() = 0;

            /// @brief Set the name of the Registry
            /// @param name new name of the registry
            virtual void setName(std::string name) = 0;

            /// @brief Get the name of the registry
            /// @return 
            virtual std::string getName() = 0;

            /// @brief Set the path to the logging file
            /// @param path 
            virtual void setLogPath(std::string path) = 0;
            
            /// @brief get the path to the logging file
            /// @return path to the logging file
            virtual std::string getLogPath() = 0;
        protected:
        private:
    };
} // namespace eng

#endif /* !IREGISTRY_HPP_ */
