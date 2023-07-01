
uniform vec2 screenSize;

float f(float x)
{
    return exp(x) - 1.0 / x;
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
    const float zoom_factor = 2.5;
    vec2 position = ((gl_FragCoord.xy / screenSize - vec2(0.5, 0.5)) * 2.0) * zoom_factor;

    float result = iterate(position.x, position.y, 2048);
    float error_relative = abs(result - LIMIT) / LIMIT;

    gl_FragColor = vec4(applyColorMap(error_relative), 1.0);
}
