#version 330 core
const float texIndex = 2.0;
in vec3 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
out vec4 FragColor;
void main(){
	if(TexCoord.z==texIndex){
		FragColor = texture(texture1, vec2(TexCoord.x, TexCoord.y)); 
	}else{
		FragColor = texture(texture2, vec2(TexCoord.x, TexCoord.y)); 
	}
	 
}
