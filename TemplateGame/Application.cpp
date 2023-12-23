#include "Application.h"
#include "Actors/StaticMeshActor.h"
#include "Rendering/Assets/Mesh.h"
#include "Core/World.h"
#include "Rendering/Utils/ShaderUtils.h"
#include "Utils/FileUtils.h"
#include "Rendering/RHI/RHI.h"

void Application::Begin()
{
    Actor::Begin();

    ActorSpawnParams Params;
    StaticMeshActor* SMActor = GetWorld()->SpawnActor<StaticMeshActor>(Params);

    std::string VertexShaderSource;
    ShaderUtils::LoadShaderContents(FileUtils::GetContentDirectory() + "Engine/Shaders/SimpleVertex.shader", VertexShaderSource);
    
    std::string PixelShaderSource;
    ShaderUtils::LoadShaderContents(FileUtils::GetContentDirectory() + "Engine/Shaders/SimpleFragment.shader", PixelShaderSource);
    
    RHIVertexShader* VertexShader = RHICreateVertexShader(VertexShaderSource);
    RHIPixelShader* PixelShader = RHICreatePixelShader(PixelShaderSource);
    RHIShaderProgram* Program = RHICreateShaderProgram(VertexShader, PixelShader);
    RHIUseShaderProgram(Program);
    
    Mesh* Quad = Mesh::CreateQuad();
    SMActor->GetStaticMeshComponent()->SetMesh(Quad);
}
