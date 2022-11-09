/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** IScene
*/

#ifndef OLDISCENE_HPP_
#define OLDISCENE_HPP_

#include <EngineCoreSuper/EngineCoreSuper.hpp>

namespace rtp
{
    class IScene {
        public:
            virtual ~IScene(){}
            /// @brief Sets up the sparseArrays in the registry
            /// @return True on success
            virtual void setupRegistry() = 0;
            /// @brief Launch all the systems of the scene (once)
            virtual void systemRun() = 0;
        protected:
        private:
    };
} // namespace rtp

#endif /* !OLDISCENE_HPP_ */
