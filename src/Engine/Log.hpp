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
    /// @brief A class managing logging
    class Log {
        public:
            /// @brief Log object constructor
            Log();
            ~Log();
            /// @brief set the path to the logging file
            /// @param path new path
            void setPath(std::string path);
            /// @brief Get the path to the current logging file
            /// @return 
            std::string getPath();
            /// @brief save a message in the log file
            /// @param msg message to log
            void log(std::string msg);
            /// @brief get the state of the log object
            /// @return true if active, false otherwise
            bool isEnabled();
            /// @brief enable logging
            void enable();
            /// @brief disable logging
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
