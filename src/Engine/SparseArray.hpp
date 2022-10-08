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
#include <optional>

namespace eng
{
    template <typename Component>
    class SparseArray {
        public:
            using OptionalComponent = std::optional<Component>;
            using Container = std::vector<OptionalComponent>;
            using Iterator = typename Container::iterator;
        public:
            SparseArray() {}
            ~SparseArray() {}

            /// @return an iterator that points at the beginning of the Components Container
            Iterator begin() {
                return _data.begin();
            }

            /// @return an iterator that points at the end of the Components Container
            Iterator end() {
                return _data.end();
            }

            /// @brief Remove a Component
            /// @param pos the index of the component
            void erase(size_t pos) {
                if (pos >= size())
                    return;
                _data.at(pos).reset();
                while (_data[size() - 1].has_value() == false && size() > 0)
                    _data.pop_back();
            }

            /// @return The size of the array
            size_t size() {
                return _data.size();
            }

            /// @brief Provide access to the Component contained in the array
            /// @param id The index of the Component
            /// @return A reference to the component stored in the array
            OptionalComponent &operator[](size_t id) {
                return _data[id];
            }

            /// @brief Insert the Component, erasing the old value or resizing if needed
            /// @param pos The index of the component
            /// @param c The component
            /// @return A reference to the component stored in the array
            OptionalComponent &insertAt(size_t pos, Component const &c) {
                while (pos >= size()) {
                    _data.push_back({});
                }
                if (_data[pos].has_value())
                    erase(pos);
                _data[pos].emplace(c);
                return _data[pos];
            }

            /// @brief Get the index of a Component
            /// @param c The component
            /// @return The index of 'c'
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
            std::vector<std::optional<Component>> _data;
    };
} // namespace eng

#endif /* !SPARSEARRAY_HPP_ */
