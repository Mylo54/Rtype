/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** RegistryManager
*/

#ifndef RegistryManager_HPP_
#define RegistryManager_HPP_

#include "IRegistryManager.hpp"

namespace eng
{
    class RegistryManager {
        public:
            RegistryManager();
            ~RegistryManager();

            /// @brief Add a registry to the top of _regs stack
            /// @param reg registry to add
            void addRegistry(std::string name);

            /// @brief Remove the top Registry of _regs stack
            void popRegistry();

            /// @brief Get the top element of registry stack
            /// @return ref to the top registry
            eng::Registry &getTop();

            /// @brief get the full registry stack
            /// @return registry stack
            std::stack<eng::Registry> &getRegistries();

            /// @brief set the debug mode
            /// @param isEnable if true : logging activated
            void setDebugMode(bool isEnable);

            /// @brief get the debug mode
            /// @return true if logging activated, false otherwise
            bool getDebugMode();

            /// @brief set the path to the current logging file
            /// @param path new path to the file
            void setLogPath(std::string path);

            /// @brief get the path to the current logging file
            /// @return current logging file
            std::string getLogPath();

            /// @brief set a new log file based on time and date
            void createLogPath();
        protected:
        private:
            /// @brief stack of all the registries
            std::stack<eng::Registry> _regs;

            /// @brief if true : logging activated, false otherwise
            bool _debugMode = false;

            /// @brief the path to the current logging file
            std::string _logPath = "";
    };
} // namespace eng
#endif /* !RegistryManager_HPP_ */
