#version 120

attribute vec3 pos;
attribute vec2 texCoord;

varying vec2 transfer_textCoord;

uniform mat4 transform;

void main() {
	//Tambahkan satu elemen/data biar jadi vec4
	//Ini yang belom pake transformasi
	//gl_Position = vec4(pos, 1.0);

	//Update positionisinya dengan perkalian terhadap matriks transformasi
	gl_Position = transform * vec4(pos, 1.0);

	//Kalo varnya 0.0, kgk bakal ada transformasi
	//Kalo 1.0 normal
	//Kalo 2.0 berarti bakal dikali dua, semacam konstanta matriks
	//gl_positionition = transform * vec4(pos, 0.0);

	//Setting texture sample yang mau dipake di mesh
	transfer_textCoord = texCoord;
}
