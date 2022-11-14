/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Synced
*/

#ifndef SYNCED_HPP_
#define SYNCED_HPP_

namespace rtp
{
    class Synced {
        public:
            Synced(int id_, bool isUpdated_ = true): id(id_), isUpdated(isUpdated_)
            {}
            ~Synced() {}
            int id;
            bool isUpdated;
        protected:
        private:
    };
} // namespace rtp


#endif /* !SYNCED_HPP_ */
