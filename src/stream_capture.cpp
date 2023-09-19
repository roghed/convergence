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

#include "stream_capture.hpp"
#include <ostream>
#include <streambuf>
#include <string>

StreamCapture::StreamCapture(std::ostream& output_stream)
    : stream_(output_stream), originalStreamBuf_(stream_.rdbuf())
{}

StreamCapture::~StreamCapture()
{
    stop();
}

void StreamCapture::start()
{
    (void) stream_.rdbuf(streamContents_.rdbuf());
}

void StreamCapture::stop()
{
    (void) stream_.rdbuf(originalStreamBuf_);
}

std::string StreamCapture::getString() const
{
    return streamContents_.str();
}
