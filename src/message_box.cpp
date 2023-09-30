/* Copyright (C) 2023 Jan Rogowski

This file is part of Convergence.

Convergence is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

Convergence is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
Convergence. If not, see <https://www.gnu.org/licenses/>.*/

#include "message_box.hpp"

#if defined __linux__
#include <gtkmm.h>
#elif defined _WIN32
#include <Windows.h>
#endif

namespace
{

#if defined __linux__
using native_msg_t = Gtk::MessageType;
#elif defined _WIN32
// todo: declare Windows message box type
#endif

native_msg_t nativeType(MessageBox::Type t)
{
    switch (t)
    {
        default:
        [[fallthrough]];
#if defined __linux__
        case MessageBox::Info:
            return Gtk::MessageType::MESSAGE_INFO;
        case MessageBox::Warning:
            return Gtk::MessageType::MESSAGE_WARNING;
        case MessageBox::Error:
            return Gtk::MessageType::MESSAGE_ERROR;
#elif defined _WIN32
        // todo
#endif
    }
}

} // anonymous

MessageBox::MessageBox(const std::string& message, Type type)
{
#if defined __linux__
    Gtk::Main gtk_main;
    Gtk::MessageDialog box(message, false, nativeType(type));
    box.run();
#elif defined _WIN32
    // todo
#endif
}