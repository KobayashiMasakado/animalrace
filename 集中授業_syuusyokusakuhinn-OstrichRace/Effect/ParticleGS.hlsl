#include "Particle.hlsli"

[maxvertexcount(3)]
void main(
	triangle PS_INPUT input[3],
	inout TriangleStream< PS_INPUT > output
)
{
	for (uint i = 0; i < 3; i++)
	{
		PS_INPUT element;

		element.Pos = mul(input[i].Pos,matWorld);
		element.Pos = mul(element.Pos, matView);
		element.Pos = mul(element.Pos, matProj);


		element.Tex = input[i].Tex;
		output.Append(element);
	}
}