/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Miscellaneous
*/

#ifndef MISCELLANEOUS_HPP_
#define MISCELLANEOUS_HPP_

#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../Components/Components.hpp"

namespace rtp
{
    /// @brief Sets up the sparseArrays in the registry
    /// @param reg The registry to set up
    /// @return True on success
    void setupRegistry(eng::Registry &reg);
} // namespace rtp


#endif /* !MISCELLANEOUS_HPP_ */
