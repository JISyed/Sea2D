//
//  FirstScene.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/7/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "FirstScene.hpp"
#include "engine/SceneSys/Entities/Entity.hpp"
#include "engine/SceneSys/Behaviors/EveryBehaviorInclude.hpp"

#include "engine/GraphicsSys/MeshRegistry.hpp"
#include "engine/GraphicsSys/ShaderRegistry.hpp"
#include "engine/GraphicsSys/TextureRegistry.hpp"
#include "engine/SpriteSys/SpriteRegistry.hpp"
#include "engine/SceneSys/Scenes/SceneRegistry.hpp"

#include "engine/AppSys/App.hpp"

namespace sea2d
{
    // VIRTUAL OVERRRIDE
    /// This is where you determine what Entites you want to load for this scene
    void FirstScene::OnLoad()
    {
        App::SetClearColor(Color(0.55f, 0.55f, 0.55f));
        
        Entity* firstEntity = Entity::Create("FirstEntity");
        Transform& firstTransform = firstEntity->GetTransform();
        firstTransform.SetPosition(Vector2(120.0f, -30.0f));
        firstTransform.SetScale(Vector2(120.0f, -120.0f));
        firstTransform.SetRotation(0.0f * MathConstants::Pi);
        
        TexturedMeshRenderer* firstRenderer = (TexturedMeshRenderer*) firstEntity->AddBehavior(BehaviorIdentity::TexturedMeshRenderer);
        firstRenderer->ChangeMesh(MeshRegistry::Find("Quad"));
        firstRenderer->ChangeShader(ShaderRegistry::Find("Standard"));
        firstRenderer->ChangeTexture(TextureRegistry::Find("AppIcon"));
        firstRenderer->SetTintColor(Color::White);
        
        
        Entity* spriteEntity = Entity::Create("SpriteTest");
        Transform& spriteTransform = spriteEntity->GetTransform();
        spriteTransform.SetPosition(Vector2(0.0f, 0.0f));
        spriteTransform.SetScale(Vector2(1.0f, 1.0f));
        spriteTransform.SetRotation(0.0f * MathConstants::Pi);
        
        SpriteRenderer* firstSpriteRenderer = (SpriteRenderer*) spriteEntity->AddBehavior(BehaviorIdentity::SpriteRenderer);
        firstSpriteRenderer->SetTintColor(Color::White);
        firstSpriteRenderer->ChangeSprite(SpriteRegistry::Find("fish_swimming"));
        firstSpriteRenderer->ChangePlaybackSpeed(1.0f);

        
        Entity* secondEntity = Entity::Create("SecondEntity");
        Transform& secondTransform = secondEntity->GetTransform();
        secondTransform.SetPosition(Vector2(60.0f, 120.0f));
        secondTransform.SetScale(Vector2(90.0f, 60.0f));
        secondTransform.SetRotation(0.75f * MathConstants::Pi);
        secondEntity->AddBehavior(BehaviorIdentity::TexturedMeshRenderer);
        
        
        Entity* thirdEntity = Entity::Create("ThirdEntity");
        Transform& thirdTransform = thirdEntity->GetTransform();
        thirdTransform.SetPosition(Vector2(-130.0f, 0.0f));
        thirdTransform.SetScale(Vector2(90.0f, 90.0f));
        thirdTransform.SetRotation(0.0f * MathConstants::Pi);
        ConstantRotation* orbitRotation = (ConstantRotation*) thirdEntity->AddBehavior(BehaviorIdentity::ConstantRotation);
        orbitRotation->SetRotationSpeed(2.0f);
        thirdEntity->AddBehavior(BehaviorIdentity::TexturedMeshRenderer);
        
        
        Entity* fourthEntity = Entity::Create(thirdEntity, "FourthEntity");
        Transform& fourthTransform = fourthEntity->GetTransform();
        fourthTransform.SetPosition(Vector2(150.0f, 0.0f));
        fourthTransform.SetScale(Vector2(0.006f, 0.006f));
        fourthTransform.SetRotation(1.0f * MathConstants::Pi);
        ConstantRotation* fourthRotator = (ConstantRotation*) fourthEntity->AddBehavior(BehaviorIdentity::ConstantRotation);
        fourthRotator->SetRotationSpeed(1.0f * MathConstants::Pi);
        SpriteRenderer* fourthSpriteRenderer = (SpriteRenderer*) fourthEntity->AddBehavior(BehaviorIdentity::SpriteRenderer);
        fourthSpriteRenderer->ChangeSprite(SpriteRegistry::Find("green_alien_walk"));
        
        Entity* fifthEntity = Entity::Create(fourthEntity, "FifthEntity");
        Transform& fifthTransform = fifthEntity->GetTransform();
        fifthTransform.SetPosition(Vector2(70.0f, 0.0f));
        fifthTransform.SetScale(Vector2(60.0f, 60.0f));
        fifthTransform.SetRotation(0.0f * MathConstants::Pi);
        ConstantRotation* fifthRotator = (ConstantRotation*) fifthEntity->AddBehavior(BehaviorIdentity::ConstantRotation);
        fifthRotator->SetRotationSpeed(-4.0f * MathConstants::Pi);
        TexturedMeshRenderer* fifthRenderer = (TexturedMeshRenderer*) fifthEntity->AddBehavior(BehaviorIdentity::TexturedMeshRenderer);
        fifthRenderer->SetTintColor(Color::Purple);
        
        
        Entity* firstCameraEnt = Entity::Create("FirstCam");
        Transform& firstCamTransform = firstCameraEnt->GetTransform();
        firstCamTransform.SetPosition(Vector2(0.0f, 0.0f));
        firstCamTransform.SetRotation(0.0f*MathConstants::Pi);
        CameraBehavior* firstCamera = (CameraBehavior*) firstCameraEnt->AddBehavior(BehaviorIdentity::CameraBehavior);
        firstCamera->SetActive(true);
        
        
        Entity* secondCameraEnt = Entity::Create("SecondCam");
        Transform& secondCamTransform = secondCameraEnt->GetTransform();
        secondCamTransform.SetPosition(Vector2(0.0f, 0.0f));
        secondCamTransform.SetRotation(-0.6f*MathConstants::Pi);
        CameraBehavior* secondCamera = (CameraBehavior*) secondCameraEnt->AddBehavior(BehaviorIdentity::CameraBehavior);
        secondCamera->SetProjection(App::GetWindowWidth(), App::GetWindowHeight());
        secondCamera->SetViewport(0, 0, (int) (App::GetWindowWidth() / 2.0f), (int) (App::GetWindowHeight() / 2.0f));
        secondCamera->SetActive(true);
        ConstantRotation* secondCamRotator = (ConstantRotation*) secondCameraEnt->AddBehavior(BehaviorIdentity::ConstantRotation);
        secondCamRotator->SetRotationSpeed(0.3f * MathConstants::Pi);
        
        
        Entity* sceneSwitcherEnt = Entity::Create("SceneSwitcher");
        KeyTriggerSceneSwitcher* sceneSwitcher = (KeyTriggerSceneSwitcher*) sceneSwitcherEnt->AddBehavior(BehaviorIdentity::KeyTriggerSceneSwitcher);
        sceneSwitcher->ChangeTriggerKey(Input::Key::Backspace);
        sceneSwitcher->SetScene(SceneRegistry::Find("SpriteDemoScene"));
        
    }
}