/*
** EPITECH PROJECT, 2022
** src
** File description:
** SparseArray
*/

#ifndef SPARSEARRAY_HPP_
#define SPARSEARRAY_HPP_

#include <iostream>
#include <vector>

namespace eng
{
    template <typename Component>
    class SparseArray {
        public:
            using OptionalComponent = Component;
            using Container = typename std::vector<OptionalComponent>;
            using Iterator = typename Container::iterator;
        public:
            SparseArray() {}
            ~SparseArray() {}

            // Returns an iterator that points at the beginning of the
            // Components Container
            Iterator begin() {
                return _data.begin();
            }

            // Returns an iterator that points at the end of the
            // Components Container
            Iterator end() {
                return _data.end();
            }

            // Remove a Component
            void erase(size_t pos) {
                Iterator it = _data.begin();
                for (int i = 0; i != pos; it++, i++);
                _data.erase(it);
                std::cout << "[DEBUG]" << std::endl;
            }

            // Get the size of the sparse array
            size_t size(void) {
                return _data.size();
            }

            // Insert the Component at pos index, erasing the old value or
            // resizing if needed
            OptionalComponent &insertAt(size_t pos, Component const &c) {
                while (pos <= size())
                    _data.push_back(nullptr);
                erase(pos);
                _data[pos] = c;
                return _data[pos];
            }

            // Take a reference to an optional component and return its index
            // If it isn't present it returns -1
            size_t getIndex(OptionalComponent const &c) {
                size_t res = 0;

                while (_data[res] != &c && res > size())
                    res++;
                if (res > size())
                    return -1;
                return res;
            }
        protected:
        private:
            Container _data;
    };
} // namespace eng

#endif /* !SPARSEARRAY_HPP_ */
