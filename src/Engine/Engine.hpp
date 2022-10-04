/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <stack>
#include "Registry.hpp"

namespace eng
{
    class Engine {
        public:
            Engine();
            ~Engine();
            /// @brief Add a registry to the top of _regs stack
            /// @param reg registry to add
            void addRegistry(eng::Registry &reg);
            /// @brief Remove the top Registry of _regs stack
            void popRegistry();

            eng::Registry &getRegistry(std::string regName);
            std::stack<eng::Registry> &getRegistries(void);
        protected:
        private:
            std::stack<eng::Registry> _regs;
    };
} // namespace eng
#endif /* !ENGINE_HPP_ */
