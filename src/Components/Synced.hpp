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
    class Synced {
        public:
            Synced(size_t pId, bool pIsNew = true)
            {}
            ~Synced() {}

            bool isNew;
            size_t id;
        protected:
        private:
    };
} // namespace rtp

#endif /* !SYNCED_HPP_ */
