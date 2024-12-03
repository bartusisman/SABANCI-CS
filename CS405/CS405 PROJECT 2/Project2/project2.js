/**
 * @Instructions
 * 		@task1 : Complete the setTexture function to handle non power of 2 sized textures
 * 		@task2 : Implement the lighting by modifying the fragment shader, constructor,
 *      @task3: 
 *      @task4: 
 * 		setMesh, draw, setAmbientLight, setSpecularLight and enableLighting functions 
 */


function GetModelViewProjection(projectionMatrix, translationX, translationY, translationZ, rotationX, rotationY) {
	
	var trans1 = [
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		translationX, translationY, translationZ, 1
	];
	var rotatXCos = Math.cos(rotationX);
	var rotatXSin = Math.sin(rotationX);

	var rotatYCos = Math.cos(rotationY);
	var rotatYSin = Math.sin(rotationY);

	var rotatx = [
		1, 0, 0, 0,
		0, rotatXCos, -rotatXSin, 0,
		0, rotatXSin, rotatXCos, 0,
		0, 0, 0, 1
	]

	var rotaty = [
		rotatYCos, 0, -rotatYSin, 0,
		0, 1, 0, 0,
		rotatYSin, 0, rotatYCos, 0,
		0, 0, 0, 1
	]

	var test1 = MatrixMult(rotaty, rotatx);
	var test2 = MatrixMult(trans1, test1);
	var mvp = MatrixMult(projectionMatrix, test2);

	return mvp;
}


class MeshDrawer {
	// The constructor is a good place for taking care of the necessary initializations.
	constructor() {
		// Initialize shader program
		this.prog = InitShaderProgram(meshVS, meshFS);

		// Get attribute locations
		this.vertPosLoc = gl.getAttribLocation(this.prog, 'pos');
		this.texCoordLoc = gl.getAttribLocation(this.prog, 'texCoord');
		this.normalLoc = gl.getAttribLocation(this.prog, 'normal');

		// Get uniform locations
		this.mvpLoc = gl.getUniformLocation(this.prog, 'mvp');
		this.showTexLoc = gl.getUniformLocation(this.prog, 'showTex');
		this.enableLightingLoc = gl.getUniformLocation(this.prog, 'enableLighting');
		this.lightPosLoc = gl.getUniformLocation(this.prog, 'lightPos');
		this.ambientLoc = gl.getUniformLocation(this.prog, 'ambient');
		this.specularIntensityLoc = gl.getUniformLocation(this.prog, 'specularIntensity');
		this.viewPosLoc = gl.getUniformLocation(this.prog, 'viewPos');

		// Multiple texture uniforms
		this.useSecondTexLoc = gl.getUniformLocation(this.prog, 'useSecondTex');
		this.blendFactorLoc = gl.getUniformLocation(this.prog, 'blendFactor');
		this.tex2TypeLoc = gl.getUniformLocation(this.prog, 'tex2Type');

		// Create buffers
		this.vertbuffer = gl.createBuffer();
		this.texbuffer = gl.createBuffer();
		this.normalbuffer = gl.createBuffer();

		// Initialize state
		this.lightPos = [1.0, 1.0, 1.0];
		this.ambient = 0.3;
		this.specularIntensity = 0.5;
		this.viewPos = [0.0, 0.0, 5.0];
		this.isLightingEnabled = false;

		// Multiple texture state
		this.texture1 = null;
		this.texture2 = null;
		this.useSecondTex = false;
		this.blendFactor = 0.5;
		this.tex2Type = 0;  // 0: color map, 1: normal map
	}

	setMesh(vertPos, texCoords, normalCoords) {
		// Set vertex positions
		gl.bindBuffer(gl.ARRAY_BUFFER, this.vertbuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertPos), gl.STATIC_DRAW);

		// Set texture coordinates
		gl.bindBuffer(gl.ARRAY_BUFFER, this.texbuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(texCoords), gl.STATIC_DRAW);

		// Set normals
		gl.bindBuffer(gl.ARRAY_BUFFER, this.normalbuffer);
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normalCoords), gl.STATIC_DRAW);

		this.numTriangles = vertPos.length / 3;
	}

	setTexture(img, textureNum = 1) {
		const texture = gl.createTexture();
		gl.bindTexture(gl.TEXTURE_2D, texture);

		// Set texture image
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, img);

		// Handle non-power-of-2 textures
		if (isPowerOf2(img.width) && isPowerOf2(img.height)) {
			gl.generateMipmap(gl.TEXTURE_2D);
		} else {
			gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
			gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
			gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
			gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
		}

		// Store and set up texture based on textureNum
		if (textureNum === 1) {
			if (this.texture1) gl.deleteTexture(this.texture1);
			this.texture1 = texture;
		} else {
			if (this.texture2) gl.deleteTexture(this.texture2);
			this.texture2 = texture;
			this.useSecondTex = true;
		}
	}

	// New methods for texture control
	setBlendFactor(factor) {
		this.blendFactor = Math.max(0.0, Math.min(1.0, factor));
	}

	setSecondTextureType(type) {
		this.tex2Type = type;  // 0: color map, 1: normal map
	}

	enableSecondTexture(enable) {
		this.useSecondTex = enable && this.texture2 !== null;
	}

	draw(trans) {
		gl.useProgram(this.prog);

		// Set transformation
		gl.uniformMatrix4fv(this.mvpLoc, false, trans);

		// Set up attributes
		gl.bindBuffer(gl.ARRAY_BUFFER, this.vertbuffer);
		gl.enableVertexAttribArray(this.vertPosLoc);
		gl.vertexAttribPointer(this.vertPosLoc, 3, gl.FLOAT, false, 0, 0);

		gl.bindBuffer(gl.ARRAY_BUFFER, this.texbuffer);
		gl.enableVertexAttribArray(this.texCoordLoc);
		gl.vertexAttribPointer(this.texCoordLoc, 2, gl.FLOAT, false, 0, 0);

		gl.bindBuffer(gl.ARRAY_BUFFER, this.normalbuffer);
		gl.enableVertexAttribArray(this.normalLoc);
		gl.vertexAttribPointer(this.normalLoc, 3, gl.FLOAT, false, 0, 0);

		// Set up textures
		if (this.texture1) {
			gl.activeTexture(gl.TEXTURE0);
			gl.bindTexture(gl.TEXTURE_2D, this.texture1);
			gl.uniform1i(gl.getUniformLocation(this.prog, 'tex1'), 0);
		}

		if (this.texture2) {
			gl.activeTexture(gl.TEXTURE1);
			gl.bindTexture(gl.TEXTURE_2D, this.texture2);
			gl.uniform1i(gl.getUniformLocation(this.prog, 'tex2'), 1);
		}

		// Update texture uniforms
		gl.uniform1i(this.useSecondTexLoc, this.useSecondTex);
		gl.uniform1f(this.blendFactorLoc, this.blendFactor);
		gl.uniform1i(this.tex2TypeLoc, this.tex2Type);

		// Update lighting uniforms
		gl.uniform1i(this.enableLightingLoc, this.isLightingEnabled);
		gl.uniform3fv(this.lightPosLoc, this.lightPos);
		gl.uniform1f(this.ambientLoc, this.ambient);
		gl.uniform1f(this.specularIntensityLoc, this.specularIntensity);
		gl.uniform3fv(this.viewPosLoc, this.viewPos);

		// Update light position
		updateLightPos();
		this.lightPos = [lightX, lightY, 1.0];

		// Draw
		gl.drawArrays(gl.TRIANGLES, 0, this.numTriangles);
	}

	// Core methods with exact names required by HTML interface
	enableLighting(show) {
		this.isLightingEnabled = show;
	}

	setAmbientLight(value) {
		this.ambient = Math.max(0.0, Math.min(1.0, value));
	}

	setSpecularLight(value) {
		this.specularIntensity = Math.max(0.0, Math.min(1.0, value));
		gl.useProgram(this.prog);
		gl.uniform1f(this.specularIntensityLoc, this.specularIntensity);
	}

	showTexture(show) {
		gl.useProgram(this.prog);
		gl.uniform1i(this.showTexLoc, show);
	}
}

// Vertex shader
const meshVS = `
	attribute vec3 pos;
	attribute vec2 texCoord;
	attribute vec3 normal;

	uniform mat4 mvp;

	varying vec2 v_texCoord;
	varying vec3 v_normal;
	varying vec3 v_fragPos;

	void main() {
		v_texCoord = texCoord;
		v_normal = normalize(normal);
		v_fragPos = pos;
		gl_Position = mvp * vec4(pos, 1);
	}`;

// Fragment shader
const meshFS = `
	precision mediump float;

	uniform bool showTex;
	uniform bool enableLighting;
	uniform sampler2D tex1;      // Base texture
	uniform sampler2D tex2;      // Second texture
	uniform bool useSecondTex;   // Whether to use second texture
	uniform float blendFactor;   // How much to blend between textures
	uniform int tex2Type;        // 0: color map, 1: normal map
	uniform vec3 lightPos;
	uniform vec3 viewPos;
	uniform float ambient;
	uniform float specularIntensity;

	varying vec2 v_texCoord;
	varying vec3 v_normal;
	varying vec3 v_fragPos;

	vec3 calculateNormalMap(vec3 normalMapColor) {
		// Convert RGB normal map to normal vector
		return normalize(normalMapColor * 2.0 - 1.0);
	}

	void main() {
		// Get base texture color
		vec3 baseColor = texture2D(tex1, v_texCoord).rgb;
		
		// Handle second texture based on its type
		if (useSecondTex) {
			vec3 tex2Color = texture2D(tex2, v_texCoord).rgb;
			
			if (tex2Type == 0) {  // Color map
				baseColor = mix(baseColor, tex2Color, blendFactor);
			}
			// For normal mapping, we'll modify the normal used in lighting
			vec3 normal = tex2Type == 1 ? calculateNormalMap(tex2Color) : normalize(v_normal);
		}

		if (!showTex) {
			baseColor = vec3(1.0);
		}
		
		if(enableLighting) {
			// Normalize vectors
			vec3 normal = normalize(v_normal);
			vec3 lightDir = normalize(lightPos - v_fragPos);
			vec3 viewDir = normalize(viewPos - v_fragPos);
			
			// Ambient
			vec3 ambientColor = ambient * baseColor;
			
			// Diffuse
			float diff = max(dot(normal, lightDir), 0.0);
			vec3 diffuseColor = diff * baseColor;
			
			// Specular
			vec3 reflectDir = reflect(-lightDir, normal);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
			vec3 specularColor = specularIntensity * spec * vec3(1.0);
			
			// Combine
			vec3 finalColor = ambientColor + diffuseColor + specularColor;
			gl_FragColor = vec4(min(finalColor, vec3(1.0)), 1.0);
		} else {
			gl_FragColor = vec4(baseColor, 1.0);
		}
	}`;

// Helper function for slider
function SetSpecularLight(param) {
	meshDrawer.setSpecularLight(param.value / 100);
	DrawScene();
}

function isPowerOf2(value) {
	return (value & (value - 1)) == 0;
}

// Light direction parameters for Task 2
var lightX = 1;
var lightY = 1;

const keys = {};
function updateLightPos() {
	const translationSpeed = 1;
	if (keys['ArrowUp']) lightY -= translationSpeed;
	if (keys['ArrowDown']) lightY += translationSpeed;
	if (keys['ArrowRight']) lightX -= translationSpeed;
	if (keys['ArrowLeft']) lightX += translationSpeed;
}

function SetSpecularLight(param) {
    meshDrawer.setSpecularLight(param.value / 100);
    DrawScene();
}

// Global interface functions required by HTML
function EnableLight(param) {
    meshDrawer.enableLighting(param.checked);
    DrawScene();
}

function SetAmbientLight(param) {
    meshDrawer.setAmbientLight(param.value / 100);
    DrawScene();
}

function SetSpecularLight(param) {
    meshDrawer.setSpecularLight(param.value / 100);
    DrawScene();
}

// UI control functions for multiple textures
function LoadTexture2(param) {
    if (param.files && param.files[0]) {
        const reader = new FileReader();
        reader.onload = function(e) {
            const img = new Image();
            img.src = e.target.result;
            img.onload = function() {
                meshDrawer.setTexture(img, 2);
                DrawScene();
            };
        };
        reader.readAsDataURL(param.files[0]);
    }
}

function SetBlendFactor(param) {
    meshDrawer.setBlendFactor(param.value / 100);
    DrawScene();
}

function SetTextureType(param) {
    meshDrawer.setSecondTextureType(parseInt(param.value));
    DrawScene();
}

function ToggleSecondTexture(param) {
    meshDrawer.enableSecondTexture(param.checked);
    DrawScene();
}
///////////////////////////////////////////////////////////////////////////////////