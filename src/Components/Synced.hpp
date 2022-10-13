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
            Synced(int pId, bool pIsNew = true) : id(pId)
            {}
            ~Synced() {}

            bool isNew;
            int id;
        protected:
        private:
    };
} // namespace rtp

#endif /* !SYNCED_HPP_ */
