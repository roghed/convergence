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

#include "application.hpp"

#ifdef HAS_WINMAIN_ENTRY_POINT
#include <Windows.h>

int main();

int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, int)
{
    return main();
}
#endif

int main()
{
    Application app;
    app.execute();
}
