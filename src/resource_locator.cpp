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

#include "resource_locator.hpp"
#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/filesystem/path.hpp>
#include <filesystem>
#include <string>
#include <vector>
#include <cstdlib> // std::strtok
#include <utility>

using namespace std::filesystem;

ResourceLocator::ResourceLocator(
    const std::string& application_directory_name,
    const std::string& resource_directory_name) :
    resDirectory_(resource_directory_name),
    appDirectory_(application_directory_name)
{}

std::vector<std::string> split(std::string str, char delim)
{
    std::vector<std::string> result;

    char* input = str.data();
    const char delimiters[] = {delim, '\0'};

    for (char* token = std::strtok(input, delimiters); token; token = std::strtok(nullptr, delimiters))
    {
        result.push_back(std::string(token));
    }

    return result;
}

const std::filesystem::path& ResourceLocator::locate(const std::string& filename)
{
    auto cache_entry = cache_.find(filename);
    bool is_in_cache = cache_entry != cache_.cend();

    if (is_in_cache)
    {
        return cache_entry->second;
    }

    path working_dir = current_path();

    if (search(working_dir.append(resDirectory_).append(filename)))
    {
        return cache_[filename];
    }

    path executable_dir = boost::dll::program_location().string();

    if (search(executable_dir.append(resDirectory_).append(filename)))
    {
        return cache_[filename];
    }

    for (path p : split(std::string(std::getenv("XDG_DATA_DIRS")), ':'))
    {
        if (search(p.append(appDirectory_).append(resDirectory_).append(filename)))
        {
            return cache_[filename];
        }
    }

    if (search(path("/usr/local/share").append(appDirectory_).append(resDirectory_).append(filename)))
    {
        return cache_[filename];
    }

    if (search(path("/usr/share").append(appDirectory_).append(resDirectory_).append(filename)))
    {
        return cache_[filename];
    }

    throw std::runtime_error("Resource file '" + filename + "' could not be located");
}

bool ResourceLocator::search(const path& p)
{
    if (exists(p))
    {
        cache_[p.filename().string()] = absolute(p);
        return true;
    }

    return false;
}
