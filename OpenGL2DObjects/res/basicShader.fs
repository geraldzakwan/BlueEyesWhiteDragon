#version 120

varying vec2 transfer_textCoord;

uniform sampler2D u_sample;


void main() {
	//Semua pixel jadiin merah
	//R = 1, G = 0, B = 0
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);

	//Bisa juga isi pake texture
	//Ini ngesample/ambil sample pixel si texture di 0.2,0.2
	//gl_FragColor = texture2D(u_sample, vec2 (0.2, 0.2));
	//gl_FragColor = texture2D(u_sample, vec2 (0.3, 0.8));
	gl_FragColor = texture2D(u_sample, transfer_textCoord);
}
