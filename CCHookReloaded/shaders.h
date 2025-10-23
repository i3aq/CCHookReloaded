#pragma once

#include "engine.h"

struct ShaderDefinition
{
    const char* name;
    const char* script;
    qhandle_t handle;
};

class ShaderSystem
{
private:
    static constexpr size_t MAX_SHADERS = 64;
    static ShaderDefinition shaders[MAX_SHADERS];
    static size_t shaderCount;

public:
    static void RegisterShader(const char* name, const char* script)
	{
        if (shaderCount >= MAX_SHADERS) return;
        shaders[shaderCount++] = {name, script, 0};
    }

    static qhandle_t GetShader(const char* name, uint32_t spoofSeed)
	{
        for (size_t i = 0; i < shaderCount; i++)
		{
            if (strcmp(shaders[i].name, name) == 0)
			{
                if (shaders[i].handle == 0)
				{
                    shaders[i].handle = eng::RegisterAndLoadShader(shaders[i].script, spoofSeed + i);
                }
                return shaders[i].handle;
            }
        }
        return 0;
    }
	
    static void Reset()
    {
        for (size_t i = 0; i < shaderCount; i++)
        {
            shaders[i].handle = 0;
        }
    }
};

#define SHADER_COVER_SCRIPT \
	"%s\n\
		{\n\
			cull none\n\
			deformVertexes wave 100 sin 1.5 0 0 0\n\
			{\n\
				map textures/sfx/construction.tga\n\
				blendfunc GL_SRC_ALPHA GL_ONE\n\
				rgbgen entity\n\
				tcGen environment\n\
				tcmod rotate 30\n\
				tcmod scroll 1 .1\n\
			}\n\
		}\n"

#define SHADER_PLAIN_SCRIPT \
	"%s\n\
		{\n\
			nomipmaps\n\
			nofog\n\
			nopicmip\n\
			{\n\
				map *white\n\
				rgbGen const ( 0 0 0 )\n\
				blendFunc gl_dst_color gl_zero\n\
			}\n\
			{\n\
				map *white\n\
				rgbGen entity\n\
				depthWrite\n\
			}\n\
		}\n"

#define SHADER_QUAD_SCRIPT \
	"%s\n\
		{\n\
			deformVertexes wave 100 sin 3 0 0 0\n\
			{\n\
				map gfx/effects/quad.tga\n\
				blendfunc GL_ONE GL_ONE\n\
				rgbgen entity\n\
				tcGen environment\n\
				depthWrite\n\
				tcmod rotate 30\n\
				tcmod scroll 1 .1\n\
			}\n\
		}\n"

#define SHADER_CRYSTAL_SCRIPT \
	"%s\n\
		{\n\
			cull none\n\
			deformVertexes wave 100 sin 2 0 0 0\n\
			noPicmip\n\
			surfaceparm trans\n\
			{\n\
				map textures/sfx/construction.tga\n\
				blendFunc GL_SRC_ALPHA GL_ONE\n\
				rgbGen entity\n\
				tcGen environment\n\
				tcMod scroll 0.025 -0.07625\n\
			}\n\
		}\n"

#define SHADER_PLASTIC_SCRIPT \
	"%s\n\
		{\n\
			deformVertexes wave 100 sin 0 0 0 0\n\
			{\n\
				map gfx/effects/fx_white.tga\n\
				rgbGen entity\n\
				blendfunc GL_ONE GL_ONE\n\
			}\n\
		}\n"

#define SHADER_CIRCLE_SCRIPT \
	"%s\n\
		{\n\
			polygonOffset\n\
			{\n\
				map gfx/effects/disk.tga\n\
				blendFunc GL_SRC_ALPHA GL_ONE\n\
				rgbGen exactVertex\n\
			}\n\
		}"

#define SHADER_QUAD_RED_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 3 0\n\
		{\n\
			map gfx/effects/quadmap2red.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			depthWrite\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_QUAD_PURPLE_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 3 0\n\
		{\n\
			map gfx/effects/quadmap2purple.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			depthWrite\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_QUAD_MATRIX_BLUE_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 3 0\n\
		{\n\
			map gfx/effects/quadmap2matrixblue.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			depthWrite\n\
			tcmod rotate 1\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_QUAD_BLUE_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 3 0\n\
		{\n\
			map gfx/effects/quadmap2blue.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			tcmod rotate 30\n\
			depthWrite\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_QUAD_GREEN_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 3 0\n\
		{\n\
			map gfx/effects/quadmap2green.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			depthWrite\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_QUAD_YELLOW_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 3 0\n\
		{\n\
			map gfx/effects/quadmap2yellow.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			depthWrite\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_QUAD_BROWN_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 3 0\n\
		{\n\
			map gfx/effects/quadmap2brown.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			depthWrite\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_QUAD_CYAN_SCRIPT \
	"%s\n\
	{\n\
		{\n\
			map textures/effects/envmap_slate.tga\n\
			rgbGen lightingDiffuse\n\
			tcGen environment\n\
		}\n\
		cull none\n\
		{\n\
			map gfx/effects/quadmap2green.jpg\n\
			tcmod rotate 2\n\
			tcmod scroll 1 .01\n\
			tcGen environment\n\
			rgbGen lightingDiffuse\n\
		}\n\
	}\n"

#define SHADER_OQUAD_RED_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 1 0 4 0\n\
		{\n\
			map gfx/effects/quadmap2red.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			depthWrite\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_OQUAD_BLUE_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 1 0 4 0\n\
		{\n\
			map gfx/effects/quadmap2blue.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			depthWrite\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_OMARBLE_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 1 0 4 0\n\
		surfaceparm nodamage\n\
		nopicmip\n\
		{\n\
			map $lightmap\n\
			rgbGen identity\n\
		}\n\
		{\n\
			map gfx/effects/marble.tga\n\
			rgbGen entity\n\
		}\n\
		{\n\
			map gfx/effects/shine.tga\n\
			rgbGen identity\n\
			blendfunc GL_SRC_ALPHA GL_ONE\n\
			tcgen environment\n\
		}\n\
	}\n"

#define SHADER_OCRYSTAL_SCRIPT \
	"%s\n\
	{\n\
		cull none\n\
		deformVertexes wave 100 sin 1 0 4 0\n\
		noPicmip\n\
		surfaceparm trans\n\
		{\n\
			map textures/sfx/construction.tga\n\
			blendFunc GL_SRC_ALPHA GL_ONE\n\
			rgbGen entity\n\
			tcGen environment\n\
			tcMod scroll 0.025 -0.07625\n\
		}\n\
	}\n"

#define SHADER_OTHERMAL_SCRIPT \
	"%s\n\
	{\n\
		cull none\n\
		deformVertexes wave 100 sin 1 0 4 0\n\
		noPicmip\n\
		surfaceparm trans\n\
		{\n\
			map gfx/effects/thermal.tga\n\
			tcGen environment\n\
			tcmod rotate 4\n\
			tcmod scroll 0.5 .1\n\
			rgbgen entity\n\
			blendFunc GL_SRC_ALPHA GL_ONE_MINUS_DST_ALPHA\n\
		}\n\
		{\n\
			map gfx/effects/thermal.tga\n\
			blendFunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			tcmod rotate 4\n\
			tcmod scroll 0.5 .1\n\
			rgbgen entity\n\
		}\n\
		{\n\
			map gfx/effects/rain.tga\n\
			tcGen environment\n\
			rgbgen entity\n\
			tcmod rotate 8\n\
			tcmod scroll 0.5 .1\n\
			blendfunc GL_ONE GL_ONE\n\
		}\n\
	}\n"

#define SHADER_WQUAD_RED_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 4 0\n\
		{\n\
			map gfx/effects/quadmap2red.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			depthWrite\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_WQUAD_PURPLE_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 4 0\n\
		{\n\
			map gfx/effects/quadmap2purple.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			depthWrite\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_WQUAD_MATRIX_BLUE_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 4 0\n\
		{\n\
			map gfx/effects/quadmap2matrixblue.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			depthWrite\n\
			tcmod rotate 1\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_WQUAD_BLUE_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 4 0\n\
		{\n\
			map gfx/effects/quadmap2blue.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			tcmod rotate 30\n\
			depthWrite\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_WQUAD_GREEN_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 4 0\n\
		{\n\
			map gfx/effects/quadmap2green.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			depthWrite\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_WQUAD_YELLOW_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 4 0\n\
		{\n\
			map gfx/effects/quadmap2yellow.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			depthWrite\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_WQUAD_BROWN_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 4 0\n\
		{\n\
			map gfx/effects/quadmap2brown.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			depthWrite\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_WQUAD_CYAN_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 4 0\n\
		{\n\
			map gfx/effects/quadmap2cyan.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			depthWrite\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_KERAMIC_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		cull none\n\
		deformVertexes wave 100 sin 0 0 3 0\n\
		noPicmip\n\
		surfaceparm trans\n\
		{\n\
			map textures/sfx/construction.tga\n\
			blendFunc GL_SRC_ALPHA GL_ONE\n\
			rgbGen entity\n\
			tcGen environment\n\
			tcMod scroll 0.025 -0.07625\n\
		}\n\
	}\n"

#define SHADER_TEST_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 0 0\n\
		{\n\
			map gfx/effects/test.tga\n\
			tcGen environment\n\
			tcmod rotate 2\n\
			tcmod scroll 0.001 0.04\n\
			rgbgen entity\n\
			blendfunc GL_ONE GL_ONE\n\
		}\n\
	}\n"

#define SHADER_PLASTIC_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 3 0\n\
		{\n\
			map gfx/effects/fx_white.tga\n\
			rgbGen entity\n\
			blendfunc GL_ONE GL_ONE\n\
		}\n\
	}\n"

#define SHADER_CRISPWAVE_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		surfaceparm trans\n\
		nopicmip\n\
		tesssize 128\n\
		cull disable\n\
		deformVertexes wave 150 sin -0.0 2 .15 0.3\n\
		{\n\
			map textures/temperate_sd/rock_graynoise.tga\n\
			rgbGen entity\n\
		}\n\
	}\n"

#define SHADER_OUT_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 2 0 3 0\n\
		{\n\
			map textures/sfx/construction.tga\n\
			blendFunc GL_ONE GL_ONE\n\
			rgbGen entity\n\
			tcGen environment\n\
			tcMod scroll 0.025 -0.07625\n\
		}\n\
	}\n"

#define SHADER_OUT_CHAMS_MARBLE_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 2 0 3 0\n\
		surfaceparm nodamage\n\
		nopicmip\n\
		{\n\
			map $lightmap\n\
			rgbGen identity\n\
		}\n\
		{\n\
			map gfx/effects/marble.tga\n\
			rgbGen entity\n\
		}\n\
		{\n\
			map gfx/effects/shine.tga\n\
			rgbGen identity\n\
			blendfunc GL_SRC_ALPHA GL_ONE\n\
			tcgen environment\n\
		}\n\
	}\n"

#define SHADER_OUT_CHAMS_CRYSTAL_SCRIPT \
	"%s\n\
	{\n\
		cull none\n\
		deformVertexes wave 100 sin 2 0 3 0\n\
		noPicmip\n\
		surfaceparm trans\n\
		{\n\
			map textures/sfx/construction.tga\n\
			blendFunc GL_SRC_ALPHA GL_ONE\n\
			rgbGen entity\n\
			tcGen environment\n\
			tcMod scroll 0.025 -0.07625\n\
		}\n\
	}\n"

#define SHADER_OUT_CHAMS_THERMAL_SCRIPT \
	"%s\n\
	{\n\
		cull none\n\
		deformVertexes wave 100 sin 2 0 3 0\n\
		noPicmip\n\
		surfaceparm trans\n\
		{\n\
			map gfx/effects/thermal.tga\n\
			tcGen environment\n\
			tcmod rotate 4\n\
			tcmod scroll 0.5 .1\n\
			rgbgen entity\n\
			blendFunc GL_SRC_ALPHA GL_ONE_MINUS_DST_ALPHA\n\
		}\n\
		{\n\
			map gfx/effects/thermal.tga\n\
			blendFunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			tcmod rotate 4\n\
			tcmod scroll 0.5 .1\n\
			rgbgen entity\n\
		}\n\
		{\n\
			map gfx/effects/rain.tga\n\
			tcGen environment\n\
			rgbgen entity\n\
			tcmod rotate 8\n\
			tcmod scroll 0.5 .1\n\
			blendfunc GL_ONE GL_ONE\n\
		}\n\
	}\n"

#define SHADER_OUT_CHAMS_QUAD_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 2 0 3 0\n\
		{\n\
			map gfx/effects/quad.tga\n\
			depthWrite\n\
			tcGen environment\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
			rgbgen entity\n\
			blendfunc GL_ONE GL_ONE\n\
		}\n\
	}\n"

#define SHADER_OUT_CHAMS_PLASMA_SCRIPT \
	"%s\n\
	{\n\
		cull none\n\
		deformVertexes wave 100 sin 2 0 3 0\n\
		noPicmip\n\
		surfaceparm trans\n\
		{\n\
			map gfx/effects/plasma.tga\n\
			blendfunc GL_ONE GL_ONE\n\
			rgbGen entity\n\
			tcGen environment\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_OUT_CHAMS_PLASTIC_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 2 0 3 0\n\
		{\n\
			map menu/art/fx_white.tga\n\
			rgbGen entity\n\
			blendfunc GL_ONE GL_ONE\n\
		}\n\
	}\n"

#define SHADER_CRYSTAL_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		cull none\n\
		deformVertexes wave 100 sin 0 0 0 1\n\
		noPicmip\n\
		surfaceparm trans\n\
		{\n\
			map textures/sfx/construction.tga\n\
			blendFunc GL_SRC_ALPHA GL_ONE\n\
			alphaFunc GE128\n\
			depthWrite\n\
			rgbGen entity\n\
			tcGen environment\n\
			tcMod scroll 0.025 -0.07625\n\
		}\n\
	}\n"

#define SHADER_GLOW_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sawtooth 0 0 3 0\n\
		{\n\
			map menu/art/fx_white.tga\n\
			rgbGen entity\n\
			depthWrite\n\
			blendFunc GL_ONE GL_ONE\n\
		}\n\
	}\n"

#define SHADER_FLAME_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 3 0\n\
		{\n\
			animMap 10 gfx/effects/r.tga\n\
			blendFunc GL_ONE GL_ONE\n\
			depthWrite\n\
			rgbGen entity\n\
			tcGen environment\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
		{\n\
			animMap 10 gfx/effects/r.tga\n\
			blendFunc GL_ONE GL_ONE\n\
			depthWrite\n\
			rgbGen entity\n\
			tcGen environment\n\
			tcmod rotate 20\n\
			tcmod scroll 1 .1\n\
		}\n\
		{\n\
			map gfx/effects/quad.tga\n\
			depthWrite\n\
			blendFunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
			rgbGen entity\n\
		}\n\
	}\n"

#define SHADER_SOLID_A_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		tessSize 100\n\
		deformVertexes wave 100 square 0 0 3 0\n\
		deformVertexes normal .5 .1\n\
		{\n\
			map *white\n\
			blendfunc GL_SRC_ALPHA GL_ZERO\n\
			rgbGen entity\n\
			alphaGen const 1.0\n\
		}\n\
	}\n"

#define SHADER_SOLID_B_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 1.5 0 0 0\n\
		{\n\
			map gfx/effects/quadmap2red.jpg\n\
			blendfunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

#define SHADER_QUAD_A_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 3 0\n\
		{\n\
			map gfx/effects/q.jpg\n\
			depthWrite\n\
			tcGen environment\n\
			tcmod rotate 30\n\
			tcmod scroll 1 .1\n\
			rgbgen entity\n\
			blendfunc GL_ONE GL_ONE\n\
		}\n\
	}\n"

#define SHADER_QUAD_B_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 64 sin 0 0 3 0\n\
		nofog\n\
		{\n\
			map gfx/effects/q.jpg\n\
			rgbgen entity\n\
			tcGen environment\n\
		}\n\
	}\n"

#define SHADER_QUAD_C_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		{\n\
			map textures/effects/envmap_slate.tga\n\
			rgbGen lightingDiffuse\n\
			tcGen environment\n\
		}\n\
		cull none\n\
		{\n\
			map gfx/effects/q.jpg\n\
			tcmod rotate 2\n\
			tcmod scroll 1 .01\n\
			tcGen environment\n\
			rgbgen entity\n\
		}\n\
	}\n"

#define SHADER_QUAD_D_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 3 0\n\
		{\n\
			map gfx/effects/quad.tga\n\
			alphaFunc GE128\n\
			depthWrite\n\
			tcGen environment\n\
			tcmod rotate 8\n\
			tcmod scroll 0.5 .1\n\
			rgbgen entity\n\
			blendFunc GL_SRC_ALPHA GL_ONE_MINUS_DST_ALPHA\n\
		}\n\
		{\n\
			map gfx/effects/quad.tga\n\
			alphaFunc GE128\n\
			depthWrite\n\
			blendFunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			tcmod rotate 18\n\
			tcmod scroll 0.5 .1\n\
		}\n\
		{\n\
			map gfx/effects/q.jpg\n\
			alphaFunc GE128\n\
			depthWrite\n\
			tcGen environment\n\
			rgbgen entity\n\
			tcmod rotate 16\n\
			tcmod scroll 0.5 .1\n\
			blendfunc GL_ONE GL_ONE\n\
		}\n\
	}\n"

#define SHADER_MATRIX_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 3 0\n\
		{\n\
			map gfx/effects/matrix.tga\n\
			blendFunc GL_SRC_ALPHA GL_ONE\n\
			alphaFunc GE128\n\
			depthWrite\n\
			rgbgen entity\n\
			tcGen environment\n\
			tcmod scroll 1 .1\n\
		}\n\
		{\n\
			map gfx/effects/q.jpg\n\
			blendFunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			tcmod scroll 1 .1\n\
			rgbGen entity\n\
		}\n\
	}\n"

#define SHADER_THERMAL_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 3 0\n\
		{\n\
			map gfx/effects/thermal.tga\n\
			tcGen environment\n\
			tcmod rotate 4\n\
			tcmod scroll 0.5 .1\n\
			rgbgen entity\n\
			blendFunc GL_SRC_ALPHA GL_ONE_MINUS_DST_ALPHA\n\
		}\n\
		{\n\
			map gfx/effects/thermal.tga\n\
			blendFunc GL_ONE GL_ONE\n\
			tcGen environment\n\
			tcmod rotate 4\n\
			tcmod scroll 0.5 .1\n\
			rgbgen entity\n\
		}\n\
		{\n\
			map gfx/effects/rain.tga\n\
			tcGen environment\n\
			rgbgen entity\n\
			tcmod rotate 8\n\
			tcmod scroll 0.5 .1\n\
			blendfunc GL_ONE GL_ONE\n\
		}\n\
	}\n"

#define SHADER_CRYSTAL_B_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		cull none\n\
		deformVertexes wave 100 sin 0 0 3 0\n\
		noPicmip\n\
		surfaceparm trans\n\
		{\n\
			map textures/sfx/construction.tga\n\
			blendFunc GL_SRC_ALPHA GL_ONE\n\
			rgbGen entity\n\
			tcGen environment\n\
			tcMod scroll 0.025 -0.07625\n\
		}\n\
	}\n"

#define SHADER_XRAY_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		cull none\n\
		noPicmip\n\
		surfaceparm trans\n\
		{\n\
			map gfx/effects/xray.tga\n\
			blendFunc GL_SRC_ALPHA GL_ONE\n\
			rgbGen entity\n\
			tcGen environment\n\
		}\n\
	}\n"

#define SHADER_GRID_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		cull none\n\
		noPicmip\n\
		surfaceparm trans\n\
		{\n\
			map gfx/effects/grid.tga\n\
			alphaFunc GE128\n\
			rgbGen entity\n\
		}\n\
	}\n"

#define SHADER_WAVE_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		surfaceparm trans\n\
		nopicmip\n\
		tesssize 128\n\
		cull disable\n\
		deformVertexes wave 200 sin 4 3 .15 0.3\n\
		{\n\
			map gfx/effects/wave.tga\n\
			blendfunc blend\n\
			tcMod turb 0 .2 0 .05\n\
			tcmod scale .4 .4\n\
			blendFunc GL_ONE GL_ONE\n\
			rgbGen entity\n\
		}\n\
	}\n"

#define SHADER_CRISPY_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin -2.0 0 0 0\n\
		cull none\n\
		noPicmip\n\
		surfaceparm trans\n\
		{\n\
			map textures/temperate_sd/rock_graynoise.tga\n\
			rgbGen entity\n\
		}\n\
	}\n"

#define SHADER_MARBLE_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		surfaceparm nodamage\n\
		nopicmip\n\
		{\n\
			map $lightmap\n\
			rgbGen identity\n\
		}\n\
		{\n\
			map gfx/effects/marble.tga\n\
			rgbGen entity\n\
		}\n\
		{\n\
			map gfx/effects/shine.tga\n\
			rgbGen identity\n\
			blendfunc GL_SRC_ALPHA GL_ONE\n\
			tcgen environment\n\
		}\n\
	}\n"

#define SHADER_PLASMA_CHAMS_SCRIPT \
	"%s\n\
	{\n\
		deformVertexes wave 100 sin 0 0 0 0\n\
		{\n\
			map gfx/effects/plasma.tga\n\
			blendfunc GL_ONE GL_ONE\n\
			rgbGen entity\n\
			tcGen environment\n\
			tcmod rotate 15\n\
			tcmod scroll 1 .1\n\
		}\n\
	}\n"

namespace Shaders
{
    inline void Initialize()
	{
        ShaderSystem::RegisterShader("cover", SHADER_COVER_SCRIPT);
        ShaderSystem::RegisterShader("plain", SHADER_PLAIN_SCRIPT);
        ShaderSystem::RegisterShader("quad", SHADER_QUAD_SCRIPT);
        ShaderSystem::RegisterShader("crystal", SHADER_CRYSTAL_SCRIPT);
        ShaderSystem::RegisterShader("plastic", SHADER_PLASTIC_SCRIPT);
        ShaderSystem::RegisterShader("circle", SHADER_CIRCLE_SCRIPT);
        ShaderSystem::RegisterShader("quadRed", SHADER_QUAD_RED_SCRIPT);
        ShaderSystem::RegisterShader("quadPurple", SHADER_QUAD_PURPLE_SCRIPT);
        ShaderSystem::RegisterShader("quadMatrixBlue", SHADER_QUAD_MATRIX_BLUE_SCRIPT);
        ShaderSystem::RegisterShader("quadBlue", SHADER_QUAD_BLUE_SCRIPT);
        ShaderSystem::RegisterShader("quadGreen", SHADER_QUAD_GREEN_SCRIPT);
        ShaderSystem::RegisterShader("quadYellow", SHADER_QUAD_YELLOW_SCRIPT);
        ShaderSystem::RegisterShader("quadBrown", SHADER_QUAD_BROWN_SCRIPT);
        ShaderSystem::RegisterShader("quadCyan", SHADER_QUAD_CYAN_SCRIPT);
        ShaderSystem::RegisterShader("oquadRed", SHADER_OQUAD_RED_SCRIPT);
        ShaderSystem::RegisterShader("oquadBlue", SHADER_OQUAD_BLUE_SCRIPT);
        ShaderSystem::RegisterShader("omarble", SHADER_OMARBLE_SCRIPT);
        ShaderSystem::RegisterShader("ocrystal", SHADER_OCRYSTAL_SCRIPT);
        ShaderSystem::RegisterShader("othermal", SHADER_OTHERMAL_SCRIPT);
        ShaderSystem::RegisterShader("wquadRed", SHADER_WQUAD_RED_SCRIPT);
        ShaderSystem::RegisterShader("wquadPurple", SHADER_WQUAD_PURPLE_SCRIPT);
        ShaderSystem::RegisterShader("wquadMatrixBlue", SHADER_WQUAD_MATRIX_BLUE_SCRIPT);
        ShaderSystem::RegisterShader("wquadBlue", SHADER_WQUAD_BLUE_SCRIPT);
        ShaderSystem::RegisterShader("wquadGreen", SHADER_WQUAD_GREEN_SCRIPT);
        ShaderSystem::RegisterShader("wquadYellow", SHADER_WQUAD_YELLOW_SCRIPT);
        ShaderSystem::RegisterShader("wquadBrown", SHADER_WQUAD_BROWN_SCRIPT);
        ShaderSystem::RegisterShader("wquadCyan", SHADER_WQUAD_CYAN_SCRIPT);
        ShaderSystem::RegisterShader("keramicChams", SHADER_KERAMIC_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("testChams", SHADER_TEST_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("plasticChams", SHADER_PLASTIC_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("crispWaveChams", SHADER_CRISPWAVE_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("outChams", SHADER_OUT_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("outChamsMarble", SHADER_OUT_CHAMS_MARBLE_SCRIPT);
        ShaderSystem::RegisterShader("outChamsCrystal", SHADER_OUT_CHAMS_CRYSTAL_SCRIPT);
        ShaderSystem::RegisterShader("outChamsThermal", SHADER_OUT_CHAMS_THERMAL_SCRIPT);
        ShaderSystem::RegisterShader("outChamsQuad", SHADER_OUT_CHAMS_QUAD_SCRIPT);
        ShaderSystem::RegisterShader("outChamsPlasma", SHADER_OUT_CHAMS_PLASMA_SCRIPT);
        ShaderSystem::RegisterShader("outChamsPlastic", SHADER_OUT_CHAMS_PLASTIC_SCRIPT);
        ShaderSystem::RegisterShader("crystalChams", SHADER_CRYSTAL_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("glowChams", SHADER_GLOW_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("flameChams", SHADER_FLAME_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("solidAChams", SHADER_SOLID_A_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("solidBChams", SHADER_SOLID_B_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("quadAChams", SHADER_QUAD_A_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("quadBChams", SHADER_QUAD_B_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("quadCChams", SHADER_QUAD_C_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("quadDChams", SHADER_QUAD_D_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("matrixChams", SHADER_MATRIX_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("thermalChams", SHADER_THERMAL_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("crystalBChams", SHADER_CRYSTAL_B_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("xrayChams", SHADER_XRAY_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("gridChams", SHADER_GRID_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("waveChams", SHADER_WAVE_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("crispyChams", SHADER_CRISPY_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("marbleChams", SHADER_MARBLE_CHAMS_SCRIPT);
        ShaderSystem::RegisterShader("plasmaChams", SHADER_PLASMA_CHAMS_SCRIPT);
    }
}