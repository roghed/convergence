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
#include <filesystem>
#include <string>
#include <unordered_map>

class ResourceLocator
{
public:
    ResourceLocator(
        const std::string& application_directory_name = "",
        const std::string& resource_directory_name = "");

    const std::filesystem::path& locate(const std::string& resource_file_name);

private:

    bool search(const std::filesystem::path& path_to_file);

    const std::string appDirectory_;
    const std::string resDirectory_;
    std::unordered_map<std::string, std::filesystem::path> cache_;
};
