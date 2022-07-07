//#type VERTEX_SHADER
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in float a_Size;
layout (location = 2) in vec4 a_Color;
layout (location = 3) in vec2 a_TexCoord;
layout (location = 4) in float a_TexIndex;
layout (location = 5) in float a_TilingFactor;

out vec2 v_Coord;;
out float v_Size;
out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;
out float v_TilingFactor;

uniform mat4 u_ViewProjection;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	v_TilingFactor = a_TilingFactor;
	v_Size = a_Size;

	vec4 position = u_ViewProjection * vec4(a_Position, 1);
	v_Coord = position.xy;

	gl_Position = position;
}


#type FRAGMENT_SHADER
#version 330 core
			
layout(location = 0) out vec4 out_Color;

in vec2 v_Coord;
in float v_Size;
in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;
in float v_TilingFactor;

uniform sampler2D u_Texture[32];

uniform vec2 u_ViewportSize;

void main()
{
	out_Color = texture(u_Texture[int(v_TexIndex)], v_TexCoord * v_TilingFactor) * v_Color;

	// Make circle from square
//	vec2 fragCoord = mix(vec2(-1, -1), vec2(1, 1), gl_FragCoord.xy / u_ViewportSize);
//	vec2 coord = v_Coord - fragCoord;
//	float factor = 1 - dot(coord, coord) / v_Size;
//	out_Color *= factor;
}
