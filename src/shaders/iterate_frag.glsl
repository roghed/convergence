
const   vec3  AXIS_COLOR = vec3(1.0, 0.0, 0.0);
const   vec3  GRID_COLOR = vec3(0.0, 1.0, 0.0);

uniform vec2  screenSize;
uniform vec2  viewCenter;
uniform vec2  viewSize;
uniform float gridScale;

float f(float x)
{
    return @[REPLACE ME]@;
}

const float LIMIT = 0.5671432904097838729999686622;

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

vec3 applyColorMap(float normalized_value)
{
    float clr = 1.0 - normalized_value;
    return vec3(clr, clr, clr);
}

void main()
{
    vec2 normalized_frag_coord = gl_FragCoord.xy / screenSize;
    vec2 position = viewCenter + (normalized_frag_coord - vec2(0.5, 0.5)) * viewSize;

    vec2 pixel_size = viewSize / screenSize;

    vec2 nearest_grid_id = floor((position + pixel_size) / gridScale);

    // axis rendering
    if (abs(position.x) <= pixel_size.x / 2.0 || abs(position.y) <= pixel_size.y / 2.0)
    {
        gl_FragColor = vec4(AXIS_COLOR, 1.0);
    }
    // grid rendering
    else if (abs(position.x - gridScale * nearest_grid_id.x) <= pixel_size.x / 2.0
          || abs(position.y - gridScale * nearest_grid_id.y) <= pixel_size.y / 2.0)
    {
        gl_FragColor = vec4(GRID_COLOR, 1.0);
    }
    // function rendering
    else
    {
        float result = iterate(position.x, position.y, 2048);
        float error_relative = abs(result - LIMIT) / LIMIT;

        gl_FragColor = vec4(applyColorMap(error_relative), 1.0);
    }
}
