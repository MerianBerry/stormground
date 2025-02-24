#pragma stormground stage vertex
#pragma stormground entry Main

struct vertex_info
{
  float2 position : POSITION;
  float3 color : COLOR;
};

struct vertex_to_pixel
{
  float4 position : SV_POSITION;
  float3 color : COLOR;
};

vertex_to_pixel Main(in vertex_info IN) {
  vertex_to_pixel OUT;

  return OUT;
}