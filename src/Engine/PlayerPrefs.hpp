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
    class PlayerPrefs {
        public:
            PlayerPrefs();
            ~PlayerPrefs();

            // Sets the string value of the preference identified by the given key.
            void setString(std::string key, std::string value);
            // Sets the int value of the preference identified by the given key.
            void setInt(std::string key, int value);
            // Sets the float value of the preference identified by the given key.
            void setFloat(std::string key, float value);

            // Returns the value corresponding to key in the preference file if it exists.
            std::string getString(std::string key);
            // Returns the value corresponding to key in the preference file if it exists.
            float getFloat(std::string key);
            // Returns the value corresponding to key in the preference file if it exists.
            int getInt(std::string key);

            // Save all player preferences in a file on disk
            bool save();
        protected:
        private:
            std::map<std::string, std::string> _strmap;
            std::map<std::string, int> _intmap;
            std::map<std::string, float> _floatmap;
    };
} // namespace eng



#endif /* !PLAYERPREFS_HPP_ */
