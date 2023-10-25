#version 330 core
out vec4 FragColor;

in vec3 ourColor;
uniform vec3 ChangeColor;
in vec2 ourTexturePos;
uniform sampler2D texture1;
uniform sampler2D texture2;
void main()
{
   // FragColor = texture(Texture1, ourTexturePos) *vec4(ourColor,0.1f);
  
  // FragColor = mix(texture(texture1, ourTexturePos), texture(texture2, ourTexturePos), 0.2f);
   //FragColor = vec4(ourColor, 1.0f);
   FragColor = vec4(1,1,1, 1.0f);
}
