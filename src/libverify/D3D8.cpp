/*
    Copyright (C) 2019  RadWolfie

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "unittest.hpp"

static const std::map<std::string, version_ranges> database_full = {
    {"CDevice_MakeSpace", {3911, 4034, VER_NONE, VER_NONE}},
    {"CMiniport_CreateCtxDmaObject", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"CMiniport_InitHardware", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"CMiniport_IsFlipPending", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DBaseTexture_GetLevelCount", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DCubeTexture_GetCubeMapSurface", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DCubeTexture_GetCubeMapSurface2", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DCubeTexture_LockRect", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_AddRef", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_ApplyStateBlock", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_Begin", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_BeginPush", {4531, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_BeginPush2", {4039, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_BeginPushBuffer", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_BeginStateBig", {5028, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_BeginStateBlock", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_BeginVisibilityTest", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_BlockOnFence", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_BlockUntilVerticalBlank", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CaptureStateBlock", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_Clear", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CopyRects", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CreateCubeTexture", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CreateImageSurface", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CreateIndexBuffer", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CreateIndexBuffer2", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CreatePalette", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CreatePalette2", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CreatePixelShader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CreateStateBlock", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CreateTexture", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CreateTexture2", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CreateVertexBuffer", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CreateVertexBuffer2", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CreateVertexShader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_CreateVolumeTexture", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_DeletePatch", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_DeletePixelShader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_DeleteStateBlock", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_DeleteVertexShader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_DrawIndexedVertices", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_DrawIndexedVerticesUP", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_DrawRectPatch", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_DrawTriPatch", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_DrawVertices", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_DrawVerticesUP", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_EnableOverlay", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_End", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_EndPush", {4039, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_EndPushBuffer", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_EndStateBlock", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_EndVisibilityTest", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_FlushVertexCache", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetBackBuffer", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetBackBuffer2", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetBackMaterial", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetCreationParameters", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetDepthStencilSurface", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetDepthStencilSurface2", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetDeviceCaps", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetDisplayFieldStatus", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetDisplayMode", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetGammaRamp", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetLight", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetLightEnable", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetMaterial", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetModelView", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetOverlayUpdateStatus", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetPersistedSurface2", {4928, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetPixelShader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetProjectionViewportMatrix", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetPushBufferOffset", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetRenderTarget", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetRenderTarget2", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetScissors", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetShaderConstantMode", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetStreamSource2", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetTexture2", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetTile", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetTransform", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetVertexShader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetVertexShaderConstant", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetVertexShaderDeclaration", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetVertexShaderFunction", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetVertexShaderInput", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetVertexShaderSize", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetVertexShaderType", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetViewport", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetViewportOffsetAndScale", {4432, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_GetVisibilityTestResult", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_InsertCallback", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_InsertFence", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_IsBusy", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_IsFencePending", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_KickOff", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_KickPushBuffer", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_LazySetStateVB", {5028, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_LazySetStateUP", {5028, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_LightEnable", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_LoadVertexShader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_LoadVertexShaderProgram", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_MakeSpace", {4134, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_PersistDisplay", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_Present", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_PrimeVertexCache", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_Release", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_Reset", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_RunPushBuffer", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_RunVertexStateShader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SelectVertexShader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SelectVertexShaderDirect", {4361, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetBackBufferScale", {4039, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetBackMaterial", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetDepthClipPlanes", {4432, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetFlickerFilter", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetGammaRamp", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetIndices", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetLight", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetMaterial", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetModelView", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetPalette", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetPixelShader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetPixelShaderConstant", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetPixelShaderProgram", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderStateNotInline", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_BackFillMode", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_CullMode", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_Deferred", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_DoNotCullUncompressed", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_Dxt1NoiseEnable", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_EdgeAntiAlias", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_FillMode", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_FogColor", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_FrontFace", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_LineWidth", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_LogicOp", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_MultiSampleAntiAlias", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_MultiSampleMask", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_MultiSampleMode", {3925, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_MultiSampleRenderTargetMode", {4034, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_NormalizeNormals", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_OcclusionCullEnable", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_PSTextureModes", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_RopZCmpAlwaysRead", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_RopZRead", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_SampleAlpha", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_ShadowFunc", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_Simple", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_StencilCullEnable", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_StencilEnable", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_StencilFail", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_TextureFactor", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_TwoSidedLighting", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_VertexBlend", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_YuvEnable", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_ZBias", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderState_ZEnable", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderTarget", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetRenderTargetFast", {5233, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetScissors", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetScreenSpaceOffset", {4034, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetShaderConstantMode", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetSoftDisplayFilter", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetStateUP", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetStateVB", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetStipple", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetStreamSource", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetSwapCallback", {4039, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetTexture", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetTextureState_BorderColor", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetTextureState_BumpEnv", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetTextureState_ColorKeyColor", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetTextureState_TexCoordIndex", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetTile", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetTransform", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_MultiplyTransform", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVertexData2f", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVertexData2s", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVertexData4f", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVertexData4s", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVertexData4ub", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVertexDataColor", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVertexShader", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVertexShaderConstant", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVertexShaderConstant1", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVertexShaderConstant1Fast", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVertexShaderConstant4", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVertexShaderConstantNotInline", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVertexShaderConstantNotInlineFast", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVertexShaderInput", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVertexShaderInputDirect", {4361, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetVerticalBlankCallback", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SetViewport", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_Swap", {4034, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_SwitchTexture", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DDevice_UpdateOverlay", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DPalette_Lock", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DPalette_Lock2", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DResource_AddRef", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DResource_BlockUntilNotBusy", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DResource_GetType", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DResource_IsBusy", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DResource_Register", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DResource_Release", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DSurface_GetDesc", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DSurface_LockRect", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DTexture_GetSurfaceLevel", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DTexture_GetSurfaceLevel2", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DTexture_LockRect", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DVertexBuffer_GetDesc", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DVertexBuffer_Lock", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DVertexBuffer_Lock2", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3DVolumeTexture_LockBox", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_AllocContiguousMemory", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_BlockOnResource", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_BlockOnTime", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_CMiniport_GetDisplayCapabilities", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_CheckDeviceFormat", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_ClearStateBlockFlags", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_CommonSetRenderTarget", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_CreateStandAloneSurface", {4034, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_EnumAdapterModes", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_GetAdapterDisplayMode", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_GetAdapterIdentifier", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_GetAdapterModeCount", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_GetDeviceCaps", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_KickOffAndWaitForIdle", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_LazySetPointParams", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_RecordStateBlock", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_SetCommonDebugRegisters", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_SetFence", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_SetPushBufferSize", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_SetTileNoWait", {4627, VER_MAX, VER_NONE, VER_NONE}},
    {"Direct3D_CheckDeviceMultiSampleType", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"Direct3D_CreateDevice", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"Get2DSurfaceDesc", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"Lock2DSurface", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"Lock3DSurface", {3911, VER_MAX, VER_NONE, VER_NONE}},
    {"D3D_MakeRequestedSpace", {4134, VER_MAX, VER_NONE, VER_NONE}},
    {"XMETAL_StartPush", {3911, 4034, VER_NONE, VER_NONE}},
    {"IDirect3DVertexBuffer8_Lock", {4627, VER_MAX, VER_NONE, VER_NONE}},
};

void getLibraryD3D8(const library_list **db_min, const library_list **db_full)
{
	*db_min = nullptr; //&database_min;
	*db_full = &database_full;
}
