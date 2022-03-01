#version 330 core
const float texIndex = 2.0;
const float texIndex2 = 3.0;
in vec3 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
out vec4 FragColor;
void main(){
	if(TexCoord.z==texIndex){
		FragColor = texture(texture1, vec2(TexCoord.x, TexCoord.y)); 
	}else if(TexCoord.z==texIndex2){
		FragColor = texture(texture3, vec2(TexCoord.x, TexCoord.y)); 
		FragColor.a=FragColor.a*0.5;
	}else{
		FragColor = texture(texture2, vec2(TexCoord.x, TexCoord.y)); 
	}
	 
}
