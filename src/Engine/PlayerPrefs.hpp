/*
** EPITECH PROJECT, 2022
** src
** File description:
** PlayerPrefs
*/

#ifndef PLAYERPREFS_HPP_
#define PLAYERPREFS_HPP_

#include <iostream>
#include <map>

namespace eng
{
    /// @brief A class handling player preferences
    class PlayerPrefs {
        public:
            /// @brief PlayerPrefs object construcor
            PlayerPrefs();
            ~PlayerPrefs();

            /// @brief load player preferences list from file to _strmap.
            void loadPrefs();

            /// @brief Returns the value corresponding to key in the preference file if it exists.
            /// @param key key of the preference to get
            /// @return the preference value
            std::string getPref(std::string key);

            /// @brief Sets the string value of the preference identified by the given key in the file
            /// @param key key of the preference to set
            /// @param value value to set
            void savePref(std::string key, std::string value);


            /// @brief Sets the string value of the preference identified by the given key.
            /// @param key key of the preference to set
            /// @param value value to set
            /// @param saved if true : save the change in the file
            void setPref(std::string key, std::string value, bool saved = false);

            /// @brief Sets the int value of the preference identified by the given key.
            /// @param key key of the preference to set
            /// @param value value to set
            void setPref(std::string key, int value, bool saved = false);

            /// @brief Sets the float value of the preference identified by the given key.
            /// @param key key of the preference to set
            /// @param value value to set
            void setPref(std::string key, float value, bool saved = false);

            /// @brief Set the path to the player preferences file
            /// @param path new path to the file
            void setPath(std::string path);
            /// @brief Get the path to the player preferences file
            std::string getPath();
        protected:
        private:
            /// @brief load a single pref from player preferences file line
            /// @param str a line of player preference file
            void _loadPref(const std::string str);

            bool _prefLineMatch(const std::string str, std::string key);
            /// @brief map containing player preferences <key, value>
            std::map<std::string, std::string> _strmap;
            /// @brief path to the player preferences file
            std::string _path;

    };
} // namespace eng



#endif /* !PLAYERPREFS_HPP_ */
