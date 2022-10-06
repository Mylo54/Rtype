/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** Log
*/

#ifndef LOG_HPP_
#define LOG_HPP_

#include <string>

namespace eng
{
    class Log {
        public:
            Log();
            ~Log();
            /// @brief set the path to the logging file
            /// @param path new path
            void setPath(std::string path);
            /// @brief Get the path to the current logging file
            /// @return 
            std::string getPath();
            void log(std::string msg);
            bool isEnabled();
            void enable();
            void disable();
        protected:
        private:
            /// @brief Path to the logging file
            std::string _path = "";
            /// @brief If true: log activated
            bool _debugMode;
    };
} // namespace eng

#endif /* !LOG_HPP_ */
