uniform vec2 iResolution;
uniform float iGlobalTime;

void main()
{
    vec2 uv = gl_FragCoord.xy / iResolution.xy;

    vec3 col = vec3(uv,0.5+0.5*sin(iGlobalTime));

	gl_FragColor = vec4(col, 1.0);
}
