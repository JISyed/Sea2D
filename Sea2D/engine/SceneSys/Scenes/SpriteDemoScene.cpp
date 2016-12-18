//
//  SpriteDemoScene.cpp
//  Sea2D
//
//  Created by Jibran Syed on 5/23/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "SpriteDemoScene.hpp"
#include "engine/SceneSys/Entities/Entity.hpp"
#include "engine/SceneSys/Behaviors/EveryBehaviorInclude.hpp"

#include "engine/GraphicsSys/MeshRegistry.hpp"
#include "engine/GraphicsSys/ShaderRegistry.hpp"
#include "engine/GraphicsSys/TextureRegistry.hpp"
#include "engine/SpriteSys/SpriteRegistry.hpp"
#include "engine/SceneSys/Scenes/SceneRegistry.hpp"
#include "engine/SpriteSys/BitmapFontRegistry.hpp"

#include "engine/AppSys/App.hpp"

namespace sea2d
{
    // VIRTUAL OVERRRIDE
    /// This is where you determine what Entites you want to load for this scene
    void SpriteDemoScene::OnLoad()
    {
        App::SetClearColor(Color(0.66f, 0.93f, 0.97f));
        
        
        {
            Entity* alienWalk = Entity::Create("AlienWalk");
            Transform& spriteTransform = alienWalk->GetTransform();
            spriteTransform.SetPosition(Vector2(0.0f, -58.0f));
            spriteTransform.SetScale(Vector2(1.0f, 1.0f));
            spriteTransform.SetRotation(0.0f * MathConstants::Pi);
            SpriteRenderer* alienWalkRenderer = (SpriteRenderer*) alienWalk->AddBehavior(BehaviorIdentity::SpriteRenderer);
            alienWalkRenderer->ChangeSprite(SpriteRegistry::Find("green_alien_walk"));
            alienWalkRenderer->ChangePlaybackSpeed(1.0f);
        }
        
        
        {
            Entity* entity = Entity::Create("SlimeWalk");
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(170.0f, -93.0f));
            transform.SetScale(Vector2(1.0f, 1.0f));
            transform.SetRotation(0.0f * MathConstants::Pi);
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("slime_walking"));
            spriteRenderer->ChangePlaybackSpeed(1.0f);
        }
        
        
        {
            Entity* entity = Entity::Create("SnailWalk");
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(-200.0f, -90.0f));
            transform.SetScale(Vector2(-1.0f, 1.0f));
            transform.SetRotation(0.0f * MathConstants::Pi);
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("snail_walking"));
            spriteRenderer->ChangePlaybackSpeed(1.0f);
        }
        
        
        {
            Entity* entity = Entity::Create("Fly1");
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(200.0f, 90.0f));
            transform.SetScale(Vector2(1.0f, 1.0f));
            transform.SetRotation(0.5f * MathConstants::EighthPi);
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("fly_flying"));
            spriteRenderer->ChangePlaybackSpeed(1.0f);
        }
        
        {
            Entity* entity = Entity::Create("Fly2");
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(150.0f, 140.0f));
            transform.SetScale(Vector2(1.0f, 1.0f));
            transform.SetRotation(0.0f * MathConstants::EighthPi);
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("fly_flying"));
            spriteRenderer->ChangePlaybackSpeed(1.0f);
        }
        
        {
            Entity* entity = Entity::Create("Fish");
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(100.0f, -210.0f));
            transform.SetScale(Vector2(1.0f, 1.0f));
            transform.SetRotation(0.0f * MathConstants::EighthPi);
            transform.SetDepth(1.0f);
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("fish_swimming"));
            spriteRenderer->ChangePlaybackSpeed(1.0f);
        }
        
        
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(0.0f, -140.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_grass_half"));
        }
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(70.0f, -140.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_grass_half"));
        }
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(140.0f, -140.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_grass_half"));
        }
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(210.0f, -140.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_grass_half_right"));
        }
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(-70.0f, -140.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_grass_half"));
        }
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(-140.0f, -140.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_grass_half"));
        }
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(-210.0f, -140.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_grass_half_left"));
        }
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(70.0f, -70.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_plant_green"));
        }
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(-140.0f, -70.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_mushroom_red"));
        }
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(0.0f, -210.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_water_top"));
        }
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(70.0f, -210.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_water_top"));
        }
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(140.0f, -210.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_water_top"));
        }
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(210.0f, -210.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_water_top"));
        }
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(280.0f, -210.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_water_top"));
        }
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(350.0f, -210.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_water_top"));
        }
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(-70.0f, -210.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_water_top"));
        }
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(-140.0f, -210.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_water_top"));
        }
        
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(-210.0f, -210.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_water_top"));
        }
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(-280.0f, -210.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_water_top"));
        }
        {
            Entity* entity = Entity::Create();
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(-350.0f, -210.0f));
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("tile_water_top"));
        }
        
        
        
        Entity* firstCameraEnt = Entity::Create("FirstCam");
        Transform& firstCamTransform = firstCameraEnt->GetTransform();
        firstCamTransform.SetPosition(Vector2(0.0f, 0.0f));
        firstCamTransform.SetRotation(0.0f*MathConstants::Pi);
        CameraBehavior* firstCamera = (CameraBehavior*) firstCameraEnt->AddBehavior(BehaviorIdentity::CameraBehavior);
        firstCamera->SetActive(true);
        KeyTriggeredMovement* cameraMover = (KeyTriggeredMovement*) firstCameraEnt->AddBehavior(BehaviorIdentity::KeyTriggeredMovement);
        cameraMover->SetMovementSpeed(100.0f);
        cameraMover->SetInvertControls(true);
        
        
        Entity* sceneSwitcherEnt = Entity::Create("SceneSwitcher");
        KeyTriggerSceneSwitcher* sceneSwitcher = (KeyTriggerSceneSwitcher*) sceneSwitcherEnt->AddBehavior(BehaviorIdentity::KeyTriggerSceneSwitcher);
        sceneSwitcher->ChangeTriggerKey(Input::Key::Backspace);
        sceneSwitcher->SetScene(SceneRegistry::Find("FirstScene"));
        
        
        
        {
            Entity* entity = Entity::Create(firstCameraEnt, "HudPlayerIcon");
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(-280.0f, 200.0f));
            transform.SetScale(Vector2(1.0f, 1.0f));
            transform.SetRotation(0.0f * MathConstants::EighthPi);
            transform.SetDepth(10.0f);
            SpriteRenderer* spriteRenderer = (SpriteRenderer*) entity->AddBehavior(BehaviorIdentity::SpriteRenderer);
            spriteRenderer->ChangeSprite(SpriteRegistry::Find("ky_hud_p1"));
            
            // HACK: HUD object not moving with camera for some reason
            KeyTriggeredMovement* entityMover = (KeyTriggeredMovement*) entity->AddBehavior(BehaviorIdentity::KeyTriggeredMovement);
            entityMover->SetMovementSpeed(cameraMover->GetMovementSpeed() * 2.0f);
        }
        
        
        {
            Entity* entity = Entity::Create(firstCameraEnt, "HudText");
            Transform& transform = entity->GetTransform();
            transform.SetPosition(Vector2(-250.0f, 200.0f));
            //transform.SetPosition(Vector2(-10.0f, 0.0f));
            //transform.SetScale(Vector2(60.0f, 60.0f));
            transform.SetScale(Vector2(1.0f, 1.0f));
            transform.SetRotation(0.0f * MathConstants::EighthPi);
            transform.SetDepth(10.0f);
            BitmapText* text = (BitmapText*) entity->AddBehavior(BehaviorIdentity::BitmapText);
            text->ChangeBitmapFont(BitmapFontRegistry::Find(1));
            text->SetTintColor(Color(1.0f, 1.0f, 1.0f));
            text->ChangeText("Testing Bitmap Font System! 123");
            
            // HACK: HUD object not moving with camera for some reason
            KeyTriggeredMovement* entityMover = (KeyTriggeredMovement*) entity->AddBehavior(BehaviorIdentity::KeyTriggeredMovement);
            entityMover->SetMovementSpeed(cameraMover->GetMovementSpeed() * 2.0f);
        }
        
    }
}