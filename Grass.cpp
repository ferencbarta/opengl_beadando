
#include "Game.h"
#include <iostream>
#include <GLTools.h>

Grass::Grass(int _textureID) :
	textureID(_textureID)
{

    batch = new GLTriangleBatch();
    batch->BeginMesh(3*6);
    
    M3DVector3f verts[3];
    
    verts[0][0] = -1*width;
    verts[0][1] = height;
    verts[0][2] = -1*width;
    
    verts[1][0] = width;
    verts[1][1] = height;
    verts[1][2] = -1*width;
    
    verts[2][0] = width;
    verts[2][1] = height;
    verts[2][2] = width;
    
    M3DVector3f norms[3];
    
    norms[2][0]=norms[1][0]=norms[0][0] = 0.0f;
    norms[2][1]=norms[1][1]=norms[0][1] = 0.0f;
    norms[2][2]=norms[1][2]=norms[0][2] = 1.0f;
        
    M3DVector2f tex[3];
    
    tex[0][0] = 0.0f;
    tex[0][1] = 0.0f;
    tex[1][0] = 10.0f;
    tex[1][1] = 0.0f;
    tex[2][0] = 10.0f;
    tex[2][1] = 10.0f;
        
	batch->AddTriangle(verts, norms, tex);
    
    verts[0][0] = width;
    verts[0][1] = height;
    verts[0][2] = width;
    
    verts[1][0] = -1*width;
    verts[1][1] = height;
    verts[1][2] = width;
    
    verts[2][0] = -1*width;
    verts[2][1] = height;
    verts[2][2] = -1*width;
    
    tex[0][0] = 0.0f;
    tex[0][1] = 0.0f;
    tex[1][0] = 10.0f;
    tex[1][1] = 0.0f;
    tex[2][0] = 10.0f;
    tex[2][1] = 10.0f;
        
	batch->AddTriangle(verts, norms, tex);
    
	batch->End();
    
}

void Grass::paint(const M3DMatrix44f& viewMatrix, const M3DMatrix44f& projectionMatrix)
{
	static const GLfloat vWhite[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat vLightPos[] = { 100.0f, 100.0f, 1000.0f, 1.0f };
	M3DVector4f	vLightTransformed;
	m3dTransformVector4(vLightTransformed, vLightPos, viewMatrix);
	M3DMatrix44f mvpMatrix;
	m3dMatrixMultiply44(mvpMatrix, projectionMatrix, viewMatrix);
	Game::getInstance().getShaderManager().UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
                                         viewMatrix,
                                         projectionMatrix,
                                         vLightTransformed,
                                         vWhite,
                                         textureID);
	//shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vGreen);
	batch->Draw();
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

