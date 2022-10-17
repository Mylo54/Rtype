/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Synced
*/

#ifndef SYNCED_HPP_
#define SYNCED_HPP_

#include <stddef.h>

namespace rtp
{
    /// @brief Holds an id than allows the server & the client to synchronize
    /// their components together
    class Synced {
        public:
            /// @brief A Synchronized identification number constructor
            /// @param id_ The id
            /// @param pIsNew 
            Synced(int id_, bool pIsNew = true) : id(id_)
            {}
            ~Synced() {}

            bool isNew;
            int id;
        protected:
        private:
    };
} // namespace rtp

#endif /* !SYNCED_HPP_ */
