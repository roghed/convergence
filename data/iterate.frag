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

#version 460 core

const   vec3  AXIS_COLOR = vec3(0.0, 1.0, 0.0);
const   vec3  GRID_COLOR = vec3(0.0, 0.6, 0.0);

uniform vec2  screenSize;
uniform vec2  viewCenter;
uniform vec2  viewSize;
uniform float gridScale;
uniform float functionLimit;

float f(float x)
{
    return @[REPLACE ME]@;
}

float iterate(float x, float y, int n)
{
    float a = y;
    float x0 = x;

    for (int i = 0; i < n; ++i)
    {
        x0 = a * f(x0) + x0;
    }

    return x0;
}

vec3 applyColorMap(float x, const float min_value, const float max_value)
{
    x = (x - min_value) / (max_value - min_value);
    
    const vec3 COLOR_SCALE[] = {
        vec3(0.0, 0.0, 0.0), // black
        vec3(0.0, 0.0, 1.0), // blue
        vec3(0.0, 1.0, 1.0), // cyan
        vec3(0.0, 1.0, 0.0), // green
        vec3(1.0, 1.0, 0.0), // yellow
        vec3(1.0, 0.0, 0.0), // red
        vec3(1.0, 0.0, 1.0), // purple/violet
        vec3(1.0, 1.0, 1.0)  // white
    };    
    const uint  N_COLORS = COLOR_SCALE.length();
    const float SCALE_SIZE = 1.0 / (N_COLORS - 1);

    if (x < 0.0)
    {
        return COLOR_SCALE[0];
    }
    else if (x > 1.0)
    {
        return COLOR_SCALE[N_COLORS - 1];
    }
    else
    {
        uint first_color_id  = uint(x / SCALE_SIZE);
        uint second_color_id = first_color_id + 1;

        // calculate linear interpolation between first and second colors
        float x_start = first_color_id  * SCALE_SIZE;
        float interpolation_factor = (x - x_start) / SCALE_SIZE;

        vec3 interpolated_color = mix(COLOR_SCALE[first_color_id], 
                                      COLOR_SCALE[second_color_id], 
                                      interpolation_factor);
        return interpolated_color;
    }
}

out vec4 fragColor;

void main()
{
    vec2 normalized_frag_coord = gl_FragCoord.xy / screenSize;
    vec2 position = viewCenter + (normalized_frag_coord - vec2(0.5, 0.5)) * viewSize;

    vec2 pixel_size = viewSize / screenSize;

    vec2 nearest_grid_id = floor((position + pixel_size) / gridScale);

    float result = iterate(position.x, position.y, 2048);
    float error_relative = abs(result - functionLimit) / functionLimit;
    float error_relative_logscale = log(error_relative);
    vec3  function_color = applyColorMap(-error_relative_logscale, 0, 6);
    vec3  function_color_inverted = vec3(1.0, 1.0, 1.0) - function_color;

    // axis rendering
    if (abs(position.x) <= pixel_size.x / 2.0 || abs(position.y) <= pixel_size.y / 2.0)
    {
        fragColor = vec4(function_color_inverted, 1.0);
    }
    // grid rendering
    else if (abs(position.x - gridScale * nearest_grid_id.x) <= pixel_size.x / 2.0
          || abs(position.y - gridScale * nearest_grid_id.y) <= pixel_size.y / 2.0)
    {
        fragColor = vec4(mix(function_color, function_color_inverted, 0.5), 1.0);
    }
    else
    {
        fragColor = vec4(function_color, 1.0);
    }
}
