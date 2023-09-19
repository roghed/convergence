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

#pragma once
#include <ostream>
#include <streambuf>
#include <sstream>
#include <string>

// capture contents of an output stream to std::string
class StreamCapture
{
public:

    // output_stream must remain valid until this object is destroyed
    StreamCapture(std::ostream& output_stream);

    // effectively calls StreamCapture::stop() before destroying this object
    ~StreamCapture();

    void start();
    void stop();
    std::string getString() const;

private:

    std::ostream& stream_;
    std::streambuf* const originalStreamBuf_;
    std::ostringstream streamContents_;
};
